#include "pch.h"
#include "StringUtils.h"

#if !_WIN32
extern const char** __argv;
extern int __argc;
void outputDebugString( const char* string ) noexcept
{
	printf( "%s", string );
}
#endif

string StringUtils::getCommandLineArgs( const int index ) noexcept
{
	if ( index < __argc )
	{
		return string( __argv[index] );
	}

	static string empty;
	return empty;
}

string StringUtils::sprintf( const char* format, ... ) noexcept
{
	static char temp[486];

	va_list args;
	va_start( args, format );

#if _WIN32
	_vsnprintf_s( temp, 4096, 4096, format, args );
#else
	vsnprintf( temp, 4096, format, args );
#endif
	return string( temp );
}

void StringUtils::log( const char* format ) noexcept
{
	OutputDebugString( format );
 	OutputDebugString( "\n" );
}

void StringUtils::log( const char* format, ... ) noexcept
{
	static char temp[4096];

	va_list args;
	va_start( args, format );

#if _WIN32
	_vsnprintf_s( temp, 4096, 4096, format, args );
#else
	vsnprintf( temp, 4096, format, args );
#endif
	OutputDebugString( temp );
	OutputDebugString( "\n" );
}

