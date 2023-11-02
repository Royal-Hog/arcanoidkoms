#include "vector_extra_func.h"

sf::Vector2f PolarToDSC(float absolute, float angle)
{
	return Vector2f(absolute * cos(angle), absolute * sin(angle));
}
float Absolute(Vector2f my_vector)
{
	return sqrt(my_vector.x * my_vector.x + my_vector.y * my_vector.y);
}

Vector2f VectorSum(Vector2f first, Vector2f second)
{
	return Vector2f(first.x + second.x, first.y + second.y);
}
Vector2f ScalingVector(Vector2f my_vector, float my_scale)
{
	return Vector2f(my_scale * my_vector.x, my_scale * my_vector.y);
}