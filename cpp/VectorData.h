#ifndef VECTORDATA_H
#define VECTORDATA_H

#include <iterator>
#include <vector>

#include "VectorSignals.h"

template<class Type>
class VectorData: public VectorSignals
{
    using Vector = std::vector<Type>;
public:
    using Iterator = typename std::vector<Type>::iterator;

    VectorData() = default;

    typename Vector::const_iterator begin() const {
        return std::begin(data_);
    }

    typename Vector::const_iterator end() const {
        return std::end(data_);
    }

    typename Vector::iterator begin() {
        return std::begin(data_);
    }

    typename Vector::iterator end() {
        return std::end(data_);
    }

    int size() const {
        return data_.size();
    }

    const Type& operator[](int idx) const {
        return data_[idx];
    }

    const Type& front() const {
        return data_.front();
    }

    const Type& back() const {
        return data_.back();
    }

    int index(typename Vector::iterator pos) const
    {
        return static_cast<int>(pos - begin());
    }

    typename Vector::iterator position(int index)
    {
        return std::next(begin(), index);
    }

    typename Vector::const_iterator position(int index) const
    {
        return std::next(begin(), index);
    }

    typename Vector::iterator push_back(const Type& value) {
        emitPreItemAdded(size());
        data_.push_back(value);
        emitPostItemAdded();
    }

    typename Vector::iterator erase(int idx) {
        emitPreItemRemoved(idx);
        data_.erase(position(idx));
        emitPostItemRemoved();
    }

    typename Vector::iterator erase(typename Vector::iterator pos) {
        emitPreItemRemoved(index(pos));
        data_.erase(pos);
        emitPostItemRemoved();
    }

    typename Vector::iterator insert(int idx, const Type& value) {
        emitPreItemAdded(idx);
        data_.insert(position(idx), value);
        emitPostItemAdded();
    }

    typename Vector::iterator insert(typename Vector::iterator pos, const Type& value) {
        emitPreItemAdded(index(pos));
        data_.insert(pos, value);
        emitPostItemAdded();
    }

    void clear() {
        emitPreClear();
        data_.clear();
        emitPostClear();
    }

private:
    std::vector<Type> data_;
};

#endif // VECTORDATA_H
