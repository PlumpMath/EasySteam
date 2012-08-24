#include <EasySteam/Interface.hpp>
#include <EasySteam/Friend.hpp>
#include <algorithm>
#include <iostream>
#include <string>
#include <fstream>

bool run = true;

void OnMessage(const std::string& pMessage, EasySteam::Friend::pointer pFriend)
{
	std::cout << pFriend->GetPersonaName() << " sent : " << pMessage << std::endl;
	//pFriend->SendMessage("ololol");
}

void OnSend(const std::string& pMessage)
{
	std::cout << "I sent : " << pMessage << std::endl;
	if(pMessage.find("quit") != std::string::npos)
	{
		run = false;
	}
}

int main()
{
	EasySteam::Interface& steamInterface = EasySteam::Interface::GetInstance();

	std::cout << "My persona name is : " << steamInterface.GetUser()->GetPersonaName() << std::endl;

	steamInterface.GetFriends()->OnFriendMessage.connect(OnMessage);
	steamInterface.GetFriends()->OnSendMessage.connect(OnSend);

	std:: cout << "And here are my many friends ! " << std::endl;

	uint64_t i = 0;
	std::for_each(steamInterface.GetFriends()->Begin(), steamInterface.GetFriends()->End(), 
		[&i](EasySteam::Friend::pointer pPtr)
		{
			std::cout << pPtr->GetPersonaName() << std::endl;
			std::ofstream dump(std::to_string(i) + std::string(".rgba"), std::ios::binary);
			auto data = pPtr->GetAvatar(EasySteam::Avatar::LARGE)->GetRGBA();
			dump.write(data.c_str(), data.size());
			dump.close();
			++i;
			//pPtr->SendMessage("Hello I am a bot !");
		});

	std::cout << std::endl;

	while(run)
	{
		EasySteam::Interface::Run();
	}

	return 0;
}