#include "mainsettings.h"
#include "qdatetime.h"
#include "QFileInfo"
#include "QDebug"
#include <exception>


MainSettings::MainSettings(){
    qDebug() << "initialize settings";
    settings = new QSettings("settings.ini", QSettings::IniFormat);

    QString weekDayName = this->getCurrentWeekDayName();
    // read time settings
    settings->beginGroup("TimeSettings");
    this->restrictedHoursForToday = settings->value(weekDayName, "none").toString();
    settings->endGroup();

    // read exception prefix
    settings->beginGroup("ExceptionPrefix");
    this->errorPrefix = settings->value("prefix", "").toString();
    settings->endGroup();
}


MainSettings::~MainSettings(){
    delete settings;
}


QString  MainSettings::getCurrentWeekDayName(){
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


std::string MainSettings::getErrorPrefix(){
    return this->errorPrefix.toStdString();
}


bool MainSettings::executionProhibited(){
    QStringList deprecatedHoursList = this->restrictedHoursForToday.split(" ");
    return deprecatedHoursList.contains(this->getCurrentHour());
}


QString MainSettings::getCurrentHour(){
    QTime now = QTime::currentTime();
    return QString("%1").arg(now.hour());
}

