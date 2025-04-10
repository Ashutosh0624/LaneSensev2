#ifndef SENSORDATAMODEL_H
#define SENSORDATAMODEL_H

#include <QObject>
#include <QTimer>
#include "qt_grpc_client.h"

// FS-REQ ID: FS-REQ-001 for initialization logging
// FS-REQ ID: FS-REQ-002 for periodic data polling
// FS-REQ ID: FS-REQ-003 for error monitoring

class SensorDataModel : public QObject
{
    Q_OBJECT

public:
    explicit SensorDataModel(QObject* parent = nullptr);
    ~SensorDataModel();

    Q_PROPERTY(float speed READ speed NOTIFY dataUpdated)
    Q_PROPERTY(float acceleration READ acceleration NOTIFY dataUpdated)
    Q_PROPERTY(float steering READ steering NOTIFY dataUpdated)
    Q_PROPERTY(float brake READ brake NOTIFY dataUpdated)
    Q_PROPERTY(float throttle READ throttle NOTIFY dataUpdated)
    Q_PROPERTY(float laneOffset READ laneOffset NOTIFY dataUpdated)
    Q_PROPERTY(QString trafficSign READ trafficSign NOTIFY dataUpdated)
    Q_PROPERTY(QString status READ status NOTIFY dataUpdated)

    float speed() const;
    float acceleration() const;
    float steering() const;
    float brake() const;
    float throttle() const;
    float laneOffset() const;
    QString trafficSign() const;
    QString status() const;

signals:
    void dataUpdated();
    void errorOccurred(const QString &errorMessage);

private slots:
    void pollSensorData();

private:
    QTimer* m_timer;
    QtGrpcClient m_client;
    SensorData m_data;

    void handleErrors(const QString& context, const QString& fsReqId);
};

#endif // SENSORDATAMODEL_H
