#ifndef FTPUPLOADER_H
#define FTPUPLOADER_H


#include "ftpuploadersettings.h"
#include "QFile"
#include "QUrl"

class FtpUploader
{
    FtpUploaderSettings *settings;

    QUrl createUploadUrl();
    void tryToOpenFile(QFile*, QIODevice::OpenMode);
    void doSynchronousUpload(QFile*, QUrl);

public:
    FtpUploader();
    ~FtpUploader();
    void uploadFileViaFtp();
};

#endif // FTPUPLOADER_H
