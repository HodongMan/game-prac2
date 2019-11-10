#include "pch.h"

UDPSocket::~UDPSocket( void )
{
#if _WIN32
	closesocket( m_socket );
#else
	close(mSocket);
#endif
}

int UDPSocket::Bind( const SocketAddress & toAddress ) noexcept
{
	int error = bind( m_socket, &toAddress.m_sockAddr, toAddress.getSize() );
	if ( 0 != error )
	{
		SocketUtil::reportError( "UDPSocket::Bind" );
		return SocketUtil::getLastError();
	}

	return NO_ERROR;
}

int UDPSocket::SendTo( const void * toSend, int length, const SocketAddress & toAddress ) noexcept
{
	int byteSentCount = sendto( m_socket, static_cast<const char*>( toSend ), length, 0, &toAddress.m_sockAddr, toAddress.getSize() );
	
	if ( byteSentCount <= 0 )
	{
		SocketUtil::reportError( "UDPSocket::SendTo" );
		return -SocketUtil::getLastError();
	}

	return byteSentCount;
}

int UDPSocket::ReceiveFrom( void * toReceive, int maxLength, SocketAddress & fromAddress ) noexcept
{
	socklen_t fromLength = fromAddress.getSize();

	int readByCounts = recvfrom( m_socket, static_cast<char*>( toReceive ), maxLength, 0, &fromAddress.m_sockAddr, &fromLength );
	
	if ( readByCounts < 0 )
	{
		int error = SocketUtil::getLastError();

		if ( WSAEWOULDBLOCK == error )
		{
			return 0;
		}
		else if ( WSAECONNRESET == error )
		{
			LOG( "Connection reset from %s", fromAddress.toString().c_str() );
			return -WSAECONNRESET;
		}
		else
		{
			SocketUtil::reportError( "UDPSocket::ReceiveFrom" );
			return -error;
		}
	}

	return readByCounts;
}

int UDPSocket::setNonBlockingMode( const bool inShouldBeNonBlocking ) noexcept
{
#if _WIN32
	u_long arg = inShouldBeNonBlocking ? 1 : 0;
	int result = ioctlsocket( m_socket, FIONBIO, &arg );
#else
	int flags = fcntl( m_socket, F_GETFL, 0 );
	flags = inShouldBeNonBlocking ? ( flags | O_NONBLOCK ) : ( flags & ~O_NONBLOCK );
	int result = fcntl( mSocket, F_SETFL, flags );
#endif

	if ( SOCKET_ERROR == result )
	{
		SocketUtil::reportError( "UDPSocket::SetNonBlockingMode" );
		return SocketUtil::getLastError();
	}

	return NO_ERROR;
}
