#include "logger.h"
#include "configparser.h"
#include <QDebug>

logger* logger::instance = nullptr;

logger *logger::getInstance()
{
  if(instance == nullptr){
      instance = new logger;
  }
  return instance;
}

void logger::logDebug(const QString &msg)
{

}

void logger::logInfo(const QString &msg)
{

}

void logger::logError(const QString &msg)
{

}

// constructor
logger::logger()
{
    QString logPath = ConfigParser::getInstance()->getValue("ADAS", "log_file_path", "lanesense.log").toString();
    debugEnabled = ConfigParser::getInstance()->getValue("ADAS", "enable_debug", false).toBool();
    logFile.setFileName(logPath);
    if(logFile.open(QIODevice::WriteOnly) | QIODevice::Append | QIODevice::Text){
        stream.setDevice(&logFile);
        logInfo("logger initialized");
    }else{
        qWarning()<<"Failed to open log File:"<<logPath;
    }

}
