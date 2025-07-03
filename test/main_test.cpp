/**
 * @file main_test.cpp
 * @brief Programa principal para modo testing de herramientas de graficación
 * @author Isabel Nieto y Camilo Huertas
 * @date 2025
 * @details Este programa proporciona una interfaz completa para probar todas las
 *          herramientas de visualización disponibles con datos reales de simulación
 */

#include <iostream>
#include <fstream>
#include "testing.h"

/**
 * @brief Función principal del programa de testing
 * @return Código de salida (0 = éxito)
 * @details Inicializa el sistema de testing y transfiere control a ejecutarModoTesting()
 */
int main() {
    std::cout << "=== PROGRAMA DE TESTING - SIMULACIÓN GRAVITACIONAL ===\n";
    std::cout << "Este programa permite probar diferentes herramientas de graficación\n";
    std::cout << "con datos de simulación reales generados por el programa principal.\n";
    
    // Verificar si existe el archivo de datos (desde test/ necesitamos ir a ../results/)
    std::ifstream file("../results/sim_data.dat");
    if (!file.good()) {
        std::cout << "\n⚠️  ADVERTENCIA: No se encontró '../results/sim_data.dat'\n";
        std::cout << "   Puedes:\n";
        std::cout << "   1. Ejecutar primero una simulación con el programa principal\n";
        std::cout << "   2. Usar un sistema predefinido para generar datos\n";
        std::cout << "\n¿Continuar de todas formas? (s/n): ";
        char respuesta;
        std::cin >> respuesta;
        if (respuesta != 's' && respuesta != 'S') {
            return 0;
        }
    } else {
        std::cout << "\n✓ Archivo de datos encontrado: ../results/sim_data.dat\n";
        file.close();
    }
    
    Testing::ejecutarModoTesting();
    
    return 0;
}