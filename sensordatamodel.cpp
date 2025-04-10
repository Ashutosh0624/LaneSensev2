#include "sensordatamodel.h"
#include "logger.h"
#include "errormanager.h"
#include "configparser.h"

SensorDataModel::SensorDataModel(QObject* parent)
    : QObject(parent), m_timer(new QTimer(this))
{
    // FS-REQ-001: Initialization Logging
    logger::getInstance()->log("[INIT] SensorDataModel created.",
                               logger::INFO, "SensorDataModel", "FS-REQ-001");

    int pollingInterval = ConfigParser::getInstance()
                            ->getValue("ADAS", "polling_interval_ms", 500)
                            .toInt();

    connect(m_timer, &QTimer::timeout, this, &SensorDataModel::pollSensorData);
    m_timer->start(pollingInterval);
}

SensorDataModel::~SensorDataModel()
{
    if (m_timer != nullptr)
    {
        m_timer->stop();
    }
    logger::getInstance()->log("[DESTROY] SensorDataModel destroyed.",
                               logger::INFO, "SensorDataModel", "FS-REQ-001");
}

void SensorDataModel::pollSensorData()
{
    // FS-REQ-002: Periodic Sensor Data Polling
    try
    {
        m_data = m_client.getSensorData();

        if (m_data.status != "running")
        {
            handleErrors("Sensor system not running", "FS-REQ-003");
            return;
        }

        emit dataUpdated();
    }
    catch (const std::exception& ex)
    {
        handleErrors(ex.what(), "FS-REQ-003");
    }
    catch (...)
    {
        handleErrors("Unknown error occurred while polling sensor data", "FS-REQ-003");
    }
}

void SensorDataModel::handleErrors(const QString& context, const QString& fsReqId)
{
    logger::getInstance()->log("[ERROR] " + context,
                               logger::ERROR, "SensorDataModel", fsReqId);
    errorManager::getInstance()->handleCriticalSystemError(context, fsReqId);
    emit errorOccurred(context);
}

// ----------------- Q_PROPERTY Getters -----------------

float SensorDataModel::speed() const
{
    return m_data.speed;
}

float SensorDataModel::acceleration() const
{
    return m_data.acceleration;
}

float SensorDataModel::steering() const
{
    return m_data.steering;
}

float SensorDataModel::brake() const
{
    return m_data.brake;
}

float SensorDataModel::throttle() const
{
    return m_data.throttle;
}

float SensorDataModel::laneOffset() const
{
    return m_data.lane_offset;
}

QString SensorDataModel::trafficSign() const
{
    return QString::fromStdString(m_data.traffic_sign);
}

QString SensorDataModel::status() const
{
    return QString::fromStdString(m_data.status);
}
