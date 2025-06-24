#include "vector3D.h"
#include <cmath>

void vector3D::load(double x0, double y0, double z0) {
    X = x0; Y = y0; Z = z0;
}

double vector3D::x() { return X; }
double vector3D::y() { return Y; }
double vector3D::z() { return Z; }

void vector3D::show() {
    std::cout << "(" << X << ", " << Y << ", " << Z << ")\n";
}

void vector3D::operator=(vector3D v2) {
    X = v2.X; Y = v2.Y; Z = v2.Z;
}

vector3D vector3D::operator+(vector3D v2) {
    vector3D total;
    total.X = X + v2.X;
    total.Y = Y + v2.Y;
    total.Z = Z + v2.Z;
    return total;
}

void vector3D::operator+=(vector3D v2) {
    X += v2.X; Y += v2.Y; Z += v2.Z;
}

vector3D vector3D::operator-(vector3D v2) {
    vector3D total;
    total.X = X - v2.X;
    total.Y = Y - v2.Y;
    total.Z = Z - v2.Z;
    return total;
}

void vector3D::operator-=(vector3D v2) {
    X -= v2.X; Y -= v2.Y; Z -= v2.Z;
}

vector3D vector3D::operator*(double a) {
    vector3D total;
    total.X = X * a;
    total.Y = Y * a;
    total.Z = Z * a;
    return total;
}

vector3D operator*(double a, vector3D v1) {
    return v1 * a;
}

void vector3D::operator*=(double a) {
    X *= a; Y *= a; Z *= a;
}

vector3D vector3D::operator/(double a) {
    vector3D total;
    total.X = X / a;
    total.Y = Y / a;
    total.Z = Z / a;
    return total;
}

void vector3D::operator/=(double a) {
    X /= a; Y /= a; Z /= a;
}

double vector3D::operator*(vector3D v2) {
    return X * v2.X + Y * v2.Y + Z * v2.Z;
}

vector3D vector3D::operator^(vector3D v2) {
    vector3D total;
    total.X = Y * v2.Z - Z * v2.Y;
    total.Y = Z * v2.X - X * v2.Z;
    total.Z = X * v2.Y - Y * v2.X;
    return total;
}

double vector3D::norm2() {
    return X * X + Y * Y + Z * Z;
}

double vector3D::norm() {
    return std::sqrt(norm2());
}

double angle(vector3D v1, vector3D v2) {
    return std::acos((v1 * v2) / (v1.norm() * v2.norm()));
}
