#include <EasySteam/Interface.hpp>
#include <EasySteam/Friend.hpp>
#include <algorithm>
#include <iostream>
#include <string>

int main()
{
	EasySteam::Interface& steamInterface = EasySteam::Interface::GetInstance();

	std::for_each(steamInterface.GetFriends()->Begin(), steamInterface.GetFriends()->End(), 
		[](EasySteam::Friend::pointer pPtr)
		{
			std::cout << pPtr->GetPersonaName() << std::endl;
		});

	system("pause");
	return 0;
}