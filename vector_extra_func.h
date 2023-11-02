#ifndef VECTOR_EXTRA_FUNC_H
#define VECTOR_EXTRA_FUNC_H
#include <vector>
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;
Vector2f PolarToDSC(float absolute, float angle);
float Absolute(Vector2f my_vector);

Vector2f VectorSum(Vector2f first, Vector2f second);
Vector2f ScalingVector(Vector2f my_vector, float my_scale);
#endif