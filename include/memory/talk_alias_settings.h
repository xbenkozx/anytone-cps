#ifndef ANYTONE_TALK_ALIAS_SETTINGS_H
#define ANYTONE_TALK_ALIAS_SETTINGS_H

#include <QByteArray>
#include <QString>
#include <QDebug>
#include <QDataStream>

namespace Anytone {
    class TalkAliasSettings {
    public:
        TalkAliasSettings(){}
        ~TalkAliasSettings(){}

        void save(QDataStream &ds);
        void load(QDataStream &ds);

        uint8_t display_priority = 0;
        uint8_t data_format = 0;
    };
}

#endif