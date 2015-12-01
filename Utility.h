#pragma once

#include <string>

#define cDefault Utility::Color()
#define cBlue Utility::Color(4, 0, Utility::BOLD)
#define cRed Utility::Color(1, 0, Utility::BOLD)
#define cGreen Utility::Color(2, 0, Utility::BOLD)
#define cYellow Utility::Color(3, 0, Utility::BOLD)
#define cDarkGreen Utility::Color(2, 0)
#define cDarkRed Utility::Color(1, 0)
#define CDarkBlue Utility::Color(4, 0)
#define cDarkYellow Utility::Color(3, 0)

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

