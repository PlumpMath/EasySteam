#include "Interface.hpp"

namespace EasySteam
{
	static Interface* instance = nullptr;

	Interface& Interface::GetInstance()
	{
		if(instance == nullptr)
		{
			try
			{
				instance = new Interface;
			}
			catch (...)
			{
				delete instance; instance = nullptr;
				throw;
			}
		}
		return *instance;
	}

	void Interface::Kill()
	{
		delete instance; instance = nullptr;
	}

	Interface::Interface()
	{
		CreateInterfaceFn mFactory = mLoader.GetSteam3Factory();
		if(!mFactory)
			throw std::runtime_error("Steamclient not started.");

		mSteamClient = (ISteamClient012 *)mFactory(STEAMCLIENT_INTERFACE_VERSION_012, NULL);
		if(!mSteamClient)
			throw std::runtime_error("Steamclient not started.");

		mPipe = mSteamClient->CreateSteamPipe();
		mUser = mSteamClient->ConnectToGlobalUser(mPipe);

		mUserImpl.reset(new User((ISteamUser016*)mSteamClient->GetISteamUser(mUser, mPipe, STEAMUSER_INTERFACE_VERSION_016)));
		mFriendsImpl.reset(new Friends((ISteamFriends012*)mSteamClient->GetISteamFriends(mUser, mPipe, STEAMFRIENDS_INTERFACE_VERSION_012)));
	}

	Interface::~Interface()
	{
		if(mSteamClient)
		{
			mSteamClient->ReleaseUser(mPipe, mUser);
			mSteamClient->BReleaseSteamPipe(mPipe);
			mSteamClient->BShutdownIfAllPipesClosed();
		}
	}

	User* Interface::GetUser()
	{
		return mUserImpl.get();
	}

	Friends* Interface::GetFriends()
	{
		return mFriendsImpl.get();
	}
}