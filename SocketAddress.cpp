#include "pch.h"
#include "SocketAddress.h"

SocketAddress::SocketAddress( uint32_t address, uint16_t port ) noexcept
{
	getAsSockAddrIn()->sin_family = AF_INET;
	getIP4Ref() = htonl( address );
	getAsSockAddrIn()->sin_port = htons( port );
}

SocketAddress::SocketAddress( const sockaddr& socketAddress ) noexcept
{
	memcpy( &m_sockAddr, &socketAddress, sizeof( sockaddr ) );
}

SocketAddress::SocketAddress( void ) noexcept
{
	getAsSockAddrIn()->sin_family = AF_INET;
	getIP4Ref() = INADDR_ANY;
	getAsSockAddrIn()->sin_port = 0;
}

string	SocketAddress::toString( void ) const noexcept
{
#if _WIN32
	const sockaddr_in* socketAddress = getAsSockAddrIn();
	char destinationBuffer[128];

	InetNtop( socketAddress->sin_family, const_cast< in_addr* >(&socketAddress->sin_addr), destinationBuffer, sizeof(destinationBuffer ) );
	return StringUtils::sprintf( "%s:%d",
								 destinationBuffer,
								 ntohs( socketAddress->sin_port ) );
#else
	return string("not implemented on mac for now");
#endif
}