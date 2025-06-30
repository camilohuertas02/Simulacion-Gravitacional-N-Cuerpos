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
    vector3D();
    vector3D(double x0, double y0, double z0);
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
    double x() const;
    /**
     * @brief Obtiene la componente Y del vector
     * @return Componente Y
     */    
    double y() const;
    /**
     * @brief Obtiene la componente Z del vector
     * @return Componente Z
     */    
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
