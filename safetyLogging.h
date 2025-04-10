// SafetyLogging.h - Wrapper macros for Logger class (Functional Safety Logging)
#ifndef SAFETYLOGGING_H
#define SAFETYLOGGING_H

#include "logger.h"

// Log a safety warning with a Functional Safety Requirement ID
#define LOG_SAFETY(msg, reqId) \
    logger::getInstance()->log(msg, logger::Level::WARNING, "SAFETY", reqId)

// Log a successful recovery event with FS-REQ traceability
#define LOG_RECOVERY(msg, reqId) \
    logger::getInstance()->log(msg, logger::Level::INFO, "RECOVERY", reqId)

// Log a sensor-related error condition
#define LOG_SENSOR_ERROR(msg, reqId) \
    logger::getInstance()->log(msg, logger::Level::ERROR, "SENSOR", reqId)

// Log a system-level info log (typically used at startup)
#define LOG_SYSTEM_INIT(msg) \
    logger::getInstance()->log(msg, logger::Level::INFO, "SYSTEM", "FS-REQ-6.1.0")

// Generic ERROR logging with safety tag and requirement ID
#define LOG_FATAL_ERROR(msg, reqId) \
    logger::getInstance()->log(msg, logger::Level::ERROR, "ERROR", reqId)

#endif // SAFETYLOGGING_H

