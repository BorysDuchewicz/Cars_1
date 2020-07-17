#include "cars.h"



std::vector<Car> Cars::from_ptr_to_cars(const std::vector<std::unique_ptr<Car>>& cars_up)
{
	std::vector<Car> cars;
	for (const auto& up : cars_up)
	{
		Car car;
		car.model = up->model;
		car.mileage = up->mileage;
		car.price = up->price;
		car.color = up->color;

		for (const auto& c : up->components)
		{
			car.components.emplace_back(std::make_unique<std::string>(*c));
		}

		cars.emplace_back(car);
	}
	return cars;
}


std::vector<std::unique_ptr<Car>> Cars::from_cars_to_ptr(const std::vector<Car>& cars)
{
	std::vector<std::unique_ptr<Car>> cars_up;

	for (const auto& car : cars)
	{
		std::unique_ptr<Car> car_up = std::make_unique<Car>();

		car_up->model = car.model;
		car_up->mileage = car.mileage;
		car_up->price = car.price;
		car_up->color = car.color;

		for (const auto& c : car.components)
		{
			car_up->components.emplace_back(std::make_unique<std::string>(*c));
		}

		cars_up.emplace_back(std::make_unique<Car>(car));
	}

	return cars_up;
}




Cars::Cars(const std::string& file_name)
{
	this->cars = CarUtils::read_cars_from_json(file_name);

}

Cars::Cars(const Cars& cars)
{
	for(auto& c:cars.cars)
	{
		this->cars.emplace_back(std::make_unique<Car>(*c));
	}
}

Cars::Cars(Cars&& cars)
{
	this->cars = std::move(cars.cars);
}



std::vector<std::unique_ptr<Car>> Cars::sort(const std::string& sort_element, const std::string& sort_met) const
{
	
	auto cars = from_ptr_to_cars(this->cars);
	std::vector<Car> desc_cars(cars.size());
	bool ok = false;
	std::map <std::string, std::function<bool(Car, Car)>> comparators;
	comparators.emplace(std::make_pair("model", [](const Car& car1, const Car& car2) {return car1.model < car2.model; }));
	comparators.emplace(std::make_pair("price", [](const Car& car1, const Car& car2) {return car1.price< car2.price; }));
	comparators.emplace(std::make_pair("mileage", [](const Car& car1, const Car& car2) {return car1.mileage < car2.mileage; }));
	comparators.emplace(std::make_pair("color", [](const Car& car1, const Car& car2) {return car1.color < car2.color; }));
	comparators.emplace(std::make_pair("components", [](const Car& car1, const Car& car2) {return car1.components.size() < car2.components.size(); }));

		
	for (const auto& c : comparators)
	{
		if (c.first == sort_element)
			ok = true;
	}
	
	if (ok)
	{
		std::sort(cars.begin(), cars.end(), comparators[sort_element]);
		if (sort_met == "1")
		{
			return from_cars_to_ptr(cars);
		}
		else if (sort_met == "2")
		{
			std::reverse_copy(cars.begin(), cars.end(), desc_cars.begin());
			return from_cars_to_ptr(desc_cars);
		}
		throw std::exception("wrong sort method");
	
	}	
	throw std::exception("wrong element");	
}


std::vector<std::unique_ptr<Car>> Cars::find_mileage(const int& mileage)
{

	std::vector<std::unique_ptr<Car>> new_cars;

	for (const auto& car:cars)
	{
		if (car->mileage >mileage)
		{
			new_cars.emplace_back(std::make_unique<Car>(*car));
		}
		
	}
	return new_cars;
}

std::map<std::string,int,std::greater<>> Cars::count_car_color()
{
	std::map<std::string, int,std::greater<>> cars_color;
	
	for (const auto& car:cars)
	{		
		cars_color.emplace(std::make_pair(color_to_str(car->color) , 0));

		for (auto& map : cars_color)
		{
			if (map.first == color_to_str(car->color))
				map.second++;
		}
	}
	
	return cars_color;
}

