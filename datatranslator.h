#ifndef DATATRANSLATOR_H
#define DATATRANSLATOR_H

#include "QString"
#include "settings.h"
#include <map>

/**
 * @brief The DataTranslator class
 * Class that makes all needed manipulations with data
 */
class DataTranslator{
public:
    DataTranslator(Settings*);

    void readData(); /// read data from gin XML
    void translate(); /// translates data. must be called after readData()
    void writeData(); /// makes translated file with needed data
    void makeRecodedXML(); /// makes XML in win1251

    bool translationIsNecessary(); /// checks name and artist for russian letters

private:
    Settings *settings;

    QString name; /// name of song in XML
    QString artist; /// name of artist in XML

    QString metaName; /// name for meta file
    QString metaArtist; /// artist for meta file

    typedef std::map<QChar, QString> TranslateMap;
    TranslateMap tMap; /// map used to translate letters

    bool hasRussianLetters(QString); /// detrmines if given string contains russian letters
    QString translateString(QString); /// translates given string from russian to english
    void writeFile(QString, QString); /// writes string to file with given name
};

#endif // DATATRANSLATOR_H
