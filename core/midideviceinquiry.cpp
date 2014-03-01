#include "midideviceinquiry.h"
#include <iostream>

MidiDeviceInquiry::MidiDeviceInquiry(MidiIO* midi, QObject *parent) :
    QObject(parent), midi(midi)
{
}

void MidiDeviceInquiry::startDeviceInquiry(unsigned long inquiryTime)
{
    connect(midi, SIGNAL(receivedSysExMessage(std::vector<uint8_t>)), this, SLOT(receivedSysExMessage(std::vector<uint8_t>)));

    // F0 7E <deviceId> 06 01 F7
    const uint8_t devInquiry[] = { 0xF0, 0x7E, 0x7F, 0x06, 0x01, 0xF7 };
    midi->sendMessage(devInquiry, sizeof(devInquiry));

    timer = new QTimer(this);
    timer->singleShot(inquiryTime, this, SLOT(timeout()));
}

void MidiDeviceInquiry::receivedSysExMessage(const std::vector<uint8_t> &message)
{
    std::cout << "got somethin" << std::endl;
    try {
        // is a device inquiry response?
        if(message[0] == 0xF0 && message[1] == 0x7E && message[3] == 0x06 && message[4] == 0x01) {

            MidiDevice device;
            device.deviceId = message[2];

            std::vector<uint8_t>::const_iterator i = message.begin();

            // manufacturer ID can be 1 or 3 bytes (if first is 0x00)
            device.manufacturerId = *i++;
            if (device.manufacturerId == 0x00) {
                device.manufacturerId = *i << 8 | *(i + 1);
                i += 2;
            }

            device.familyCode = *i << 8 | *(i + 1);
            device.deviceMemberCode = *(i + 2) << 8 | *(i + 3);
            i += 4;

            for (int j = 0; j < sizeof(device.softwareRevision) / sizeof(device.softwareRevision[0]); j++) {
                device.softwareRevision[j] = *i++;
            }

            devices.append(device);
        }
    }
    catch(std::out_of_range) {
        // ignore malformed (too short) messages
        return;
    }
}

void MidiDeviceInquiry::timeout()
{
    disconnect(midi, SIGNAL(receivedSysExMessage(std::vector<uint8_t>)), this, SLOT(receivedSysExMessage(std::vector<uint8_t>)));
    emit deviceInquiryCompleted(devices);
}
