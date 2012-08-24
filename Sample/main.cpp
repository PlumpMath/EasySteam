#include <EasySteam/Interface.hpp>
#include <EasySteam/Friend.hpp>
#include <algorithm>
#include <iostream>
#include <string>

void OnMessage(const std::string& pMessage, EasySteam::Friend::pointer pFriend)
{
	std::cout << pFriend->GetPersonaName() << " sent : " << pMessage << std::endl;
	pFriend->SendMessage("ololol");
}

int main()
{
	EasySteam::Interface& steamInterface = EasySteam::Interface::GetInstance();

	std::cout << "My persona name is : " << steamInterface.GetUser()->GetPersonaName() << std::endl;

	steamInterface.GetFriends()->OnFriendMessage.connect(OnMessage);

	std:: cout << "And here are my many friends ! " << std::endl;
	std::for_each(steamInterface.GetFriends()->Begin(), steamInterface.GetFriends()->End(), 
		[](EasySteam::Friend::pointer pPtr)
		{
			std::cout << pPtr->GetPersonaName() << std::endl;
			pPtr->SendMessage("Hello I am a bot !");
		});
	std::cout << std::endl;

	while(1)
	{
		EasySteam::Interface::Run();
	}

	system("pause");
	return 0;
}