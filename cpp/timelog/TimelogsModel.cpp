#include "TimelogsModel.h"

TimelogsModel::TimelogsModel(QObject* parent)
    : VectorModel(parent)
{

}

TimelogsData* TimelogsModel::timelogs() const
{
    return timelogs_;
}

void TimelogsModel::setTimelogs(TimelogsData* timelogs)
{
    timelogs_ = timelogs;
    setVector(timelogs_);
}
