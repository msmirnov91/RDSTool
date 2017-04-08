#ifndef TRANSLATOR_H
#define TRANSLATOR_H


#include "QString"
#include <map>

class Translator
{
    typedef std::map<QChar, QString> TranslateMap;
    TranslateMap tMap;

    bool hasRussianLetters(QString);
    QString translateString(QString);

public:
    Translator();
    QString translate(QString);
};

#endif // TRANSLATOR_H
