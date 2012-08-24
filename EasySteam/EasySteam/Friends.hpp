#pragma once

#include "CompilerDef.hpp"
#include "ISteamFriends013.h"
#include "Friend.hpp"

namespace EasySteam
{
	class EZ_STEAM_API Friends
	{
	public:

		class EZ_STEAM_API iterator : public std::iterator<std::input_iterator_tag, Friend::pointer>
		{
			Friend::pointer mData;
			uint32_t mId;

			friend class Friends;

			iterator(uint32_t pId);

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
		std::string GetPersonaName(CSteamID& pId);
		uint32_t GetCount();

		void SendMessage(CSteamID& pSteamId, const std::string& pMessage);

		boost::signal<void(const std::string& pMessage, Friend::pointer pSender)> OnFriendMessage;
		boost::signal<void(const std::string& pMessage)> OnSendMessage;

	private:

		void DoCallback(CallbackMsg_t& pCallback);

		Friends(ISteamFriends013* pImpl);

		ISteamFriends013* mFriendsImpl;

		friend class Interface;
	};
}