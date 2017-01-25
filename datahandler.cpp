#include "datahandler.h"
#include "QFile"
#include "QByteArray"
#include "QTextStream"
#include "QRegExp"
#include "QEventLoop"
#include <QtNetwork>
#include <exception>


DataHandler::DataHandler(Settings *set){
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
    this->openReaderStream();

    this->name = this->getFirstTagContent("NAME");
    this->metaName =  this->name;

    this->artist = this->getFirstTagContent("ARTIST");
    this->metaArtist = this->artist;

    this->closeReaderStream();
}


void DataHandler::translate(){
    this->name = this->translateString(this->name);
    this->artist = this->translateString(this->artist);
}


void DataHandler::createOutputFiles(){
    if (this->settings->fileCreationProhibited()){
        return;
    }
    QString data = this->artist + " " + this->settings->getRdsSeparator()
                                                      + " " + this->name;
    this->writeStringToFile(this->settings->getRdsFilePath(), data);

    QString metaData = this->metaArtist+ " "
            + this->settings->getMetaSeparator() + " " + this->metaName;
    this->writeStringToFile(this->settings->getMetaFilePath(), metaData);

    this->createRecodedXML("Windows-1251");
}


bool DataHandler::translationIsNecessary(){
    bool result = this->hasRussianLetters(this->name)
                  || this->hasRussianLetters(this->artist);
    return result;
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


void DataHandler::writeStringToFile(QString fileName, QString toWrite){
    QFile outputFile(fileName);
    if (!outputFile.open(QIODevice::WriteOnly)){
        std::string which = fileName.toStdString();
        throw this->settings->getErrorPrefix() + " Cant open output file " + which + "!";
    }
    QTextStream out(&outputFile);
    out << toWrite;
    outputFile.close();
}


void DataHandler::createRecodedXML(const char *codecName){
    this->openReaderStream();

    this->recodedXML = new QFile(this->settings->getRecodedXmlPath());
    if (!this->recodedXML->open(QIODevice::WriteOnly)){
        throw this->settings->getErrorPrefix() + " Can't open output XML!";
    }

    this->writer = new QXmlStreamWriter(this->recodedXML);
    this->writer->setCodec(codecName);

    this->reader->readNext();
    this->writer->writeStartDocument(this->reader->documentVersion().toString());

    while (!this->reader->atEnd()){
        this->reader->readNext();
        this->writer->writeCurrentToken(*this->reader);
    }

    this->recodedXML->close();
    delete this->writer;
    delete this->recodedXML;
    this->closeReaderStream();
}


void DataHandler::openReaderStream(){
    this->inputXML = new QFile(this->settings->getInputFilePath());
    if (!this->inputXML->open(QIODevice::ReadOnly)){
        throw this->settings->getErrorPrefix() + " Can't open input XML!";
    }

    this->reader = new QXmlStreamReader(this->inputXML);
    if (this->reader->hasError()){
        throw this->settings->getErrorPrefix() + " Input XML has errors!";
    }
}


void DataHandler::closeReaderStream(){
    this->inputXML->close();
    delete this->reader;
    delete this->inputXML;
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


void DataHandler::uploadFileViaFtp(){
    if (this->settings->uploadProhibited()){
        return;
    }

    QUrl uploadUrl(this->settings->getRootFtpUrl());
    uploadUrl.setPath(this->settings->getFtpPath());
    uploadUrl.setUserName(this->settings->getFtpLogin());
    uploadUrl.setPassword(this->settings->getFtpPassword());
    uploadUrl.setPort(21);

    QNetworkAccessManager uploader;
    QNetworkRequest uploadRequest(uploadUrl);
    QNetworkReply *uploadReply;

    QString uploadingFileName = this->settings->getUploadingFilePath();
    QFile *uploadingFile = new QFile(uploadingFileName);

    QEventLoop synchronizationLoop;

    if (uploadingFile->open(QIODevice::ReadOnly)) {
        uploadReply = uploader.put(uploadRequest, uploadingFile);

        //make QNetworkAccess synchronous
        QObject::connect(uploadReply, SIGNAL(finished()),
                         &synchronizationLoop, SLOT(quit()));
        synchronizationLoop.exec();
        uploadingFile->close();
    }
    else{
        throw this->settings->getErrorPrefix() + " Can't open file for FTP transfer!";
    }
}
