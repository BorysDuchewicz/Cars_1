#include "car_validator.h"


bool CarValidator::is_car_model_valid(const Car& car)
{
	return std::regex_match(car.model, std::regex("[A-Z\\s]+"));
}


bool CarValidator::is_car_price_valid(const Car& car)
{
	return car.price > 0;
}

bool CarValidator::is_car_mileage_valid(const Car& car)
{
	return car.mileage > 0;
}

bool CarValidator::is_car_component_valid(const std::string& comp)
{
	return std::regex_match(comp, std::regex("[A-Z\\s]+"));
}

bool CarValidator::is_car_color_valid(const std::string& value)
{
	return std::find(ColorValues.begin(), ColorValues.end(), value) != ColorValues.end();
}

std::map<std::string, std::string> CarValidator::validate(const Car& car)
{
	errors.clear();
	if(!is_car_model_valid(car))
	{
		errors.emplace(std::make_pair("model ", "is not valid " + car.model));
	}
	if(!is_car_price_valid(car))
	{
		errors.emplace(std::make_pair("price ", "is not valid " + std::to_string(car.price)));
	}
	if(!is_car_color_valid(color_to_str(car.color)))
	{
		errors.emplace(std::make_pair("color ", "is not valid " + color_to_str(car.color)));
	}
	if(!is_car_mileage_valid(car))
	{
		errors.emplace(std::make_pair("mileage ", "is not valid" + std::to_string(car.mileage)));
	}
	for(const auto& component:car.components)
	{
		if(!is_car_component_valid(*component))
		{
			errors.emplace(std::make_pair("component ", *component + " is not valid"));
		}
	}

	return errors;
}

std::ostream& operator<<(std::ostream& out, const CarValidator& car_validator)
{
	for(const auto& i:car_validator.errors)
	{
		out << i.first << " " << i.second << std::endl;
	}
	return out;
}
