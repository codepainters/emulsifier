#ifndef MIDIIO_H
#define MIDIIO_H

#include <QObject>
#include <QStringList>
#include "RtMidi.h"

class MidiIO
{
public:
    explicit MidiIO(QObject *parent = 0);
    ~MidiIO();
    
    QStringList availableInputs();
    QStringList availableOutputs();
    
private:
    RtMidiIn* rtMidiIn;
    RtMidiOut* rtMidiOut;
};

#endif // MIDIIO_H
