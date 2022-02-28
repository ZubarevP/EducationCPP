#include "test_runner.h"

#include <functional>
#include <optional>
#include <string>
#include <utility>

using namespace std;

template <typename T>
class LazyValue {
public:
    explicit LazyValue(std::function<T()> init)
        :_init(move(init))
    {
    }

    bool HasValue() const {
        if(object) return true;
        return false;
    }
    const T& Get() const {
        if(!object)  object = _init();
        return  *object;
    }

private:
    function<T()> _init;
    mutable optional<T> object;
};

void UseExample() {
    const string big_string = "Giant amounts of memory";

    LazyValue<string> lazy_string([&big_string] { return big_string; });

    ASSERT(!lazy_string.HasValue());
    ASSERT_EQUAL(lazy_string.Get(), big_string);
    ASSERT_EQUAL(lazy_string.Get(), big_string);
}

void TestInitializerIsntCalled() {
    bool called = false;

    {
        LazyValue<int> lazy_int([&called] {
            called = true;
            return 0;
        });
    }
    ASSERT(!called);
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, UseExample);
    RUN_TEST(tr, TestInitializerIsntCalled);
    return 0;
}
