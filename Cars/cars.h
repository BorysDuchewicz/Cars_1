#pragma once
#include "car.h"
#include "car_utils.h"

//klasa przechowujaca samochody i wykonujaca na nich poszczegolne operacje
class Cars
{
private:

	static std::vector<Car> from_ptr_to_cars(const std::vector<std::unique_ptr<Car>>& cars_up);
	static std::vector<std::unique_ptr<Car>> from_cars_to_ptr(const std::vector<Car>& cars);
	std::vector<std::unique_ptr<Car>> cars;

	
public:
	Cars()=default;
	Cars(const std::string& file_name);
	Cars(const Cars& cars);
	Cars(Cars&& cars);

	std::vector<std::unique_ptr<Car>> sort(const std::string& sort_element,const std::string& sort_met) const;//sortuje samochoty po podanej danej i podany sposob
	std::vector<std::unique_ptr<Car>> find_mileage(const int& mileage);//zwraca samochody ktore przejechaly podana ilosc km
	std::map<std::string, int,std::greater<>> count_car_color();//zwraca ile jest samochodow kazdego z kolorow
	void car_stats();//wyswietla statystyki samochodu
	std::vector<std::unique_ptr<Car>> sort_components();//sortuje elementy samochodu 
	std::vector<std::unique_ptr<Car>> price_range(const double& a,const double& b);//zwraca samochody z podanego przedzialu cenowego
	std::map<std::string, std::vector<std::unique_ptr<Car>>> cars_with_components();//zwraca po koleji wszystkie komponenrty i wszystkie samochody ktore je posiadaja
	std::map<std::string, std::unique_ptr<Car>> highest_price_car_model();//zwraca najdrozszy samochod z danej marki
	std::vector<std::unique_ptr<Car>> highest_car_price();//zwraca najdrozsze samochody

	friend  std::ostream& operator<<(std::ostream& out,const Cars& cars);
	
	
};

