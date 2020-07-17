#include "car.h"


Car::Car(const std::string& model, const double& price, const Color& color, const int& mileage, std::vector<std::unique_ptr<std::string>> components)
	:model{ model }, price{ price }, color{ color }, mileage{ mileage }, components{ std::move(components) }{}

Car::Car(const Car& car)
{
	if (this != &car)
	{
		this->model = car.model;
		this->price = car.price;
		this->color = car.color;
		this->mileage = car.mileage;
		for (auto& c : car.components)
		{
			this->components.emplace_back(std::make_unique<std::string>(*c));
		}
	}
}

Car::Car(Car&& car)
{
	if (this != &car)
	{
		this->model = car.model;
		this->price = car.price;
		this->color = car.color;
		this->mileage = car.mileage;
		this->components = std::move(car.components);
	}
}

Car& Car::operator=(Car&& car)
{
	if (this != &car)
	{
		this->model = car.model;
		this->price = car.price;
		this->color = car.color;
		this->mileage = car.mileage;
		this->components = std::move(car.components);
	}
	return *this;
}

Car& Car::operator=(const Car& car)
{
	if (this != &car)
	{
		this->model = car.model;
		this->price = car.price;
		this->color = car.color;
		this->mileage = car.mileage;
		for (auto& c : car.components)
		{
			this->components.emplace_back(std::make_unique<std::string>(*c));
		}
		return *this;
	}
}

std::ostream& operator<<(std::ostream& out, const Car& car)
{
	out << car.model << " " << car.price << " " << color_to_str(car.color) << " " << car.mileage << " [";

	for (int i = 0; i < car.components.size(); ++i)
	{
		if (i != car.components.size() - 1)
			out << *car.components[i] << " ";
		else
			out << *car.components[i];
	}
	out << "]";
	return out;

}
