#include "filemakersettings.h"


FileMakerSettings::FileMakerSettings(){
    settings->beginGroup("MainSettings");
    this->inputFilePath = settings->value("inputFile", "cur_playing.xml").toString();
    this->rdsFilePath = settings->value("rdsFile", "rds.txt").toString();
    this->recodedXmlPath = settings->value("recodedXml", "cur_playing_1251.xml").toString();
    this->recodedXmlEncoding = settings->value("recodedXmlEncoding", "Windows-1251").toString();
    this->metaFilePath = settings->value("metaFile", "meta.txt").toString();
    this->rdsSeparator = settings->value("rdsSeparator", "-").toString();
    this->metaSeparator = settings->value("metaSeparator", "-").toString();
    settings->endGroup();
}


QString FileMakerSettings::getInputFilePath(){
   return this->inputFilePath;
}


QString FileMakerSettings::getRdsFilePath(){
    return this->rdsFilePath;
}


QString FileMakerSettings::getRecodedXmlPath(){
    return this->recodedXmlPath;
}


const char* FileMakerSettings::getRecodedXmlEncoding(){
    int resultLength = this->recodedXmlEncoding.length() + 1;
    char* cString = new char[resultLength];

    cString = strcpy(cString, this->recodedXmlEncoding.toStdString().c_str());
    cString[resultLength] = '\0';

    return cString;
}


QString FileMakerSettings::getMetaFilePath(){
    return this->metaFilePath;
}


QString FileMakerSettings::getRdsSeparator(){
    return this->rdsSeparator;
}


QString FileMakerSettings::getMetaSeparator(){
    return this->metaSeparator;
}
