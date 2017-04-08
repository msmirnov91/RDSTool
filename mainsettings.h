#ifndef CONFIGURATION_H
#define CONFIGURATION_H


#include "QSettings"

class MainSettings{
public:
    MainSettings();
    ~MainSettings();

    std::string getErrorPrefix();
    bool executionProhibited(); /// checks if file may be changed in current time

protected:
    QSettings *settings;

private:
    QString restrictedHoursForToday;
    QString errorPrefix;

    QString getCurrentWeekDayName();
    QString getCurrentHour();
};

#endif // CONFIGURATION_H
