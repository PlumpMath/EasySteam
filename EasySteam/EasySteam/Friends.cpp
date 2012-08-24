#include "Friends.hpp"
#include "Friend.hpp"
#include "Interface.hpp"

namespace EasySteam
{
	Friends::iterator::iterator(uint32_t pId)
		:mId(pId),mData(nullptr)
	{
		if(pId < Interface::GetInstance().GetFriends()->GetCount())
			mData = Interface::GetInstance().GetFriends()->GetFriendById(mId);
	}

	Friends::iterator::iterator(const iterator& pItor)
	{
		mData = pItor.mData;
		mId = pItor.mId;
	}

	Friends::iterator& Friends::iterator::operator++()
	{
		++mId;
		
		if(mId >= Interface::GetInstance().GetFriends()->GetCount())
		{
			mData = nullptr;
		}
		else
			mData = Interface::GetInstance().GetFriends()->GetFriendById(mId);

		return *this;
	}

	Friends::iterator Friends::iterator::operator++(int)
	{
		Friends::iterator itor(*this);
		return ++itor;
	}

	bool Friends::iterator::operator==(const Friends::iterator& pItor)
	{
		return (mData == pItor.mData);
	}

	bool Friends::iterator::operator!=(const Friends::iterator& pItor)
	{
		return !(*this == pItor);
	}

	Friend::pointer Friends::iterator::operator*()
	{
		return mData;
	}

	Friends::Friends(ISteamFriends013* pImpl)
		:mFriendsImpl(pImpl)
	{
	}

	Friend::pointer Friends::GetFriendById(uint32_t pId)
	{
		return Friend::pointer(new Friend(mFriendsImpl->GetFriendByIndex(pId, k_EFriendFlagImmediate)));
	}

	std::string Friends::GetPersonaName(CSteamID& pId)
	{
		return std::string(mFriendsImpl->GetFriendPersonaName(pId));
	}

	uint32_t Friends::GetCount()
	{
		return mFriendsImpl->GetFriendCount(k_EFriendFlagImmediate);
	}

	Friends::iterator Friends::Begin()
	{
		return Friends::iterator(0);
	}

	Friends::iterator Friends::End()
	{
		return Friends::iterator((std::numeric_limits<uint32_t>::max)());
	}

	void Friends::SendMessage(CSteamID& pSteamId, const std::string& pMessage)
	{
		mFriendsImpl->ReplyToFriendMessage(pSteamId, pMessage.c_str());
	}

	void Friends::DoCallback(CallbackMsg_t& pCallback)
	{
		if(pCallback.m_iCallback == FriendChatMsg_t::k_iCallback)
		{
			FriendChatMsg_t* msg = (FriendChatMsg_t*)pCallback.m_pubParam;

			std::string message;
			EChatEntryType eMsgType;

			message.resize(k_cchFriendChatMsgMax);
			message.resize(mFriendsImpl->GetFriendMessage(msg->m_ulFriendID, msg->m_iChatID, (void*)&message[0], message.size(), &eMsgType));

			if(eMsgType == k_EChatEntryTypeChatMsg || eMsgType == k_EChatEntryTypeEmote)
			{
				if(msg->m_ulSenderID != Interface::GetInstance().GetUser()->GetSteamID())
				{
					Friend::pointer ptr(new Friend(msg->m_ulFriendID));
					OnFriendMessage(message, ptr);
				}
				else
					OnSendMessage(message);
			}
		}
	}
}