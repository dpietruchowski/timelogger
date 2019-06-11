#include "VectorModel.h"

VectorModel::VectorModel(QObject* parent)
    : QAbstractListModel(parent)
{

}

VectorSignals*VectorModel::vector() const
{
    return vector_;
}

void VectorModel::setVector(VectorSignals* vector)
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
