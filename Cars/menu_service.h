#pragma once
#include "cars.h"
#include "user_data_service.h"

//klasa umozliwiajace uzytkownikowi wybor akcji ktora moze wykonac
class MenuService
{
private:
	std::unique_ptr<Cars> cars;

	static int choose_option();
	void option1()const;
	void option2()const;
	void option3()const;
	void option4()const;
	void option5()const;
	void option6()const;
	void option7()const;
	void option8()const;
	void option9()const;
	void option10()const;

public:
	MenuService(const Cars& cars);

	void main_menu()const;
	~MenuService()=default;
};

