#ifndef SYNTHCOMMAND_H
#define SYNTHCOMMAND_H

#include <vector>

namespace son {

enum SynthCommandType {
    PAUSE,
    POSITION,
    SPEED,
    LOOP,
    LOOP_POINTS,
    DATA
};

typedef struct {

    SynthCommandType type;
    bool paused;
    double pos;
    double speed;
    bool looping;
    double loopBegin;
    double loopEnd;
    std::vector<double>* data;
    unsigned int height;
    unsigned int width;

} SynthCommand;

} //namespace son

#endif // SYNTHCOMMAND_H
