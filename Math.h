#pragma once

class Vector3
{
public:

	float		m_x, m_y, m_z;

	Vector3( float x, float y, float z ) 
		: m_x( x )
		, m_y( y )
		, m_z( z )
	{
	
	}

	Vector3() 
		: m_x( 0.0f )
		, m_y( 0.0f )
		, m_z( 0.0f )
	{
	
	}

	void set( const float x, const float y, const float z ) noexcept
	{
		m_x = x;
		m_y = y;
		m_z = z;
	}

	friend Vector3 operator+( const Vector3& lhs, const Vector3& rhs ) noexcept
	{
		return Vector3( lhs.m_x + rhs.m_x, lhs.m_y + rhs.m_y, lhs.m_z + rhs.m_z );
	}

	friend Vector3 operator-( const Vector3& lhs, const Vector3& rhs ) noexcept
	{
		return Vector3( lhs.m_x - rhs.m_x, lhs.m_y - rhs.m_y, lhs.m_z - rhs.m_z );
	}

	friend Vector3 operator*( const Vector3& lhs, const Vector3& rhs ) noexcept
	{
		return Vector3( lhs.m_x * rhs.m_x, lhs.m_y * rhs.m_y, lhs.m_z * rhs.m_z );
	}

	friend Vector3 operator*( const float scala, const Vector3& vector ) noexcept
	{
		return Vector3( vector.m_x * scala, vector.m_y * scala, vector.m_z * scala );
	}

	friend Vector3 operator*( const Vector3& vector, const float scala ) noexcept
	{
		return Vector3( vector.m_x * scala, vector.m_y * scala, vector.m_z * scala );
	}

	Vector3& operator*=( const float scalar ) noexcept
	{
		m_x *= scalar;
		m_y *= scalar;
		m_z *= scalar;

		return *this;
	}

	Vector3& operator+=( const Vector3& rhs ) noexcept
	{
		m_x += rhs.m_x;
		m_y += rhs.m_y;
		m_z += rhs.m_z;

		return *this;
	}

	Vector3& operator-=( const Vector3& rhs ) noexcept
	{
		m_x -= rhs.m_x;
		m_y -= rhs.m_y;
		m_z -= rhs.m_z;

		return *this;
	}

	float length( void ) const noexcept
	{
		return sqrtf( m_x * m_x + m_y * m_y + m_z * m_z );
	}

	float lengthSq( void ) const noexcept
	{
		return m_x * m_x + m_y * m_y + m_z * m_z;
	}

	float length2D( void ) const noexcept
	{
		return sqrtf( m_x * m_x + m_y * m_y );
	}

	float lengthSq2D( void ) const noexcept
	{
		return m_x * m_x + m_y * m_y;
	}

	void normalize( void ) noexcept
	{
		float len = length();
		m_x /= len;
		m_y /= len;
		m_z /= len;
	}

	void normalize2D( void) noexcept
	{
		float length = length2D();
		m_x /= length;
		m_y /= length;
	}

	friend float dot( const Vector3& lhs, const Vector3& rhs ) noexcept
	{
		return lhs.m_x * rhs.m_x + lhs.m_y * rhs.m_y + lhs.m_z * rhs.m_z;
	}

	friend float dot2D( const Vector3& lhs, const Vector3& rhs ) noexcept
	{
		return lhs.m_x * rhs.m_x + lhs.m_y * rhs.m_y;
	}

	friend Vector3 cross( const Vector3& lhs, const Vector3& rhs ) noexcept
	{
		Vector3 temp;
		temp.m_x = lhs.m_y * rhs.m_z - lhs.m_z * rhs.m_y;
		temp.m_y = lhs.m_z * rhs.m_x - lhs.m_x * rhs.m_z;
		temp.m_z = lhs.m_x * rhs.m_y - lhs.m_y * rhs.m_x;

		return temp;
	}

	friend Vector3 lerp( const Vector3& inA, const Vector3& inB, const float t ) noexcept
	{
		return Vector3( inA + t * ( inB - inA ) );
	}

	static const Vector3 Zero;
	static const Vector3 UnitX;
	static const Vector3 UnitY;
	static const Vector3 UnitZ;
};


class Quaternion
{
public:

	float		m_x, m_y, m_z, m_w;

};


template< int value, int bits >
struct GetRequiredBitsHelper
{
	enum { value = GetRequiredBitsHelper< (value >> 1), bit + 1 >::value };
};

template< int bit >
struct GetRequiredBitsHelper< 0, bit >
{
	enum { value = bit };
};

template< int value >
struct GetRequiredBits
{
	enum { value = GetRequiredBitsHelper< value, 0 >::value };
};

namespace Math
{
	const float PI = 3.1415926535f;
	float getRandomFloat( void ) noexcept;

	Vector3 getRandomVector( const Vector3& minValue, const Vector3& maxValue ) noexcept;

	inline bool	is2DVectorEqual( const Vector3& inA, const Vector3& inB ) noexcept
	{
		return ( inA.m_x == inB.m_x && inA.m_y == inB.m_y );
	}

	inline float toDegrees( const float inRadians ) noexcept
	{
		return inRadians * 180.0f / PI;
	}
}

namespace Colors
{
	static const Vector3 Black( 0.0f, 0.0f, 0.0f );
	static const Vector3 White( 1.0f, 1.0f, 1.0f );
	static const Vector3 Red( 1.0f, 0.0f, 0.0f );
	static const Vector3 Green( 0.0f, 1.0f, 0.0f );
	static const Vector3 Blue( 0.0f, 0.0f, 1.0f );
	static const Vector3 LightYellow( 1.0f, 1.0f, 0.88f );
	static const Vector3 LightBlue( 0.68f, 0.85f, 0.9f );
	static const Vector3 LightPink( 1.0f, 0.71f, 0.76f );
	static const Vector3 LightGreen( 0.56f, 0.93f, 0.56f );
}