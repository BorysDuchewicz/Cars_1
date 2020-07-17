#include "menu_service.h"



int MenuService::choose_option()
{
	std::cout << "Menu" << std::endl;
	std::cout << "Choose option:" << std::endl;
	std::cout << "1-show cars" << std::endl;
	std::cout << "2-sorting" << std::endl;
	std::cout << "3-find mileages" << std::endl;
	std::cout << "4-how many cars color" << std::endl;
	std::cout << "5-cars statistics" << std::endl;
	std::cout << "6-sorted components" << std::endl;
	std::cout << "7-price range" << std::endl;
	std::cout << "8-cars with components" << std::endl;
	std::cout << "9-car model highest price" << std::endl;
	std::cout << "10-car highest price" << std::endl;
	std::cout << "11-exit" << std::endl;
	const int choice = UserDataService::get_int("");
	return choice;
}

void MenuService::option1() const
{
	std::cout << *cars << std::endl;
	std::cin.get();
	system("cls");
}

void MenuService::option2() const
{
	const std::string sort_by = UserDataService::get_string("Enter sorting item: \n[model][price][mileage][color][components]");
	const std::string sort_met = UserDataService::get_string("Enter sorting method[1-ascending][2-descending]:");
	auto sorted_cars = cars->sort(sort_by, sort_met);
	for(const auto& c:sorted_cars)
	{
		std::cout << *c << std::endl;
	}
	std::cin.get();
	system("cls");
}

void MenuService::option3() const
{

	const int mileage = UserDataService::get_int("Enter mileage: ");
	auto cars_mileage = cars->find_mileage(mileage);
	if(cars_mileage.empty())
	{
		std::cout << "No cars with this mileage!" << std::endl;
		std::cin.get();
		system("cls");
		return;
	}
	for(const auto& c:cars_mileage)
	{
		std::cout << *c << std::endl;
	}
	std::cin.get();
	system("cls");
}

void MenuService::option4() const
{
	const auto cars_color = cars->count_car_color();
	for(const auto& c:cars_color)
	{
		std::cout << c.first << " " << c.second << std::endl;
	}
	std::cin.get();
	system("cls");
}

void MenuService::option5() const
{
	cars->car_stats();
	std::cin.get();
	system("cls");
}

void MenuService::option6() const
{
	const auto sorted_components = cars->sort_components();
	for(const auto& c:sorted_components)
	{
		std::cout << *c << std::endl;
	}
	std::cin.get();
	system("cls");
}

void MenuService::option7() const
{
	double from = UserDataService::get_double("Enter price range from: ");
	double to = UserDataService::get_double("to: ");
	const auto cars_in_price_range = cars->price_range(from,to);
	if(cars_in_price_range.empty())
	{
		std::cout << "No cars in range!" << std::endl;
		std::cin.get();
		system("cls");
		return;
	}
	for(const auto& c:cars_in_price_range)
	{
		std::cout << *c << std::endl;
	}
	std::cin.get();
	system("cls");
}

void MenuService::option8() const
{
	const auto cars_with_comps = cars->cars_with_components();
	for(const auto& i:cars_with_comps)
	{
		std::cout << i.first << std::endl;
		std::cout<<"{"<<std::endl;
		for(const auto& j:i.second)
		{
			std::cout << *j<<std::endl;
		}
		std::cout<<"}"<<std::endl;
		std::cout << std::endl;
	}
	std::cin.get();
	system("cls");
}

void MenuService::option9() const
{
	const auto car_model_highest_price = cars->highest_price_car_model();
	for(const auto& i:car_model_highest_price)
	{
		std::cout << i.first << " " << *i.second << std::endl;
	}
	std::cin.get();
	system("cls");
}

void MenuService::option10() const
{
	const auto highest_car_price = cars->highest_car_price();
	for(const auto& car:highest_car_price)
	{
		std::cout << *car << std::endl;
	}
	std::cin.get();
	system("cls");
}


MenuService::MenuService(const Cars& cars)
{
	this->cars = std::make_unique<Cars>(cars);
}

void MenuService::main_menu() const
{
	try
	{
		while(true)
		{
			const int option = choose_option();
			switch (option)
			{
				case 1:
					option1();
					break;
				case 2:
					option2();
				break;
				case 3:
					option3();
				break;
				case 4:
					option4();
				break;
				case 5:
					option5();
				break;
				case 6:
					option6();
				break;
				case 7:
					option7();
				break;
				case 8:
					option8();
				break;
				case 9:
					option9();
					break;
				case 10:
					option10();
					break;
				case 11:
					std::cout << "Have a nice day!";
					std::cin.get();
					return;
				default:
				std::cout<<"No option with number "<<option<<std::endl;
				std::cin.get();
				system("cls");
				break;
			}
		}
	}
	catch (const std::exception& exception)
	{
		std::cout << exception.what() << std::endl;
		std::cin.get();
		system("cls");
		main_menu();
	}
}
