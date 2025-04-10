#pragma once

#include <QObject>
#include <QString>

class errorManager : public QObject
{
    Q_OBJECT
public:
    static errorManager* getInstance();


signals:
    void safeStateActivated();
    void recoverySuccessful();

public slots:
    // centralized methods to handle incoming failures from all modules
    void handleSensorFault(const QString &message, const QString &reqId);
    void handleCriticalSystemError(const QString &message, const QString &reqId);
    void reportRecovery(const QString &module, const QString &reqId);


private:
    errorManager();
    static errorManager *instance;

    //Disable copy
    errorManager(const errorManager &) = delete;
    errorManager& operator=(const errorManager&) = delete;


};

