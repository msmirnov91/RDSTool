#include "QCoreApplication"
#include "mainsettings.h"
#include "easylogging++.h"
#include "data.h"

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
        Data namesAndArtists;

        maker.readInputData();

        namesAndArtists.initialize(maker);
        namesAndArtists.replace(replacer);
        namesAndArtists.translate(translator);
        namesAndArtists.store(maker);

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
