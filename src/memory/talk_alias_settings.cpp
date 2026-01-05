#include "talk_alias_settings.h"

void Anytone::TalkAliasSettings::save(QDataStream &ds){
    ds << display_priority;
    ds << data_format;
}
void Anytone::TalkAliasSettings::load(QDataStream &ds){
    ds >> display_priority;
    ds >> data_format;
}