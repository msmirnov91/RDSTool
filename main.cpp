#include "QCoreApplication"
#include "mainsettings.h"
#include "easylogging++.h"
#include "FileMaker/filemaker.h"
#include "FtpUploader/ftpuploader.h"
#include "TextReplacer/textreplacer.h"
#include "translator.h"

INITIALIZE_EASYLOGGINGPP

int main(int argc, char *argv[]){
    // need for event loop
    QCoreApplication a(argc, argv);

    // configure logger
    el::Configurations defaultConf;
    defaultConf.set(el::Level::Error, el::ConfigurationType::Filename, "errors.log");
    el::Loggers::reconfigureLogger("default", defaultConf);

    try{
        MainSettings mainSettings;
        if (mainSettings.executionProhibited()){
            return 0;
        }

        FileMaker maker;
        Translator translator;
        FtpUploader uploader;
        TextReplacer replacer;

        maker.readInputData();

        // get data
        QString name = maker.getName();
        QString artist = maker.getArtist();
        QString metaName = maker.getMetaName();
        QString metaArtist = maker.getMetaArtist();

        // replacing strings in name and artist
        name = replacer.replaceAllOccurancesIn(name);
        artist = replacer.replaceAllOccurancesIn(artist);

        // replacing strings in metaName and metaArtist
        metaName = replacer.replaceAllOccurancesIn(metaName);
        metaArtist = replacer.replaceAllOccurancesIn(metaArtist);

        // translating name and arist
        name = translator.translate(name);
        artist = translator.translate(artist);

        // store data
        maker.setName(name);
        maker.setArtist(artist);
        maker.setMetaName(metaName);
        maker.setMetaArtist(metaArtist);

        maker.createOutputFiles();
        uploader.uploadFileViaFtp();
    }
    catch (std::string str){
        LOG(ERROR) << str;
    }
    catch (std::exception e){
        LOG(ERROR) << e.what();
    }
    catch (...){
        LOG(ERROR) << "Unknown exception!";
    }
    return 0;
}
