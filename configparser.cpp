#include "configparser.h"

ConfigParser *ConfigParser::instance = nullptr;

ConfigParser::ConfigParser(const QString &configFilePath)
{
  settings = new QSettings(configFilePath, QSettings::IniFormat);
}

ConfigParser *ConfigParser::getInstance(const QString &configFilepath)
{
     if(instance == nullptr){
         instance = new ConfigParser(configFilepath);
     }
     return instance;
}

QVariant ConfigParser::getValue(const QString &group, const QString &key, const QVariant &defaultValue)
{
    settings->beginGroup(group);
    QVariant value = settings->value(key, defaultValue);
    settings->endGroup();
    return value;
}
