#ifndef VECTORSIGNALS_H
#define VECTORSIGNALS_H

#include <QObject>

class VectorSignals : public QObject
{
    Q_OBJECT
public:
    VectorSignals() = default;

protected:
    void emitPreClear();
    void emitPostClear();
    void emitPreItemAdded(int idx);
    void emitPostItemAdded(int idx);
    void emitPreItemRemoved(int idx);
    void emitPostItemRemoved(int idx);
    void emitDataChanged(int idx);

signals:
    void preClear();
    void postClear();
    void preItemAdded(int idx);
    void postItemAdded(int idx);
    void preItemRemoved(int idx);
    void postItemRemoved(int idx);
    void dataChanged(int idx);
};

#endif // VECTORSIGNALS_H
