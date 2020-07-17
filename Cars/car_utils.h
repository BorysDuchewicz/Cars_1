#pragma once
#include "car.h"
#include "car_validator.h"

//klasa w ktora sluzy do odczytu samochodow z pliku json
class CarUtils final
{
public:
	static std::vector<std::unique_ptr<Car>> read_cars_from_json(const std::string& file_name);
	CarUtils()=delete;
	~CarUtils()=delete;
};

