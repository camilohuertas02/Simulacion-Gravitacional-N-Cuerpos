#ifndef CUERPO_H
#define CUERPO_H

#include "vector3D.h"
#include "utilidades.h" // Para G

class Cuerpo {
public:
    vector3D r, V, F; // Posición, Velocidad, Fuerza
    double m, R;      // Masa, Radio

    // Constructor (opcional, se puede usar Inicie)
    Cuerpo() {};

    // Inicializa los atributos del cuerpo
    void Inicie(double x0, double y0, double z0,
                double Vx0, double Vy0, double Vz0,
                double m0, double R0);

    // Reinicia el vector de fuerza a cero
    void BorreFuerza();

    // Calcula y suma la fuerza gravitacional ejercida por otroCuerpo
    void AdicioneFuerzaGravitacional(Cuerpo &otroCuerpo);

    // Actualiza la posición y velocidad usando el algoritmo de Verlet.
    // La implementación de Verlet requiere acceso a la fuerza actual F(t) y la fuerza futura F(t+dt).
    // Esta clase almacenará F(t). El bucle de simulación manejará el cálculo de F(t+dt).
    // r(t+dt) = r(t) + V(t)*dt + (F(t)/(2*m))*dt*dt
    void Muevase_r(double dt);
    // V(t+dt) = V(t) + (F(t) + F(t+dt))/(2*m)*dt
    void Muevase_V(double dt, const vector3D &F_siguiente);


    // Métodos inline para obtener las componentes de la posición
    inline double Getx() { return r.x(); }
    inline double Gety() { return r.y(); }
    inline double Getz() { return r.z(); }

    // Métodos inline para obtener las componentes de la velocidad (útil para salida)
    inline double GetVx() { return V.x(); }
    inline double GetVy() { return V.y(); }
    inline double GetVz() { return V.z(); }
    inline double GetVnorm() { return V.norm(); } // Velocidad escalar

    // Método para obtener la masa
    inline double Getm() { return m; }
};

#endif // CUERPO_H
