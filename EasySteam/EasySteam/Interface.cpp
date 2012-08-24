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
		delete instance; 
		instance = nullptr;
	}

	Interface::Interface()
	{
		CreateInterfaceFn mFactory = mLoader.GetSteam3Factory();
		if(!mFactory)
			throw std::runtime_error("Steamclient not started.");

		mSteamClient = (ISteamClient012 *)mFactory(STEAMCLIENT_INTERFACE_VERSION_012, NULL);
		if(!mSteamClient)
			throw std::runtime_error("Steamclient not started.");

		mClientEngine = (IClientEngine*)mFactory(CLIENTENGINE_INTERFACE_VERSION, NULL);
		if(!mClientEngine)
			throw std::runtime_error("Steamclient not started.");

		mPipe = mSteamClient->CreateSteamPipe();
		mUser = mSteamClient->ConnectToGlobalUser(mPipe);

		mClientUtils = (IClientUtils*)mClientEngine->GetIClientUtils(mPipe, CLIENTUTILS_INTERFACE_VERSION);
		mUserImpl.reset(new User((ISteamUser016*)mSteamClient->GetISteamUser(mUser, mPipe, STEAMUSER_INTERFACE_VERSION_016)));
		mFriendsImpl.reset(new Friends((ISteamFriends013*)mSteamClient->GetISteamFriends(mUser, mPipe, STEAMFRIENDS_INTERFACE_VERSION_013)));
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

	void Interface::Run()
	{
		if(instance && instance->mSteamClient)
		{
			if(instance->mUserImpl && instance->mFriendsImpl)
			{
				instance->DoRun();
			}
		}
	}

	void Interface::DoRun()
	{
		CallbackMsg_t callBack;
		while ( Steam_BGetCallback( instance->mPipe, &callBack ) )
		{
			int opcode = callBack.m_iCallback - (callBack.m_iCallback % 100);
			opcode /= 100;

			if(opcode == 3 || opcode == 8) mFriendsImpl->DoCallback(callBack);

			Steam_FreeLastCallback(mPipe);
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