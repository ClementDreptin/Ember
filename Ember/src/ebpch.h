#pragma once

#include <iostream>
#include <memory>
#include <utility>
#include <algorithm>
#include <functional>

#include <string>
#include <sstream>
#include <array>
#include <vector>
#include <unordered_map>
#include <unordered_set>

#include "Ember/Core/Log.h"
#include "Ember/Debug/Instrumentor.h"

#ifdef EB_PLATFORM_WINDOWS
	#include <Windows.h>
#endif