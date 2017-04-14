#include "data.h"

Data::Data(){
    name = "";
    artist = "";
    metaName = "";
    metaArtist = "";
}


void Data::initialize(FileMaker& maker){
    name = maker.getName();
    artist = maker.getArtist();
    metaName = maker.getMetaName();
    metaArtist = maker.getMetaArtist();
}


void Data::replace(TextReplacer& replacer){
    name = replacer.replaceAllOccurancesIn(name);
    artist = replacer.replaceAllOccurancesIn(artist);
    metaName = replacer.replaceAllOccurancesIn(metaName);
    metaArtist = replacer.replaceAllOccurancesIn(metaArtist);
}


void Data::translate(Translator& translator){
    name = translator.translate(name);
    artist = translator.translate(artist);
}


void Data::store(FileMaker& maker){
    maker.setName(name);
    maker.setArtist(artist);
    maker.setMetaName(metaName);
    maker.setMetaArtist(metaArtist);
}
