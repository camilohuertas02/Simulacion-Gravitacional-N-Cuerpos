# Simulación Gravitacional N-Cuerpos

Este proyecto es una simulación numérica del problema de N-cuerpos, donde el movimiento de un conjunto de masas puntuales se calcula bajo la influencia de su mutua atracción gravitacional según la ley de Newton. El simulador está implementado en C++11 con un enfoque en la programación orientada a objetos y la validación física de los resultados.

## Features Principales

- **Motor de Simulación:** Implementación del problema de N-cuerpos utilizando el robusto algoritmo de integración numérica **Verlet de velocidad**.
- **Diseño Orientado a Objetos:** Código modular y extensible en C++11.
- **Entrada de Datos Interactiva:** Interfaz de consola para configurar todos los parámetros de la simulación, con validación de datos para prevenir errores.
- **Validación Física:** Cálculo y registro continuo de las energías cinética, potencial y total del sistema para verificar la conservación de la energía, un indicador clave de la precisión de la simulación.
- **Suite de Visualización Inteligente:** Incluye scripts en **Gnuplot, Python y Octave** que son totalmente **autosuficientes**:
    - No requieren argumentos desde la línea de comandos.
    - Detectan automáticamente el número de cuerpos (`N`) a partir del archivo de datos.
    - Analizan los datos para determinar si el movimiento es 2D o 3D y generan la gráfica más apropiada.
- **Gestión de Proyecto con Makefile:** Incluye un `Makefile` completo para compilar el proyecto, generar documentación del código (Doxygen) y documentación teórica (LaTeX), y limpiar los archivos generados.

## Estructura del Proyecto

- **`bin/`**: Contiene el ejecutable `gravedad` después de la compilación.
- **`include/`**: Contiene los archivos de cabecera (`.h`) para las clases `vector3D`, `Cuerpo` y utilidades.
- **`src/`**: Contiene los archivos de implementación (`.cpp`) del proyecto.
- **`scripts/`**: Contiene los scripts autosuficientes para graficar los resultados (`plot_gravedad.gp`, `plot_gravedad.py`, `plot_gravedad.m`).
- **`results/`**: Directorio donde se guardan los datos de salida (`sim_data.dat`) y las gráficas generadas.
- **`documents/`**: Contiene la documentación teórica (`.tex`), la configuración de Doxygen y la salida generada.
- **`Makefile`**: Automatiza la compilación, la generación de documentación y la limpieza.
- **`README.md`**: Este archivo.

## Requisitos

- Un compilador de C++ que soporte C++11 (ej. `g++`).
- `make` para automatizar la construcción.
- **Para la visualización, se requiere al menos uno de los siguientes:**
    - `gnuplot`
    - `python3` con las librerías `numpy` y `matplotlib`. Se pueden instalar con: `pip install numpy matplotlib`
    - `octave`
- **(Opcional) Para la documentación:**
    - `doxygen` para generar la documentación del código.
    - Una distribución de LaTeX (ej. `pdflatex`) para generar el documento teórico en PDF.

## Compilación

Para compilar el proyecto, ejecute el siguiente comando en el directorio raíz:
```bash
make all
````

Esto creará el ejecutable `gravedad` en el directorio `bin/`.

## Ejecución

1.  **Ejecutar la simulación:**

    ```bash
    ./bin/gravedad
    ```

2.  **Introducir los datos:** El programa solicitará interactivamente todos los parámetros necesarios (número de cuerpos, sus masas, posiciones y velocidades iniciales, y los parámetros del tiempo de simulación).

3.  **Análisis de Salida:**

      - Los datos numéricos de la simulación se guardarán en un archivo de nombre fijo: **`results/sim_data.dat`**.
      - Al finalizar, el programa ofrecerá un menú para elegir una herramienta de visualización (Gnuplot, Python u Octave).
      - El script seleccionado analizará `sim_data.dat` y generará automáticamente las gráficas de **trayectorias** (en 2D o 3D, según corresponda) y de **energías** en el directorio `results/`.

## Documentación y Limpieza

  - **Generar documentación del código (Doxygen):**
    ```bash
    make dox
    ```
  - **Generar PDF de la teoría (LaTeX):**
    ```bash
    make pdf
    ```
  - **Limpiar todos los archivos generados:**
    ```bash
    make clean
    ```

## Notas Adicionales

  - La constante gravitacional `G` está definida en `include/utilidades.h`.
  - La integración numérica se realiza mediante un algoritmo de **Verlet de velocidad**, conocido por su buena estabilidad a largo plazo en la conservación de la energía.
