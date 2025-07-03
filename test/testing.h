/**
 * @file testing.h
 * @brief Funciones de testing para herramientas de graficación
 * @author Isabel Nieto
 * @date 2025
 */

#ifndef TESTING_H
#define TESTING_H

#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>
#include <fstream>
#include <cmath>

namespace Testing {
    
    /**
     * @brief Estructura para datos de un cuerpo en simulación
     */
    struct DatosCuerpo {
        double masa, radio;
        double x, y, z;
        double vx, vy, vz;
    };
    
    /**
     * @brief Estructura para configuración de sistema de prueba
     */
    struct SistemaPrueba {
        std::string nombre;
        std::string descripcion;
        int n_cuerpos;
        double dt;
        double t_max;
        std::vector<DatosCuerpo> cuerpos;
    };
    
    /**
     * @brief Muestra el menú principal de testing
     */
    void mostrarMenuTesting();
    
    /**
     * @brief Ejecuta un comando del sistema y reporta el resultado
     * @param comando Comando a ejecutar
     * @return Código de retorno del comando
     */
    int ejecutarComando(const std::string& comando);
    
    /**
     * @brief Prueba la generación de gráficas con Python
     */
    void probarPython();
    
    /**
     * @brief Prueba la generación de gráficas con Octave/MATLAB
     */
    void probarOctave();
    
    /**
     * @brief Prueba la generación de gráficas con Gnuplot
     */
    void probarGnuplot();
    
    /**
     * @brief Prueba todas las herramientas de graficación
     */
    void probarTodasLasHerramientas();
    
    /**
     * @brief Muestra los archivos de resultados generados
     */
    void verArchivosResultados();
    
    /**
     * @brief Función principal del modo testing
     */
    void ejecutarModoTesting();
    
    /**
     * @brief Obtiene sistemas predefinidos para testing
     * @return Vector con configuraciones de sistemas predefinidos
     */
    std::vector<SistemaPrueba> obtenerSistemasPredefinidos();
    
    /**
     * @brief Muestra y permite seleccionar sistemas predefinidos
     */
    void mostrarSistemasPredefinidos();
    
    /**
     * @brief Genera archivo de entrada para el programa principal
     * @param sistema Sistema predefinido a usar
     */
    void generarArchivoEntrada(const SistemaPrueba& sistema);
    
    /**
     * @brief Ejecuta simulación usando el programa principal
     * @param sistema Sistema predefinido a simular
     */
    void ejecutarSimulacionConSistema(const SistemaPrueba& sistema);
    
    /**
     * @brief Verifica el formato del archivo de datos generado
     */
    void verificarFormatoArchivo();
    
} // namespace Testing

#endif // TESTING_H