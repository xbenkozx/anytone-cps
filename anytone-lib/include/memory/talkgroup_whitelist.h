#ifndef TALKGROUP_WHITELIST_H
#define TALKGROUP_WHITELIST_H

#include <QByteArray>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>

namespace Anytone {
    class TalkgroupWhitelist {
    public:
        TalkgroupWhitelist(){}
        ~TalkgroupWhitelist(){}

        void save(QXmlStreamWriter &xml);
        void load(QXmlStreamReader &xml);

        int index = 0;
        int dmr_id = 0;
        int call_type = 1;
    };
}

#endif