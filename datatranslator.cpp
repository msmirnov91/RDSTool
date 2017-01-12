#include "datatranslator.h"
#include "xmlhandler.h"
#include "QXmlStreamReader"
#include "QXmlStreamWriter"
#include "QFile"
#include "QByteArray"
#include "QTextStream"
#include <exception>


/**
 * @brief DataTranslator::DataTranslator
 * @param set - program settings
 */
DataTranslator::DataTranslator(Settings *set){
    this->settings = set;

    // initialize names and artists with empty string
    this->name = "";
    this->metaName = "";
    this->artist = "";
    this->metaArtist = "";

    // initialize translation map
    this->tMap[L'а'] = "a";
    this->tMap[L'б'] = "b";
    this->tMap[L'в'] = "v";
    this->tMap[L'г'] = "g";
    this->tMap[L'д'] = "d";
    this->tMap[L'е'] = "e";
    this->tMap[L'ё'] = "yo";
    this->tMap[L'ж'] = "zh";
    this->tMap[L'з'] = "z";
    this->tMap[L'и'] = "i";
    this->tMap[L'й'] = "y";
    this->tMap[L'к'] = "k";
    this->tMap[L'л'] = "l";
    this->tMap[L'м'] = "m";
    this->tMap[L'н'] = "n";
    this->tMap[L'о'] = "o";
    this->tMap[L'п'] = "p";
    this->tMap[L'р'] = "r";
    this->tMap[L'с'] = "s";
    this->tMap[L'т'] = "t";
    this->tMap[L'у'] = "u";
    this->tMap[L'ф'] = "f";
    this->tMap[L'х'] = "h";
    this->tMap[L'ц'] = "ts";
    this->tMap[L'ч'] = "ch";
    this->tMap[L'ш'] = "sh";
    this->tMap[L'щ'] = "sh'";
    this->tMap[L'ь'] = "'";
    this->tMap[L'ы'] = "i";
    this->tMap[L'ъ'] = "";
    this->tMap[L'э'] = "e";
    this->tMap[L'ю'] = "yu";
    this->tMap[L'я'] = "ya";

    this->tMap[L'А'] = "A";
    this->tMap[L'Б'] = "B";
    this->tMap[L'В'] = "V";
    this->tMap[L'Г'] = "G";
    this->tMap[L'Д'] = "D";
    this->tMap[L'Е'] = "E";
    this->tMap[L'Ё'] = "YO";
    this->tMap[L'Ж'] = "ZH";
    this->tMap[L'З'] = "Z";
    this->tMap[L'И'] = "I";
    this->tMap[L'Й'] = "Y";
    this->tMap[L'К'] = "K";
    this->tMap[L'Л'] = "L";
    this->tMap[L'М'] = "M";
    this->tMap[L'Н'] = "N";
    this->tMap[L'О'] = "O";
    this->tMap[L'П'] = "P";
    this->tMap[L'Р'] = "R";
    this->tMap[L'С'] = "S";
    this->tMap[L'Т'] = "T";
    this->tMap[L'У'] = "U";
    this->tMap[L'Ф'] = "F";
    this->tMap[L'Х'] = "H";
    this->tMap[L'Ц'] = "TS";
    this->tMap[L'Ч'] = "CH";
    this->tMap[L'Ш'] = "SH";
    this->tMap[L'Щ'] = "SH'";
    this->tMap[L'Ь'] = "'";
    this->tMap[L'Ы'] = "I";
    this->tMap[L'Ъ'] = "";
    this->tMap[L'Э'] = "E";
    this->tMap[L'Ю'] = "YU";
    this->tMap[L'Я'] = "YA";
}


/**
 * @brief DataTranslator::readData
 * reads name and artist from XML file
 */
void DataTranslator::readData(){
    XMLHandler handler(this->settings);

    this->name = handler.getFirstTagContent("NAME");
    this->metaName =  this->name;

    this->artist = handler.getFirstTagContent("ARTIST");
    this->metaArtist = this->artist;

}


/**
 * @brief DataTranslator::translate
 * translates name and artist
 */
void DataTranslator::translate(){
    this->name = this->translateString(this->name);
    this->artist = this->translateString(this->artist);
}


/**
 * @brief DataTranslator::writeData
 * writes name and artist in output file.
 */
void DataTranslator::writeData(){
    // write data
    QString data = this->artist + " " + this->settings->getSeparator()
                                + " " + this->name;
    this->writeFile(this->settings->getOutputFileName(), data);

    // write metadata
    QString metaData = this->metaArtist + " " + this->settings->getMetaSeparator()
                                        + " " + this->metaName;
    this->writeFile(this->settings->getMetaFileName(), metaData);

    XMLHandler handler(this->settings);
    handler.makeRecodedXml("Windows-1251");
}


/**
 * @brief DataTranslator::translationIsNecessary
 * @return true, if name or artist has russian letters,
 */
bool DataTranslator::translationIsNecessary(){
    bool nameHasRussianLetters = this->hasRussianLetters(this->name);
    bool artistHasRussianLetters = this->hasRussianLetters(this->artist);
    return nameHasRussianLetters || artistHasRussianLetters;
}


/**
 * @brief DataTranslator::hasRussianLetters
 * @param str - string that must be checked
 * @return true, if str has russian letters
 */
bool DataTranslator::hasRussianLetters(QString str){
    bool result = false;
    for (int i = 0; i < str.size(); i++){
        if (this->tMap.find(str[i]) != this->tMap.end()) {
            result = true;
            break;
        }
    }
    return result;
}


/**
 * @brief DataTranslator::translateString
 * @param str string that must be translated
 * @return translated string
 */
QString DataTranslator::translateString(QString str){
    QString result = "";
    TranslateMap::iterator it;
    for (int i = 0; i < str.size(); i++){
       it = this->tMap.find(str[i]);
       if (it != this->tMap.end()) {
           result += it->second;
       }
       else{
           result += str[i];
       }
    }
    return result;
}


/**
 * @brief DataTranslator::writeFile
 * writes given string to file with given name
 * @param fileName name of file to write
 * @param toWrite string that must be written
 */
void DataTranslator::writeFile(QString fileName, QString toWrite){
    QFile outputFile(fileName);
    if (!outputFile.open(QIODevice::WriteOnly)){
        std::string which = fileName.toStdString();
        throw this->settings->getPrefix() + " Cant open output file " + which + "!";
    }
    QTextStream out(&outputFile);
    out << toWrite;
    outputFile.close();
}


/**
 * @brief DataTranslator::makeRecodedXML
 * reads data form input xml and immidiatly write it
 * to new XML in windows-1251
 */
void DataTranslator::makeRecodedXML(){

}
