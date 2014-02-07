#include <QCoreApplication>
#include <QDebug>

#include "midiio.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    MidiIO midi;

    QStringList ports = midi.availableInputs();
    foreach(QString port, ports)
        qDebug() << port << endl;

    return a.exec();
}
