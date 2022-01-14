#pragma once

#include <cstdlib>
#include <algorithm>

template <typename T>
class SimpleVector {
public:
    SimpleVector()
    : data__(new T[0])
    , end__(data__)
    , capacity__(0)
    {}

    explicit SimpleVector(size_t size)
    : data__(new T[size])
    , end__(data__ + size)
    , capacity__(size)
    {}
    
    SimpleVector(const SimpleVector& other)
    : data__(new T[other.Capacity()])
    , end__(data__ + other.Size())
    , capacity__(other.Capacity()) {
        std::copy(other.begin(), other.end(), begin());
    }

    ~SimpleVector() {
      delete[] data__;
    }   
    
    void operator= ( SimpleVector other) {
        //delete[] data__;
        //data__ = new T[other.Capacity()];
        //end__ = data__ + other.Size();
        //capacity__ = other.Capacity();
        //std::copy(other.begin(), other.end(), begin());
        if(capacity__ >= other.Capacity()) {
            std::copy(other.begin(), other.end(), begin());
        } else {
            SimpleVector tmp(other);
            std::swap(tmp.data__, data__);
            std::swap(tmp.end__, end__);
            std::swap(tmp.capacity__, capacity__);
        }
    }

    T& operator[](size_t index) {
      return data__[index];
    }   
    T* begin() {return data__;}
    const T* begin () const {return data__;}
    T* end() {return end__;}
    const T* end() const {return end__;}    
    size_t Size() const {
      return end__ - data__;
    }
    size_t Capacity() const {
      return capacity__;
    }
    bool Empty() {
      return data__ == end__;
    }
    void PushBack(const T& value) {
      if(SimpleVector::Empty()) {
        delete[] data__;
        data__ = new T[1];
        end__ = data__;
        new_value(value);
        capacity__ += 1;
      } else if (SimpleVector::Size() == capacity__) {
        size_t temp_num = capacity__;
        capacity__ *= 2;
        T* temp = new T[capacity__];
        std::copy(SimpleVector::begin(), SimpleVector::end(), temp);
        delete[] data__;
        data__ = temp;
        end__ = data__ + temp_num;
        new_value(value);
      } else {
        new_value(value);   
      }
    }

private:
    T* data__;
    T* end__;
    size_t capacity__;

    void new_value(const T& value) {
      *end__ = value;
      end__ += 1;
    }
};
