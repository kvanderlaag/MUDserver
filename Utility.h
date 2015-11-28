#pragma once

#include <string>

class Utility
{
public:

	static const int BOLD = 0x01;
	static const int REVERSE = 0x02;
	static const int BLINK_SLOW = 0x04;
	static const int BLINK_FAST = 0x08;

	static std::string Color();
	static std::string Color(int fgcolor);
	static std::string Color(int fgcolor, int bgcolor);
	static std::string Color(int fgcolor, int bgcolor, int flags);
};

