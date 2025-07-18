//https://github.com/Codeant-GitHub

#pragma once
#include "common.hpp"

#include "core/commands/LoopedCommand.hpp"
#include "game/pointers/Pointers.hpp"
#include "game/gta/ScriptGlobal.hpp"

namespace YimMenu::Features
{
	class UnlockGTAPlus : public LoopedCommand
	{
		using LoopedCommand::LoopedCommand;

		bool m_OldGTAPlus;

		virtual void OnEnable() override
		{
			m_OldGTAPlus = *Pointers.HasGTAPlus;
		}

		virtual void OnTick() override
		{
			*Pointers.HasGTAPlus = true;
			*ScriptGlobal(1965683).As<bool*>() = true;
			*ScriptGlobal(1965683).At(3).As<int*>() = (1 << 3) | (1 << 1);
		}

		virtual void OnDisable() override
		{
			*Pointers.HasGTAPlus = m_OldGTAPlus;
		}
	};

	static UnlockGTAPlus _UnlockGTAPlus{"unlockgtaplus", "Unlock GTA+", "Force-unlocks GTA+ content. Use with caution"};
}