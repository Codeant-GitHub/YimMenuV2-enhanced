//https://github.com/Codeant-GitHub

#pragma once
#include "common.hpp"

#include "game/commands/PlayerCommand.hpp"
#include "core/backend/ScriptMgr.hpp"
#include "game/gta/Scripts.hpp"
#include "types/script/ScriptEvent.hpp"
#include "types/script/globals/GSBD_RandomEvents.hpp"

namespace YimMenu::Features
{
	class SendGooch : public PlayerCommand
	{
		using PlayerCommand::PlayerCommand;

		virtual void OnCall(Player player) override
		{
			Scripts::ForceScriptHost(Scripts::FindScriptThread("freemode"_J));

			if (auto GSBDRandomEvents = GSBD_RandomEvents::Get())
			{
				SCRIPT_EVENT_REQUEST_RANDOM_EVENT data;
				data.FMMCType = 310;
				data.PlayersToSend = 1;
				data.Send();

				ScriptMgr::Yield();

				GSBDRandomEvents->TargetData.XMASMuggerTarget = player.GetId();
			}
		}
	};

	static SendGooch _SendGooch{"sendgooch", "Send Gooch", "Sends the Gooch to the specified player."};
}