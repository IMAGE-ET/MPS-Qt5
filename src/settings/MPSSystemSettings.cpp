/*
 *
 */

#include "MPSSystemSettings.h"
#include <system/MPSSystem.h>
#include <dicom/net/DcmAET.h>


MPSSystemSettings::MPSSystemSettings()
{
    this->m_systemSettings = new QSettings("HealthSoft", "MPS");
}

bool MPSSystemSettings::existRemoteAET(char* aet, char* hostname)
{
    QString aetSetting((MPSSetting_REMOTE_AET_GROUP) + "/" + QString(aet));
    string aetValue, hostnameValue;
    int portValue;
    if (this->m_systemSettings->contains(aetSetting))
    {
        char* aetSettingValue = strdup(this->m_systemSettings->value(aetSetting).toString().toStdString().c_str());
        if (DcmAET::validateAetSettingValue(aetSettingValue,
                                            aetValue,
                                            hostnameValue,
                                            portValue) &&
           hostnameValue == string(hostname))
            return true;
            
    }
    
    return false;
}



/*
 * This method insert the data in the system settings if 
 * the values of parameters are valid. 
 * @param aet: can't have any space character
 * @param hostname: can't have any space character
 * @param port: can't be less than 1
 */
bool MPSSystemSettings::insertRemoteAET(QString& aet, QString& hostname, int port)
{
    if (aet.indexOf(' ') != -1 ||
        hostname.indexOf(' ') != -1 || 
        port < 1 || port > 65535) // have space
        return false;
    
    // everything is fine
    QSettings* settings = Singleton<MPSSystem>::instance()->settings()->settings();
    settings->beginGroup(MPSSetting_REMOTE_AET_GROUP);
    settings->setValue(aet, aet+"@" + hostname + ":" + QVariant(port).toString());
    settings->endGroup();
}


bool MPSSystemSettings::hasSetting(const QString& keySetting)
{
    return this->m_systemSettings->contains(keySetting);
}


QVariant MPSSystemSettings::value(const QString& keySetting)
{
    if (this->m_systemSettings->contains(keySetting))
        return this->m_systemSettings->value(keySetting);
    
    return QVariant();
}

MPSSystemSettings::~MPSSystemSettings()
{
    delete this->m_systemSettings;
}