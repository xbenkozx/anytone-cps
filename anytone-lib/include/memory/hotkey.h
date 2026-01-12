#ifndef ANYTONE_HOTKEY_H
#define ANYTONE_HOTKEY_H

#include <QString>
#include <QVector>
#include <QDebug>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>

namespace Anytone {
    class Talkgroup;
    class HotkeyKey {
    public:
        QString name;
        uint8_t mode = 1;
        uint8_t menu = 0;
        uint8_t call_type = 0xff;
        uint32_t call_obj = 0xffffffff;
        uint8_t digi_call_type = 0xff;
        uint8_t content = 0;
        Talkgroup *talkgroup;
    };

    class AnalogQuickCall {
    public:
        uint8_t operation_type = 0;
        uint8_t call_id = 0xff;
    };

    class Hotkey {
    public:
        Hotkey();
        ~Hotkey(){}

        void save(QXmlStreamWriter &xml);
        void load(QXmlStreamReader &xml);

        QVector<AnalogQuickCall*> quick_call_list;
        QVector<QString> state_content_list;
        QVector<HotkeyKey*> key_list;

        QStringList function_key_name = {
            "Hot Key 1", "Hot Key 2", "Hot Key 3", "Hot Key 4", "Hot Key 5", "Hot Key 6", "Func Key+0", "Func Key+1",
            "Func Key+2", "Func Key+3", "Func Key+4", "Func Key+5", "Func Key+6", "Func Key+7", "Func Key+8", "Func Key+9",
            "Func Key+*", "Func Key+#"
        };
    };
}
#endif