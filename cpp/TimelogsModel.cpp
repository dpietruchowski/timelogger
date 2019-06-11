#include "TimelogsModel.h"

TimelogsModel::TimelogsModel(QObject* parent)
    : VectorModel(parent)
{

}

int TimelogsModel::rowCount(const QModelIndex& parent) const
{
    if (parent.isValid() || !timelogs_)
        return 0;

    return timelogs_->size();
}

QVariant TimelogsModel::data(const QModelIndex& index, int role) const
{
    if (!index.isValid() || !timelogs_)
        return QVariant();

    int idx = index.row();
    Timelog timelog = (*timelogs_)[idx];

    switch(role) {
        case TimelogRole:
            return QVariant::fromValue(timelog);
        case TimespanRole:
            int nextIdx = idx + 1;
            if (nextIdx == timelogs_->size())
                --nextIdx;
            Timelog nextTimelog = (*timelogs_)[nextIdx];
            return QVariant::fromValue(timelog.timespan(nextTimelog));
    }

    return QVariant();
}

QHash<int, QByteArray> TimelogsModel::roleNames() const
{
    QHash<int, QByteArray> names;
    names[TimelogRole] = "timelog";
    names[TimespanRole] = "timespan";

    return names;
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
