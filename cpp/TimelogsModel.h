#ifndef TIMELOGMODEL_H
#define TIMELOGMODEL_H

#include "VectorModel.h"
#include "TimelogsData.h"

class TimelogsModel : public VectorModel
{
    Q_OBJECT
    Q_PROPERTY(TimelogsData* timelogs READ timelogs WRITE setTimelogs)
public:
    enum {
        TimelogRole = Qt::UserRole,
        TimespanRole
    };
    explicit TimelogsModel(QObject *parent = nullptr);


    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;

    TimelogsData* timelogs() const;
    void setTimelogs(TimelogsData* timelogs);

private:
    TimelogsData* timelogs_ = nullptr;
};

#endif // TIMELOGMODEL_H
