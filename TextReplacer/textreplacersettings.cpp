#include "textreplacersettings.h"


TextReplacerSettings::TextReplacerSettings(){
    int groupNumber = 0;

    while(beginNextGroup(groupNumber)){
        addNextReplacementPair();
        endGroup();
        groupNumber++;
    }
}


bool TextReplacerSettings::beginNextGroup(int groupNumber){
    QString groupName = QString("Replacement%1").arg(groupNumber);
    settings->beginGroup(groupName);

    if(currentGroupIsInvalid()){
        settings->endGroup();
        return false;
    }
    else{
        return true;
    }
}


bool TextReplacerSettings::currentGroupIsInvalid(){
    bool replaceWhatSectionExists = settings->contains("replaceWhat");
    bool replaceWithWhatSectionExists = settings->contains("replaceWithWhat");

    return !(replaceWhatSectionExists && replaceWithWhatSectionExists);
}


void TextReplacerSettings::addNextReplacementPair(){
    QString toReplace = settings->value("replaceWhat", "").toString();
    replaceWhat.append(toReplace);

    QString replaceBy = settings->value("replaceWithWhat", "").toString();
    replaceWithWhat.append(replaceBy);
}


void TextReplacerSettings::endGroup(){
    settings->endGroup();
}


int TextReplacerSettings::getPairsAmount(){
    return replaceWhat.length();
}


QString TextReplacerSettings::getReplaceWhat(int index){
    return replaceWhat[index];
}


QString TextReplacerSettings::getReplaceWithWhat(int index){
    return replaceWithWhat[index];
}
