/**
 * @file vector3D.h
 * @brief Definición de la clase vector3D para álgebra vectorial 3D
 * @author Isabel Nieto & Camilo Huertas  
 * @date 2025
 */

#ifndef VECTOR3D_H
#define VECTOR3D_H

#include <iostream>

/**
 * @brief Clase para manipular vectores tridimensionales
 * @details Proporciona operaciones básicas de álgebra vectorial necesarias
 *          para simulaciones físicas en 3D
 */
class vector3D {
private:
    double X, Y, Z; ///< Componentes cartesianas del vector

public:
    /**
     * @brief Inicializa el vector con componentes específicas
     * @param x0 Componente X
     * @param y0 Componente Y  
     * @param z0 Componente Z
     * @post El vector queda inicializado con (x0, y0, z0)
     */
    void load(double x0, double y0, double z0);

    /**
     * @brief Obtiene la componente X del vector
     * @return Componente X
     */
    double x(void);
    
    /**
     * @brief Obtiene la componente Y del vector
     * @return Componente Y
     */
    double y(void);
    
    /**
     * @brief Obtiene la componente Z del vector
     * @return Componente Z
     */
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
