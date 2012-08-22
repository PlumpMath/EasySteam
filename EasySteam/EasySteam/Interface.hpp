#pragma once

#include <Steamworks.h>

namespace EasySteam
{
	class Interface
	{
	public:

		static Interface& GetInstance();
		static void Kill();

	private:

		Interface();
		~Interface();

		CSteamAPILoader mLoader;
		CreateInterfaceFn mFactory;
		ISteamClient012 *mSteamClient;
		HSteamPipe mPipe;
		HSteamUser mUser;
	};
}