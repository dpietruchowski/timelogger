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
    void emitPreItemAdded(int index);
    void emitPostItemAdded();
    void emitPreItemRemoved(int index);
    void emitPostItemRemoved();

signals:
    void preClear();
    void postClear();
    void preItemAdded(int index);
    void postItemAdded();
    void preItemRemoved(int index);
    void postItemRemoved();
};

#endif // VECTORSIGNALS_H
