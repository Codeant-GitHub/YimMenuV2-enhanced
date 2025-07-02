//https://github.com/Codeant-GitHub

#pragma once
#include "common.hpp"

#include "LuaUserInterface.hpp"

namespace YimMenu::Lua
{
	UIElementBase::UIElementBase(LuaUserInterface& interface) :
	    m_Interface(interface)
	{
	}
}