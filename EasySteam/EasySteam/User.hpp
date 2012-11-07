#pragma once

#include "CompilerDef.hpp"
#include "ISteamUser016.h"

namespace EasySteam
{
	class EZ_STEAM_API User
	{
	public:

		CSteamID GetSteamID();
		std::string GetUserDirectory(); 
		std::string GetPersonaName();

		bool IsLoggedOn();

	private:

		User(ISteamUser016* pUserImpl);

		ISteamUser016* mUserImpl;

		friend class Interface;
	};
}