#ifndef CUERPO_H
#define CUERPO_H

#include "vector3D.h"
#include "utilidades.h" // Para G

/**
 * @file Cuerpo.h
 * @brief Definición de la clase Cuerpo para simulación gravitacional N-cuerpos
 * @author Isabel Nieto & Camilo Huertas
 * @date 2025
 */

/**
 * @brief Clase que representa un cuerpo celeste en la simulación gravitacional
 * 
 * Esta clase encapsula las propiedades físicas y métodos necesarios para
 * simular el comportamiento de un cuerpo en un sistema gravitacional N-cuerpos.
 * Utiliza el algoritmo de Verlet para la integración numérica.
 * 
 * @see vector3D
 * @see utilidades.h
 */
class Cuerpo {
public:
    vector3D r; ///< Vector posición del cuerpo [unidades de longitud]
    vector3D V; ///< Vector velocidad del cuerpo [unidades de velocidad]
    vector3D F; ///< Vector fuerza total sobre el cuerpo [unidades de fuerza]
    double m;   ///< Masa del cuerpo [unidades de masa]
    double R;   ///< Radio del cuerpo [unidades de longitud] - Solo referencia, no afecta cálculos

    /**
     * @brief Constructor por defecto
     * @details Inicializa todos los vectores y valores escalares en cero
     */
    Cuerpo() {};

    /**
     * @brief Inicializa los atributos del cuerpo con valores específicos
     * @param x0 Posición inicial en X [unidades de longitud]
     * @param y0 Posición inicial en Y [unidades de longitud]
     * @param z0 Posición inicial en Z [unidades de longitud]
     * @param Vx0 Velocidad inicial en X [unidades de velocidad]
     * @param Vy0 Velocidad inicial en Y [unidades de velocidad]
     * @param Vz0 Velocidad inicial en Z [unidades de velocidad]
     * @param m0 Masa del cuerpo [unidades de masa] - Debe ser > 0
     * @param R0 Radio del cuerpo [unidades de longitud] - Debe ser >= 0
     * @pre m0 > 0 && R0 >= 0
     * @post El cuerpo queda inicializado con fuerza cero
     */
    void Inicie(double x0, double y0, double z0,
                double Vx0, double Vy0, double Vz0,
                double m0, double R0);

    /**
     * @brief Reinicia el vector de fuerza a cero
     * @details Se debe llamar antes de calcular las fuerzas en cada paso temporal
     * @post F = (0, 0, 0)
     */
    void BorreFuerza();

    /**
     * @brief Calcula y suma la fuerza gravitacional ejercida por otro cuerpo
     * @param otroCuerpo Referencia al cuerpo que ejerce la fuerza gravitacional
     * @details Implementa la ley de gravitación universal: F = G*m1*m2/r²
     * @pre La distancia entre cuerpos debe ser > 0 para evitar singularidades
     * @post La fuerza F se actualiza sumando la contribución gravitacional
     * @warning No verifica colisiones físicas entre cuerpos
     */
    void AdicioneFuerzaGravitacional(Cuerpo &otroCuerpo);

    /**
     * @brief Actualiza la posición usando el algoritmo de Verlet
     * @param dt Paso de tiempo para la integración [unidades de tiempo]
     * @details Implementa: r(t+dt) = r(t) + V(t)*dt + (F(t)/(2*m))*dt²
     * @pre dt > 0 && m > 0
     * @post La posición r se actualiza al siguiente paso temporal
     */
    void Muevase_r(double dt);
    
    /**
     * @brief Actualiza la velocidad usando el algoritmo de Verlet
     * @param dt Paso de tiempo para la integración [unidades de tiempo]
     * @param F_siguiente Fuerza en el siguiente paso de tiempo F(t+dt)
     * @details Implementa: V(t+dt) = V(t) + (F(t) + F(t+dt))/(2*m)*dt
     * @pre dt > 0 && m > 0
     * @post La velocidad V se actualiza al siguiente paso temporal
     */
    void Muevase_V(double dt, const vector3D &F_siguiente);

    // === Métodos de acceso (getters) ===
    
    /**
     * @brief Obtiene la coordenada X de la posición
     * @return Coordenada X actual [unidades de longitud]
     */
    inline double Getx() { return r.x(); }
    
    /**
     * @brief Obtiene la coordenada Y de la posición
     * @return Coordenada Y actual [unidades de longitud]
     */
    inline double Gety() { return r.y(); }
    
    /**
     * @brief Obtiene la coordenada Z de la posición
     * @return Coordenada Z actual [unidades de longitud]
     */
    inline double Getz() { return r.z(); }

    /**
     * @brief Obtiene la componente X de la velocidad
     * @return Velocidad en X [unidades de velocidad]
     */
    inline double GetVx() { return V.x(); }
    
    /**
     * @brief Obtiene la componente Y de la velocidad
     * @return Velocidad en Y [unidades de velocidad]
     */
    inline double GetVy() { return V.y(); }
    
    /**
     * @brief Obtiene la componente Z de la velocidad
     * @return Velocidad en Z [unidades de velocidad]
     */
    inline double GetVz() { return V.z(); }
    
    /**
     * @brief Obtiene la magnitud de la velocidad
     * @return Velocidad escalar (norma del vector velocidad) [unidades de velocidad]
     * @details Calcula |V| = sqrt(Vx² + Vy² + Vz²)
     */
    inline double GetVnorm() { return V.norm(); }

    /**
     * @brief Obtiene la masa del cuerpo
     * @return Masa del cuerpo [unidades de masa]
     */
    inline double Getm() { return m; }
};

#endif // CUERPO_H
