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
    QString getInputFilePath();
    QString getRdsFilePath();
    QString getRecodedXmlPath();
    QString getMetaFilePath();
    QString getRdsSeparator();
    QString getMetaSeparator();

    QString getUploadingFilePath();
    QString getRootFtpUrl();
    QString getFtpPath();
    QString getFtpLogin();
    QString getFtpPassword();

    std::string getErrorPrefix();

    bool fileCreationAllowed(); /// checks if file may be changed in current time
    bool uploadAllowed();

private:
    // main settings
    QString inputFilePath; /// name of XML
    QString rdsFilePath; /// name of output file
    QString recodedXmlPath; /// name of output XML file in another encoding
    QString metaFilePath; /// name of meta file
    QString rdsSeparator; /// will separate name and aritst in output file
    QString metaSeparator; /// separator for metadata

    // FTP settings
    QString uploadingFilePath; /// name of file that must be uploaded via FTP
    QString rootFtpUrl;
    QString ftpLogin;
    QString ftpPassword;

    // various settings
    QString restrictedHoursForToday; /// contains string with hours when file creation is not allowed separated by space
    QString errorPrefix; /// smth with what the exception message must begin
};

#endif // CONFIGURATION_H
