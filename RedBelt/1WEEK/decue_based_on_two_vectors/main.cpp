#include <iostream>
#include <vector>
#include <exception>
#include <algorithm>
#include <string>
#include "test_runner.h"

#define OPER index < back.size() ? back[back.size() - index - 1u] : front[index - back.size()]

using namespace std;

template <typename T>
class Deque {
public:
    Deque() {}
    const bool Empty () const {
        return front.empty() && back.empty();
    }
    const size_t Size () const {
        return front.size() + back.size();
    }
    T& operator[] (size_t index) {
        return OPER;
    }
    const  T& operator[] (size_t index) const {
        return OPER;
    }
    T& Front () {
        if (!back.empty()) {
            return back.back();
        } 
        return front.front();
    }
    const T& Front () const {
        if (!back.empty()) {
            return back.back();
        } 
        return front.front();
    }
    T& Back () {
        if (!front.empty()) {
            return front.back();
        }
        return back.front();
    }
    const T& Back () const {
           if (!front.empty()) {
            return front.back();
        }
        return back.front();
    }
    void PushBack(T value) {
       front.push_back(value);
    }
    void PushFront (T value) {
        back.push_back(value);
    }
    T& At(size_t index) {
        if (index < 0 || index >= front.size() + back.size()) throw out_of_range("out of range");
        return OPER;
    }
    const T& At(size_t index) const {
        if (index < 0 || index >= front.size() + back.size()) throw out_of_range("out of range");
        return OPER;
    }
    
    void Clear() {
        front.clear();
        back.clear();
    }
    void Print() {
        cout << "back: ";
        for (int i = back.size() - 1; i >= 0; i--) {
            cout << back[i] << " ";
        }
        cout << endl;
        cout << "front: ";
        for (int j = 0; j < front.size(); j++) {
            cout << front[j] << " ";
        }
        cout << endl << endl;
    }
    
private:
    vector<T> front;
    vector<T> back;
};

void TestDeque() {
    Deque<int> ex;
    ASSERT_EQUAL(ex.Empty(), true);
    ASSERT_EQUAL(ex.Size(), 0);
    for (int i = 0; i < 8; i++) {
        ex.PushBack(i);
    }
    ex.Print();
    ASSERT_EQUAL(ex.Empty(), false);
    ASSERT_EQUAL(ex.Size(), 8);
    ASSERT_EQUAL(ex[3], 3);
    ASSERT_EQUAL(ex.Front(), 0);
    ASSERT_EQUAL(ex.Back(), 7);
    ex.PushFront(99);
    ex.Print();
    ASSERT_EQUAL(ex[0], 99);
    ASSERT_EQUAL(ex.Front(), 99);
    ASSERT_EQUAL(ex.Back(), 7);
    ASSERT_EQUAL(ex.At(0), 99);
    Deque<int> ll;
}

int main(){
    TestRunner tr;
    RUN_TEST(tr, TestDeque);
    return 0;
}