#include "pch.h"
#include "SocketUtil.h"

bool SocketUtil::staticInit( void ) noexcept
{
#if _WIN32
	WSADATA wsaData;
	int result = WSAStartup( MAKEWORD( 2, 2 ), &wsaData );
	if ( NO_ERROR != result )
	{
		reportError( "Starting Up" );
		return false;
	}
#endif
	return true;
}

void SocketUtil::cleanUp( void ) noexcept
{
#if _WIN32
	WSACleanup();
#endif
}

void SocketUtil::reportError( const char * operationDescription ) noexcept
{
#if _WIN32
	LPVOID messageBuffer;
	DWORD errorNumber = GetLastError();

	FormatMessage( FORMAT_MESSAGE_ALLOCATE_BUFFER |
				   FORMAT_MESSAGE_FROM_SYSTEM |
				   FORMAT_MESSAGE_IGNORE_INSERTS,
				   NULL,
				   errorNumber,
				   MAKELANGID( LANG_NEUTRAL, SUBLANG_DEFAULT ),
				   (LPTSTR)&messageBuffer,
				   0, NULL);


	LOG( "Error %s: %d- %s", operationDescription, errorNumber, messageBuffer);
#else
	LOG("Error: %hs", inOperationDesc);
#endif
}

int SocketUtil::getLastError( void ) noexcept
{
#if _WIN32
	return WSAGetLastError();
#else
	return errno;
#endif
}

int SocketUtil::Select( const vector<TCPSocketPtr>* inReadSet, vector<TCPSocketPtr>* outReadSet, const vector<TCPSocketPtr>* inWriteSet, vector<TCPSocketPtr>* outWriteSet, const vector<TCPSocketPtr>* inExceptSet, vector<TCPSocketPtr>* outExceptSet ) noexcept
{
	fd_set read;
	fd_set write; 
	fd_set except;

	int nfds = 0;

	fd_set *readPtr		= fillSetFromVector( read, inReadSet, nfds );
	fd_set *writePtr	= fillSetFromVector( read, inWriteSet, nfds );
	fd_set *exceptPtr	= fillSetFromVector( read, inExceptSet, nfds );

	int toRet = select( nfds + 1, readPtr, writePtr, exceptPtr, nullptr );

	if ( 0 < toRet )
	{
		fillVectorFromSet( outReadSet, inReadSet, read );
		fillVectorFromSet( outWriteSet, inWriteSet, write );
		fillVectorFromSet( outExceptSet, inExceptSet, except );
	}

	return toRet;

}

UDPSocketPtr SocketUtil::createUDPSocket( SocketAddressFamily family ) noexcept
{
	SOCKET s = socket( family, SOCK_DGRAM, IPPROTO_UDP );

	if ( INVALID_SOCKET == s )
	{
		reportError( "SocketUtil::CreateUDPSocket" );
		return nullptr;
	}

	return UDPSocketPtr( new UDPSocket( s ) );
}

TCPSocketPtr SocketUtil::createTCPSocket(SocketAddressFamily family) noexcept
{
	SOCKET s = socket( family, SOCK_STREAM, IPPROTO_TCP );

	if ( INVALID_SOCKET == s )
	{
		reportError( "SocketUtil::CreateTCPSocket" );
		return nullptr;
	}

	return TCPSocketPtr( new TCPSocket( s ) );


}

inline fd_set * SocketUtil::fillSetFromVector( fd_set & outSet, const vector<TCPSocketPtr>* inSockets, int & ioNaxNfds ) noexcept
{
	if ( nullptr == inSockets )
	{
		return nullptr;
	}

	FD_ZERO( &outSet );
		
	for ( const TCPSocketPtr& socket : *inSockets )
	{
		FD_SET( socket->m_socket, &outSet );
#if !_WIN32
			ioNaxNfds = std::max( ioNaxNfds, socket->mSocket );
#endif
	}
		return &outSet;
}

inline void SocketUtil::fillVectorFromSet(vector<TCPSocketPtr>* outSockets, const vector<TCPSocketPtr>* inSockets, const fd_set & inSet) noexcept
{
	if ( nullptr == inSockets )
	{
		return;
	}
	if ( nullptr == outSockets )
	{
		return;
	}
	
	outSockets->clear();
	
	for ( const TCPSocketPtr& socket : *inSockets )
	{
		if( FD_ISSET( socket->m_socket, &inSet ) )
		{
			outSockets->push_back( socket );
		}
	}
}
