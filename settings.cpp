#include "settings.h"
#include "qdatetime.h"
#include <exception>


/**
 * @brief Settings::Settings
 * initializes class object with settings from file
 * @param settingsFileName name of file contains stored settings
 */
Settings::Settings(QString settingsFileName){

    QSettings settings(settingsFileName, QSettings::IniFormat);

    // read main settings
    settings.beginGroup("MainSettings");
    this->inputFileName = settings.value("inputFileName", "cur_playing.xml").toString();
    this->outputFileName = settings.value("outputFileName", "rds.txt").toString();
    this->metaFileName = settings.value("metaFileName", "meta.txt").toString();
    this->separator = settings.value("separator", " - ").toString();
    this->metaSeparator = settings.value("metaSeparator", " - ").toString();
    settings.endGroup();

    // get name of current week day
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
        default: throw this->getPrefix() + "QDate is mad!";
                 break;
    }

    // read time settings
    settings.beginGroup("TimeSettings");
    this->deprecatedHours = settings.value(weekDayName, "none").toString();
    settings.endGroup();

    // read exception prefix
    settings.beginGroup("ExceptionPrefix");
    this->prefix = settings.value("prefix", "").toString();
    settings.endGroup();
}


QString Settings::getInputFileName(){
   return this->inputFileName;
}


QString Settings::getOutputFileName(){
    return this->outputFileName;
}


QString Settings::getMetaFileName(){
    return this->metaFileName;
}


QString Settings::getSeparator(){
    return this->separator;
}


QString Settings::getMetaSeparator(){
    return this->metaSeparator;
}


std::string Settings::getPrefix(){
    return this->prefix.toStdString();
}


/**
 * @brief Settings::writeAllowed
 * checks if output file may be created in current time
 * @return true if file creation is allowed
 */
bool Settings::writeAllowed(){
    // get current hour as a string
    QTime now = QTime::currentTime();
    QString currentHour = QString("%1").arg(now.hour());

    // search current hour in deprecated for today hours
    QStringList deprecatedHoursList = this->deprecatedHours.split(" ");
    bool result = !deprecatedHoursList.contains(currentHour);
    return result;
}
