#ifndef CMDLISTDEVICES_H
#define CMDLISTDEVICES_H

#include <QObject>

#include "midideviceinquiry.h"
#include "midiio.h"

class CmdListDevices : public QObject
{
    Q_OBJECT

public:
    CmdListDevices(MidiIO* midi);

    virtual void execute();

private slots:
    void deviceInquiryCompleted(const QList<MidiDevice>& devices);

private:
    MidiDeviceInquiry* inquiry;

};

#endif // CMDLISTDEVICES_H
