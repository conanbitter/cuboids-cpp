#pragma once

struct Vector2D {
    float x;
    float y;

    Vector2D() : x{0.0f}, y{0.0f} {}
    Vector2D(float x, float y) : x{x}, y{y} {}
    bool isZero();
    float length();
    Vector2D toUnit();
    float distance(const Vector2D& other);
    friend Vector2D& operator+=(Vector2D& left, const Vector2D& right);
    friend Vector2D operator+(Vector2D left, const Vector2D& right);
    friend Vector2D& operator-=(Vector2D& left, const Vector2D& right);
    friend Vector2D operator-(Vector2D left, const Vector2D& right);
    friend Vector2D operator*(const Vector2D& left, const float right);
    friend Vector2D operator/(const Vector2D& left, const float right);

    Vector2D rotate(float angle);
    float pseudoCross(const Vector2D& other);
};