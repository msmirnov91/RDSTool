#include "datatranslator.h"
#include "settings.h"
#include "easylogging++.h"

INITIALIZE_EASYLOGGINGPP

int main(int argc, char *argv[]){
    // configure logger
    el::Configurations defaultConf;
    defaultConf.set(el::Level::Error, el::ConfigurationType::Filename, "errors.log");
    el::Loggers::reconfigureLogger("default", defaultConf);

    try{      
        // initialize settings from chosen file
        Settings settingsFromFile("settings.ini");

        // initialize translator with settings
        DataTranslator translator(&settingsFromFile);

        translator.readData();
        if (translator.translationIsNecessary()){
            translator.translate();
        }
        if (settingsFromFile.writeAllowed()){
            translator.writeData();
            translator.makeRecodedXML("Windows-1251");
        }
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
