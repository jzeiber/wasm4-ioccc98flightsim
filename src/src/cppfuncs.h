#pragma once

#include <stddef.h>

template<size_t N, class T>
constexpr size_t countof(T(&)[N]) { return N; }
