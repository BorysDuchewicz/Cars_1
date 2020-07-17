#pragma once
#include<iostream>
#include<memory>
#include<fstream>
#include<string>
#include<vector>
#include<algorithm>
#include<unordered_map>
#include<regex>
#include"json.hpp"
#include<algorithm>
#include <exception>

using json = nlohmann::json;

enum class Color{RED, BLUE, GREEN};

static const std::vector<std::string> ColorValues = { "RED", "BLUE", "GREEN" };

inline Color str_to_color ( const std::string& color_str )
{
	if ( color_str == "RED")
	{
		return Color::RED;
	}
	else if (color_str == "BLUE")
	{
		return Color::BLUE;
	}
	else if (color_str == "GREEN")
	{
		return Color::GREEN;
	}
	std::string message = "no color for value: " + color_str;
	throw std::exception(message.c_str());
}

inline std::string color_to_str(Color color)
{
	return ColorValues[static_cast<int>(color)];
}