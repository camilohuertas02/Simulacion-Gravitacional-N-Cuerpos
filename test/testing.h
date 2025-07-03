/**
 * @file testing.h
 * @brief Funciones de testing para herramientas de graficación
 * @author Isabel Nieto y Camilo Huertas
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

/**
 * @namespace Testing
 * @brief Espacio de nombres para funciones de testing y validación
 */
namespace Testing {
    
    /**
     * @struct DatosCuerpo
     * @brief Estructura para almacenar datos físicos de un cuerpo celeste
     */
    struct DatosCuerpo {
        double masa;  ///< Masa del cuerpo [kg]
        double radio; ///< Radio del cuerpo [m]
        double x, y, z; ///< Posición inicial [m]
        double vx, vy, vz; ///< Velocidad inicial [m/s]
    };
    
    /**
     * @struct SistemaPrueba
     * @brief Estructura para configuración completa de un sistema de prueba
     */
    struct SistemaPrueba {
        std::string nombre;        ///< Nombre descriptivo del sistema
        std::string descripcion;   ///< Descripción detallada del comportamiento esperado
        int n_cuerpos;            ///< Número de cuerpos en el sistema
        double dt;                ///< Paso de tiempo para la simulación [s]
        double t_max;             ///< Tiempo total de simulación [s]
        std::vector<DatosCuerpo> cuerpos; ///< Vector con datos de todos los cuerpos
    };
    
    /**
     * @brief Muestra el menú principal de testing con todas las opciones disponibles
     * @details Presenta un menú organizado en secciones: simulación, herramientas estáticas,
     *          animaciones GIF y utilidades
     */
    void mostrarMenuTesting();
    
    /**
     * @brief Ejecuta un comando del sistema y reporta el resultado
     * @param comando Comando a ejecutar en el shell del sistema
     * @return Código de retorno del comando (0 = éxito, ≠0 = error)
     * @details Usa system() para ejecutar el comando y proporciona feedback visual
     */
    int ejecutarComando(const std::string& comando);
    
    /**
     * @brief Prueba la generación de gráficas estáticas con Python/matplotlib
     * @details Verifica instalación de Python3 y matplotlib, luego ejecuta script de graficación
     * @pre Debe existir el archivo ../results/sim_data.dat
     */
    void probarPython();
    
    /**
     * @brief Prueba la generación de gráficas estáticas con Octave/MATLAB
     * @details Verifica instalación de Octave, luego ejecuta script de graficación
     * @pre Debe existir el archivo ../results/sim_data.dat
     */
    void probarOctave();
    
    /**
     * @brief Prueba la generación de gráficas estáticas con Gnuplot
     * @details Verifica instalación de Gnuplot, luego ejecuta script de graficación
     * @pre Debe existir el archivo ../results/sim_data.dat
     */
    void probarGnuplot();
    
    /**
     * @brief Prueba todas las herramientas de graficación estática secuencialmente
     * @details Ejecuta probarPython(), probarOctave() y probarGnuplot() en orden
     */
    void probarTodasLasHerramientas();
    
    /**
     * @brief Prueba la creación de GIF animado usando Python/matplotlib
     * @details Verifica dependencias (matplotlib, PIL), luego crea animación GIF
     * @pre Debe existir el archivo ../results/sim_data.dat
     * @post Genera archivo GIF en directorio results/
     */
    void probarGIFPython();
    
    /**
     * @brief Prueba la creación de GIF animado usando Gnuplot
     * @details Verifica instalación de Gnuplot, luego crea animación GIF
     * @pre Debe existir el archivo ../results/sim_data.dat
     * @post Genera archivo GIF en directorio results/
     */
    void probarGIFGnuplot();
    
    /**
     * @brief Prueba todas las herramientas incluyendo gráficas estáticas y GIFs animados
     * @details Ejecuta secuencialmente todas las herramientas de graficación disponibles
     */
    void probarTodasLasHerramientasConGIF();
    
    /**
     * @brief Lista y muestra información de todos los archivos en directorio results/
     * @details Usa comando ls para mostrar archivos generados por simulaciones y scripts
     */
    void verArchivosResultados();
    
    /**
     * @brief Función principal del modo testing que maneja el bucle de menú
     * @details Controla la interfaz de usuario, manejo de opciones y flujo del programa
     */
    void ejecutarModoTesting();
    
    /**
     * @brief Obtiene la lista de sistemas predefinidos disponibles para testing
     * @return Vector con configuraciones completas de sistemas conocidos
     * @details Incluye sistemas como órbita circular, problema de 3 cuerpos, etc.
     */
    std::vector<SistemaPrueba> obtenerSistemasPredefinidos();
    
    /**
     * @brief Presenta menú de sistemas predefinidos y permite selección interactiva
     * @details Muestra lista numerada de sistemas y ejecuta simulación del seleccionado
     */
    void mostrarSistemasPredefinidos();
    
    /**
     * @brief Genera archivo de entrada temporal para el programa principal
     * @param sistema Sistema predefinido cuyos datos se escribirán al archivo
     * @details Crea input_temp.txt con formato compatible con main.cpp
     */
    void generarArchivoEntrada(const SistemaPrueba& sistema);
    
    /**
     * @brief Ejecuta simulación completa usando el programa principal compilado
     * @param sistema Sistema predefinido a simular
     * @details Genera archivo de entrada, compila y ejecuta programa principal
     * @pre Código fuente debe estar en directorio ../src/
     * @post Genera archivos de datos en ../results/
     */
    void ejecutarSimulacionConSistema(const SistemaPrueba& sistema);
    
    /**
     * @brief Verifica estructura y formato del archivo de datos generado
     * @details Analiza cabecera, número de columnas y consistencia de datos
     * @pre Debe existir archivo ../results/sim_data.dat
     */
    void verificarFormatoArchivo();
    
} // namespace Testing

#endif // TESTING_H