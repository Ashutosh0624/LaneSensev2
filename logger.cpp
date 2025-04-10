#include "logger.h"
#include "configparser.h"
#include <QDebug>

logger* logger::instance = nullptr;
QMutex logger::mutex;

logger *logger::getInstance()
{
  if(instance == nullptr){
      instance = new logger;
  }
  return instance;
}

void logger::log(const QString &msg, Level level, const QString &tag, const QString &reqId)
{
    QMutexLocker locker(&mutex);
    if(!debugEnabled && level== DEBUG)return;

    QString logMessage = getTimeStamp();
    logMessage += " "+ logLevelToString(level);
    logMessage += " [" + tag + "]";

    if(!reqId.isEmpty()){
        logMessage += "[" + reqId + "]";
    }

    logMessage += " " + msg;

    if(stream.device()){
        stream << logMessage << Qt::endl;
        stream.flush();
    }
    qDebug() << logMessage;
}
// constructor
logger::logger()
{
    QString path = ConfigParser::getInstance()->getValue("ADAS", "log_file_path", "lanesense.log").toString();
    debugEnabled = ConfigParser::getInstance()->getValue("ADAS", "enable_debug", false).toBool();
    logFile.setFileName(path);
    if(logFile.open(QIODevice::WriteOnly) | QIODevice::Append | QIODevice::Text){
        stream.setDevice(&logFile);
        qDebug()<<("logger initialized");
    }else{
        qWarning()<<"Failed to open log File:"<<path;
    }

}

QString logger::getTimeStamp()
{
    return QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss");
}

QString logger::logLevelToString(Level level)
{
  switch(level){
    case DEBUG: return "[DEBUG]";
    case INFO:  return "[INFO]";
    case WARNING: return "[WARNING]";
    case ERROR: return "[ERROR]";
    default: return "[UNKOWN]";
  }
}
