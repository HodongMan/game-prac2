#include "pch.h"

TCPSocket::~TCPSocket( void )
{
#if _WIN32
	closesocket( m_socket );
#else
	close( mSocket );
#endif
}

int TCPSocket::Connect( const SocketAddress & address ) noexcept
{
	int error = connect( m_socket, &address.m_sockAddr, address.getSize() );

	if ( error < 0 )
	{
		SocketUtil::reportError( "TCPSocket::Connect" );
		return -SocketUtil::getLastError();
	}

	return NO_ERROR;
}

int TCPSocket::Bind( const SocketAddress & address ) noexcept
{
	int error = bind( m_socket, &address.m_sockAddr, address.getSize() );

	if ( error < 0 )
	{
		SocketUtil::reportError( "TCPSocket::Connect" );
		return -SocketUtil::getLastError();
	}

	return NO_ERROR;
}

int TCPSocket::Listen( int backLog ) noexcept
{
	int error = listen( m_socket, backLog );
	if ( error < 0 )
	{
		SocketUtil::reportError( "TCPSocket::Listen" );
		return -SocketUtil::getLastError();
	}

	return NO_ERROR;
}

TCPSocketPtr TCPSocket::Address( SocketAddress & fromAddress ) noexcept
{
	socklen_t length = fromAddress.getSize();
	SOCKET newSocket = accept( m_socket, &fromAddress.m_sockAddr, &length );

	if ( INVALID_SOCKET == newSocket )
	{
		SocketUtil::reportError( "TCPSocket::Accept" );
		return nullptr;
	}

	return TCPSocketPtr( new TCPSocket( newSocket ) );
}

int32_t TCPSocket::Send( const void * data, size_t len ) noexcept
{
	int bytesSentCount = send( m_socket, static_cast< const char* >( data ), len, 0 );
	if ( bytesSentCount < 0 )
	{
		SocketUtil::reportError( "TCPSocket::Send" );
		return -SocketUtil::getLastError();
	}

	return bytesSentCount;
}

int32_t TCPSocket::Receive( void * buffer, size_t len ) noexcept
{
	int bytesReceivedCount = recv( m_socket, static_cast< char* >( buffer ), len, 0 );
	if ( bytesReceivedCount < 0 )
	{
		SocketUtil::reportError( "TCPSocket::Receive" );
		return -SocketUtil::getLastError();
	}

	return bytesReceivedCount;
}
