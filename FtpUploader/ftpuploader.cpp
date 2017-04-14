#include "ftpuploader.h"
#include "QTimer"
#include "QEventLoop"
#include "QDebug"
#include <QtNetwork>
#include <exception>


FtpUploader::FtpUploader(){
    qDebug() << "initialize FtpUploader";
    settings = new FtpUploaderSettings();
}


FtpUploader::~FtpUploader(){
    delete settings;
}


void FtpUploader::uploadFileViaFtp(){
    if (this->settings->uploadProhibited()){
        return;
    }

    QUrl uploadUrl = this->createUploadUrl();

    QString uploadingFileName = this->settings->getUploadingFilePath();
    qDebug() << "uploading file " << uploadingFileName << " to " << uploadUrl;

    QFile *uploadingFile = new QFile(uploadingFileName);

    this->tryToOpenFile(uploadingFile, QIODevice::ReadOnly);
    this->doSynchronousUpload(uploadingFile, uploadUrl);

    uploadingFile->close();
    delete uploadingFile;
}


QUrl FtpUploader::createUploadUrl(){
    QUrl url(this->settings->getRootFtpUrl());
    url.setPath(this->settings->getFtpPath());
    url.setUserName(this->settings->getFtpLogin());
    url.setPassword(this->settings->getFtpPassword());
    url.setPort(21);
    return url;
}


void FtpUploader::tryToOpenFile(QFile* file, QIODevice::OpenMode mode){
    if (!file->open(mode)){
        throw this->settings->getErrorPrefix() + " Can't open  " + file->fileName().toStdString();
    }
}


void FtpUploader::doSynchronousUpload(QFile *fileToUpload, QUrl uploadUrl){
    QNetworkAccessManager uploader;
    QNetworkRequest uploadRequest(uploadUrl);
    QNetworkReply *uploadReply;

    QEventLoop synchronizationLoop;

    uploadReply = uploader.put(uploadRequest, fileToUpload);

    //make QNetworkAccess synchronous
    QObject::connect(uploadReply, SIGNAL(finished()),
                         &synchronizationLoop, SLOT(quit()));
    QTimer::singleShot(5000, &synchronizationLoop, SLOT(quit()));

    synchronizationLoop.exec();

    qDebug() << "uploaded with reply error code " << uploadReply->error();
}

