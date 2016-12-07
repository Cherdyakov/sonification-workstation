#ifndef USERDATA_H
#define USERDATA_H

#endif // USERDATA_H

#include "mainwindow.h"
#include "synthgraph.h"
#include "Gamma/Oscillator.h"
#include "sequencer.h"

namespace son {

typedef struct {
    SynthGraph* graph;
    Sequencer* seq;

} UserData;

} //namespace son
