#ifndef FILEMAKER_H
#define FILEMAKER_H

#include "filemakersettings.h"
#include "QString"
#include "QFile"
#include "QXmlStreamReader"
#include "QXmlStreamWriter"

class FileMaker
{
    FileMakerSettings *settings;

    QString name;
    QString artist;
    QString metaName;
    QString metaArtist;

    QFile *inputXML;
    QFile *recodedXML;

    QXmlStreamReader *reader;
    QXmlStreamWriter *writer;

    void tryToOpenFile(QFile*, QIODevice::OpenMode);
    QString getFirstTagContent(QString);

    void writeStringToFile(QString, QString);

    void openReaderStream();
    void closeReaderStream();

    void createRdsFile();
    QString createRdsFileContent();

    void createMetaFile();
    QString createMetaFileContent();

    void createRecodedXML();
    void writeRecodedXmlBeginning();
    void writeRecodedXmlContent();

public:
    FileMaker();
    ~FileMaker();
    void readInputData();
    void createOutputFiles();

    QString getName();
    QString getArtist();

    void setName(QString);
    void setArtist(QString);

    QString getMetaName();
    QString getMetaArtist();

    void setMetaName(QString);
    void setMetaArtist(QString);
};

#endif // FILEMAKER_H
