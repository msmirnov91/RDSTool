#ifndef TEXTREPLACER_H
#define TEXTREPLACER_H


#include "textreplacer.h"
#include "textreplacersettings.h"

class TextReplacer
{
    TextReplacerSettings *settings;

public:
    TextReplacer();
    ~TextReplacer();

    QString replaceAllOccurancesIn(QString);
};

#endif // TEXTREPLACER_H
