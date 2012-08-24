#pragma once

#include "CompilerDef.hpp"
#include <Steamworks.h>
#include "Avatar.hpp"

namespace EasySteam
{
	class EZ_STEAM_API Friend : public std::enable_shared_from_this<Friend>
	{
	public:

		typedef std::shared_ptr<Friend> pointer;

		~Friend();

		std::string GetPersonaName();
		CSteamID GetSteamID();
		Avatar::pointer GetAvatar(Avatar::Size pSize);

		void SendMessage(const std::string& pMessage);

	private:

		Friend(CSteamID pId);

		class Friends*	mFriends;
		CSteamID		mId;

		friend class Friends;
	};
}