#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include "QSettings"


class Settings{
public:
    Settings(QString);

    QString getInputFilePath();
    QString getRdsFilePath();
    QString getRecodedXmlPath();
    QString getMetaFilePath();
    QString getRdsSeparator();
    QString getMetaSeparator();

    QString getUploadingFilePath();
    QString getRootFtpUrl();
    QString getFtpPath();
    QString getFtpLogin();
    QString getFtpPassword();

    std::string getErrorPrefix();

    bool fileCreationProhibited(); /// checks if file may be changed in current time
    bool uploadProhibited();

private:
    // main settings
    QString inputFilePath;
    QString rdsFilePath;
    QString recodedXmlPath;
    QString metaFilePath;
    QString rdsSeparator;
    QString metaSeparator;

    // FTP settings
    QString doUpload;
    QString uploadingFilePath;
    QString rootFtpUrl;
    QString ftpLogin;
    QString ftpPassword;

    // various settings
    QString restrictedHoursForToday;
    QString errorPrefix;
};

#endif // CONFIGURATION_H
