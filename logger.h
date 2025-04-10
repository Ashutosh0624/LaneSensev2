#pragma once

#include <QString>
#include <QFile>   // to open/write log file
#include <QTextStream> // text-based I/O
#include <QDateTime>   // for timestamp , in log timestamp may be required
#include <QDebug>
#include <QMutex>
#include "configparser.h"

class logger
{
public:
    // function to get the instance of logger
    enum Level{DEBUG, INFO, WARNING, ERROR};

    static logger* getInstance();

    //logger functions
    void log(const QString& msg,
             Level level,
             const QString& tag,
             const QString& reqId = " ");

private:
    logger();  // private constructor
    static QMutex mutex;
    static logger* instance;
    QFile logFile;
    QTextStream stream;   // to write line in file
    bool debugEnabled;    //  will be decide after reading config
    QString getTimeStamp();
    QString logLevelToString(Level level);

    // prevent copy
    logger(const logger&) = delete;
    logger& operator=(const logger&) = delete;
    // disabling the copy constructor
    /*
       Since, Logger class is a singleton class, so it should have only one object
       so if someone might try to create a copy of that object like " logger copy = logger::getInstance()
       to avoid this , disabling the copy constructor is required.
       Similarly, assignment operator overloading should be disabled to avoid copy of logger object.
       In c++ 11, we can explicitly delete any function by using  = delete
       Its like saying to compiler that this function is not allowed.
       So, to enforce Singleton design pattern, we explicitly delete the copy constructor and assignment operator so that
       no additional logger instance can be created.
    */
      //
};


