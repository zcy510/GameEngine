#pragma once

#include <iostream>
#include <memory>
#include <utility>
#include <algorithm>
#include<functional>
#include <sstream>
#include <array>
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>

#include "Taro/Core/Log.h"
#include "Taro/Debug/Instrumentor.h"

#ifdef TR_PLATFORM_WINDOWS
	#include <Windows.h>
#endif