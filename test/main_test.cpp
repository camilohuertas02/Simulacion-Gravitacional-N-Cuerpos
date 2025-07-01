/**
 * @file main_test.cpp
 * @brief Programa principal para modo testing de herramientas de graficación
 * @author Isabel
 * @date 2025
 */

#include <iostream>
#include <fstream>
#include "testing.h"

int main() {
    std::cout << "=== PROGRAMA DE TESTING - SIMULACIÓN GRAVITACIONAL ===\n";
    std::cout << "Este programa permite probar diferentes herramientas de graficación\n";
    std::cout << "Asegúrate de haber ejecutado una simulación primero para tener datos.\n";
    
    // Verificar si existe el archivo de datos
    std::ifstream file("results/sim_data.dat");
    if (!file.good()) {
        std::cout << "\n⚠️  ADVERTENCIA: No se encontró 'results/sim_data.dat'\n";
        std::cout << "   Ejecuta primero una simulación con el programa principal.\n";
        std::cout << "\n¿Continuar de todas formas? (s/n): ";
        char respuesta;
        std::cin >> respuesta;
        if (respuesta != 's' && respuesta != 'S') {
            return 0;
        }
    }
    
    Testing::ejecutarModoTesting();
    
    std::cout << "\n¡Gracias por usar el modo testing!\n";
    return 0;
}