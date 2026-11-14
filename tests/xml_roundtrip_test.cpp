// Checks that every setting survives saving to .atd (XML) and loading again.
//
// Per seed and radio model: fill an in-memory radio image with random printable bytes, read it
// into the Memory (like a read from the radio), encode it back into image A (what would be
// written to the radio), save the Memory to XML, re-initialise the Memory, load the XML and
// encode again into image B. A and B must be identical: every difference is a value that
// the .atd file loses (attribute name typo on load, a field that is saved but never read, ...).
//
// Usage: xml-roundtrip-test [seeds]      Build: -DANYTONE_BUILD_TESTS=ON, target xml-roundtrip-test
#include <QCoreApplication>
#include <QBuffer>
#include <QFile>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include <QDebug>
#include <map>
#include <random>
#include "device.h"

using namespace Anytone;

class MemDevice : public Device {
public:
    QByteArray image = QByteArray(0x8000000, char(0xff));
    QByteArray readMemoryAddress(int a, int l) override { return image.mid(a, l); }
    void writeMemoryAddress(int a, QByteArray d) override { image.replace(a, d.size(), d); }
    std::vector<QString> readDeviceInfo() override { return {QString("ID878UV2"), QString("V101")}; }
};

static QByteArray saveAtd(){
    QByteArray out;
    QBuffer buf(&out);
    buf.open(QIODevice::WriteOnly);
    QXmlStreamWriter w(&buf);
    w.setAutoFormatting(true);
    Memory::saveData(w);
    return out;
}

int main(int argc, char **argv){
    QCoreApplication app(argc, argv);
    if(argc > 1 && QString(argv[1]).endsWith(".atd")){
        // show the APRS texts a codeplug file really loads (they used to come back empty)
        Memory::radio_model = RadioModel::D878UVII_FW400;
        Memory::init();
        Memory::initDigitalContacts();
        QFile f(argv[1]);
        if(!f.open(QIODevice::ReadOnly)){ qCritical() << "cannot open" << argv[1]; return 2; }
        QXmlStreamReader xml(&f);
        Memory::loadData(xml);
        auto *a = Memory::aprs_settings;
        qInfo().noquote() << "to_call:" << a->to_call << "ssid" << a->to_call_ssid << "| your_call:" << a->your_call << "ssid" << a->your_call_ssid
                          << "| path:" << a->digipeater_path << "| sending_text:" << a->sending_text << "| fix_1_lat:" << a->fix_1_lat;
        return 0;
    }
    const int seeds = argc > 1 ? QString(argv[1]).toInt() : 12;
    int failures = 0;
    std::map<QString, std::map<int, int>> lost;   // model -> offset -> seeds that lost it
    const std::pair<RadioModel, QString> models[] = {
        {RadioModel::D878UVII_FW400, "D878UVII"}, {RadioModel::D890UV_FW103, "D890UV"}};
    for(const auto &[model, name] : models){
        for(int seed = 1; seed <= seeds; seed++){
            std::mt19937 rng(seed * 7919u);
            MemDevice src;
            for(int i = 0; i < src.image.size(); i++){
                // printable ASCII keeps strings XML-safe; most numeric fields become non-zero
                src.image[i] = char(0x30 + rng() % 0x4a);
            }
            Memory::radio_model = model;
            Memory::init();
            src.readOtherData();
            Memory::linkReferences();

            MemDevice a;
            a.writeOtherData();
            const QByteArray xml_bytes = saveAtd();

            Memory::radio_model = model;
            Memory::init();
            QXmlStreamReader xml(xml_bytes);
            Memory::loadData(xml);
            Memory::radio_model = model;
            Memory::linkReferences();

            MemDevice b;
            b.writeOtherData();

            const int n = std::min(a.image.size(), b.image.size());
            int diff = 0;
            for(int i = 0; i < n; i++){
                if(a.image[i] != b.image[i]){ lost[name][i]++; diff++; }
            }
            if(diff) failures++;
            if(diff && seed == 1 && qEnvironmentVariableIsSet("XR_DEBUG")){
                for(int i = 0; i < n; i++) if(a.image[i] != b.image[i]){
                    qInfo().noquote() << name << QString("first diff 0x%1").arg(i, 0, 16)
                        << "before:" << a.image.mid(i - i % 16, 32).toHex(' ') << "after:" << b.image.mid(i - i % 16, 32).toHex(' ');
                    break;
                }
            }
        }
    }
    for(const auto &[name, offsets] : lost){
        qInfo().noquote() << name << ": bytes lost through the .atd file:" << int(offsets.size());
        // group neighbouring offsets
        int start = -1, prev = -2;
        for(const auto &[off, cnt] : offsets){
            if(off != prev + 1){
                if(start >= 0) qInfo().noquote() << QString("   0x%1-0x%2").arg(start, 0, 16).arg(prev, 0, 16);
                start = off;
            }
            prev = off;
        }
        if(start >= 0) qInfo().noquote() << QString("   0x%1-0x%2").arg(start, 0, 16).arg(prev, 0, 16);
    }
    qInfo() << "seeds with differences:" << failures << "of" << seeds * 2;
    return failures == 0 ? 0 : 1;
}
