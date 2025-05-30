#pragma once

#include <AsyncLogger/Logger.hpp>
#include <MinHook.h>
#include <windows.h>
#include <array>
#include <atomic>
#include <chrono>
#include <cstddef>
#include <filesystem>
#include <fstream>
#include <functional>
#include <future>
#include <imgui.h>
#include <iostream>
#include <map>
#include <memory>
#include <string_view>
#include <thread>
#include <vector>
#include <stack>
#include <unordered_set>

#include <nlohmann/json.hpp>

using namespace al;
#include "core/logger/LogHelper.hpp"

#undef Yield

namespace YimMenu
{
	using namespace std::chrono_literals;
	using namespace std::string_view_literals;

	extern std::atomic<bool> g_Running;
	extern HINSTANCE g_DllInstance;
	extern HANDLE g_MainThread;
	extern DWORD g_MainThreadId;
}