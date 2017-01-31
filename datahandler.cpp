#include "datahandler.h"
#include "QFile"
#include "QByteArray"
#include "QTextStream"
#include "QRegExp"
#include "QTimer"
#include "QEventLoop"
#include <QtNetwork>
#include <exception>


DataHandler::DataHandler(Settings *set){
    qDebug() << "initialize dataHandler";
    this->settings = set;

    this->name = "";
    this->metaName = "";
    this->artist = "";
    this->metaArtist = "";

    this->tMap[L'а'] = "a";
    this->tMap[L'б'] = "b";
    this->tMap[L'в'] = "v";
    this->tMap[L'г'] = "g";
    this->tMap[L'д'] = "d";
    this->tMap[L'е'] = "e";
    this->tMap[L'ё'] = "yo";
    this->tMap[L'ж'] = "zh";
    this->tMap[L'з'] = "z";
    this->tMap[L'и'] = "i";
    this->tMap[L'й'] = "y";
    this->tMap[L'к'] = "k";
    this->tMap[L'л'] = "l";
    this->tMap[L'м'] = "m";
    this->tMap[L'н'] = "n";
    this->tMap[L'о'] = "o";
    this->tMap[L'п'] = "p";
    this->tMap[L'р'] = "r";
    this->tMap[L'с'] = "s";
    this->tMap[L'т'] = "t";
    this->tMap[L'у'] = "u";
    this->tMap[L'ф'] = "f";
    this->tMap[L'х'] = "h";
    this->tMap[L'ц'] = "ts";
    this->tMap[L'ч'] = "ch";
    this->tMap[L'ш'] = "sh";
    this->tMap[L'щ'] = "sh'";
    this->tMap[L'ь'] = "'";
    this->tMap[L'ы'] = "i";
    this->tMap[L'ъ'] = "";
    this->tMap[L'э'] = "e";
    this->tMap[L'ю'] = "yu";
    this->tMap[L'я'] = "ya";

    this->tMap[L'А'] = "A";
    this->tMap[L'Б'] = "B";
    this->tMap[L'В'] = "V";
    this->tMap[L'Г'] = "G";
    this->tMap[L'Д'] = "D";
    this->tMap[L'Е'] = "E";
    this->tMap[L'Ё'] = "YO";
    this->tMap[L'Ж'] = "ZH";
    this->tMap[L'З'] = "Z";
    this->tMap[L'И'] = "I";
    this->tMap[L'Й'] = "Y";
    this->tMap[L'К'] = "K";
    this->tMap[L'Л'] = "L";
    this->tMap[L'М'] = "M";
    this->tMap[L'Н'] = "N";
    this->tMap[L'О'] = "O";
    this->tMap[L'П'] = "P";
    this->tMap[L'Р'] = "R";
    this->tMap[L'С'] = "S";
    this->tMap[L'Т'] = "T";
    this->tMap[L'У'] = "U";
    this->tMap[L'Ф'] = "F";
    this->tMap[L'Х'] = "H";
    this->tMap[L'Ц'] = "TS";
    this->tMap[L'Ч'] = "CH";
    this->tMap[L'Ш'] = "SH";
    this->tMap[L'Щ'] = "SH'";
    this->tMap[L'Ь'] = "'";
    this->tMap[L'Ы'] = "I";
    this->tMap[L'Ъ'] = "";
    this->tMap[L'Э'] = "E";
    this->tMap[L'Ю'] = "YU";
    this->tMap[L'Я'] = "YA";
}


void DataHandler::readInputData(){
    qDebug() << "parse input XML";
    this->openReaderStream();

    this->name = this->getFirstTagContent("NAME");
    this->metaName =  this->name;

    this->artist = this->getFirstTagContent("ARTIST");
    this->metaArtist = this->artist;

    this->closeReaderStream();
    qDebug() << "parsed successfully";
}


void DataHandler::openReaderStream(){
    this->inputXML = new QFile(this->settings->getInputFilePath());
    this->tryToOpenFile(this->inputXML, QIODevice::ReadOnly);

    this->reader = new QXmlStreamReader(this->inputXML);
    if (this->reader->hasError()){
        throw this->settings->getErrorPrefix() + " Input XML has errors!";
    }
}


QString DataHandler::getFirstTagContent(QString tagName){
    while (!this->reader->atEnd()){
        this->reader->readNext();
        if (this->reader->name().toString() == tagName){
            return this->reader->readElementText();
        }
    }
    throw this->settings->getErrorPrefix() + " Can't find tag "
                                      + tagName.toStdString() + "!";
}


