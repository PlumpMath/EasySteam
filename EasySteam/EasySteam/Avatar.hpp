#pragma once

#include "CompilerDef.hpp"
#include <Steamworks.h>

namespace EasySteam
{
	class EZ_STEAM_API Avatar : public std::enable_shared_from_this<Avatar>
	{
	public:

		enum Size
		{
			SMALL, MEDIUM, LARGE
		};

		typedef std::shared_ptr<Avatar> pointer;

		~Avatar();

		Size GetSize();
		int GetImageId();

		bool IsLoaded();

		std::string GetRGBA();

	private:

		Avatar(class Friend* pFriend, Size pSize);

		class Friend* mFriend;
		Size mSize;

		friend class Friend;
	};
}