void Cars::car_stats()
{	
	int sum_mileage = 0;
	double sum_price =0;

	for(const auto& car:cars)
	{
		sum_mileage += car->mileage;
		sum_price += car->price;
	}
		
	const auto min_max_mileage=std::minmax_element(cars.begin(), cars.end(), [](const std::unique_ptr<Car>& c1, const std::unique_ptr<Car>& c2) {return c1->mileage> c2->mileage;});
	const auto min_max_price=std::minmax_element(cars.begin(), cars.end(), [](const std::unique_ptr<Car>& c1, const std::unique_ptr<Car>& c2) {return c1->price> c2->price;});

	std::cout << "Cars statistics:" << std::endl;
	std::cout << "average_mileage: " << sum_mileage /static_cast<double>(cars.size())<<std::endl;
	std::cout << "average_price: " << sum_price / cars.size()<<std::endl;
	std::cout << "Highest mileage: " << (*min_max_mileage.first)->mileage<<std::endl;
	std::cout << "Highest price: " << (*min_max_price.first)->price<<std::endl;
	std::cout << "Least mileage: " << (*min_max_mileage.second)->mileage<<std::endl;
	std::cout << "Least price: " << (*min_max_price.second)->price<<std::endl;
}

std::vector<std::unique_ptr<Car>> Cars::sort_components()
{
	
	std::vector<std::string>v;
	std::vector<std::unique_ptr<Car>> new_cars;

	for (int i = 0; i < cars.size(); ++i)
	{
		new_cars.emplace_back(std::make_unique<Car>(Car{}));
		new_cars[i]->model = cars[i]->model;
		new_cars[i]->price = cars[i]->price;
		new_cars[i]->mileage = cars[i]->mileage;
		new_cars[i]->color = cars[i]->color;
	
		for (const auto& cc : cars[i]->components)
		{
			v.emplace_back(*cc);
		}
		std::sort(v.begin(), v.end());
		for(const auto& cc : v)
		{
			new_cars[i]->components.emplace_back(std::make_unique<std::string>(cc));
		}

		v.clear();
				
	}
	
	return new_cars;
}


std::vector<std::unique_ptr<Car>> Cars::price_range(const double& a, const double& b)
{
	std::vector<std::unique_ptr<Car>> new_cars;
	for (const auto& car:cars)
	{
		if (a <= car->price && b >=car->price)
		{
			new_cars.emplace_back(std::make_unique<Car>(*car));
		}
	}
	return new_cars;
}

std::map<std::string, std::vector<std::unique_ptr<Car>>> Cars::cars_with_components()
{
	std::map<std::string, std::vector<std::unique_ptr<Car>>> cars_comp_map;
	std::vector<Car> cars_with_component;

	for(const auto& car:cars)
	{
		for(const auto& comp:car->components)
		{
			cars_comp_map[*comp];
		}
	}

	for(auto& m:cars_comp_map)
	{
		cars_with_component.clear();
		for(const auto& car:cars)
		{
			for(const auto& comp:car->components )
			{
				if(*comp==m.first)
				{
					cars_with_component.emplace_back(*car);
					break;
				}
			}
	
		}
		m.second = from_cars_to_ptr(cars_with_component);
	}
	return cars_comp_map;
}

std::map<std::string, std::unique_ptr<Car>> Cars::highest_price_car_model()
{
	std::map<std::string, std::unique_ptr<Car>> cars_model_map;

	for (const auto& car : cars)
	{
		cars_model_map.emplace(std::make_pair(car->model,std::make_unique<Car>(*car)));
	}
	for (auto& map : cars_model_map)
	{
		for(const auto& car:cars)
		{
			if (map.first==car->model)
			{
				if(map.second->price<car->price)
				{
					map.second = std::make_unique<Car>(*car);
				}
			}
		}
		
	}
	return cars_model_map;
}

std::vector<std::unique_ptr<Car>> Cars::highest_car_price()
{
	std::vector<std::unique_ptr<Car>> cars_price;
	double highest_price = 0;
	for(const auto& car:cars)
	{
		if(car->price>highest_price)
		{
			highest_price = car->price;
		}
	}
	for(const auto& car:cars)
	{
		if(car->price==highest_price)
		{
			cars_price.emplace_back(std::make_unique<Car>(*car));
		}
	}
	return cars_price;
}


std::ostream& operator<<(std::ostream& out, const Cars& cars)
{
	for(const auto& c: cars.cars)
	{
		out << *c<<std::endl;
	}

	return out;	
}
