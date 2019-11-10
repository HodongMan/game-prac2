#include "pch.h"
#include "Math.h"

#include <random>

const Vector3 Vector3::Zero( 0.0f, 0.0f, 0.0f );
const Vector3 Vector3::UnitX( 1.0f, 0.0f, 0.0f );
const Vector3 Vector3::UnitY( 0.0f, 1.0f, 0.0f );
const Vector3 Vector3::UnitZ( 0.0f, 0.0f, 1.0f );

float Math::getRandomFloat( void ) noexcept
{
	static std::random_device rand;
	static std::mt19937 gen( rand() );
	static std::uniform_real_distribution< float > dis( 0.f, 1.f );

	return dis( gen );
}

Vector3 Math::getRandomVector( const Vector3& minValue, const Vector3& maxValue ) noexcept
{
	Vector3 randomValue = Vector3( getRandomFloat(), getRandomFloat(), getRandomFloat() );
	return minValue + ( maxValue - minValue ) * randomValue;
}
