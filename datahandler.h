#ifndef DATATRANSLATOR_H
#define DATATRANSLATOR_H

#include "QString"
#include "QFile"
#include "QXmlStreamReader"
#include "QXmlStreamWriter"
#include "settings.h"
#include <map>


class DataHandler{
public:
    DataHandler(Settings*);

    void readInputData();
    void translate();
    void createOutputFiles();
    void createRecodedXML(const char *);
    void uploadFileViaFtp();

    bool translationIsNecessary();

private:
    Settings *settings;

    QFile *inputXML;
    QFile *recodedXML;

    QXmlStreamReader *reader;
    QXmlStreamWriter *writer;

    QString name;
    QString artist;

    QString metaName;
    QString metaArtist;

    typedef std::map<QChar, QString> TranslateMap;
    TranslateMap tMap;

    bool hasRussianLetters(QString);
    QString translateString(QString);
    void writeStringToFile(QString, QString);

    void openReaderStream();
    void closeReaderStream();
    QString getFirstTagContent(QString);
};

#endif // DATATRANSLATOR_H
