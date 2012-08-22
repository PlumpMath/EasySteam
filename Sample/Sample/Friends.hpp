#pragma once

#include "CompilerDef.hpp"
#include "ISteamFriends012.h"
#include "Friend.hpp"

namespace EasySteam
{
	class EZ_STEAM_API Friends
	{
	public:

		class iterator : public std::iterator<std::input_iterator_tag, Friend*>
		{
			Friends* mImpl;
			Friend::pointer mData;
			uint32_t mId;

			friend class Friends;

			iterator(uint32_t pId, Friends* pImpl);

		public:

			iterator(const iterator& pItor);
			iterator& operator++();
			iterator operator++(int);
			bool operator==(const iterator& pItor);
			bool operator!=(const iterator& pItor);
			Friend::pointer operator*();
		};

		iterator Begin();
		iterator End();

		Friend::pointer GetFriendById(uint32_t pId);

		std::string GetPersonaName(CSteamID pId);

		uint32_t GetCount();

	private:

		ISteamFriends012* mFriendsImpl;

		friend class Interface;
	};
}