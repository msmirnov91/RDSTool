#include "settings.h"
#include "qdatetime.h"
#include "QFileInfo"
#include "QDebug"
#include <exception>


/**
 * @brief Settings::Settings
 * initializes class object with settings from file
 * @param settingsFileName name of file contains stored settings
 */
Settings::Settings(QString settingsFileName){
    qDebug() << "initialize settings";
    QSettings settings(settingsFileName, QSettings::IniFormat);

    // read main settings
    settings.beginGroup("MainSettings");
    this->inputFilePath = settings.value("inputFile", "cur_playing.xml").toString();
    this->rdsFilePath = settings.value("rdsFile", "rds.txt").toString();
    this->recodedXmlPath = settings.value("recodedXml", "cur_playing_1251.xml").toString();
    this->recodedXmlEncoding = settings.value("recodedXmlEncoding", "Windows-1251").toString();
    this->metaFilePath = settings.value("metaFile", "meta.txt").toString();
    this->rdsSeparator = settings.value("rdsSeparator", "-").toString();
    this->metaSeparator = settings.value("metaSeparator", "-").toString();
    settings.endGroup();

    // read ftp settings
    settings.beginGroup("FTPSettings");
    this->doUpload = settings.value("doUpload", "true").toString();
    this->uploadingFilePath = settings.value("fileToUpload", "cur_playing.xml").toString();
    this->rootFtpUrl = settings.value("url", "").toString();
    this->ftpLogin = settings.value("login", "").toString();
    this->ftpPassword = settings.value("password", "").toString();
    settings.endGroup();

    QString weekDayName = this->getCurrentWeekDayName();
    // read time settings
    settings.beginGroup("TimeSettings");
    this->restrictedHoursForToday = settings.value(weekDayName, "none").toString();
    settings.endGroup();

    // read exception prefix
    settings.beginGroup("ExceptionPrefix");
    this->errorPrefix = settings.value("prefix", "").toString();
    settings.endGroup();
}


QString  Settings::getCurrentWeekDayName(){
    QDate today = QDate::currentDate();
    QString weekDayName = "";

    switch (today.dayOfWeek()){
        case 1:  weekDayName = "mon";
                 break;
        case 2:  weekDayName = "tue";
                 break;
        case 3:  weekDayName = "wed";
                 break;
        case 4:  weekDayName = "thu";
                 break;
        case 5:  weekDayName = "fri";
                 break;
        case 6:  weekDayName = "sat";
                 break;
        case 7:  weekDayName = "sun";
                 break;
        default: throw this->getErrorPrefix() + "QDate is mad!";
                 break;
    }
    return weekDayName;
}


QString Settings::getInputFilePath(){
   return this->inputFilePath;
}


QString Settings::getRdsFilePath(){
    return this->rdsFilePath;
}


QString Settings::getRecodedXmlPath(){
    return this->recodedXmlPath;
}


const char* Settings::getRecodedXmlEncoding(){
    int resultLength = this->recodedXmlEncoding.length() + 1;
    char* cString = new char[resultLength];

    cString = strcpy(cString, this->recodedXmlEncoding.toStdString().c_str());
    cString[resultLength] = '\0';

    return cString;
}


QString Settings::getMetaFilePath(){
    return this->metaFilePath;
}


QString Settings::getRdsSeparator(){
    return this->rdsSeparator;
}


QString Settings::getMetaSeparator(){
    return this->metaSeparator;
}


QString Settings::getUploadingFilePath(){
     return this->uploadingFilePath;
}


QString Settings::getRootFtpUrl(){
    return this->rootFtpUrl;
}


QString Settings::getFtpPath(){
    QFileInfo uploadingFileInfo(this->uploadingFilePath);
    return "/" + uploadingFileInfo.fileName();
}


QString Settings::getFtpLogin(){
    return this->ftpLogin;
}


QString Settings::getFtpPassword(){
    return this->ftpPassword;
}


std::string Settings::getErrorPrefix(){
    return this->errorPrefix.toStdString();
}


bool Settings::executionProhibited(){
    QStringList deprecatedHoursList = this->restrictedHoursForToday.split(" ");
    return deprecatedHoursList.contains(this->getCurrentHour());
}


QString Settings::getCurrentHour(){
    QTime now = QTime::currentTime();
    return QString("%1").arg(now.hour());
}


bool Settings::uploadProhibited(){
    return this->doUpload.toLower() == "false";
}
