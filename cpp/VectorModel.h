#ifndef VECTORMODEL_H
#define VECTORMODEL_H

#include <QAbstractListModel>

#include "VectorData.h"

template<class Type>
class VectorModel : public QAbstractListModel
{
public:
    enum {
        DataItem = Qt::UserRole
    };

    explicit VectorModel(QObject *parent = nullptr)
        : QAbstractListModel(parent)
    {
    }

    int rowCount(const QModelIndex &index = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;

protected:
    VectorData<Type>* vector() const;
    void setVector(VectorData<Type>* vector);

private:
    VectorData<Type>* vector_ = nullptr;
};

template<class Type>
int VectorModel<Type>::rowCount(const QModelIndex& index) const
{
    if (index.isValid() || !vector_)
        return 0;

    return vector_->size();
}

template<class Type>
QVariant VectorModel<Type>::data(const QModelIndex& index, int role) const
{
    if (!index.isValid() || !vector_)
        return QVariant();

    switch(role) {
        case DataItem:
            return QVariant::fromValue((*vector_)[index.row()]);
    }

    return QVariant();
}

template<class Type>
QHash<int, QByteArray> VectorModel<Type>::roleNames() const
{
    QHash<int, QByteArray> names;
    names[DataItem] = "item";

    return names;
}

template<class Type>
VectorData<Type>* VectorModel<Type>::vector() const
{
    return vector_;
}

template<class Type>
void VectorModel<Type>::setVector(VectorData<Type>* vector)
{

    beginResetModel();

    if (vector_)
        vector_->disconnect();

    vector_ = vector;

    if (vector_) {
        connect(vector_, &VectorSignals::preItemAdded,
                [this] (int idx) { beginInsertRows(QModelIndex(), idx, idx); });
        connect(vector_, &VectorSignals::postItemAdded,
                [this] { endInsertRows(); });
        connect(vector_, &VectorSignals::preItemRemoved,
                [this] (int idx) { beginRemoveRows(QModelIndex(), idx, idx); });
        connect(vector_, &VectorSignals::postItemRemoved,
                [this] { endRemoveRows(); });
        connect(vector_, &VectorSignals::preClear,
                [this] { beginResetModel(); });
        connect(vector_, &VectorSignals::postClear,
                [this] { endResetModel(); });
    }

    endResetModel();
}

#endif // VECTORMODEL_H
