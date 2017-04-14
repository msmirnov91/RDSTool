#ifndef DATA_H
#define DATA_H

#include "QString"
#include "FileMaker/filemaker.h"
#include "FtpUploader/ftpuploader.h"
#include "TextReplacer/textreplacer.h"
#include "Translator/translator.h"


class Data
{
    QString name;
    QString artist;
    QString metaName;
    QString metaArtist;

public:
    Data();
    void initialize(FileMaker& maker);
    void replace(TextReplacer& replacer);
    void translate(Translator& translator);
    void store(FileMaker& maker);
};

#endif // DATA_H
