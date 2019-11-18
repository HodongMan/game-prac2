#pragma once

#include <cstdint>
#include <cstdlib>
#include <string>

class GameObject;


inline uint32_t convertToFixed( const float inNumber, const float min, const float precision ) noexcept
{
	return static_cast< int > ( ( inNumber - min) / precision );
}

inline float convertFromFixed( const uint32_t inNumber, const float min, const float precision ) noexcept
{
	return static_cast< float >( inNumber ) * precision + min;
}


class OutputMemoryBitStream
{
public:
	OutputMemoryBitStream( void )
		: m_bitHead( 0 )
		, m_buffer( nullptr ) 
	{
		reallocBuffer( 1500 * 8 );
	}

	~OutputMemoryBitStream( void )
	{
		std::free( m_buffer );
	}

	void			writeBits( uint8_t data, uint32_t bitCount ) noexcept;
	void			writeBits( const void* data, uint32_t bitCount ) noexcept;

private:
	void			reallocBuffer( uint32_t newBitCapacity ) noexcept;

	char*			m_buffer;
	uint32_t		m_bitHead;
	uint32_t		m_bitCapacity;
};