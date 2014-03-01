#include <QCoreApplication>
#include <iostream>

#include "midiio.h"
#include "cmdlistdevices.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    MidiIO midi;

    QStringList ports = midi.availableInputs();
    std::cout << "MIDI INs:" << std::endl;
    foreach(QString port, ports)
        std::cout << " " << port.toUtf8().constData() << std::endl;
    std::cout << std::endl;

    ports = midi.availableOutputs();
    std::cout << "MIDI OUTs:" << std::endl;
    foreach(QString port, ports)
        std::cout << " " << port.toUtf8().constData() << std::endl;
    std::cout << std::endl;

    midi.selectInput(2);
    midi.selectOutput(6);

    CmdListDevices cmd(&midi);
    cmd.execute();

    return a.exec();
}
