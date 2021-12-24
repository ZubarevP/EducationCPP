#pragma once

#include <array>
#include <stdexcept>
using namespace std;

template <typename T, size_t N>
class StackVector {
public:
  explicit StackVector(size_t a_size = 0)
  :max_num(a_size)
  {
    if (a_size > N) {throw invalid_argument("invalid argument.");}
  }

  void PushBack(const T& value) {
    if (Capacity() == Size()) {throw overflow_error("overflow stack.");}
    stack[max_num++] = value;
  }
  T PopBack() {
    if (StackVector::begin() == StackVector::end()) {throw underflow_error("underflow stack.");}
    return stack[--max_num];
  }


  size_t Size() const {return max_num;}
  size_t Capacity() const {return stack.size();}
  T& operator[](size_t index){ return stack[index];}
  const T& operator[](size_t index) const {return stack[index];}
  T* begin(){return stack.data();}
  T* end() {return stack.data() + max_num;}
  const T* begin() const{return stack.data();}
  const T* end() const {return stack.data() + max_num;}
private:
  array<T, N> stack;
  size_t max_num;
};