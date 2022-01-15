#pragma once

#include <cstdint>
#include <algorithm>
#include <iterator>

#include <iostream>

using namespace std;

template <typename T>
class SimpleVector {
public:
    SimpleVector() = default;

    explicit SimpleVector(size_t size)
    :data__(new T[size])
    ,end__(data__ + size)
    ,capacity__(size)
    {}

    ~SimpleVector(){delete[] data__;}
    T& operator[](size_t index) {return data__[index];}
    T* begin() {return data__;}
    const T* begin() const {return data__;}
    T* end() {return end__;}
    const T* end() const {return end__;}
    size_t Size() const {return end__ - data__;}
    bool Empty() {return data__ == end__;}
    size_t Capacity() const {return capacity__;}

    void PushBack(const T& value) {
      if(Empty()) {
        new_and_swap();
        data__[0] = value;
      } else if (Size() < Capacity()) {
        *(end__++) = value;
      } else {
        size_t temp_num = capacity__;
        capacity__ *= 2;
        T* temp = new T[capacity__];
        copy(begin(), end(), temp);
        delete[] data__;
        data__ = temp;
        end__ = data__ + temp_num;
        *(end__++) = value;
      } 
    }

    void PushBack(T&& value) {
      if(Empty()) {
        new_and_swap();
        data__[0] = move(value);
      } else if (Size() < Capacity()) {
        *(end__++) = move(value);
      } else {
        size_t temp_num = capacity__;
        capacity__ *= 2;
        T* temp = new T[capacity__];
        copy(make_move_iterator(begin()), make_move_iterator(end()), temp);
        delete[] data__;
        data__ = move(temp);
        end__ = data__ + temp_num;
        *(end__++) = move(value);
      } 
    }

private:
    T* data__ = nullptr;
    T* end__ = nullptr;
    size_t capacity__ = 0;

    void new_and_swap() {
        SimpleVector tmp(1);
        swap(tmp.data__, data__);
        swap(tmp.end__, end__);
        swap(tmp.capacity__, capacity__);
    }
};