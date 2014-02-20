#include "midiio.h"

MidiIO::MidiIO(QObject *parent) :
    QObject(parent), rtMidiIn(NULL), rtMidiOut(NULL)
{
    rtMidiIn = new RtMidiIn();
    rtMidiOut = new RtMidiOut();
    rtMidiIn->setCallback(MidiIO::rtMidiCallback, this);
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

void MidiIO::sendMessage(const std::vector<unsigned char> &message)
{
    rtMidiOut->sendMessage(const_cast<std::vector<unsigned char>*>(&message));
}

void MidiIO::rtMidiCallback(double timeStamp, std::vector<unsigned char> *message, void *userData)
{
    MidiIO *self = static_cast<MidiIO*>(userData);
    self->onMessageReceived(timeStamp, *message);
}

void MidiIO::onMessageReceived(double timeStamp, const std::vector<unsigned char> &message)
{
    size_t size = message.size();
    if (size > 0) {
        const unsigned char status = message[0];
        if (status == STATUS_SYSEX && size > 2 && message[size - 1] == EOX) {
            emit receivedSysExMessage(message);
        }
        else if ((size == 2 || size == 3) && message[0] != 0x7F) {
            emit receivedRealtimeMessage(timeStamp, status, message[1], size > 2 ? message[2] : 0);
        }
        else {
            /* Ignored for now - unexpected message format */
        }

    }
}
