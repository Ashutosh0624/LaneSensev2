#include "errormanager.h"
#include "safetyLogging.h"

errorManager* errorManager::instance = nullptr;

errorManager* errorManager::getInstance(){
    if(instance == nullptr){
        instance = new errorManager();
    }
    return instance;
}

void errorManager::handleSensorFault(const QString &message, const QString &reqId)
{
   LOG_SENSOR_ERROR(message, reqId);

   // enter safe state immidiately
   emit safeStateActivated();
}

void errorManager::handleCriticalSystemError(const QString &message, const QString &reqId)
{
  LOG_FATAL_ERROR(message, reqId);   // logs a system-level fatal error

  //Enter safe state
  emit safeStateActivated();
}

void errorManager::reportRecovery(const QString &module, const QString &reqId)
{
   QString message = module + "recoverd successfully";
   LOG_RECOVERY(message, reqId);

   emit recoverySuccessful();
}

errorManager::errorManager(){
    // constructor logic if needed
}
