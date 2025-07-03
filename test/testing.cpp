/**
 * @file testing.cpp
 * @brief Módulo de testing para probar herramientas de graficación con datos del programa principal
 * @author Isabel Nieto y Camilo Huertas
 * @date 2025
 */

#include "testing.h"

namespace Testing {

/**
 * @brief Obtiene sistemas predefinidos como plantillas para el programa principal
 */
std::vector<SistemaPrueba> obtenerSistemasPredefinidos() {
    std::vector<SistemaPrueba> sistemas;
    
    // Sistema 1: Órbita circular simple (2D)
    sistemas.push_back({
        "orbita_circular",
        "Sistema binario con órbita circular estable (2D)",
        2, 0.01, 15.0,
        {
            {100.0, 1.0, 0.0, 0.0, 0.1, 0.0, 0.0, 0.2},      // Cuerpo central masivo
            {1.0, 0.1, 5.0, 0.0, 0.1, 0.0, 4.47, 0.2}        // Cuerpo orbitante
        }
    });
    
    // Sistema 2: Órbita elíptica
    sistemas.push_back({
        "orbita_eliptica",
        "Sistema con órbita elíptica pronunciada",
        2, 0.01, 20.0,
        {
            {50.0, 0.8, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0},
            {2.0, 0.2, 8.0, 0.0, 0.0, 0.0, 2.5, 0.0}
        }
    });
    
    // Sistema 3: Tres cuerpos en línea
    sistemas.push_back({
        "tres_cuerpos_lineal",
        "Tres cuerpos alineados - configuración inestable",
        3, 0.005, 8.0,
        {
            {15.0, 0.6, -3.0, 0.0, 0.0, 0.0, 1.2, 0.0},
            {20.0, 0.7, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0},
            {15.0, 0.6, 3.0, 0.0, 0.0, 0.0, -1.2, 0.0}
        }
    });
    
    // Sistema 4: Movimiento 3D complejo
    sistemas.push_back({
        "sistema_3d",
        "Sistema 3D con movimiento en todas las direcciones",
        3, 0.01, 10.0,
        {
            {50.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0},
            {8.0, 0.4, 4.0, 0.0, 1.0, 0.0, 2.8, 1.5},
            {8.0, 0.4, -2.0, 3.5, -1.0, 1.5, -1.0, -0.8}
        }
    });
    
    // Sistema 5: Cuatro cuerpos caótico
    sistemas.push_back({
        "cuatro_cuerpos_caotico",
        "Sistema de cuatro cuerpos - comportamiento caótico",
        4, 0.002, 5.0,
        {
            {10.0, 0.4, 2.0, 2.0, 0.0, 0.5, -0.5, 0.0},
            {10.0, 0.4, -2.0, 2.0, 0.0, -0.5, -0.5, 0.0},
            {10.0, 0.4, -2.0, -2.0, 0.0, -0.5, 0.5, 0.0},
            {10.0, 0.4, 2.0, -2.0, 0.0, 0.5, 0.5, 0.0}
        }
    });
    
    // Sistema 6: Colisión programada
    sistemas.push_back({
        "colision_frontal",
        "Dos cuerpos en curso de colisión frontal",
        2, 0.005, 3.0,
        {
            {25.0, 0.8, -5.0, 0.0, 0.0, 3.0, 0.0, 0.0},
            {25.0, 0.8, 5.0, 0.0, 0.0, -3.0, 0.0, 0.0}
        }
    });
    
    return sistemas;
}

/**
 * @brief Genera archivo de entrada para el programa principal
 */
void generarArchivoEntrada(const SistemaPrueba& sistema) {
    std::ofstream archivo("input_temp.txt");
    if (!archivo.is_open()) {
        archivo.open("input_temp.txt");
        if (!archivo.is_open()) {
            std::cout << "❌ Error: No se pudo crear archivo de entrada temporal\n";
            return;
        }
    }
    
    // Escribir datos en el formato que espera el programa principal
    archivo << sistema.n_cuerpos << "\n";
    
    for (const auto& cuerpo : sistema.cuerpos) {
        archivo << cuerpo.masa << "\n";
        archivo << cuerpo.radio << "\n";
        archivo << cuerpo.x << " " << cuerpo.y << " " << cuerpo.z << "\n";
        archivo << cuerpo.vx << " " << cuerpo.vy << " " << cuerpo.vz << "\n";
    }
    
    archivo << sistema.dt << "\n";
    archivo << sistema.t_max << "\n";
    archivo << "4\n"; // No graficar desde el programa principal
    
    archivo.close();
}

/**
 * @brief Ejecuta simulación con el programa principal usando sistema predefinido
 */
void ejecutarSimulacionConSistema(const SistemaPrueba& sistema) {
    std::cout << "\n=== EJECUTANDO SIMULACIÓN CON PROGRAMA PRINCIPAL ===\n";
    std::cout << "Sistema: " << sistema.nombre << "\n";
    std::cout << "Descripción: " << sistema.descripcion << "\n";
    std::cout << "Cuerpos: " << sistema.n_cuerpos << ", dt: " << sistema.dt 
              << ", Tiempo: " << sistema.t_max << "s\n\n";
    
    // Generar archivo de entrada en el directorio correcto
    generarArchivoEntrada(sistema);
    
    // Compilar el programa principal si es necesario
    std::cout << "Compilando programa principal...\n";
    std::string compile_cmd = "cd .. && g++ -o bin/gravedad src/main.cpp src/Cuerpo.cpp src/utilidades.cpp src/vector3D.cpp -I include";
    if (system(compile_cmd.c_str()) != 0) {
        std::cout << "❌ Error en compilación. Verifica que el código esté correcto.\n";
        return;
    }
    
    std::cout << "✅ Compilación exitosa\n";
    std::cout << "Ejecutando simulación con algoritmo de Verlet...\n";
    
    // Ejecutar simulación (desde bin/ el archivo temporal estará en ../test/)
    std::string run_cmd = "cd .. && ./bin/gravedad < test/input_temp.txt";
    int resultado = system(run_cmd.c_str());
    
    // Limpiar archivo temporal
    system("rm -f test/input_temp.txt");
    
    if (resultado == 0) {
        std::cout << "✅ Simulación completada exitosamente\n";
        std::cout << "📁 Datos guardados en: results/sim_data.dat\n";
        
        // Verificar que se generó el archivo (desde bin/)
        std::ifstream check("../results/sim_data.dat");
        if (!check.good()) {
            check.open("results/sim_data.dat");
        }
        if (check.good()) {
            std::cout << "✅ Archivo de datos verificado\n";
            check.close();
        } else {
            std::cout << "❌ Warning: No se encontró el archivo de datos generado\n";
        }
    } else {
        std::cout << "❌ Error en la simulación\n";
    }
}

/**
 * @brief Muestra menú de sistemas predefinidos
 */
void mostrarSistemasPredefinidos() {
    auto sistemas = obtenerSistemasPredefinidos();
    
    std::cout << "\n=== SISTEMAS PREDEFINIDOS PARA TESTING ===\n";
    std::cout << "Estos sistemas ejecutarán el programa principal con datos predefinidos\n";
    std::cout << "para generar datos reales usando el algoritmo de Verlet.\n\n";
    
    for (size_t i = 0; i < sistemas.size(); ++i) {
        std::cout << i + 1 << ". " << sistemas[i].nombre << "\n";
        std::cout << "   " << sistemas[i].descripcion << "\n";
        std::cout << "   (" << sistemas[i].n_cuerpos << " cuerpos, " 
                  << sistemas[i].t_max << "s)\n\n";
    }
    
    std::cout << "Selecciona un sistema (1-" << sistemas.size() << "): ";
    int opcion;
    std::cin >> opcion;
    
    if (opcion >= 1 && opcion <= static_cast<int>(sistemas.size())) {
        const SistemaPrueba& sistema_seleccionado = sistemas[opcion - 1];
        ejecutarSimulacionConSistema(sistema_seleccionado);
    } else {
        std::cout << "❌ Opción no válida\n";
    }
}

/**
 * @brief Menú principal actualizado
 */
void mostrarMenuTesting() {
    std::cout << "\n=== MODO TESTING - HERRAMIENTAS DE GRAFICACIÓN ===\n";
    std::cout << "--- SIMULACIÓN CON PROGRAMA PRINCIPAL ---\n";
    std::cout << "1. Ejecutar simulación con sistema predefinido\n";
    std::cout << "2. Ver información de sistemas disponibles\n";
    std::cout << "3. Ejecutar programa principal manualmente\n";
    std::cout << "\n--- HERRAMIENTAS DE GRAFICACIÓN ---\n";
    std::cout << "4. Probar Python (matplotlib)\n";
    std::cout << "5. Probar Octave/MATLAB\n";
    std::cout << "6. Probar Gnuplot\n";
    std::cout << "7. Probar TODAS las herramientas\n";
    std::cout << "\n--- UTILIDADES ---\n";
    std::cout << "8. Ver archivos de resultados\n";
    std::cout << "9. Verificar datos generados\n";
    std::cout << "10. Limpiar archivos de resultados\n";
    std::cout << "11. Salir\n";
    std::cout << "================================================\n";
}

void ejecutarModoTesting() {
    int opcion;
    bool continuar = true;
    
    while (continuar) {
        mostrarMenuTesting();
        std::cout << "Selecciona una opción (1-11): ";
        std::cin >> opcion;
        std::cin.ignore(); // Limpiar buffer
        
        switch (opcion) {
            case 1:
                mostrarSistemasPredefinidos();
                break;
            case 2: {
                auto sistemas = obtenerSistemasPredefinidos();
                std::cout << "\n=== INFORMACIÓN DETALLADA DE SISTEMAS ===\n";
                for (const auto& sistema : sistemas) {
                    std::cout << "• " << sistema.nombre << "\n";
                    std::cout << "  " << sistema.descripcion << "\n";
                    std::cout << "  Cuerpos: " << sistema.n_cuerpos 
                              << ", dt: " << sistema.dt 
                              << ", Tiempo: " << sistema.t_max << "s\n\n";
                }
                break;
            }
            case 3:
                std::cout << "\n=== EJECUCIÓN MANUAL DEL PROGRAMA PRINCIPAL ===\n";
                std::cout << "Compilando...\n";
                if (system("cd .. && g++ -o simulacion src/main.cpp src/Cuerpo.cpp src/utilidades.cpp src/vector3D.cpp -I include") == 0) {
                    std::cout << "✅ Compilación exitosa\n";
                    std::cout << "Ejecutando programa principal...\n";
                    system("cd .. && ./simulacion");
                } else {
                    std::cout << "❌ Error en compilación\n";
                }
                break;
            case 4:
                probarPython();
                break;
            case 5:
                probarOctave();
                break;
            case 6:
                probarGnuplot();
                break;
            case 7:
                probarTodasLasHerramientas();
                break;
            case 8:
                verArchivosResultados();
                break;
            case 9:
                verificarFormatoArchivo();
                break;
            case 10:
                std::cout << "¿Confirmar limpieza de archivos? (s/n): ";
                char resp;
                std::cin >> resp;
                if (resp == 's' || resp == 'S') {
                    system("rm -f ../results/*.dat ../results/*.png ../results/*.pdf ../results/*.eps");
                    std::cout << "✅ Archivos limpiados\n";
                }
                break;
            case 11:
                std::cout << "Saliendo del modo testing...\n";
                continuar = false;
                break;
            default:
                std::cout << "❌ Opción no válida. Intenta nuevamente.\n";
                continue;
        }
        
        // Solo mostrar opción de salir después de ejecutar herramientas de graficación
        if (continuar && opcion >= 4 && opcion <= 7) {
            std::cout << "\n¿Salir del programa? (s/n): ";
            char respuesta;
            std::cin >> respuesta;
            std::cin.ignore();
            
            if (respuesta == 's' || respuesta == 'S') {
                continuar = false;
            }
        }
        
        // Pausa para otras opciones
        if (continuar && (opcion >= 1 && opcion <= 3)) {
            std::cout << "\nPresiona Enter para continuar...";
            std::cin.get();
        }
        
        // Pausa para utilidades
        if (continuar && (opcion >= 8 && opcion <= 10)) {
            std::cout << "\nPresiona Enter para continuar...";
            std::cin.get();
        }
    }
}

/**
 * @brief Verifica el formato del archivo de datos generado
 */
void verificarFormatoArchivo() {
    std::cout << "\n=== VERIFICANDO FORMATO DE ARCHIVO DE DATOS ===\n";
    
    // Intentar diferentes rutas posibles
    std::ifstream archivo("../results/sim_data.dat");
    if (!archivo.is_open()) {
        archivo.open("results/sim_data.dat");
        if (!archivo.is_open()) {
            std::cout << "❌ Error: No se encontró el archivo de datos\n";
            std::cout << "   Rutas buscadas: ../results/sim_data.dat, results/sim_data.dat\n";
            std::cout << "   Ejecuta primero una simulación (opciones 1 o 3)\n";
            return;
        }
        std::cout << "✅ El archivo de datos está disponible: results/sim_data.dat\n";
    } else {
        std::cout << "✅ El archivo de datos está disponible: ../results/sim_data.dat\n";
    }
    
    std::cout << "   Primeras líneas del archivo:\n";
    
    std::string linea;
    for (int i = 0; i < 10 && std::getline(archivo, linea); ++i) {
        std::cout << "   " << linea << "\n";
    }
    
    archivo.close();
    std::cout << "\n📊 El archivo contiene datos generados por el programa principal\n";
    std::cout << "   usando el algoritmo de Verlet para integración numérica.\n";
}

/**
 * @brief Ejecuta un comando del sistema y reporta el resultado
 */
int ejecutarComando(const std::string& comando) {
    std::cout << "Ejecutando: " << comando << std::endl;
    int resultado = system(comando.c_str());
    if (resultado == 0) {
        std::cout << "✅ Comando ejecutado exitosamente\n";
    } else {
        std::cout << "❌ Error al ejecutar comando (código: " << resultado << ")\n";
    }
    return resultado;
}

/**
 * @brief Prueba Python/matplotlib con scripts existentes
 */
void probarPython() {
    std::cout << "\n=== PROBANDO PYTHON/MATPLOTLIB ===\n";
    std::cout << "Verificando instalación de Python...\n";
    
    if (ejecutarComando("python3 --version") != 0) {
        std::cout << "❌ Python3 no encontrado\n";
        return;
    }
    
    std::cout << "Verificando matplotlib...\n";
    if (ejecutarComando("python3 -c 'import matplotlib; print(\"matplotlib OK\")'") != 0) {
        std::cout << "❌ matplotlib no encontrado\n";
        std::cout << "Instalar con: pip3 install matplotlib\n";
        return;
    }
    
    std::cout << "✅ Python/matplotlib disponible\n";
    
    // Verificar si existe archivo de datos del programa principal
    std::ifstream archivo_datos("../results/sim_data.dat");
    if (!archivo_datos.good()) {
        std::cout << "❌ No se encontró ../results/sim_data.dat\n";
        std::cout << "   Ejecuta primero una simulación (opciones 1 o 3)\n";
        return;
    }
    
    std::cout << "✅ Datos del programa principal encontrados\n";
    std::cout << "Ejecutando script de Python existente...\n";
    // Mantener el comando correcto que ya funciona
    if (ejecutarComando("cd .. && python3 scripts/plot_gravedad.py") == 0) {
        std::cout << "✅ Gráficas generadas con Python\n";
    }
}

void probarOctave() {
    std::cout << "\n=== PROBANDO OCTAVE/MATLAB ===\n";
    
    if (ejecutarComando("octave --version") != 0) {
        std::cout << "❌ Octave no encontrado\n";
        std::cout << "Instalar con: sudo apt install octave\n";
        return;
    }
    
    std::cout << "✅ Octave disponible\n";
    
    // Verificar si existe archivo de datos del programa principal
    std::ifstream archivo_datos("../results/sim_data.dat");
    if (!archivo_datos.good()) {
        std::cout << "❌ No se encontró ../results/sim_data.dat\n";
        std::cout << "   Ejecuta primero una simulación (opciones 1 o 3)\n";
        return;
    }
    
    std::cout << "✅ Datos del programa principal encontrados\n";
    std::cout << "Ejecutando script de Octave existente...\n";
    // Cambiar la ruta para ejecutar desde el directorio correcto
    if (ejecutarComando("cd .. && octave --no-gui scripts/plot_gravedad.m") == 0) {
        std::cout << "✅ Gráficas generadas con Octave\n";
    }
}

void probarGnuplot() {
    std::cout << "\n=== PROBANDO GNUPLOT ===\n";
    
    if (ejecutarComando("gnuplot --version") != 0) {
        std::cout << "❌ Gnuplot no encontrado\n";
        std::cout << "Instalar con: sudo apt install gnuplot\n";
        return;
    }
    
    std::cout << "✅ Gnuplot disponible\n";
    
    // Verificar si existe archivo de datos del programa principal
    std::ifstream archivo_datos("../results/sim_data.dat");
    if (!archivo_datos.good()) {
        std::cout << "❌ No se encontró ../results/sim_data.dat\n";
        std::cout << "   Ejecuta primero una simulación (opciones 1 o 3)\n";
        return;
    }
    
    std::cout << "✅ Datos del programa principal encontrados\n";
    std::cout << "Ejecutando script de Gnuplot existente...\n";
    // Cambiar la ruta para ejecutar desde el directorio correcto
    if (ejecutarComando("cd .. && gnuplot scripts/plot_gravedad.gp") == 0) {
        std::cout << "✅ Gráficas generadas con Gnuplot\n";
    }
}

/**
 * @brief Prueba todas las herramientas con scripts existentes
 */
void probarTodasLasHerramientas() {
    std::cout << "\n=== PROBANDO TODAS LAS HERRAMIENTAS ===\n";
    probarPython();
    probarOctave();
    probarGnuplot();
}

/**
 * @brief Ver archivos de resultados
 */
void verArchivosResultados() {
    std::cout << "\n=== ARCHIVOS EN DIRECTORIO RESULTS ===\n";
    ejecutarComando("ls -la ../results/");
}

} // namespace Testing