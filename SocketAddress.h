#pragma once

class UDPSocket;
class TCPSocket;

class SocketAddress
{
public:
	SocketAddress( uint32_t address, uint16_t port ) noexcept;
	SocketAddress( const sockaddr& socketAddress ) noexcept;
	SocketAddress( void ) noexcept;

	bool operator==( const SocketAddress& rhs ) const noexcept
	{
		return ( ( AF_INET == m_sockAddr.sa_family ) &&
				 ( getAsSockAddrIn()->sin_port == rhs.getAsSockAddrIn()->sin_port ) &&
				 ( getIP4Ref() == rhs.getIP4Ref() ) );
	}

	size_t getHash( void ) const noexcept
	{
		return( ( getIP4Ref() ) | 
				( static_cast< uint32_t >( getAsSockAddrIn()->sin_port ) << 13 ) |
				( m_sockAddr.sa_family ) );
	}

	uint32_t		getSize( void ) const noexcept { return sizeof( sockaddr ); }
	string			toString( void ) const noexcept;

private:
	friend class UDPSocket;
	friend class TCPSocket;

	sockaddr m_sockAddr;

#if _WIN32
	uint32_t&				getIP4Ref( void ) noexcept { return *reinterpret_cast< uint32_t* >( &getAsSockAddrIn()->sin_addr.S_un.S_addr ); }
	const uint32_t&			getIP4Ref( void ) const noexcept { return *reinterpret_cast< const uint32_t* >( &getAsSockAddrIn()->sin_addr.S_un.S_addr ); }
#else
	uint32_t&				getIP4Ref( void ) noexcept { return getAsSockAddrIn()->sin_addr.s_addr; }
	const uint32_t&			getIP4Ref( void ) const noexcept { return getAsSockAddrIn()->sin_addr.s_addr; }
#endif

	sockaddr_in*			getAsSockAddrIn( void ) noexcept { return reinterpret_cast< sockaddr_in* >( &m_sockAddr ); }
	const sockaddr_in*		getAsSockAddrIn( void ) const noexcept { return reinterpret_cast< const sockaddr_in* >( &m_sockAddr ); }
};

typedef shared_ptr<SocketAddress> SocketAddressPtr;

namespace std
{
	template<> struct hash< SocketAddress >
	{
		size_t operator()( const SocketAddress& address ) const noexcept
		{
			return address.getHash();
		}
	};
}