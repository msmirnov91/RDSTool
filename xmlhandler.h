#ifndef XMLHANDLER_H
#define XMLHANDLER_H


#include "QString"
#include "QFile"
#include "QXmlStreamReader"
#include "QXmlStreamWriter"
#include "settings.h"


class XMLHandler{
public:
    XMLHandler(Settings*);
    ~XMLHandler();

    QString getFirstTagContent(QString);
    void makeRecodedXml(const char *);

private:
    QFile *inputFile;
    QFile *outputFile;

    QXmlStreamReader *reader;
    QXmlStreamWriter *writer;

    Settings *settings;
};

#endif // XMLHANDLER_H
