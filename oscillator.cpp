#include "oscillator.h"

namespace son {

Oscillator::Oscillator()
{
    gen = new gam::Sine<>(440);
    gens.push_back(gen);
}

float Oscillator::process()
{
    float s = 0.0;

//    QVector<gam::Sine<>*>::const_iterator i;

//    for (i = gens.constBegin(); i != gens.constEnd(); ++i)
//    {
//        gam::Sine<>* sine = *i;
//        s += sine->operator ()();
//    }

      s = gen->operator ()();

//    qDebug() << gen->operator ()();

    //test noise
//    s = ((qrand() * 1.0 / RAND_MAX) - 1.0) * 0.2;
    //test mssg
    //qDebug() << "processGraph";

    return s;
}

}
