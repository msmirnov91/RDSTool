#ifndef DATASTRUCT_H
#define DATASTRUCT_H

struct Data{
    QString name;
    QString artist;
    QString metaName;
    QString metaArtist;
};


void init(Data& data, FileMaker& maker){
    data.name = maker.getName();
    data.artist = maker.getArtist();
    data.metaName = maker.getMetaName();
    data.metaArtist = maker.getMetaArtist();
}


void replace(Data& data, TextReplacer& replacer){
    data.name = replacer.replaceAllOccurancesIn(data.name);
    data.artist = replacer.replaceAllOccurancesIn(data.artist);
    data.metaName = replacer.replaceAllOccurancesIn(data.metaName);
    data.metaArtist = replacer.replaceAllOccurancesIn(data.metaArtist);
}


void translate(Data& data, Translator& translator){
    data.name = translator.translate(data.name);
    data.artist = translator.translate(data.artist);
}


void storeDataStruct(Data& data, FileMaker& maker){
    maker.setName(data.name);
    maker.setArtist(data.artist);
    maker.setMetaName(data.metaName);
    maker.setMetaArtist(data.metaArtist);
}

#endif // DATASTRUCT_H
