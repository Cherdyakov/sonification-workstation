#ifndef SYNTHCOMMAND_H
#define SYNTHCOMMAND_H

#include <vector>

namespace son {

enum SynthCommandType {
    PAUSE,
    POSITION,
    SPEED,
    LOOP,
    LOOP_BEGIN,
    LOOP_END,
    DATA
};

typedef struct {

    SynthCommandType command;
    bool paused;
    double pos;
    double speed;
    bool loop;
    double loopBegin;
    double loopEnd;
    std::vector<double>* data;
    unsigned int height;
    unsigned int width;

} SynthCommand;

} //namespace son

#endif // SYNTHCOMMAND_H
