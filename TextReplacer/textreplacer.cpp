#include "textreplacer.h"
#include "QDebug"


TextReplacer::TextReplacer(){
    qDebug() << "initialize TextReplacer";
    settings = new TextReplacerSettings();
}


TextReplacer::~TextReplacer(){
    delete settings;
}


QString TextReplacer::replaceAllOccurancesIn(QString string){
    int amountOfReplacementPairs = settings->getPairsAmount();

    if(amountOfReplacementPairs == 0){
        return string;
    }

    for (int i = 0; i < amountOfReplacementPairs; i++){
        QString what = settings->getReplaceWhat(i);
        QString withWhat = settings->getReplaceWithWhat(i);

        qDebug() << "Replacing...";
        string.replace(what, withWhat);
    }

    return string;
}
