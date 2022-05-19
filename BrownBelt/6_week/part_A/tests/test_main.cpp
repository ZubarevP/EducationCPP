#include "test_parse.h"
#include "test_storage.h"
#include "test_request.h"
#include "test_process.h"
#include "test_manager.h"

int main() {
    TestRunner tr;
    RUN_TEST(tr, Test_Parse);
    RUN_TEST(tr, Test_Storage);
    RUN_TEST(tr, Test_Request);
    RUN_TEST(tr, Test_Manager);
    RUN_TEST(tr, Test_Process);
}