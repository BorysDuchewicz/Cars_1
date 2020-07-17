#include "car_utils.h"

std::vector<std::unique_ptr<Car>> CarUtils::read_cars_from_json(const std::string& file_name)
{

	std::vector<std::unique_ptr<Car>> car_utils;
	CarValidator validator{};
	std::ifstream reader;
	reader.open(file_name + ".json");
	

	if (reader.is_open())
	{
		json j;
		reader >> j;

		for (const auto& cars : j)
		{
			Car car;
			car.model = cars["model"].get<std::string>();
			car.price = cars["price"].get<double>();
			car.mileage = cars["mileage"].get<int>();

			std::string color_str_from_json = cars["color"].get<std::string>();
			car.color = str_to_color(color_str_from_json);

			auto components_from_json = cars["components"].get<std::vector<std::string>>();			
			for (const auto& components : components_from_json)
			{
				car.components.emplace_back(std::make_unique<std::string>(components));
			}
			
			if (validator.validate(car).empty()) {					
				car_utils.emplace_back(std::make_unique<Car>(car));
			}
			else
				std::cout << validator;
			
			
		}
		reader.close();




	}
	else
	{
		std::cout << "Json file reader error" << std::endl;
	}


	
	return car_utils;
}
