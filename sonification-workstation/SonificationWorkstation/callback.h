#ifndef CALLBACK_H
#define CALLBACK_H

#endif // CALLBACK_H

#include <QDebug>
#include "userdata.h"
#include "Gamma/AudioIO.h"

using namespace gam;

namespace sow {

void callback(AudioIOData& io)
{

    // Cast data passed through stream to our struct.
    UserData& uData = io.user<UserData>();
    SynthItem* root = uData.root;

    while(io()) {
        Frame frame = root->process();
        io.out(0) = frame.left;
        io.out(1) = frame.right;
    }

    root->controlProcess();

}

} // namespace sow
