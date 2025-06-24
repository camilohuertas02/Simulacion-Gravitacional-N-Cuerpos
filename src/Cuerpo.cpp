#include "Cuerpo.h"
#include "vector3D.h"
#include "utilidades.h" // Para G
#include <cmath>       // Para std::pow y std::sqrt (aunque vector3D::norm ya usa sqrt)

void Cuerpo::Inicie(double x0, double y0, double z0,
                    double Vx0, double Vy0, double Vz0,
                    double m0, double R0) {
    r.load(x0, y0, z0);
    V.load(Vx0, Vy0, Vz0);
    m = m0;
    R = R0;
    F.load(0, 0, 0); // Fuerza inicial es cero
}

void Cuerpo::BorreFuerza() {
    F.load(0, 0, 0);
}

void Cuerpo::AdicioneFuerzaGravitacional(Cuerpo &otroCuerpo) {
    vector3D dr = otroCuerpo.r - r; // Vector de r a otroCuerpo.r
    double distancia_cubed = std::pow(dr.norm(), 3);

    // Evitar división por cero si los cuerpos están en la misma posición (aunque verificarDatos debería prevenir esto)
    if (distancia_cubed < 1e-12) { // Un umbral pequeño para evitar problemas numéricos
        return;
    }

    // Fuerza F = G * m1 * m2 * (r2 - r1) / |r2 - r1|^3
    vector3D F_grav = dr * (G * m * otroCuerpo.m / distancia_cubed);
    F += F_grav;
}

// Actualiza la posición: r(t+dt) = r(t) + V(t)*dt + (F(t)/(2*m))*dt*dt
void Cuerpo::Muevase_r(double dt) {
    if (m == 0) return; // No mover cuerpos sin masa (o manejar error)
    vector3D aceleracion_actual = F / m;
    r += V * dt + aceleracion_actual * (0.5 * dt * dt);
}

// Actualiza la velocidad: V(t+dt) = V(t) + (F(t) + F(t+dt))/(2*m)*dt
void Cuerpo::Muevase_V(double dt, const vector3D &F_siguiente_const) {
    if (m == 0) return; // No mover cuerpos sin masa

    vector3D F_siguiente = F_siguiente_const; // Copia no constante para poder usar operadores no-const

    vector3D aceleracion_actual = F / m;
    vector3D aceleracion_siguiente = F_siguiente / m;
    V += (aceleracion_actual + aceleracion_siguiente) * (0.5 * dt);
}
