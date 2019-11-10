#pragma once


class SocketAddressFactory
{
	static SocketAddressPtr createIPv4FromString( const string& string ) noexcept;
};