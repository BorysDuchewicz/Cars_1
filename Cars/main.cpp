#include"cars.h"
#include "user_data_service.h"
#include "menu_service.h"

int main()
{
	
	const std::string file_name = "cars";
	//const std::string file_name = UserDataService::get_string("Enter file name");
	const Cars cars{ file_name };
	MenuService menu_service{ cars };
	menu_service.main_menu();
	

	std::cin.get();
	return 0;
}
