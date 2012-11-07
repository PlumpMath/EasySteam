#include "Friend.hpp"
#include "Friends.hpp"
#include "Interface.hpp"


namespace EasySteam
{
	Friend::Friend(CSteamID pId)
		:mFriends(Interface::GetInstance()->GetFriends()), mId(pId)
	{
	}

	Friend::~Friend()
	{
	}

	std::string Friend::GetPersonaName()
	{
		return std::move(mFriends->GetPersonaName(mId));
	}

	CSteamID Friend::GetSteamID()
	{
		return mId;
	}

	Avatar::pointer Friend::GetAvatar(Avatar::Size pSize)
	{
		return Avatar::pointer(new Avatar(this, pSize));
	}

	void Friend::SendMessage(const std::string& pMessage)
	{
		mFriends->SendMessage(mId, pMessage);
	}

	
}