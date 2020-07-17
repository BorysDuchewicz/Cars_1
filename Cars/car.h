#pragma once
#include "lib.h"

//struktura przechowujaca dane o samochodzie
struct Car
{
	std::string model;
	double price;
	Color color;
	int mileage;
	std::vector<std::unique_ptr<std::string>> components;

	Car() = default;

	Car(const std::string& model, const double& price, const Color& color, const int& mileage, std::vector<std::unique_ptr<std::string>> components);
	Car(const Car& car);
	Car(Car&& car);

	Car& operator=(Car&& car);
	Car& operator=(const Car& car);
	friend std::ostream& operator<<(std::ostream& out, const Car& car);

};








