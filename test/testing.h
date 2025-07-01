/**
 * @file testing.h
 * @brief Funciones de testing para herramientas de graficación
 * @author Isabel Nieto
 * @date 2025
 */

#ifndef TESTING_H
#define TESTING_H

#include <string>

namespace Testing {
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
     * @brief Abre un archivo con el visualizador predeterminado
     * @param archivo Ruta del archivo a abrir
     */
    void abrirVisualizador(const std::string& archivo);
    
    /**
     * @brief Menú para visualizar gráficas generadas
     */
    void menuVisualizacion();
    
    /**
     * @brief Función principal del modo testing
     */
    void ejecutarModoTesting();
}

#endif // TESTING_H