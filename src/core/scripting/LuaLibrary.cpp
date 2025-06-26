//https://github.com/Codeant-GitHub

#pragma once
#include "common.hpp"

#include "LuaLibrary.hpp"
#include "LuaManager.hpp"

namespace YimMenu
{
	LuaLibrary::LuaLibrary()
	{
		LuaManager::RegisterLibrary(this);
	}
}