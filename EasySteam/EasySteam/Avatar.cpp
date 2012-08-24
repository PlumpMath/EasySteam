#include "Friend.hpp"
#include "Avatar.hpp"
#include "Friends.hpp"
#include "Interface.hpp"


namespace EasySteam
{
	Avatar::Avatar(Friend* pFriend, Size pSize)
		:mFriend(pFriend), mSize(pSize)
	{
	}

	Avatar::~Avatar()
	{
	}

	Avatar::Size Avatar::GetSize()
	{
		return mSize;
	}

	int Avatar::GetImageId()
	{
		if(mSize == SMALL)
			return Interface::GetInstance().GetFriends()->mFriendsImpl->GetSmallFriendAvatar(mFriend->GetSteamID());
		else if(mSize == MEDIUM)
			return Interface::GetInstance().GetFriends()->mFriendsImpl->GetMediumFriendAvatar(mFriend->GetSteamID());
		else
			return Interface::GetInstance().GetFriends()->mFriendsImpl->GetLargeFriendAvatar(mFriend->GetSteamID());

		return -1;
	}

	bool Avatar::IsLoaded()
	{
		return GetImageId() != -1;
	}

	std::string Avatar::GetRGBA()
	{
		if(IsLoaded())
		{
			uint32_t width, height;
			if(Interface::GetInstance().mClientUtils->GetImageSize(GetImageId(), &width, &height))
			{
				std::string data(4 * height * width * sizeof(char), '\0');
				if(Interface::GetInstance().mClientUtils->GetImageRGBA(GetImageId(), (uint8_t*)&data[0], data.size()))
					return data;
			}
		}
		return std::string("");
	}
}