#pragma once

#include "car.h"

//klasa sprawdzajaca czy poszczegolne elementy klasy Car zostaly poprawnie wprowadzone
class CarValidator final
{

private:
	std::map<std::string, std::string> errors;

	static bool is_car_model_valid(const Car& car);
	static bool is_car_price_valid(const Car& car);
	static bool is_car_mileage_valid(const Car& car);
	static bool is_car_component_valid(const std::string& comp);
	static bool is_car_color_valid(const std::string& value);
public:

	CarValidator() = default;
	~CarValidator() = default;

	std::map<std::string, std::string> validate(const Car& car);
	friend std::ostream& operator<<(std::ostream& out, const CarValidator& car_validator);

};

