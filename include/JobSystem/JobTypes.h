#pragma once

namespace std { class mutex; }
class Graph;
class IStatisticCalculator;

#include <functional>

typedef std::function<void(void)> Job;