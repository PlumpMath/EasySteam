#include "User.hpp"
#include "Interface.hpp"

namespace EasySteam
{
	User::User(ISteamUser016* pUserImpl)
		:mUserImpl(pUserImpl)
	{
	}

	CSteamID User::GetSteamID()
	{
		return mUserImpl->GetSteamID();
	}

	std::string User::GetUserDirectory()
	{
		std::string dir;
		dir.resize(2048);

		mUserImpl->GetUserDataFolder(&dir[0], 2048);

		return dir;
	}

	std::string User::GetPersonaName()
	{
		return std::move(std::string(Interface::GetInstance().GetFriends()->GetPersonaName(GetSteamID())));
	}
}