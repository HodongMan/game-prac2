#pragma once


class TCPSocket
{
public:
	~TCPSocket( void );
	int						Connect( const SocketAddress& address ) noexcept;
	int						Bind( const SocketAddress& address ) noexcept;
	int						Listen( int backLog = 32 ) noexcept;
	shared_ptr< TCPSocket >	Address( SocketAddress& fromAddress ) noexcept;
	int32_t					Send( const void* data, size_t len ) noexcept;
	int32_t					Receive( void* buffer, size_t len ) noexcept;

private:
	friend class SocketUtil;
	TCPSocket( SOCKET socket ) 
		: m_socket( socket )
	{
	
	}

	SOCKET m_socket;
};

typedef shared_ptr< TCPSocket > TCPSocketPtr;