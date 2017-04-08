#include "ftpuploadersettings.h"
#include "QFileInfo"


FtpUploaderSettings::FtpUploaderSettings(){
    settings->beginGroup("FTPSettings");
    this->doUpload = settings->value("doUpload", "true").toString();
    this->uploadingFilePath = settings->value("fileToUpload", "cur_playing.xml").toString();
    this->rootFtpUrl = settings->value("url", "").toString();
    this->ftpLogin = settings->value("login", "").toString();
    this->ftpPassword = settings->value("password", "").toString();
    settings->endGroup();
}


QString FtpUploaderSettings::getUploadingFilePath(){
     return this->uploadingFilePath;
}


QString FtpUploaderSettings::getRootFtpUrl(){
    return this->rootFtpUrl;
}


QString FtpUploaderSettings::getFtpPath(){
    QFileInfo uploadingFileInfo(this->uploadingFilePath);
    return "/" + uploadingFileInfo.fileName();
}


QString FtpUploaderSettings::getFtpLogin(){
    return this->ftpLogin;
}


QString FtpUploaderSettings::getFtpPassword(){
    return this->ftpPassword;
}


bool FtpUploaderSettings::uploadProhibited(){
    return this->doUpload.toLower() == "false";
}
