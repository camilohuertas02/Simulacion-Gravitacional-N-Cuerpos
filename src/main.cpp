#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <cmath>
#include <limits>
#include <iomanip>
#include <cstdlib>

#include "vector3D.h"
#include "Cuerpo.h"
#include "utilidades.h"

// Variables globales para la simulación
int N_cuerpos;
double dt_sim;
double t_max_sim;
std::vector<Cuerpo> planetas;
std::vector<vector3D> fuerzas_siguientes;

// --- Declaraciones de funciones ---
void solicitarDatos();
bool verificarDatos();
void calcularTodasLasFuerzas(std::vector<Cuerpo>& cuerpos_actuales, std::vector<vector3D>& fuerzas_a_calcular);
double calcularEnergiaCineticaTotal(const std::vector<Cuerpo>& cuerpos_actuales);
double calcularEnergiaPotencialTotal(const std::vector<Cuerpo>& cuerpos_actuales);
void graficarResultados();

// --- Implementación de funciones ---

void solicitarDatos() {
    std::cout << "--- Configuración de la Simulación Gravitacional N-Cuerpos ---" << std::endl;
    std::cout << "Ingrese el número de cuerpos (N): ";
    while (!(std::cin >> N_cuerpos) || N_cuerpos <= 0) {
        std::cout << "Error: Por favor, ingrese un entero positivo para N: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    planetas.resize(N_cuerpos);
    fuerzas_siguientes.resize(N_cuerpos);
    for (int i = 0; i < N_cuerpos; ++i) {
        std::cout << "\n--- Datos para el Cuerpo " << i + 1 << " ---" << std::endl;
        double x, y, z, vx, vy, vz, m, r;
        std::cout << "Masa: ";
        while (!(std::cin >> m) || m <= 0) {
            std::cout << "Error: La masa debe ser un número real positivo. Ingrese de nuevo: ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        std::cout << "Radio (solo para referencia, no usado en cálculo de fuerza): ";
        while (!(std::cin >> r) || r < 0) {
            std::cout << "Error: El radio debe ser un número real no negativo. Ingrese de nuevo: ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        std::cout << "Posición inicial (x y z): ";
        while (!(std::cin >> x >> y >> z)) {
            std::cout << "Error: Entrada inválida. Ingrese tres números para x y z: ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        std::cout << "Velocidad inicial (Vx Vy Vz): ";
        while (!(std::cin >> vx >> vy >> vz)) {
            std::cout << "Error: Entrada inválida. Ingrese tres números para Vx Vy Vz: ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        planetas[i].Inicie(x, y, z, vx, vy, vz, m, r);
    }
    std::cout << "\n--- Parámetros de Simulación ---" << std::endl;
    std::cout << "Paso de tiempo (dt): ";
    while (!(std::cin >> dt_sim) || dt_sim <= 0) {
        std::cout << "Error: dt debe ser un número real positivo. Ingrese de nuevo: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    std::cout << "Tiempo total de simulación (t_max): ";
    while (!(std::cin >> t_max_sim) || t_max_sim <= 0 || t_max_sim < dt_sim) {
        std::cout << "Error: t_max debe ser positivo y mayor o igual a dt. Ingrese de nuevo: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

bool verificarDatos() {
    if (N_cuerpos <= 0) {
        std::cerr << "Error de Verificación: El número de cuerpos debe ser positivo." << std::endl;
        return false;
    }
    for (int i = 0; i < N_cuerpos; ++i) {
        if (planetas[i].m <= 0) {
            std::cerr << "Error de Verificación: La masa del cuerpo " << i + 1 << " debe ser estrictamente positiva." << std::endl;
            return false;
        }
        for (int j = i + 1; j < N_cuerpos; ++j) {
            vector3D dr = planetas[i].r - planetas[j].r;
            if (dr.norm2() < 1e-12) {
                std::cerr << "Error de Verificación: Los cuerpos " << i + 1 << " y " << j + 1
                          << " no pueden tener la misma posición inicial." << std::endl;
                return false;
            }
        }
    }
    if (dt_sim <= 0) {
        std::cerr << "Error de Verificación: El paso de tiempo (dt) debe ser estrictamente positivo." << std::endl;
        return false;
    }
    if (t_max_sim <= 0 || t_max_sim < dt_sim) {
        std::cerr << "Error de Verificación: El tiempo total (t_max) debe ser positivo y mayor o igual que dt." << std::endl;
        return false;
    }
    return true;
}


void calcularTodasLasFuerzas(std::vector<Cuerpo>& cuerpos_actuales, std::vector<vector3D>& fuerzas_a_calcular) {
    for (int i = 0; i < N_cuerpos; ++i) { cuerpos_actuales[i].BorreFuerza(); }
    for (int i = 0; i < N_cuerpos; ++i) {
        for (int j = i + 1; j < N_cuerpos; ++j) {
            vector3D dr = cuerpos_actuales[j].r - cuerpos_actuales[i].r;
            double dist_cubed = std::pow(dr.norm(), 3);
            if (dist_cubed < 1e-18) { continue; }
            vector3D F_ij = dr * (G * cuerpos_actuales[i].m * cuerpos_actuales[j].m / dist_cubed);
            cuerpos_actuales[i].F += F_ij;
            cuerpos_actuales[j].F -= F_ij;
        }
    }
    for(int i=0; i<N_cuerpos; ++i) { fuerzas_a_calcular[i] = cuerpos_actuales[i].F; }
}

double calcularEnergiaCineticaTotal(const std::vector<Cuerpo>& cuerpos_actuales) {
    double K_total = 0.0;
    for (int i = 0; i < N_cuerpos; ++i) {
        K_total += 0.5 * cuerpos_actuales[i].m * cuerpos_actuales[i].V.norm2();
    }
    return K_total;
}

double calcularEnergiaPotencialTotal(const std::vector<Cuerpo>& cuerpos_actuales) {
    double U_total = 0.0;
    for (int i = 0; i < N_cuerpos; ++i) {
        for (int j = i + 1; j < N_cuerpos; ++j) {
            vector3D dr = cuerpos_actuales[i].r - cuerpos_actuales[j].r;
            double distancia = dr.norm();
            if (distancia < 1e-9) {
                U_total -= G * cuerpos_actuales[i].m * cuerpos_actuales[j].m / 1e-9;
            } else {
                U_total -= G * cuerpos_actuales[i].m * cuerpos_actuales[j].m / distancia;
            }
        }
    }
    return U_total;
}

void graficarResultados() {
    std::cout << "\n--- Visualización de Resultados ---" << std::endl;
    std::cout << "Elija una herramienta para graficar:" << std::endl;
    std::cout << "1. Gnuplot" << std::endl;
    std::cout << "2. Python (matplotlib)" << std::endl;
    std::cout << "3. Octave" << std::endl;
    std::cout << "4. No graficar" << std::endl;
    std::cout << "Opción: ";
    int opcion;
    std::cin >> opcion;

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    
    std::string comando;

    switch (opcion) {
        case 1:
            comando = "gnuplot scripts/plot_gravedad.gp";
            std::cout << "Ejecutando: " << comando << std::endl;
            system(comando.c_str());
            break;
        case 2:
            // Usando 'python' como solicitaste
            comando = "python scripts/plot_gravedad.py";
            std::cout << "Ejecutando: " << comando << std::endl;
            system(comando.c_str());
            break;
        case 3:
            comando = "octave scripts/plot_gravedad.m";
            std::cout << "Ejecutando: " << comando << std::endl;
            system(comando.c_str());
            break;
        case 4:
            std::cout << "No se graficarán los resultados." << std::endl;
            break;
        default:
            std::cout << "Opción no válida. No se graficará." << std::endl;
            break;
    }
}

int main() {
    solicitarDatos();
    
    if (!verificarDatos()) {
        return 1;
    }

    system("mkdir -p results");

    const std::string nombre_archivo_salida = "results/sim_data.dat";
    std::ofstream archivo_salida(nombre_archivo_salida);

    if (!archivo_salida.is_open()) {
        std::cerr << "Error: No se pudo abrir el archivo de salida " << nombre_archivo_salida << std::endl;
        return 1;
    }

    archivo_salida << "# Tiempo";
    for (int i = 0; i < N_cuerpos; ++i) { archivo_salida << "\t" << "x" << i+1 << "\t" << "y" << i+1 << "\t" << "z" << i+1; }
    for (int i = 0; i < N_cuerpos; ++i) { archivo_salida << "\t" << "v" << i+1; }
    archivo_salida << "\tK_total\tU_total\tE_total" << std::endl;
    archivo_salida << std::fixed << std::setprecision(8);

    calcularTodasLasFuerzas(planetas, fuerzas_siguientes);

    double t_actual = 0;
    int paso_impresion = 0;
    int pasos_totales = static_cast<int>(t_max_sim / dt_sim);
    int intervalo_impresion = pasos_totales / 10; // Imprimir progreso un 10% de las veces
    if (intervalo_impresion == 0) intervalo_impresion = 1;


    while (t_actual <= t_max_sim) {
        archivo_salida << t_actual;
        for (int i = 0; i < N_cuerpos; ++i) { archivo_salida << "\t" << planetas[i].Getx() << "\t" << planetas[i].Gety() << "\t" << planetas[i].Getz(); }
        for (int i = 0; i < N_cuerpos; ++i) { archivo_salida << "\t" << planetas[i].GetVnorm(); }
        double K = calcularEnergiaCineticaTotal(planetas);
        double U = calcularEnergiaPotencialTotal(planetas);
        archivo_salida << "\t" << K << "\t" << U << "\t" << K + U << std::endl;

        for (int i = 0; i < N_cuerpos; ++i) { planetas[i].Muevase_r(dt_sim); }
        std::vector<Cuerpo> planetas_temp_para_F_siguiente = planetas;
        calcularTodasLasFuerzas(planetas_temp_para_F_siguiente, fuerzas_siguientes);
        for (int i = 0; i < N_cuerpos; ++i) { planetas[i].Muevase_V(dt_sim, fuerzas_siguientes[i]); }
        for (int i = 0; i < N_cuerpos; ++i) { planetas[i].F = fuerzas_siguientes[i]; }

        t_actual += dt_sim;
        
        if (static_cast<int>(t_actual / dt_sim) % intervalo_impresion == 0 && t_actual > 0) {
            std::cout << "Simulación en t = " << std::fixed << std::setprecision(2) << t_actual 
                      << " / " << t_max_sim << std::endl;
        }
    }

    archivo_salida.close();
    std::cout << "Simulación completada. Resultados guardados en " << nombre_archivo_salida << std::endl;

    graficarResultados();

    return 0;
}
