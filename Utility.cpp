#include "Utility.h"
#include <sstream>

std::string Utility::Color() {
	return "\x1b[0m";
}

std::string Utility::Color(int fgcolor) {
	std::ostringstream code;
	if (fgcolor > 7 || fgcolor < 0) {
		return "\x1b[0m";
	}
	code << "\x1b[3" << fgcolor << "m";
	return code.str();
}

std::string Utility::Color(int fgcolor, int bgcolor) {
	std::ostringstream code;
	if (fgcolor > 7 || fgcolor < 0 || bgcolor > 7 || bgcolor < 0) {
		return "\x1b[0m";
	}
	code << "\x1b[3" << fgcolor << ";4" <<bgcolor << "m";
	return code.str();
}

std::string Utility::Color(int fgcolor, int bgcolor, int flags) {
	std::ostringstream code;
	if (fgcolor > 7 || fgcolor < 0 || bgcolor > 7 || bgcolor < 0) {
		return "\x1b[0m";
	}
	code << "\x1b[3" << fgcolor << ";4" << bgcolor;
	if (flags == 0) {
		code << "m";
		return code.str();
	}
	if (flags & Utility::BOLD) {
		code << ";1";
		if (flags ^= Utility::BOLD == 0) {
			code << "m";
		}
	}
	if (flags & Utility::BLINK_SLOW) {
		code << ";5";
		if (flags ^= Utility::BLINK_SLOW == 0) {
			code << "m";
		}
	}
	if (flags & Utility::BLINK_FAST) {
		code << ";6";
		if (flags ^= Utility::BLINK_FAST == 0) {
			code << "m";
		}
	}
	if (flags & Utility::REVERSE) {
		code << ";7";
		if (flags ^= Utility::REVERSE) {
			code << "m";
		}
	}

	return code.str();
}