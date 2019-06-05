#include "TimelogsModel.h"

TimelogsModel::TimelogsModel(QObject* parent)
    : QAbstractListModel(parent)
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
        case TimeSpanRole:
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
    names[TimeSpanRole] = "timespan";

    return names;
}

TimelogsData* TimelogsModel::timelogs() const
{
    return timelogs_;
}

void TimelogsModel::setTimelogs(TimelogsData* timelogs)
{
    beginResetModel();

    if (timelogs_)
        timelogs_->disconnect();

    timelogs_ = timelogs;

    if (timelogs_) {
        connect(timelogs_, &TimelogsData::preLogAdded,
                [this] (int idx) { beginInsertRows(QModelIndex(), idx, idx); });
        connect(timelogs_, &TimelogsData::postLogAdded,
                [this] { endInsertRows(); });
        connect(timelogs_, &TimelogsData::preLogRemoved,
                [this] (int idx) { beginRemoveRows(QModelIndex(), idx, idx); });
        connect(timelogs_, &TimelogsData::postLogRemoved,
                [this] { endRemoveRows(); });
        connect(timelogs_, &TimelogsData::preClear,
                [this] { beginResetModel(); });
        connect(timelogs_, &TimelogsData::postClear,
                [this] { endResetModel(); });
    }

    endResetModel();
}
