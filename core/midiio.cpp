#include "midiio.h"

MidiIO::MidiIO(QObject *parent) :
    rtMidiIn(NULL), rtMidiOut(NULL)
{
    rtMidiIn = new RtMidiIn();
    rtMidiOut = new RtMidiOut();
}

MidiIO::~MidiIO()
{
    delete rtMidiIn;
    delete rtMidiOut;
}

QStringList MidiIO::availableInputs()
{
    unsigned int nPorts = rtMidiIn->getPortCount();
    QStringList ports;
    for (unsigned int i = 0; i < nPorts; i++) {
        ports.append(QString::fromLatin1(rtMidiIn->getPortName(i).c_str()));
    }
    return ports;
}

QStringList MidiIO::availableOutputs()
{
    unsigned int nPorts = rtMidiOut->getPortCount();
    QStringList ports;
    for (unsigned int i = 0; i < nPorts; i++) {
        ports.append(QString::fromLatin1(rtMidiOut->getPortName(i).c_str()));
    }
    return ports;
}
