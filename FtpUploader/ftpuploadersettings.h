#ifndef FTPUPLOADERSETTINGS_H
#define FTPUPLOADERSETTINGS_H


#include "mainsettings.h"
#include "QString"

class FtpUploaderSettings: public MainSettings
{
public:
    FtpUploaderSettings();

    QString getUploadingFilePath();
    QString getRootFtpUrl();
    QString getFtpPath();
    QString getFtpLogin();
    QString getFtpPassword();

    bool uploadProhibited();

private:
    QString doUpload;
    QString uploadingFilePath;
    QString rootFtpUrl;
    QString ftpLogin;
    QString ftpPassword;
};

#endif // FTPUPLOADERSETTINGS_H
