#ifndef TIMESPANSMODEL_H
#define TIMESPANSMODEL_H

#include "VectorModel.h"
#include "TimespansData.h"

class TimespansModel : public VectorModel<Timespan>
{
    Q_OBJECT
    Q_PROPERTY(TimespansData* timespans READ timespans WRITE setTimespans)
public:
    explicit TimespansModel(QObject *parent = nullptr);

    TimespansData* timespans() const;
    void setTimespans(TimespansData* timespans);

private:
    TimespansData* timespans_ = nullptr;
};

#endif // TIMESPANSMODEL_H
