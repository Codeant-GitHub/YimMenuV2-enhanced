//https://github.com/Codeant-GitHub

#pragma once
#include "common.hpp"

#include "game/commands/PlayerCommand.hpp"
#include "core/commands/FloatCommand.hpp"
#include "game/gta/Entity.hpp"
#include "game/gta/Player.hpp"
#include "game/gta/Pools.hpp"
#include "game/gta/Natives.hpp"
#include "game/backend/Self.hpp"
#include "core/backend/ScriptMgr.hpp"

namespace YimMenu::Features
{
	static FloatCommand m_Radius{
	    "forcefieldradius",
	    "Forcefield Radius",
	    "Radius around the target player where vehicles/peds are pushed away.",
	    20.0f, // default
	    0.0f,  // min
	    100.0f // max
	};

	static FloatCommand m_Magnitude{
	    "forcefieldmagnitude",
	    "Forcefield Magnitude",
	    "Strength of the push away from the target player.",
	    10.0f, // default
	    0.0f,  // min
	    100.0f // max
	};

	void ApplyForcefield(Player player)
	{
		if (!player || !player.GetPed())
			return;

		Vector3 targetCoords = player.GetPed().GetPosition();
		float radius = m_Radius.GetState();
		float magnitude = m_Magnitude.GetState();
		float radiusSq = radius * radius;

		// Vehicles
		for (auto veh : Pools::GetVehicles())
		{
			if (!ENTITY::DOES_ENTITY_EXIST(veh.GetHandle()))
				continue;

			Vector3 pos = ENTITY::GET_ENTITY_COORDS(veh.GetHandle(), false);
			float dx = pos.x - targetCoords.x;
			float dy = pos.y - targetCoords.y;
			float dz = pos.z - targetCoords.z;
			float distSq = dx * dx + dy * dy + dz * dz;

			if (distSq <= radiusSq)
			{
				// Push away instead of pull
				Vector3 dir{dx * magnitude, dy * magnitude, dz * magnitude};

				veh.ForceControl();
				ENTITY::APPLY_FORCE_TO_ENTITY(
				    veh.GetHandle(),
				    2,
				    dir.x,
				    dir.y,
				    dir.z,
				    0.0f,
				    0.0f,
				    0.0f,
				    0,
				    false,
				    true,
				    true,
				    false,
				    false);
			}
		}

		// Peds
		for (auto ped : Pools::GetPeds())
		{
			if (!ENTITY::DOES_ENTITY_EXIST(ped.GetHandle()) || PED::IS_PED_A_PLAYER(ped.GetHandle()))
				continue;

			Vector3 pos = ENTITY::GET_ENTITY_COORDS(ped.GetHandle(), false);
			float dx = pos.x - targetCoords.x;
			float dy = pos.y - targetCoords.y;
			float dz = pos.z - targetCoords.z;
			float distSq = dx * dx + dy * dy + dz * dz;

			if (distSq <= radiusSq)
			{
				// Push away instead of pull
				Vector3 dir{dx * magnitude, dy * magnitude, dz * magnitude};

				ped.ForceControl();
				ENTITY::APPLY_FORCE_TO_ENTITY(
				    ped.GetHandle(),
				    2,
				    dir.x,
				    dir.y,
				    dir.z,
				    0.0f,
				    0.0f,
				    0.0f,
				    0,
				    false,
				    true,
				    true,
				    false,
				    false);
			}
		}

		/* GRAPHICS::DRAW_MARKER_SPHERE(
		    targetCoords.x,
		    targetCoords.y,
		    targetCoords.z,
		    radius,
		    0,
		    255,
		    0,
		    0.3);*/
	}

	class Forcefield : public PlayerCommand
	{
		using PlayerCommand::PlayerCommand;

		std::atomic<bool> m_Enabled{false};
		Player m_TargetPlayer;

	public:
		virtual void OnCall(Player player) override
		{
			if (!player || !player.GetPed())
				return;

			if (m_Enabled && m_TargetPlayer == player)
			{
				m_Enabled = false;
				return;
			}

			m_Enabled = true;
			m_TargetPlayer = player;

				while (m_Enabled)
				{
					ApplyForcefield(m_TargetPlayer);
					ScriptMgr::Yield(100ms); // 100ms between ticks
				}
		}
	};

	static Forcefield _Forcefield{
	    "forcefield",
	    "Forcefield (Togglable)",
	    "Pushes vehicles and peds away from the selected player."};
}
