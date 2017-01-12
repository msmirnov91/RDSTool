#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include "QSettings"


/**
 * @brief The configuration class
 * works with configuration file ininiformat
 * keeps program settings
 */
class Settings{
public:
    Settings(QString);

    // getters
    QString getInputFileName();
    QString getOutputFileName();
    QString getOutputXmlName();
    QString getMetaFileName();
    QString getSeparator();
    QString getMetaSeparator();
    std::string getPrefix();

    bool writeAllowed(); /// checks if file may be changed in current time
private:
    QString inputFileName; /// name of XML
    QString outputFileName; /// name of output file
    QString outputXmlName; /// name of output XML file in another encoding
    QString metaFileName; /// name of meta file
    QString separator; /// will separate name and aritst in output file
    QString metaSeparator; /// separator for metadata

    QString deprecatedHours; /// contains string with hours when file creation is not allowed separated by space

    QString prefix; /// smth with what the exception message must begin
};

#endif // CONFIGURATION_H
