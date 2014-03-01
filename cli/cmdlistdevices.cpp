#include <QApplication>
#include <iostream>

#include "cmdlistdevices.h"

CmdListDevices::CmdListDevices(MidiIO* midi) :
    QObject()
{
    inquiry = new MidiDeviceInquiry(midi, this);
}

void CmdListDevices::execute()
{
    connect(inquiry, SIGNAL(deviceInquiryCompleted(QList<MidiDevice>)), this, SLOT(deviceInquiryCompleted(QList<MidiDevice>)));
    inquiry->startDeviceInquiry(5000);
}

void CmdListDevices::deviceInquiryCompleted(const QList<MidiDevice>& devices)
{
    std::cout << "Devices:" << std::endl;

    QApplication::exit();
}
