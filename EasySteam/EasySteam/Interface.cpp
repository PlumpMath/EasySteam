#include "Interface.hpp"

namespace EasySteam
{
	static Interface* instance = nullptr;

	Interface& Interface::GetInstance()
	{
		if(instance == nullptr)
			instance = new Interface;
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
	}

	Interface::~Interface()
	{
		mSteamClient->ReleaseUser(mPipe, mUser);
		mSteamClient->BReleaseSteamPipe(mPipe);
		mSteamClient->BShutdownIfAllPipesClosed();
	}
}