#include "pch.h"
#include "SocketAddressFactory.h"

SocketAddressPtr SocketAddressFactory::createIPv4FromString( const string& string ) noexcept
{
	size_t pos = string.find_last_of( ':' );
	std::string host, service;

	if ( string::npos != pos )
	{
		host = string.substr( 0, pos );
		service = string.substr( pos + 1 );
	}
	else
	{
		host = string;
		service = "0";
	}
	
	addrinfo hint;
	memset( &hint, 0, sizeof( hint ) );
	hint.ai_family = AF_INET;

	addrinfo* result = nullptr;
	int error = getaddrinfo( host.c_str(), service.c_str(), &hint, &result );
	addrinfo* initResult = result;

	if ( 0 != error && nullptr != result )
	{
		SocketUtil::reportError("SocketAddressFactory::CreateIPv4FromString");
		return nullptr;
	}

	while( !result->ai_addr && result->ai_next )
	{
		result = result->ai_next;
	}

	if ( !result->ai_addr )
	{
		return nullptr;
	}

	auto toRet = std::make_shared< SocketAddress >( *result->ai_addr );
	
	freeaddrinfo( result );
	
	return toRet;
}