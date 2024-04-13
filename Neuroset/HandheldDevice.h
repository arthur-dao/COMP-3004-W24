#ifndef HANDHELDDEVICE_H
#define HANDHELDDEVICE_H

#include "defs.h"
#include "Headset.h"
#include "Session.h"
#include <QTimer>
#include <QObject>
#include <QDebug>
#include <list>
#include "pcwindow.h"
#include "Treatment.h"
#include <QThread>

using namespace std;

class HandheldDevice : public QObject {
    Q_OBJECT

public:
    explicit HandheldDevice(Headset* headset, int batteryLevel = 100, QObject* parent = nullptr);
    ~HandheldDevice();

    int getBattery() { return batteryPercent; }
    RunStatus getRunStatus() { return runStatus; }
    QList<Session> getSessions();
    int getSiteNum() { return headset->getSiteNum(); };

public slots:
    void createSession();
    void shutdown();
    void beginSession();
    void stop();
    void pause();
    void resume();
    void dateTimeSelection();

    void menuToggle();
    void uploadToPC(int);
    void updateMenu();
    void powerToggle();
    void reduceBattery();
    void chargeBatteryToFull();
    void disconnect();

signals:
    void sessionStarted();
    void sessionStopped();
    void startSimulation(Headset*);

private:
    Headset* headset;
    DeviceStatus deviceStatus;
    RunStatus runStatus;
    int batteryPercent;
    bool contact;
    bool treatmentSig;
    Session* currentSession;
    Treatment* treatment;

    QTimer stopTimer;
    QTimer runTimer;
    QList<Session> sessions;

    static const int size = MAX_SIZE;
    PCWindow *pcWindow;

    QThread treatmentThread;
};

#endif // HANDHELDDEVICE_H
