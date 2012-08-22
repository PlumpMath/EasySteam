#pragma once

#include "CompilerDef.hpp"
#include <Steamworks.h>

#include "User.hpp"

namespace EasySteam
{
	class EZ_STEAM_API Interface
	{
	public:

		static Interface& GetInstance();
		static void Kill();

		User* GetUser();

	private:

		Interface();
		~Interface();

		std::unique_ptr<User> mUserImpl;

		CSteamAPILoader mLoader;
		CreateInterfaceFn mFactory;
		ISteamClient012 *mSteamClient;
		HSteamPipe mPipe;
		HSteamUser mUser;
	};
}