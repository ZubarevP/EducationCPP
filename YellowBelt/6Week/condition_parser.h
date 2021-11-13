#pragma once

#include "node.h"
#include "database.h"
#include "date.h"

#include <memory>
#include <iostream>

using namespace std;

extern int g_num_of_var;

shared_ptr<Node> ParseCondition(istream& is);

void TestParseCondition();