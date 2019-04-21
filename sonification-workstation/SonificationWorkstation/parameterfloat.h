#ifndef PARAMETERFLOAT_H
#define PARAMETERFLOAT_H

#include "parameter.h"
#include "mapevaluator.h"
#include "utility.h"

namespace sow {

class ParameterFloat : public Parameter
{
    Q_OBJECT
public:

    explicit ParameterFloat(QObject *parent = nullptr);

    float value();
    void setData(const Dataset* dataset, const std::vector<float>* currentData) override;
    bool setMap(const QString map);

protected:

    virtual void processCommand(const ParameterCommand cmd) override;

private:

    // Backing variables.
    QString name_ = "";
    bool scale_ = true;
    float scaleOutLow_ = 200.0f;
    float scaleOutHigh_ = 8000.0f;
    float scaleExponent_ = 1.0f;
    QString map_ = "";
    std::vector<float>* data_ = nullptr;
    std::vector<float>* mins_ = nullptr;
    std::vector<float>* maxes_ = nullptr;

    // Map expression evaulator.
    MapEvaluator<float> mapEvaluator_;

    virtual void processSetMap(std::string expression);

};

} // namespace sow

#endif // PARAMETERFLOAT_H
