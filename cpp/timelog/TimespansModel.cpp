#include "TimespansModel.h"

TimespansModel::TimespansModel(QObject* parent)
{

}

TimespansData*TimespansModel::timespans() const
{
    return timespans_;
}

void TimespansModel::setTimespans(TimespansData* timespans)
{
    timespans_ = timespans;
    setVector(timespans_);
}
