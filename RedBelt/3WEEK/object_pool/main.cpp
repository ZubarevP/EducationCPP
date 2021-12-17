#include "test_runner.h"

#include <algorithm>
#include <iostream>
#include <string>
#include <queue>
#include <stdexcept>
#include <set>
using namespace std;

template <class T>
class ObjectPool {
public:
  T* Allocate() {
    if (dealloc_.empty()) {
      T *object = new T;
      alloc_.insert(object);
      return object;
    } else {
      alloc_.insert(dealloc_.front());
      T *temp = dealloc_.front();
      dealloc_.pop();
      return temp;
    }
  }
  T* TryAllocate(){
    if (dealloc_.empty()) {
      return nullptr;
    } else {
      alloc_.insert(dealloc_.front());
      T *temp = dealloc_.front();
      dealloc_.pop();
      return temp;
    }
  }
  void Deallocate(T* object) {
    if (alloc_.count(object)) {
      dealloc_.push(object);
      alloc_.erase(object);
    } else {
      throw invalid_argument("-> invalid");
    }
  }

  ~ObjectPool() {
    for (auto key : alloc_) {
      delete key;
    }
    while(!dealloc_.empty()){
      delete dealloc_.front();
      dealloc_.pop();
    }
  }
private:
set<T*> alloc_;
queue<T*> dealloc_;
};

void TestObjectPool() {
  ObjectPool<string> pool;

  auto p1 = pool.Allocate();
  auto p2 = pool.Allocate();
  auto p3 = pool.Allocate();

  *p1 = "first";
  *p2 = "second";
  *p3 = "third";
  pool.Deallocate(p2);
  ASSERT_EQUAL(*pool.Allocate(), "second");

  pool.Deallocate(p3);
  pool.Deallocate(p1);
  ASSERT_EQUAL(*pool.Allocate(), "third");
  ASSERT_EQUAL(*pool.Allocate(), "first");

  pool.Deallocate(p1);
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  TestRunner tr;
  RUN_TEST(tr, TestObjectPool);
  return 0;
}