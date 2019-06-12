#include "VectorSignals.h"

void VectorSignals::emitPreClear()
{
    emit preClear();
}

void VectorSignals::emitPostClear()
{
    emit postClear();
}

void VectorSignals::emitPreItemAdded(int idx)
{
    emit preItemAdded(idx);
}

void VectorSignals::emitPostItemAdded(int idx)
{
    emit postItemAdded(idx);
}

void VectorSignals::emitPreItemRemoved(int idx)
{
    emit preItemRemoved(idx);
}

void VectorSignals::emitPostItemRemoved(int idx)
{
    emit postItemRemoved(idx);
}