void DataHandler::closeReaderStream(){
    this->inputXML->close();
    delete this->reader;
    delete this->inputXML;
}


void DataHandler::tryToOpenFile(QFile* file, QIODevice::OpenMode mode){
    if (!file->open(mode)){
        throw this->settings->getErrorPrefix() + " Can't open  " + file->fileName().toStdString();
    }
}


bool DataHandler::translationIsNecessary(){
    return this->hasRussianLetters(this->name) || this->hasRussianLetters(this->artist);
}


bool DataHandler::hasRussianLetters(QString str){
    QRegExp oneOrMoreRussianLetters("[а-яёА-ЯЁ]");
    if (oneOrMoreRussianLetters.indexIn(str) == -1){
        return false;
    }
    else{
        return true;
    }
}


void DataHandler::translate(){
    qDebug() << "translating...";
    this->name = this->translateString(this->name);
    this->artist = this->translateString(this->artist);
}


QString DataHandler::translateString(QString str){
    QString result = "";
    TranslateMap::iterator it;
    for (int i = 0; i < str.size(); i++){
       it = this->tMap.find(str[i]);
       if (it != this->tMap.end()) {
           result += it->second;
       }
       else{
           result += str[i];
       }
    }
    return result;
}


void DataHandler::createOutputFiles(){
    this->createRdsFile();
    this->createMetaFile();
    this->createRecodedXML();
}


void DataHandler::createRdsFile(){
    QString rdsContent = this->createRdsFileContent();
    this->writeStringToFile(this->settings->getRdsFilePath(), rdsContent);
}


void DataHandler::createMetaFile(){
    QString metaContent = this->createMetaFileContent();
    this->writeStringToFile(this->settings->getMetaFilePath(), metaContent);
}


QString DataHandler::createRdsFileContent(){
    return this->artist + " " + this->settings->getRdsSeparator() + " " + this->name;
}


QString DataHandler::createMetaFileContent(){
    return this->metaArtist+ " " + this->settings->getMetaSeparator() + " " + this->metaName;
}


void DataHandler::writeStringToFile(QString fileName, QString toWrite){
    qDebug() << "creating output file " << fileName << "...";

    QFile *outputFile = new QFile(fileName);
    this->tryToOpenFile(outputFile, QIODevice::WriteOnly);

    QTextStream out(outputFile);
    out << toWrite;
    outputFile->close();
    qDebug() << "created successfully";
}


void DataHandler::createRecodedXML(){
    qDebug() << "creating recoded XML";
    this->openReaderStream();

    this->recodedXML = new QFile(this->settings->getRecodedXmlPath());
    this->tryToOpenFile(this->recodedXML, QIODevice::WriteOnly);

    this->writer = new QXmlStreamWriter(this->recodedXML);
    const char* codecName = this->settings->getRecodedXmlEncoding();
    this->writer->setCodec(codecName);

    this->writeRecodedXmlBeginning();
    this->writeRecodedXmlContent();

    this->recodedXML->close();
    delete this->writer;
    delete this->recodedXML;
    delete codecName;
    this->closeReaderStream();
    qDebug() << "created successfully";
}


void DataHandler::writeRecodedXmlBeginning(){
    this->reader->readNext();
    this->writer->writeStartDocument(this->reader->documentVersion().toString());
}


void DataHandler::writeRecodedXmlContent(){
    while (!this->reader->atEnd()){
        this->reader->readNext();
        this->writer->writeCurrentToken(*this->reader);
    }
}


void DataHandler::uploadFileViaFtp(){
    if (this->settings->uploadProhibited()){
        return;
    }

    QUrl uploadUrl = this->createUploadUrl();
    qDebug() << "uploading file to " << uploadUrl;

    QString uploadingFileName = this->settings->getUploadingFilePath();
    QFile *uploadingFile = new QFile(uploadingFileName);

    this->tryToOpenFile(uploadingFile, QIODevice::ReadOnly);
    this->doSynchronousUpload(uploadingFile, uploadUrl);

    uploadingFile->close();
    delete uploadingFile;
}


QUrl DataHandler::createUploadUrl(){
    QUrl url(this->settings->getRootFtpUrl());
    url.setPath(this->settings->getFtpPath());
    url.setUserName(this->settings->getFtpLogin());
    url.setPassword(this->settings->getFtpPassword());
    url.setPort(21);
    return url;
}


void DataHandler::doSynchronousUpload(QFile *fileToUpload, QUrl uploadUrl){
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

