#include "memory/talkgroup.h"

#include "utils.h"
#include "int.h"

using namespace Anytone;

Talkgroup::Talkgroup(){}
void Talkgroup::decode(QByteArray data){
    call_type = static_cast<int>(data.at(0));
    name = QString(data.mid(0x1, 0x10));
    call_alert= static_cast<int>(data.at(0x22));
    dmr_id = QString(data.mid(0x23, 0x4).toHex()).toInt();

    name.remove(QChar('\0'));
}
QByteArray Talkgroup::encode(){
    QByteArray data(0x64, 0);
    auto* bytes = reinterpret_cast<std::uint8_t*>(data.data());

    data[0] = call_type;
    data.replace(1, 0x10, 
        name.toUtf8().leftJustified(16, '\0')
    );
    data[0x22] = call_alert;
    data.replace(0x23, 4, 
        QByteArray::fromHex(QString::number(dmr_id).rightJustified(8, '0').toUtf8())
    );
    return data;
}