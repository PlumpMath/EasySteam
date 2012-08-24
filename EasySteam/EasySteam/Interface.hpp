#pragma once

#include "CompilerDef.hpp"
#include <Steamworks.h>

#include "User.hpp"
#include "Friends.hpp"

namespace EasySteam
{
	class EZ_STEAM_API Interface
	{
	public:

		static Interface& GetInstance();
		static void Kill();
		static void Run();

		User* GetUser();
		Friends* GetFriends();

	private:

		Interface();
		~Interface();

		std::unique_ptr<User> mUserImpl;
		std::unique_ptr<Friends> mFriendsImpl;

		void DoRun();

		CSteamAPILoader mLoader;
		CreateInterfaceFn mFactory;
		ISteamClient012 *mSteamClient;
		HSteamPipe mPipe;
		HSteamUser mUser;
	};
}