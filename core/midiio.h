#ifndef MIDIIO_H
#define MIDIIO_H

#include <QObject>
#include <QStringList>
#include "RtMidi.h"

class MidiIO : public QObject
{
    Q_OBJECT
public:
    explicit MidiIO(QObject *parent = 0);
    ~MidiIO();
    
    QStringList availableInputs();
    QStringList availableOutputs();

    void sendMessage(const std::vector<unsigned char> &message);

signals:
    void receivedRealtimeMessage(double timeStamp, const unsigned char status, const unsigned char data1, const unsigned char data2);
    void receivedSysExMessage(const std::vector<unsigned char> &message);

private:
    enum {
        STATUS_SYSEX = 0xF0,
        EOX = 0xF7
    };

    RtMidiIn* rtMidiIn;
    RtMidiOut* rtMidiOut;

    static void rtMidiCallback(double timeStamp, std::vector<unsigned char> *message, void *userData);
    void onMessageReceived(double timeStamp, const std::vector<unsigned char> &message);
};

#endif // MIDIIO_H
