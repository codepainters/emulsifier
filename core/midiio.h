#ifndef MIDIIO_H
#define MIDIIO_H

#include <QObject>
#include <QStringList>
#include <inttypes.h>

#include "RtMidi.h"

typedef std::vector<uint8_t> MidiMessageData;

class MidiIO : public QObject
{
    Q_OBJECT
public:
    explicit MidiIO(QObject *parent = 0);
    ~MidiIO();
    
    QStringList availableInputs();
    QStringList availableOutputs();

    void selectInput(unsigned int input);
    void selectOutput(unsigned int output);

    void sendMessage(const uint8_t* message, size_t length);
    void sendMessage(const std::vector<uint8_t> &message);

signals:
    void receivedRealtimeMessage(double timeStamp, const uint8_t status, const uint8_t data1, const uint8_t data2);
    void receivedSysExMessage(const MidiMessageData &message);

private:
    enum {
        STATUS_SYSEX = 0xF0,
        EOX = 0xF7
    };

    RtMidiIn* rtMidiIn;
    RtMidiOut* rtMidiOut;

    static void rtMidiCallback(double timeStamp, std::vector<unsigned char> *message, void *userData);
    void onMessageReceived(double timeStamp, const MidiMessageData &message);
};

#endif // MIDIIO_H
