#include <math.h>
#include "vectors.hpp"

const float ROUNDING_ERROR_f32 = 0.000001f;

bool floatIsZero(float val) {
    return (val + ROUNDING_ERROR_f32 >= 0.0f) && (val - ROUNDING_ERROR_f32 <= 0.0f);
}

bool floatInUnit(float val) {
    return (val >= 0.0f) && (val <= 1.0f);
}

bool Vector2D::isZero() {
    return floatIsZero(x) && floatIsZero(y);
}

float Vector2D::length() {
    return sqrtf(x * x + y * y);
}

Vector2D Vector2D::toUnit() {
    float len = 1 / length();
    return Vector2D(x * len, y * len);
}

float Vector2D::distance(const Vector2D& other) const {
    return sqrtf((x - other.x) * (x - other.x) + (y - other.y) * (y - other.y));
}

Vector2D& operator+=(Vector2D& left, const Vector2D& right) {
    left.x += right.x;
    left.y += right.y;
    return left;
}

Vector2D& operator-=(Vector2D& left, const Vector2D& right) {
    left.x -= right.x;
    left.y -= right.y;
    return left;
}

Vector2D operator+(Vector2D left, const Vector2D& right) {
    left += right;
    return left;
}

Vector2D operator-(Vector2D left, const Vector2D& right) {
    left -= right;
    return left;
}

Vector2D operator*(const Vector2D& left, const float right) {
    return Vector2D(left.x * right, left.y * right);
}

Vector2D operator/(const Vector2D& left, const float right) {
    return Vector2D(left.x / right, left.y / right);
}

Vector2D Vector2D::rotate(float angle) {
    return Vector2D(
        x * cosf(angle) - y * sinf(angle),
        x * sinf(angle) + y * cosf(angle));
}

float Vector2D::pseudoCross(const Vector2D& other) {
    return x * other.y - y * other.x;
}