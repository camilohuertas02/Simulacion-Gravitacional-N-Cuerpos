# Simulación Gravitacional N-Cuerpos

Este proyecto simula el movimiento de N cuerpos interactuando mutuamente mediante la ley de la gravitación universal de Newton. Está implementado en C++ y utiliza la Programación Orientada a Objetos.

## Estructura del Proyecto

-   `bin/`: Contiene el ejecutable `gravedad` después de la compilación.
-   `include/`: Contiene los archivos de cabecera (`.h`):
    -   `vector3D.h`: Definición de la clase para álgebra vectorial en 3D.
    -   `Cuerpo.h`: Definición de la clase `Cuerpo` que representa un cuerpo celeste.
    -   `utilidades.h`: Constantes globales (como `G`) y posibles funciones de utilidad.
-   `src/`: Contiene los archivos de implementación (`.cpp`):
    -   `vector3D.cpp`: Implementación de la clase `vector3D`.
    -   `Cuerpo.cpp`: Implementación de la clase `Cuerpo`.
    -   `utilidades.cpp`: Implementación de funciones de utilidad.
    -   `main.cpp`: Lógica principal de la simulación, manejo de entrada/salida y bucle de integración.
-   `scripts/`: Contiene scripts para graficar los resultados:
    -   `plot_gravedad.gp`: Script para Gnuplot.
    -   `plot_gravedad.py`: Script para Python (usando Matplotlib).
    -   `plot_gravedad.m`: Script para Octave/MATLAB.
-   `results/`: Directorio donde se guardan los datos de salida de la simulación (ej. `datos_N.dat`) y las gráficas generadas.
-   `documents/`: Contiene la documentación del proyecto:
    -   `gravitacional.tex`: Documento LaTeX con la descripción teórica del problema.
    -   `Doxyfile`: Archivo de configuración para Doxygen.
    -   `html/` (generado): Documentación HTML generada por Doxygen.
    -   `latex/` (generado): Documentación LaTeX generada por Doxygen.
    -   `gravitacional.pdf` (generado): PDF del documento teórico.
-   `Makefile`: Para compilar el proyecto, generar documentación y limpiar.
-   `README.md`: Este archivo.

## Requisitos de Compilación y Ejecución

-   Un compilador de C++ que soporte C++11 (ej. g++).
-   `make` para construir el proyecto.
-   `doxygen` (opcional, para generar la documentación del código fuente).
-   `pdflatex` (opcional, para generar el PDF de la documentación teórica).
-   Para graficar los resultados, se necesita al menos uno de los siguientes:
    -   `gnuplot`
    -   `python` con la librería `matplotlib` y `numpy` (`pip install matplotlib numpy`)
    -   `octave`

## Compilación

Para compilar el proyecto, ejecute el siguiente comando en el directorio raíz del proyecto:

```bash
make
```
o
```bash
make all
```

Esto compilará los archivos fuente y creará el ejecutable `gravedad` en el directorio `bin/`.

## Generación de Documentación

### Documentación del Código Fuente (Doxygen)
Para generar la documentación del código fuente en formato HTML y LaTeX:
```bash
make dox
```
La salida HTML se encontrará en `documents/html/` y la LaTeX en `documents/latex/`.

### Documento Teórico (PDF)
Para compilar el archivo `gravitacional.tex` y generar `gravitacional.pdf`:
```bash
make pdf
```
El PDF se guardará en el directorio `documents/`.

## Ejecución de la Simulación

Una vez compilado, el ejecutable se encuentra en `bin/gravedad`. Para ejecutarlo:

```bash
./bin/gravedad
```

El programa solicitará interactivamente:
1.  El número de cuerpos (N).
2.  Para cada cuerpo:
    -   Masa
    -   Radio (informativo, no usado en el cálculo de fuerzas)
    -   Posición inicial (x y z)
    -   Velocidad inicial (Vx Vy Vz)
3.  Parámetros de la simulación:
    -   Paso de tiempo (dt)
    -   Tiempo total de simulación (t_max)

Los resultados de la simulación (tiempo, posiciones, velocidades escalares, energías) se guardarán en un archivo llamado `results/datos_N.dat`, donde N es el número de cuerpos.

Después de que la simulación termine, el programa ofrecerá la opción de graficar los resultados utilizando Gnuplot, Python o Octave, si los scripts correspondientes están disponibles y las herramientas instaladas. Las gráficas generadas (trayectorias y energías) también se guardarán en el directorio `results/`.

## Limpieza

Para eliminar los archivos objeto, el ejecutable, los datos de resultados y la documentación generada:

```bash
make clean
```

## Casos de Prueba Sugeridos

-   **N = 1**: Un solo planeta orbitando un "foco central" (se puede simular con un cuerpo de masa muy grande y velocidad inicial cero en el origen, y un segundo cuerpo con masa pequeña y velocidad tangencial). Verificar la conservación de momento angular y energía.
-   **N = 2**: Dos cuerpos de masas comparables. Observar el movimiento elíptico mutuo alrededor del centro de masas.
-   **N = 3**: Problema de los tres cuerpos. Probar con diferentes condiciones iniciales para observar órbitas estables, caóticas o colisiones (el programa actual no maneja colisiones físicas, los cuerpos pueden pasar a través de otros).

## Notas Adicionales
- La constante gravitacional `G` está normalizada a `1.0` en `include/utilidades.h`.
- La clase `vector3D` proporcionada se utiliza para todas las operaciones vectoriales.
- La integración numérica se realiza mediante el algoritmo de Verlet (velocity Verlet).
- Se calculan y guardan las energías cinética, potencial y total del sistema para verificar la conservación de energía.
