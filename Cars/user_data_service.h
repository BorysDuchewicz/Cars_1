#pragma once
#include "lib.h"

//klasa posiadajaca metody ktore pozwalaja pobierac od uzytkownika dane 
class UserDataService final
{
public:
	UserDataService()=delete;
	~UserDataService()=delete;

	static int get_int(const std::string& message);
	static double get_double(const std::string& message);
	static Color get_color(const std::string& message);
	static std::string get_string(const std::string& message);

};

