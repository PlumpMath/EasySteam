#include "Friend.hpp"
#include "Friends.hpp"


namespace EasySteam
{
	Friend::Friend(class Friends* pFriends, CSteamID pId)
		:mFriends(pFriends), mId(pId)
	{

	}

	std::string Friend::GetPersonaName()
	{
		return std::move(mFriends->GetPersonaName(mId));
	}
}