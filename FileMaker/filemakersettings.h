#ifndef FILEMAKERSETTINGS_H
#define FILEMAKERSETTINGS_H


#include "mainsettings.h"
#include "QString"

class FileMakerSettings: public MainSettings
{
private:
    QString inputFilePath;
    QString rdsFilePath;
    QString recodedXmlPath;
    QString recodedXmlEncoding;
    QString metaFilePath;
    QString rdsSeparator;
    QString metaSeparator;

public:
    FileMakerSettings();

    QString getInputFilePath();
    QString getRdsFilePath();
    QString getRecodedXmlPath();
    const char* getRecodedXmlEncoding();
    QString getMetaFilePath();
    QString getRdsSeparator();
    QString getMetaSeparator();
};

#endif // FILEMAKERSETTINGS_H
