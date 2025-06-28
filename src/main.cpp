/**
 * @file main.cpp
 * @brief Programa principal para simulación gravitacional N-cuerpos
 * @details Implementa el algoritmo de Verlet para resolver el problema
 *          gravitacional de N cuerpos con conservación de energía
 * @author Isabel Nieto & Camilo Huertas
 * @date 2025
 */

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <cmath>
#include <limits>
#include <iomanip>

#include "vector3D.h"
#include "Cuerpo.h"
#include "utilidades.h"

/**
 * @brief Variables globales para la simulación
 * @details Estas variables mantienen el estado de la simulación
 */
int N_cuerpos;                           ///< Número de cuerpos en la simulación
double dt_sim;                          ///< Paso de tiempo [unidades de tiempo]
double t_max_sim;                       ///< Tiempo total de simulación [unidades de tiempo]
std::vector<Cuerpo> planetas;           ///< Contenedor de todos los cuerpos
std::vector<vector3D> fuerzas_siguientes; ///< Fuerzas F(t+dt) para algoritmo de Verlet

/**
 * @brief Solicita y valida los datos de entrada del usuario
 * @details Pide número de cuerpos, propiedades físicas y parámetros de simulación
 * @post Todos los vectores globales quedan inicializados
 */
void solicitarDatos();

/**
 * @brief Verifica la validez de los datos ingresados
 * @return true si todos los datos son válidos, false en caso contrario
 * @details Verifica masas positivas y que no haya cuerpos en la misma posición
 */
bool verificarDatos();

/**
 * @brief Calcula las fuerzas gravitacionales para todos los cuerpos
 * @param cuerpos_actuales Vector de cuerpos con posiciones actuales
 * @param fuerzas_a_calcular Vector donde se almacenan las fuerzas calculadas
 * @details Implementa la suma de fuerzas N-cuerpos evitando doble conteo
 * @note Complejidad: O(N²) donde N es el número de cuerpos
 */
void calcularTodasLasFuerzas(std::vector<Cuerpo>& cuerpos_actuales, 
                            std::vector<vector3D>& fuerzas_a_calcular);

/**
 * @brief Calcula la energía cinética total del sistema
 * @param cuerpos_actuales Vector de cuerpos con velocidades actuales
 * @return Energía cinética total K = Σ(½mᵢvᵢ²)
 */
double calcularEnergiaCineticaTotal(const std::vector<Cuerpo>& cuerpos_actuales);

/**
 * @brief Calcula la energía potencial gravitacional total
 * @param cuerpos_actuales Vector de cuerpos con posiciones actuales
 * @return Energía potencial total U = -Σᵢ<ⱼ(Gmᵢmⱼ/rᵢⱼ)
 */
double calcularEnergiaPotencialTotal(const std::vector<Cuerpo>& cuerpos_actuales);

/**
 * @brief Interfaz para seleccionar herramienta de graficación
 * @details Permite elegir entre Gnuplot, Python/Matplotlib u Octave
 */
void graficarResultados();

// --- Implementación de funciones ---

