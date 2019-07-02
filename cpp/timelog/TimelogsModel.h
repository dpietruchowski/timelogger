#ifndef TIMELOGMODEL_H
#define TIMELOGMODEL_H

#include "VectorModel.h"
#include "TimelogsData.h"

class TimelogsModel : public VectorModel<Timelog>
{
    Q_OBJECT
    Q_PROPERTY(TimelogsData* timelogs READ timelogs WRITE setTimelogs)
public:
    explicit TimelogsModel(QObject *parent = nullptr);

    TimelogsData* timelogs() const;
    void setTimelogs(TimelogsData* timelogs);

private:
    TimelogsData* timelogs_ = nullptr;
};

#endif // TIMELOGMODEL_H
