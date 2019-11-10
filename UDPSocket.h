#pragma once


class UDPSocket
{
public:
	~UDPSocket( void );

	int Bind( const SocketAddress& toAddress ) noexcept;
	int SendTo( const void* toSend, int length, const SocketAddress& toAddress ) noexcept;
	int ReceiveFrom( void* toReceive, int maxLength, SocketAddress& fromAddress ) noexcept;

	int setNonBlockingMode( const bool inShouldBeNonBlocking ) noexcept;

private:
	friend class SocketUtil;

	UDPSocket( SOCKET socket ) 
		: m_socket( socket )
	{
		
	}

	SOCKET m_socket;
};

typedef shared_ptr< UDPSocket >	UDPSocketPtr;