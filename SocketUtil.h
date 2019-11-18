#pragma once


class SocketUtil
{
public:
	static bool				staticInit( void ) noexcept;
	static void				cleanUp( void ) noexcept;

	static void				reportError( const char* operationDesc ) noexcept;
	static int				getLastError( void ) noexcept;

	static int				Select( const vector< TCPSocketPtr >* inReadSet, 
									vector< TCPSocketPtr >* outReadSet,
									const vector< TCPSocketPtr >* inWriteSet,
									vector< TCPSocketPtr >* outWriteSet, 
									const vector< TCPSocketPtr >* inExceptSet,
									vector< TCPSocketPtr >* outExceptSet ) noexcept;

	static UDPSocketPtr		createUDPSocket( SocketAddressFamily family ) noexcept;
	static TCPSocketPtr		createTCPSocket( SocketAddressFamily family ) noexcept;

private:
	inline static fd_set*	fillSetFromVector( fd_set& outSet, const vector< TCPSocketPtr >* inSockets, int& ioNaxNfds ) noexcept;
	inline static void		fillVectorFromSet( vector< TCPSocketPtr >* outSockets, const vector< TCPSocketPtr >* inSockets, const fd_set& inSet ) noexcept;
};