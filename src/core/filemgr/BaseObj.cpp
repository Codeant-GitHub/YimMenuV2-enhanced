//https://github.com/Codeant-GitHub

#pragma once
#include "common.hpp"

#include "BaseObj.hpp"

namespace YimMenu
{
	BaseObj::BaseObj(const std::filesystem::path& path) :
	    m_Path(path)
	{
	}

	[[nodiscard]] bool BaseObj::Exists() const
	{
		return exists(m_Path);
	}

	const std::filesystem::path& BaseObj::Path() const
	{
		return m_Path;
	}
}