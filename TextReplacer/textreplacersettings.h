#ifndef TEXTREPLACERSETTINGS_H
#define TEXTREPLACERSETTINGS_H


#include "mainsettings.h"
#include "QVector"

class TextReplacerSettings: public MainSettings
{
    QVector<QString> replaceWhat;
    QVector<QString> replaceWithWhat;

    bool beginNextGroup(int);
    void addNextReplacementPair();
    void endGroup();

    bool currentGroupIsInvalid();
public:
    TextReplacerSettings();

    int getPairsAmount();

    QString getReplaceWhat(int);
    QString getReplaceWithWhat(int);
};

#endif // TEXTREPLACERSETTINGS_H
