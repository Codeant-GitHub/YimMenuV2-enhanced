//https://github.com/Codeant-GitHub

#pragma once
#include "common.hpp"

#include "DrawVariable.hpp"
#include "Locals.hpp"
#include "core/filemgr/FileMgr.hpp"
#include "game/backend/Self.hpp"
#include "game/pointers/Pointers.hpp"
#include "core/backend/FiberPool.hpp"
#include "game/gta/ScriptFunction.hpp"
#include "game/gta/Natives.hpp"

namespace YimMenu::Submenus
{
	std::shared_ptr<Category> BuildMiscMenu()
	{
		auto misc = std::make_unique<Category>("Misc");

		misc->AddItem(std::make_unique<ImGuiItem>([] {
			if (ImGui::Button("Network Bail"))
			{
				FiberPool::Push([] {
					NETWORK::NETWORK_BAIL(0, 24, 0);
				});
			}

			static int team;
			ImGui::InputInt("Team", &team);
			if (ImGui::Button("fm_mission_controller DoTeamSwap"))
			{
				FiberPool::Push([] {
					static ScriptFunction DoTeamSwap("fm_mission_controller"_J, ScriptPointer("DoTeamSwap", "2D 02 04 00 00 38 00 50"));
					DoTeamSwap.Call<void>(team, true);
				});
			}
		}));

		return misc;
	}
}