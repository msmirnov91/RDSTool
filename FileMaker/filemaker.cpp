#include "filemaker.h"
#include "QDebug"
#include "QByteArray"
#include "QTextStream"
#include <exception>


FileMaker::FileMaker(){
    qDebug() << "initialize FileMaker";
    settings = new FileMakerSettings();

    this->name = "";
    this->metaName = "";
    this->artist = "";
    this->metaArtist = "";
}


FileMaker::~FileMaker(){
    delete settings;
}


QString FileMaker::getName(){
    return name;
}


QString FileMaker::getArtist(){
    return artist;
}


void FileMaker::setName(QString name){
    this->name  = name;
}


void FileMaker::setArtist(QString artist){
    this->artist = artist;
}


QString FileMaker::getMetaName(){
    return metaName;
}


QString FileMaker::getMetaArtist(){
    return metaArtist;
}


void FileMaker::setMetaName(QString metaName){
    this->metaName = metaName;
}


void FileMaker::setMetaArtist(QString metaArtist){
    this->metaArtist = metaArtist;
}


void FileMaker::readInputData(){
    qDebug() << "parse input XML";
    this->openReaderStream();

    this->name = this->getFirstTagContent("NAME");
    this->metaName = this->name;

    this->artist = this->getFirstTagContent("ARTIST");
    this->metaArtist = this->artist;

    this->closeReaderStream();
    qDebug() << "parsed successfully";
}


void FileMaker::openReaderStream(){
    this->inputXML = new QFile(this->settings->getInputFilePath());
    this->tryToOpenFile(this->inputXML, QIODevice::ReadOnly);

    this->reader = new QXmlStreamReader(this->inputXML);
    if (this->reader->hasError()){
        throw this->settings->getErrorPrefix() + " Input XML has errors!";
    }
}


QString FileMaker::getFirstTagContent(QString tagName){
    while (!this->reader->atEnd()){
        this->reader->readNext();
        if (this->reader->name().toString() == tagName){
            return this->reader->readElementText();
        }
    }
    throw this->settings->getErrorPrefix() + " Can't find tag "
                                      + tagName.toStdString() + "!";
}


void FileMaker::closeReaderStream(){
    this->inputXML->close();
    delete this->reader;
    delete this->inputXML;
}


void FileMaker::tryToOpenFile(QFile* file, QIODevice::OpenMode mode){
    if (!file->open(mode)){
        throw this->settings->getErrorPrefix() + " Can't open  " + file->fileName().toStdString();
    }
}


void FileMaker::createOutputFiles(){
    this->createRdsFile();
    this->createMetaFile();
    this->createRecodedXML();
}


void FileMaker::createRdsFile(){
    QString rdsContent = this->createRdsFileContent();
    this->writeStringToFile(this->settings->getRdsFilePath(), rdsContent);
}


void FileMaker::createMetaFile(){
    QString metaContent = this->createMetaFileContent();
    this->writeStringToFile(this->settings->getMetaFilePath(), metaContent);
}


QString FileMaker::createRdsFileContent(){
    return this->artist + " " + this->settings->getRdsSeparator() + " " + this->name;
}


QString FileMaker::createMetaFileContent(){
    return this->metaArtist+ " " + this->settings->getMetaSeparator() + " " + this->metaName;
}


void FileMaker::writeStringToFile(QString fileName, QString toWrite){
    qDebug() << "creating output file " << fileName << "...";

    QFile *outputFile = new QFile(fileName);
    this->tryToOpenFile(outputFile, QIODevice::WriteOnly);

    QTextStream out(outputFile);
    out << toWrite;
    outputFile->close();
    qDebug() << "created successfully";
}


void FileMaker::createRecodedXML(){
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


void FileMaker::writeRecodedXmlBeginning(){
    this->reader->readNext();
    this->writer->writeStartDocument(this->reader->documentVersion().toString());
}


void FileMaker::writeRecodedXmlContent(){
    while (!this->reader->atEnd()){
        this->reader->readNext();
        this->writer->writeCurrentToken(*this->reader);
    }
}
