#pragma once

namespace StringUtils
{		
	string getCommandLineArgs( const int index ) noexcept;
	string sprintf( const char* format, ... ) noexcept;

	void log( const char* format ) noexcept;
	void log( const char* format, ...) noexcept;
}


#define LOG( ... ) StringUtils::log( __VA_ARGS__ )