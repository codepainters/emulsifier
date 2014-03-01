#ifndef MIDIDEVICEINQUIRY_H
#define MIDIDEVICEINQUIRY_H

#include <QObject>
#include <QTimer>
#include <QList>

#include "midiio.h"

struct MidiDevice
{
    uint8_t deviceId;
    uint32_t manufacturerId;
    uint16_t familyCode;
    uint16_t deviceMemberCode;
    uint8_t softwareRevision[4];
};

class MidiDeviceInquiry : public QObject
{
    Q_OBJECT
public:
    explicit MidiDeviceInquiry(MidiIO* midi, QObject *parent = 0);
    
    void startDeviceInquiry(unsigned long inquiryTime = 100);

signals:
    void deviceInquiryCompleted(const QList<MidiDevice>& devices);

private slots:
    void timeout();
    void receivedSysExMessage(const std::vector<uint8_t> &message);

private:
    MidiIO* midi;
    QTimer* timer;
    QList<MidiDevice> devices;
};

#endif // MIDIDEVICEINQUIRY_H
