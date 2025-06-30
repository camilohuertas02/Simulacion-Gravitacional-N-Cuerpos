#include "vector3D.h"
#include <cmath>
#include <iostream>

// --- IMPLEMENTACIÓN DE CONSTRUCTORES ---
// Constructor por defecto
vector3D::vector3D() : X(0), Y(0), Z(0) {}

// Constructor que inicializa con valores
vector3D::vector3D(double x0, double y0, double z0) : X(x0), Y(y0), Z(z0) {}


// --- IMPLEMENTACIÓN DE MÉTODOS ---
void vector3D::load(double x0, double y0, double z0) {
    X = x0; Y = y0; Z = z0;
}

// Métodos "getter" y de visualización ahora son const
double vector3D::x() const { return X; }
double vector3D::y() const { return Y; }
double vector3D::z() const { return Z; }

void vector3D::show() const {
    std::cout << "(" << X << ", " << Y << ", " << Z << ")";
}

// La función operator= HA SIDO ELIMINADA. El compilador la generará por nosotros.

vector3D vector3D::operator+(const vector3D& v2) const {
    return vector3D(X + v2.X, Y + v2.Y, Z + v2.Z); // Versión más compacta
}

void vector3D::operator+=(const vector3D& v2) {
    X += v2.X; Y += v2.Y; Z += v2.Z;
}

vector3D vector3D::operator-(const vector3D& v2) const {
    return vector3D(X - v2.X, Y - v2.Y, Z - v2.Z); // Versión más compacta
}

void vector3D::operator-=(const vector3D& v2) {
    X -= v2.X; Y -= v2.Y; Z -= v2.Z;
}

vector3D vector3D::operator*(double a) const {
    return vector3D(X * a, Y * a, Z * a); // Versión más compacta
}

// Función libre (no es un método de la clase)
vector3D operator*(double a, const vector3D& v1) {
    return v1 * a; // Reutiliza el operator* que ya es miembro de la clase
}

void vector3D::operator*=(double a) {
    X *= a; Y *= a; Z *= a;
}

vector3D vector3D::operator/(double a) const {
    return vector3D(X / a, Y / a, Z / a); // Versión más compacta
}

void vector3D::operator/=(double a) {
    X /= a; Y /= a; Z /= a;
}

// Producto punto (dot product)
double vector3D::operator*(const vector3D& v2) const {
    return X * v2.X + Y * v2.Y + Z * v2.Z;
}

// Producto cruz (cross product)
vector3D vector3D::operator^(const vector3D& v2) const {
    return vector3D(Y * v2.Z - Z * v2.Y,
                    Z * v2.X - X * v2.Z,
                    X * v2.Y - Y * v2.X);
}

double vector3D::norm2() const {
    return X * X + Y * Y + Z * Z;
}

double vector3D::norm() const {
    return std::sqrt(norm2());
}

// Función libre
double angle(const vector3D& v1, const vector3D& v2) {
    double norm_product = v1.norm() * v2.norm();
    // Evitar división por cero si uno de los vectores es nulo
    if (norm_product == 0) return 0;
    return std::acos((v1 * v2) / norm_product);
}
