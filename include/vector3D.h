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
    /// Inicializa el vector con componentes (x, y, z)
    void load(double x0, double y0, double z0);

    /// Retorna la componente X
    double x(void);
    /// Retorna la componente Y
    double y(void);
    /// Retorna la componente Z
    double z(void);

    /// Muestra el vector por consola
    void show(void);

    /// Sobrecarga de operador '='
    void operator=(vector3D v2);

    /// Sobrecarga de suma
    vector3D operator+(vector3D v2);
    void operator+=(vector3D v2);

    /// Sobrecarga de resta
    vector3D operator-(vector3D v2);
    void operator-=(vector3D v2);

    /// Producto por escalar
    vector3D operator*(double a);
    void operator*=(double a);
    friend vector3D operator*(double a, vector3D v1);

    /// División por escalar
    vector3D operator/(double a);
    void operator/=(double a);

    /// Producto punto
    double operator*(vector3D v2);

    /// Producto cruz
    vector3D operator^(vector3D v2);

    /// Norma al cuadrado
    double norm2(void);
    /// Norma (módulo)
    double norm(void);

    /// Ángulo entre dos vectores
    friend double angle(vector3D v1, vector3D v2);
};

#endif // VECTOR3D_H
