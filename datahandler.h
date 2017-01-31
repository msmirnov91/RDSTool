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
    void createRecodedXML();
    void uploadFileViaFtp();

    bool translationIsNecessary();

private:
    Settings *settings;

    QFile *inputXML;
    QFile *recodedXML;

    void tryToOpenFile(QFile*, QIODevice::OpenMode);
    QString getFirstTagContent(QString);
    bool hasRussianLetters(QString);
    QString translateString(QString);
    void writeStringToFile(QString, QString);

    QXmlStreamReader *reader;
    QXmlStreamWriter *writer;
    void openReaderStream();
    void closeReaderStream();
    void writeRecodedXmlBeginning();
    void writeRecodedXmlContent();

    typedef std::map<QChar, QString> TranslateMap;
    TranslateMap tMap;

    QString name;
    QString artist;
    QString createRdsFileContent();
    void createRdsFile();

    QString metaName;
    QString metaArtist;
    QString createMetaFileContent();
    void createMetaFile();

    QUrl createUploadUrl();
    void doSynchronousUpload(QFile*, QUrl);
};

#endif // DATATRANSLATOR_H
