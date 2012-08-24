#pragma once

#include "CompilerDef.hpp"
#include <Steamworks.h>

namespace EasySteam
{
	class EZ_STEAM_API Friend : public std::enable_shared_from_this<Friend>
	{
	public:

		typedef std::shared_ptr<Friend> pointer;

		std::string GetPersonaName();

		void SendMessage(const std::string& pMessage);

		CSteamID GetSteamID();

	private:

		Friend(class Friends* pFriends, CSteamID pId);

		class Friends* mFriends;
		CSteamID mId;
		friend class Friends;
	};
}