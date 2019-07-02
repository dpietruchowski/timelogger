#ifndef TIMESPANSDATA_H
#define TIMESPANSDATA_H

#include "Timespan.h"
#include "VectorData.h"

class TimespansData : public VectorData<Timespan>
{
public:
    TimespansData() = default;
};

#endif // TIMESPANSDATA_H
