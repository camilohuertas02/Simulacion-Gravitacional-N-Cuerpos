/**
 * @file testing.cpp
 * @brief Módulo de testing para probar diferentes herramientas de graficación
 * @author Isabel
 * @date 2025
 */

#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>
#include <fstream>  // Añadir para verificar archivos
#include "testing.h"

namespace Testing {

void mostrarMenuTesting() {
    std::cout << "\n=== MODO TESTING - HERRAMIENTAS DE GRAFICACIÓN ===\n";
    std::cout << "1. Generar gráficas con Python (matplotlib)\n";
    std::cout << "2. Generar gráficas con Octave/MATLAB\n";
    std::cout << "3. Generar gráficas con Gnuplot\n";
    std::cout << "4. Probar TODAS las herramientas\n";
    std::cout << "5. Ver archivos de resultados generados\n";
    std::cout << "6. Salir del modo testing\n";
    std::cout << "================================================\n";
}

int ejecutarComando(const std::string& comando) {
    std::cout << "Ejecutando: " << comando << std::endl;
    int resultado = system(comando.c_str());
    if (resultado == 0) {
        std::cout << "✓ Comando ejecutado exitosamente\n";
    } else {
        std::cout << "✗ Error al ejecutar comando (código: " << resultado << ")\n";
    }
    return resultado;
}

void probarPython() {
    std::cout << "\n--- Probando Python + matplotlib ---\n";
    int resultado = ejecutarComando("python3 scripts/plot_gravedad.py");
    if (resultado == 0) {
        std::cout << "Python: Gráficas generadas exitosamente\n";
        // Mostrar archivos generados
        ejecutarComando("ls -la results/*.png | grep python");
    }
    else {
        std::cout << "✗ Error al ejecutar comando (código: " << resultado << ")\n";
    }
}

void probarOctave() {
    std::cout << "\n--- Probando Octave/MATLAB ---\n";
    int resultado = ejecutarComando("octave --no-gui scripts/plot_gravedad.m");
    if (resultado == 0) {
        std::cout << "Octave: Gráficas generadas exitosamente\n";
        // Mostrar archivos generados
        ejecutarComando("ls -la results/*.png | grep octave");
    }
    else {
        std::cout << "✗ Error al ejecutar comando (código: " << resultado << ")\n";
    }
}

void probarGnuplot() {
    std::cout << "\n--- Probando Gnuplot ---\n";
    int resultado = ejecutarComando("gnuplot scripts/plot_gravedad.gp");
    if (resultado == 0) {
        std::cout << "Gnuplot: Gráficas generadas exitosamente\n";
        // Mostrar archivos generados
        ejecutarComando("ls -la results/*.png | grep gnuplot");
    }
    else {
        std::cout << "✗ Error al ejecutar comando (código: " << resultado << ")\n";
    }
}

void probarTodasLasHerramientas() {
    std::cout << "\n=== PROBANDO TODAS LAS HERRAMIENTAS ===\n";
    
    probarPython();
    std::cout << "\n" << std::string(50, '-') << "\n";
    
    probarOctave();
    std::cout << "\n" << std::string(50, '-') << "\n";
    
    probarGnuplot();
    std::cout << "\n" << std::string(50, '-') << "\n";
    
    std::cout << "\n=== RESUMEN DE ARCHIVOS GENERADOS ===\n";
    ejecutarComando("ls -la results/*.png 2>/dev/null || echo 'No se encontraron archivos PNG'");
}

void verArchivosResultados() {
    std::cout << "\n--- Archivos en results/ ---\n";
    ejecutarComando("ls -la results/");
    
    std::cout << "\n--- Archivos PNG generados ---\n";
    ejecutarComando("ls -la results/*.png 2>/dev/null || echo 'No hay archivos PNG'");
    
    std::cout << "\n--- Archivos de datos ---\n";
    ejecutarComando("ls -la results/*.dat 2>/dev/null || echo 'No hay archivos de datos'");
}

void abrirVisualizador(const std::string& archivo) {
    std::string comando = "xdg-open " + archivo + " 2>/dev/null &";
    std::cout << "Abriendo: " << archivo << std::endl;
    system(comando.c_str());
}

void menuVisualizacion() {
    std::cout << "\n--- ¿Deseas abrir alguna gráfica generada? ---\n";
    
    // Listar archivos PNG disponibles
    std::vector<std::string> archivos_png;
    
    // Método simple: usar system para listar y mostrar opciones
    std::cout << "Archivos disponibles:\n";
    system("ls results/*.png 2>/dev/null | nl");
    
    std::cout << "\nIngresa el nombre completo del archivo a abrir (o 'n' para saltar): ";
    std::string archivo;
    std::getline(std::cin, archivo);
    
    if (archivo != "n" && archivo != "N" && !archivo.empty()) {
        if (archivo.find("results/") != 0) {
            archivo = "results/" + archivo;
        }
        abrirVisualizador(archivo);
    }
}

void ejecutarModoTesting() {
    int opcion;
    bool continuar = true;
    
    while (continuar) {
        mostrarMenuTesting();
        std::cout << "Selecciona una opción (1-6): ";
        std::cin >> opcion;
        std::cin.ignore(); // Limpiar buffer
        
        switch (opcion) {
            case 1:
                probarPython();
                break;
            case 2:
                probarOctave();
                break;
            case 3:
                probarGnuplot();
                break;
            case 4:
                probarTodasLasHerramientas();
                break;
            case 5:
                verArchivosResultados();
                break;
            case 6:
                std::cout << "Saliendo del modo testing...\n";
                continuar = false;
                break;
            default:
                std::cout << "Opción no válida. Intenta nuevamente.\n";
                continue;
        }
        
        if (continuar && opcion >= 1 && opcion <= 4) {
            menuVisualizacion();
            
            std::cout << "\n¿Continuar con más pruebas? (s/n): ";
            char respuesta;
            std::cin >> respuesta;
            std::cin.ignore();
            
            if (respuesta != 's' && respuesta != 'S') {
                continuar = false;
            }
        }
    }
}

} // namespace Testing