void solicitarDatos() {
    std::cout << "--- Configuración de la Simulación Gravitacional N-Cuerpos ---" << std::endl;

    std::cout << "Ingrese el número de cuerpos (N): ";
    while (!(std::cin >> N_cuerpos) || N_cuerpos <= 0) {
        std::cout << "Por favor, ingrese un entero positivo para N: ";
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
            std::cout << "Masa debe ser positiva. Ingrese de nuevo: ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

        std::cout << "Radio (solo para referencia, no usado en cálculo de fuerza): ";
         while (!(std::cin >> r) || r < 0) { // Radio puede ser 0 para un punto material
            std::cout << "Radio debe ser no negativo. Ingrese de nuevo: ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

        std::cout << "Posición inicial (x y z): ";
        while (!(std::cin >> x >> y >> z)) {
            std::cout << "Entrada inválida. Ingrese tres números para x y z: ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

        std::cout << "Velocidad inicial (Vx Vy Vz): ";
        while (!(std::cin >> vx >> vy >> vz)) {
            std::cout << "Entrada inválida. Ingrese tres números para Vx Vy Vz: ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        planetas[i].Inicie(x, y, z, vx, vy, vz, m, r);
    }

    std::cout << "\n--- Parámetros de Simulación ---" << std::endl;
    std::cout << "Paso de tiempo (dt): ";
    while (!(std::cin >> dt_sim) || dt_sim <= 0) {
        std::cout << "dt debe ser positivo. Ingrese de nuevo: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    std::cout << "Tiempo total de simulación (t_max): ";
    while (!(std::cin >> t_max_sim) || t_max_sim <= 0 || t_max_sim < dt_sim) {
        std::cout << "t_max debe ser positivo y mayor o igual a dt. Ingrese de nuevo: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

bool verificarDatos() {
    if (N_cuerpos <= 0) {
        std::cerr << "Error: Número de cuerpos debe ser positivo." << std::endl;
        return false;
    }
    for (int i = 0; i < N_cuerpos; ++i) {
        if (planetas[i].m <= 0) {
            std::cerr << "Error: La masa del cuerpo " << i + 1 << " debe ser positiva." << std::endl;
            return false;
        }
        // Verificar si hay cuerpos en la misma posición (podría causar división por cero)
        for (int j = i + 1; j < N_cuerpos; ++j) {
            vector3D dr = planetas[i].r - planetas[j].r;
            if (dr.norm2() < 1e-9) { // Umbral pequeño para considerar "misma posición"
                std::cerr << "Advertencia: Cuerpos " << i + 1 << " y " << j + 1
                          << " están en posiciones iniciales muy cercanas o idénticas." << std::endl;
                // No necesariamente un error fatal, pero puede llevar a fuerzas enormes.
            }
        }
    }
    if (dt_sim <= 0) {
        std::cerr << "Error: El paso de tiempo (dt) debe ser positivo." << std::endl;
        return false;
    }
    if (t_max_sim <= 0 || t_max_sim < dt_sim) {
        std::cerr << "Error: El tiempo total de simulación (t_max) debe ser positivo y >= dt." << std::endl;
        return false;
    }
    return true;
}

void calcularTodasLasFuerzas(std::vector<Cuerpo>& cuerpos_actuales, std::vector<vector3D>& fuerzas_a_calcular) {
    for (int i = 0; i < N_cuerpos; ++i) {
        cuerpos_actuales[i].BorreFuerza(); // Reinicia la fuerza del cuerpo i (F(t) o F(t+dt) según el contexto)
    }
    for (int i = 0; i < N_cuerpos; ++i) {
        for (int j = i + 1; j < N_cuerpos; ++j) { // j > i para evitar duplicados y auto-interacción
            // Cuerpo i calcula la fuerza que j le ejerce y la suma a su F
            // Cuerpo j calcula la fuerza que i le ejerce y la suma a su F
            // Esto se hace dentro de AdicioneFuerzaGravitacional si se pasa el otro cuerpo
            // o se puede hacer explícitamente aquí.
            // La implementación actual de AdicioneFuerzaGravitacional en Cuerpo.cpp calcula la fuerza que "otroCuerpo" ejerce
            // sobre "this" y la suma a F de "this".
            // Necesitamos calcular ambas interacciones.

            vector3D dr = cuerpos_actuales[j].r - cuerpos_actuales[i].r;
            double dist_cubed = std::pow(dr.norm(), 3);
            if (dist_cubed < 1e-18) { // Evitar division por cero si están exactamente en el mismo lugar
                continue;
            }
            vector3D F_ij = dr * (G * cuerpos_actuales[i].m * cuerpos_actuales[j].m / dist_cubed); // Fuerza sobre i debida a j

            cuerpos_actuales[i].F += F_ij;        // i siente la fuerza de j
            cuerpos_actuales[j].F -= F_ij;        // j siente la fuerza opuesta de i (Ley de Acción-Reacción)
        }
    }
    // Guardar las fuerzas calculadas (que están en cuerpo.F) en el vector de fuerzas_a_calcular
    for(int i=0; i<N_cuerpos; ++i) {
        fuerzas_a_calcular[i] = cuerpos_actuales[i].F;
    }
}


double calcularEnergiaCineticaTotal(const std::vector<Cuerpo>& cuerpos_actuales) {
    double K_total = 0.0;
    for (int i = 0; i < N_cuerpos; ++i) {
        vector3D V_copy = cuerpos_actuales[i].V; // Copia no-const
        K_total += 0.5 * cuerpos_actuales[i].m * V_copy.norm2();
    }
    return K_total;
}

double calcularEnergiaPotencialTotal(const std::vector<Cuerpo>& cuerpos_actuales) {
    double U_total = 0.0;
    for (int i = 0; i < N_cuerpos; ++i) {
        for (int j = i + 1; j < N_cuerpos; ++j) { // j > i para evitar duplicados
            vector3D r_i_copy = cuerpos_actuales[i].r; // Copia no-const
            vector3D r_j_copy = cuerpos_actuales[j].r; // Copia no-const
            vector3D dr = r_i_copy - r_j_copy;
            double distancia = dr.norm();
            if (distancia < 1e-9) { // Evitar división por cero si están muy cerca
                U_total -= G * cuerpos_actuales[i].m * cuerpos_actuales[j].m / 1e-9; // Cap a un valor grande
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

    std::string comando;
    std::string archivo_datos = "results/datos_" + std::to_string(N_cuerpos) + ".dat";

    // Asegurarse que los scripts son ejecutables y están en el path o usar path relativo
    // cd al directorio del script o usar path completo al script.
    // Por simplicidad, asumimos que los scripts están en ./scripts/ y son ejecutables.
    // Y que gnuplot, python, octave están en el PATH del sistema.

    switch (opcion) {
        case 1:
            // comando = "gnuplot -e \"filename='results/datos_" + std::to_string(N_cuerpos) + ".dat'; N_bodies=" + std::to_string(N_cuerpos) + "\" scripts/plot_gravedad.gp";
            // Gnuplot prefiere que las variables se pasen así si el script las usa directamente.
            // O el script puede estar hardcodeado para leer un nombre de archivo fijo.
            // Para el plot_gravedad.gp que se espera, pasaremos N y el nombre del archivo como argumentos.
            comando = "gnuplot scripts/plot_gravedad.gp " + std::to_string(N_cuerpos) + " " + archivo_datos;
            std::cout << "Ejecutando: " << comando << std::endl;
            system(comando.c_str());
            break;
        case 2:
            comando = "python scripts/plot_gravedad.py " + archivo_datos + " " + std::to_string(N_cuerpos);
            std::cout << "Ejecutando: " << comando << std::endl;
            system(comando.c_str());
            break;
        case 3:
            // Octave puede necesitar un wrapper o que el script .m tome argumentos
            // comando = "octave --eval \"plot_gravedad('" + archivo_datos + "', " + std::to_string(N_cuerpos) + ")\"";
            // O si el script plot_gravedad.m está hecho para ser llamado directamente y busca el archivo:
            comando = "octave scripts/plot_gravedad.m " + archivo_datos + " " + std::to_string(N_cuerpos); // Asumiendo que el script maneja args
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
        return 1; // Termina si los datos son inválidos
    }

    std::string nombre_archivo_salida = "results/datos_" + std::to_string(N_cuerpos) + ".dat";
    std::ofstream archivo_salida(nombre_archivo_salida);

    if (!archivo_salida.is_open()) {
        std::cerr << "Error: No se pudo abrir el archivo de salida " << nombre_archivo_salida << std::endl;
        return 1;
    }

    // Escribir cabeceras en el archivo de datos
    archivo_salida << "# Tiempo";
    for (int i = 0; i < N_cuerpos; ++i) {
        archivo_salida << "\tx" << i + 1 << "\ty" << i + 1 << "\tz" << i + 1;
    }
    for (int i = 0; i < N_cuerpos; ++i) {
        archivo_salida << "\tv" << i + 1; // Velocidad escalar
    }
    archivo_salida << "\tK_total\tU_total\tE_total" << std::endl;
    archivo_salida << std::fixed << std::setprecision(8); // Formato para los números

    // --- Bucle principal de la simulación (Algoritmo de Verlet) ---

    // 1. Calcular F(t=0) para todos los cuerpos
    //    La función calcularTodasLasFuerzas actualiza directamente el miembro .F de cada cuerpo.
    //    Y también copia estas fuerzas en el vector `planetas_fuerzas_actuales` (que no estamos usando directamente aquí).
    //    El miembro .F de cada `planeta` es la fuerza actual F(t).
    calcularTodasLasFuerzas(planetas, fuerzas_siguientes); // Pone las F(t=0) en planetas[i].F y en fuerzas_siguientes (que aquí es F(t))

    double t_actual = 0;
    int paso = 0;

    while (t_actual <= t_max_sim) {
        // Escribir datos actuales (antes de mover)
        archivo_salida << t_actual;
        for (int i = 0; i < N_cuerpos; ++i) {
            archivo_salida << "\t" << planetas[i].Getx()
                           << "\t" << planetas[i].Gety()
                           << "\t" << planetas[i].Getz();
        }
        for (int i = 0; i < N_cuerpos; ++i) {
            archivo_salida << "\t" << planetas[i].GetVnorm();
        }
        double K = calcularEnergiaCineticaTotal(planetas);
        double U = calcularEnergiaPotencialTotal(planetas);
        archivo_salida << "\t" << K << "\t" << U << "\t" << K + U << std::endl;

        // Algoritmo de Verlet:
        // Paso A: Actualizar posiciones r(t+dt) usando V(t) y F(t)
        // r_i(t+dt) = r_i(t) + V_i(t)*dt + (F_i(t)/(2*m_i))*dt*dt
        for (int i = 0; i < N_cuerpos; ++i) {
            planetas[i].Muevase_r(dt_sim); // Usa planetas[i].F que es F(t)
        }

        // Paso B: Calcular las nuevas fuerzas F_i(t+dt) usando las nuevas posiciones r_i(t+dt)
        //         Guardar estas fuerzas en `fuerzas_siguientes`
        //         (No modificar planetas[i].F todavía, ya que es F(t) y se necesita para V)
        std::vector<Cuerpo> planetas_temp_para_F_siguiente = planetas; // Copia para calcular F_siguiente sin alterar F_actual
        calcularTodasLasFuerzas(planetas_temp_para_F_siguiente, fuerzas_siguientes);
        // Ahora, fuerzas_siguientes[i] contiene F_i(t+dt) para cada cuerpo i.
        // Y planetas_temp_para_F_siguiente[i].F también tiene F_i(t+dt).

        // Paso C: Actualizar velocidades V_i(t+dt) usando F_i(t) y F_i(t+dt)
        // V_i(t+dt) = V_i(t) + (F_i(t) + F_i(t+dt))/(2*m_i)*dt
        for (int i = 0; i < N_cuerpos; ++i) {
            // planetas[i].F es F_i(t)
            // fuerzas_siguientes[i] es F_i(t+dt)
            planetas[i].Muevase_V(dt_sim, fuerzas_siguientes[i]);
        }

        // Paso D: Actualizar F_i(t) para el siguiente ciclo. F_i(t) ahora será F_i(t+dt).
        for (int i = 0; i < N_cuerpos; ++i) {
            planetas[i].F = fuerzas_siguientes[i];
        }

        t_actual += dt_sim;
        paso++;
        if (paso % 1000 == 0) { // Opcional: imprimir progreso a consola
             std::cout << "Simulación en t = " << t_actual << " / " << t_max_sim << std::endl;
        }
    }

    archivo_salida.close();
    std::cout << "Simulación completada. Resultados guardados en " << nombre_archivo_salida << std::endl;

    graficarResultados();

    return 0;
}
