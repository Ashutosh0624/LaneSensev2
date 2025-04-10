#pragma once

#include <QString>
#include <QVariant>
#include <QSettings>

class ConfigParser
{
public:
    static ConfigParser* getInstance(const QString& configFilepath = "app.conf");

    QVariant getValue(const QString &group, const QString &key, const QVariant &defaultValue = QVariant());

private:
    explicit ConfigParser(const QString &configFilePath);
    static ConfigParser* instance;
    QSettings *settings;

    //prevent copyting
    ConfigParser(const ConfigParser&) = delete;
    ConfigParser& operator=(const ConfigParser&) = delete;
};

