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

    Type& operator[](int idx) {
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

    typename Vector::iterator position(int idx)
    {
        return std::next(begin(), idx);
    }

    typename Vector::const_iterator position(int idx) const
    {
        return std::next(begin(), idx);
    }

    typename Vector::iterator push_back(const Type& value) {
        int idx = size();
        emitPreItemAdded(idx);
        data_.push_back(value);
        emitPostItemAdded(idx);
    }

    typename Vector::iterator erase(int idx) {
        emitPreItemRemoved(idx);
        data_.erase(position(idx));
        emitPostItemRemoved(idx);
    }

    typename Vector::iterator erase(typename Vector::iterator pos) {
        int idx = index(pos);
        emitPreItemRemoved(idx);
        data_.erase(pos);
        emitPostItemRemoved(idx);
    }

    typename Vector::iterator insert(int idx, const Type& value) {
        emitPreItemAdded(idx);
        data_.insert(position(idx), value);
        emitPostItemAdded(idx);
    }

    typename Vector::iterator insert(typename Vector::iterator pos, const Type& value) {
        int idx = index(pos);
        emitPreItemAdded(idx);
        data_.insert(pos, value);
        emitPostItemAdded(idx);
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
