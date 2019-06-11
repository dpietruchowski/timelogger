#include "VectorSignals.h"

void VectorSignals::emitPreClear()
{
    emit preClear();
}

void VectorSignals::emitPostClear()
{
    emit postClear();
}

void VectorSignals::emitPreItemAdded(int index)
{
    emit preItemAdded(index);
}

void VectorSignals::emitPostItemAdded()
{
    emit postItemAdded();
}

void VectorSignals::emitPreItemRemoved(int index)
{
    emit preItemRemoved(index);
}

void VectorSignals::emitPostItemRemoved()
{
    emit postItemRemoved();
}
