#include <QApplication>
#include <iostream>
#include <iomanip>

#include "cmdlistdevices.h"

CmdListDevices::CmdListDevices(MidiIO* midi) :
    QObject()
{
    inquiry = new MidiDeviceInquiry(midi, this);
}

void CmdListDevices::execute()
{
    std::cout << "Devices:" << std::endl;

    connect(inquiry, SIGNAL(deviceInquiryCompleted(QList<MidiDevice>)), this, SLOT(deviceInquiryCompleted(QList<MidiDevice>)));
    inquiry->startDeviceInquiry();
}

void CmdListDevices::deviceInquiryCompleted(const QList<MidiDevice>& devices)
{

    MidiDevice device;
    unsigned int idx = 1;
    foreach(device, devices) {
        std::cout << " " << std::dec << std::setw(2) << idx++ << " ";

        // set integers to be printed as 0xnn, 0 padded
        std::cout << std::showbase << std::internal << std::setfill('0') << std::hex;

        std::cout << std::setw(6) << device.manufacturerId << " ";
        std::cout << std::setw(6) << device.familyCode << " ";
        std::cout << std::setw(6) << device.deviceMemberCode << " ";
        std::cout << std::endl;

    }

    std::cout << std::endl;

    QApplication::exit();
}
