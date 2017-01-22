#include "QCoreApplication"
#include "datahandler.h"
#include "settings.h"
#include "easylogging++.h"

INITIALIZE_EASYLOGGINGPP

int main(int argc, char *argv[]){
    // need for event loop
    QCoreApplication a(argc, argv);

    // configure logger
    el::Configurations defaultConf;
    defaultConf.set(el::Level::Error, el::ConfigurationType::Filename, "errors.log");
    el::Loggers::reconfigureLogger("default", defaultConf);

    try{      
        // initialize settings from chosen file
        Settings settingsFromFile("settings.ini");

        // initialize handler with settings
        DataHandler handler(&settingsFromFile);

        handler.readInputData();
        if (handler.translationIsNecessary()){
            handler.translate();
        }
        if (settingsFromFile.fileCreationAllowed()){
            handler.createOutputFiles();
            handler.createRecodedXML("Windows-1251");
        }
        handler.uploadFileViaFtp();
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
