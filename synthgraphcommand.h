#ifndef SYNTHGRAPHCOMMAND_H
#define SYNTHGRAPHCOMMAND_H

namespace son {

enum class SynthGraphCommandType {
    PAUSE,
    POSITION,
    SPEED,
    LOOP,
    LOOP_POINTS,
    DATA
};

typedef struct {

    SynthGraphCommandType type;
    bool paused;
    double pos;
    double speed;
    bool looping;
    double loopBegin;
    double loopEnd;
    std::vector<double>* data;
    unsigned int height;
    unsigned int width;

} SynthGraphCommand;

} //namespace son

#endif // SYNTHGRAPHCOMMAND_H
