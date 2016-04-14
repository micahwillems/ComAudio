#ifndef AUDIOMANAGER_H
#define AUDIOMANAGER_H

#include <QAudioFormat>
#include <QAudioOutput>
#include <QFile>
#include <QDebug>
#include <QMetaType>
#include <QAudioInput>
#include "win32communicationworker.h"
#include "wavheader.h"
#include "songstate.h"
#include "circularbuffer.h"
#include "readfileworker.h"
#include "populatebufferworker.h"
#include "Client.h"

extern QAudioInput * audio;
extern QPalette palette;

extern QAudioInput * audioFile;
extern CircularBuffer * cb, *circularBufferRecv, *micBuf;
extern QBuffer *microphoneBuffer, *listeningBuffer;

extern QAudioInput *audio;

//Carson
class AudioManager : public QObject {
Q_OBJECT
public:
    AudioManager(QObject * parent);
    ~AudioManager();

    void pause();
    void resume();
    void skip(float seconds);
    QIODevice * play();
    void setVolume(float volume);
    void loadSong(QFile * file);
    void stop();
    void Init(QBuffer * buf, CircularBuffer * circ);

public slots:
    void receivedWavHeader(wav_hdr wavHeader);
    void playRecord();

private:
    QAudioFormat format;
    QAudioOutput *audioOutput;
    QObject *parent;
    QFile *file;
    QIODevice *device;
    float volume = 10;
    SongState songState;
    CircularBuffer *circularBuffer;
    QBuffer *buffer;
    ReadFileWorker *readFileWorker;
    PopulateBufferWorker *populateBufferWorker;
    Win32CommunicationWorker *win32CommunicationWorker;
    QThread readWorkerThread;
    QThread populateBufferThread;
    QThread win32CommunicationThread;
    int bytesPerSecond;
};

extern AudioManager *audioManager;

#endif // AUDIOMANAGER_H
