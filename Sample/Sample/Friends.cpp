#include "Friends.hpp"
#include "Friend.hpp"

namespace EasySteam
{
	Friends::iterator::iterator(uint32_t pId, Friends* pImpl)
		:mId(pId),mImpl(pImpl)
	{
		mData = mImpl->GetFriendById(mId);
	}

	Friends::iterator::iterator(const iterator& pItor)
	{
		mData = pItor.mData;
		mId = pItor.mId;
		mImpl = pItor.mImpl;
	}

	Friends::iterator& Friends::iterator::operator++()
	{
		++mId;
		
		if(mId >= mImpl->GetCount())
		{
			mData = nullptr;
			mImpl = nullptr;
		}
		else
			mData = mImpl->GetFriendById(mId);
	}

	Friends::iterator Friends::iterator::operator++(int)
	{
		Friends::iterator itor(*this);
		return ++itor;
	}

	bool Friends::iterator::operator==(const Friends::iterator& pItor)
	{
		return (mData == pItor.mData) && (mImpl == pItor.mImpl);
	}

	bool Friends::iterator::operator!=(const Friends::iterator& pItor)
	{
		return !(*this == pItor);
	}

	Friend::pointer Friends::iterator::operator*()
	{
		return mData;
	}

	Friend::pointer Friends::GetFriendById(uint32_t pId)
	{
		return Friend::pointer(new Friend(this, mFriendsImpl->GetFriendByIndex(pId, k_EFriendFlagImmediate)));
	}

	std::string Friends::GetPersonaName(CSteamID pId)
	{
		return std::string(mFriendsImpl->GetFriendPersonaName(pId));
	}

	uint32_t Friends::GetCount()
	{
		return mFriendsImpl->GetFriendCount(k_EFriendFlagImmediate);
	}

	Friends::iterator Friends::Begin()
	{
		return Friends::iterator(0, this);
	}

	Friends::iterator Friends::End()
	{
		return Friends::iterator((std::numeric_limits<uint32_t>::max)(), nullptr);
	}
}