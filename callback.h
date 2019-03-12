#ifndef CALLBACK_H
#define CALLBACK_H

#endif // CALLBACK_H

#include <QDebug>
#include "userdata.h"
#include "portaudio.h"

namespace sow {

static int callback( const void *inputBuffer,
                     void *outputBuffer,
                     unsigned long framesPerBuffer,
                     const PaStreamCallbackTimeInfo* timeInfo,
                     PaStreamCallbackFlags statusFlags,
                     void *userData )
{
    // Prevent unused parameter warnings.
    Q_UNUSED(timeInfo)
    Q_UNUSED(inputBuffer)
    Q_UNUSED(statusFlags)

    // Cast data passed through stream to our struct.
    UserData *uData = (UserData*)userData;
    float *buffer = (float*) outputBuffer;
    QtSynthItem* root = uData->root;

    // Write interleaved audio data.
    for (unsigned int i=0; i < framesPerBuffer; ++i) {
        Frame frame = root->process();
        frame *= 0.1;
        *buffer++ = frame.left;
        *buffer++ = frame.right;
    }

    root->controlProcess();

    return 0;
}

} // namespace sow
