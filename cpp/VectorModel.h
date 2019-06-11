#ifndef VECTORMODEL_H
#define VECTORMODEL_H

#include <QAbstractListModel>

#include "VectorSignals.h"

class VectorModel : public QAbstractListModel
{
public:
    VectorModel(QObject *parent = nullptr);

protected:
    VectorSignals* vector() const;
    void setVector(VectorSignals* vector);

private:
    VectorSignals* vector_ = nullptr;
};

#endif // VECTORMODEL_H
