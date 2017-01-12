#include "xmlhandler.h"


XMLHandler::XMLHandler(Settings *inputSettings){
    this->settings = inputSettings;

    this->inputFile = new QFile(this->settings->getInputFileName());
    if (!this->inputFile->open(QIODevice::ReadOnly)){
        throw this->settings->getPrefix() + " Can't open input XML!";
    }
    this->outputFile = new QFile(this->settings->getOutputXmlName());
    if (!this->outputFile->open(QIODevice::WriteOnly)){
        throw this->settings->getPrefix() + " Can't open output XML!";
    }

    this->reader = new QXmlStreamReader(this->inputFile);
    if (this->reader->hasError()){
        throw this->settings->getPrefix() + " Input XML has errors!";
    }

    this->writer = new QXmlStreamWriter(this->outputFile);
}


XMLHandler::~XMLHandler(){
    this->inputFile->close();
    this->outputFile->close();

    delete this->reader;
    delete this->writer;
    delete this->inputFile;
}


QString XMLHandler::getFirstTagContent(QString tagName){
    while (!this->reader->atEnd()){
        this->reader->readNext();
        if (this->reader->name().toString() == tagName){
            return this->reader->readElementText();
        }
    }
    throw this->settings->getPrefix() + " Can't find tag " + tagName.toStdString() + "!";
}


void XMLHandler::makeRecodedXml(const char *codecName){
    this->writer->setCodec(codecName);

    this->reader->readNext();
    this->writer->writeStartDocument(this->reader->documentVersion().toString());

    while (!this->reader->atEnd()){
        this->reader->readNext();
        this->writer->writeCurrentToken(*this->reader);
    }

}

