#include "utility.h"
#include "math.h"

namespace sow {

// based on the Max "Scale" object
// https://docs.cycling74.com/max7/maxobject/scale
// default exp = 1 is linear scaling
double scale(double x, double in_low, double in_high, double out_low, double out_high, double exp)
{
    return ((x-in_low)/(in_high-in_low) == 0.0) ? out_low : (((x-in_low)/(in_high-in_low)) > 0.0) ? (out_low + (out_high-out_low) * pow(((x-in_low)/(in_high-in_low)),exp)) : ( out_low + (out_high-out_low) * -(pow((((-x+in_low)/(in_high-in_low))),exp)));
}

//Frame visitChildren(QVector<QtSynthItem *> children)
//{
//    Frame frame;
//    for (int i = 0; i < children.size(); ++i)
//    {
//        QtSynthItem* gen = children[i];
//        frame += gen->process();
//    }
//    frame /= children.size();
//    return frame;
//}




}// namespace sow
