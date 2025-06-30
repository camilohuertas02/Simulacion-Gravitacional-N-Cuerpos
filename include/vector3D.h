/* ---------------------------------------------
 * vector3D.h
 * Definición de la clase vector3D para álgebra vectorial en 3D.
 * ---------------------------------------------*/
#ifndef VECTOR3D_H
#define VECTOR3D_H

#include <iostream>

/**
 * @brief Clase para manipular vectores tridimensionales.
 */
class vector3D {
private:
    double X, Y, Z;

public:
    // --- Constructores (Buena Práctica) ---
    /// Inicializa el vector en (0,0,0)
    vector3D();
    /// Inicializa el vector con componentes (x, y, z)
    vector3D(double x0, double y0, double z0);

    // --- Métodos de Acceso y Modificación ---
    /// Carga el vector con componentes (x, y, z)
    void load(double x0, double y0, double z0);

    /// Retorna la componente X
    double x() const;
    /// Retorna la componente Y
    double y() const;
    /// Retorna la componente Z
    double z() const;

    /// Muestra el vector por consola
    void show() const;

    // --- Sobrecarga de Operadores ---
    // operator= se elimina para usar la versión generada por el compilador

    /// Sobrecarga de suma
    vector3D operator+(const vector3D& v2) const;
    void operator+=(const vector3D& v2);

    /// Sobrecarga de resta
    vector3D operator-(const vector3D& v2) const;
    void operator-=(const vector3D& v2);

    /// Producto por escalar
    vector3D operator*(double a) const;
    void operator*=(double a);
    
    /// División por escalar
    vector3D operator/(double a) const;
    void operator/=(double a);

    /// Producto punto
    double operator*(const vector3D& v2) const;

    /// Producto cruz
    vector3D operator^(const vector3D& v2) const;

    // --- Métodos de Cálculo ---
    /// Norma al cuadrado
    double norm2() const;
    /// Norma (módulo)
    double norm() const;
};

// --- Funciones Amigas (friend) ahora definidas como funciones libres ---
// No necesitan ser 'friend' si solo usan la interfaz pública (x(), y(), z())
vector3D operator*(double a, const vector3D& v1);
double angle(const vector3D& v1, const vector3D& v2);


#endif // VECTOR3D_H
