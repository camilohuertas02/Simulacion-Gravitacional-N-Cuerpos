# Simulación Gravitacional N-Cuerpos

Este proyecto es una simulación numérica del problema de N-cuerpos, donde el movimiento de un conjunto de masas puntuales se calcula bajo la influencia de su mutua atracción gravitacional según la ley de Newton. El simulador está implementado en C++11 con un enfoque en la programación orientada a objetos y la validación física de los resultados.

## Features Principales

- **Motor de Simulación:** Implementación del problema de N-cuerpos utilizando el robusto algoritmo de integración numérica **Verlet de velocidad**.
- **Diseño Orientado a Objetos:** Código modular y extensible en C++11.
- **Entrada de Datos Interactiva:** Interfaz de consola para configurar todos los parámetros de la simulación, con validación de datos para prevenir errores.
- **Validación Física:** Cálculo y registro continuo de las energías cinética, potencial y total del sistema para verificar la conservación de la energía, un indicador clave de la precisión de la simulación.
- **Suite de Visualización Completa:** Incluye scripts en **Gnuplot, Python y Octave** que son totalmente **autosuficientes**:
    - No requieren argumentos desde la línea de comandos.
    - Detectan automáticamente el número de cuerpos (`N`) a partir del archivo de datos.
    - Analizan los datos para determinar si el movimiento es 2D o 3D y generan la gráfica más apropiada.
    - **Gráficas estáticas:** Trayectorias y evolución de energías.
    - **Animaciones GIF:** Visualización dinámica del comportamiento temporal del sistema.
- **Sistema de Testing Avanzado:** Marco completo de pruebas para desarrolladores y validación de herramientas.
- **Gestión de Proyecto con Makefile:** Incluye un `Makefile` completo para compilar el proyecto, generar documentación del código (Doxygen) y documentación teórica (LaTeX), y limpiar los archivos generados.

## Estructura del Proyecto

- **`bin/`**: Contiene los ejecutables después de la compilación.
- **`include/`**: Contiene los archivos de cabecera (`.h`) para las clases `vector3D`, `Cuerpo` y utilidades.
- **`src/`**: Contiene los archivos de implementación (`.cpp`) del programa principal.
- **`test/`**: **Sistema de testing para desarrolladores** con simulaciones predefinidas y validación de herramientas.
- **`scripts/`**: Scripts autosuficientes para graficación:
  - `plot_gravedad.{py,m,gp}`: Gráficas estáticas de trayectorias y energías.
  - `create_gif.{py,gp}`: Generación de animaciones GIF dinámicas.
- **`results/`**: Directorio donde se guardan los datos de salida y todas las visualizaciones generadas.
- **`documents/`**: Contiene la documentación teórica (`.tex`), la configuración de Doxygen y la salida generada.
- **`Makefile`**: Automatiza la compilación, testing, generación de documentación y limpieza.

## Requisitos

### Requisitos Básicos
- Un compilador de C++ que soporte C++11 (ej. `g++`).
- `make` para automatizar la construcción.

### Para Visualización (al menos uno requerido)
- **Gnuplot:** `sudo apt install gnuplot`
- **Python3 con bibliotecas:** 
  ```bash
  sudo apt install python3
  pip install numpy matplotlib pillow  # pillow requerido para GIFs
  ```
- **Octave:** `sudo apt install octave`

### Opcional - Para Documentación
- **Doxygen:** `sudo apt install doxygen` (documentación del código)
- **LaTeX:** `sudo apt install texlive-full` (documentación teórica en PDF)

## Compilación y Uso

### Compilación del Programa Principal
```bash
make all
```

### Ejecución para Usuarios Finales

1. **Ejecutar la simulación:**
   ```bash
   ./bin/gravedad
   ```

2. **Introducir los datos:** El programa solicitará interactivamente todos los parámetros necesarios.

3. **Seleccionar visualización:** Al finalizar, el programa ofrece un menú con opciones:
   - **Gráficas estáticas:** Gnuplot, Python o Octave
   - **Animaciones GIF:** Python o Gnuplot (nuevas opciones)
   - **No graficar:** Solo generar datos

4. **Análisis de resultados:**
   - **Datos numéricos:** `results/sim_data.dat`
   - **Gráficas estáticas:** `results/trayectorias_*.png`, `results/energias_*.png`
   - **Animaciones:** `results/simulacion_animada_*.gif`

## Sistema de Testing (Para Desarrolladores)

El proyecto incluye un sistema de testing completo diseñado para **desarrolladores y validación de herramientas**:

### Compilación del Sistema de Testing
```bash
make test
```

### Funcionalidades del Testing

#### 🔬 **Simulaciones Predefinidas**
- Sistemas físicos conocidos (órbita circular, problema de 3 cuerpos, etc.)
- Configuración automática de parámetros
- Validación de comportamiento esperado

#### 🛠️ **Validación de Herramientas**
- Verificación automática de instalaciones (Python, Octave, Gnuplot)
- Pruebas de generación de gráficas estáticas
- Pruebas de creación de animaciones GIF
- Verificación de formato de datos generados

#### 📊 **Opciones del Sistema de Testing**
```bash
./bin/testing
```
- **Opciones 1-3:** Simulaciones con sistemas predefinidos
- **Opciones 4-7:** Pruebas de herramientas de graficación estática
- **Opciones 8-10:** Pruebas de generación de GIFs animados
- **Opciones 11-14:** Utilidades de verificación y limpieza

#### 🎯 **Casos de Uso del Testing**
- **Desarrolladores:** Validar modificaciones al código
- **Instalación:** Verificar que todas las dependencias funcionan
- **Demos:** Generar rápidamente ejemplos con sistemas conocidos
- **Debugging:** Analizar comportamiento con datos controlados

## Características Avanzadas de Visualización

### Gráficas Estáticas Inteligentes
- **Detección automática 2D/3D:** Los scripts analizan el rango de movimiento en Z
- **Escalado automático:** Ajuste de límites de ejes según los datos
- **Múltiples formatos:** PNG de alta calidad para publicaciones

### Animaciones GIF Dinámicas
- **Trayectorias con estela:** Visualización de la historia reciente del movimiento
- **Marcadores de posición:** Indicadores claros de la posición actual de cada cuerpo
- **Información temporal:** Tiempo de simulación mostrado en cada frame
- **Optimización automática:** Reducción inteligente de frames para archivos manejables
- **Soporte 2D/3D:** Animaciones apropiadas según la dimensionalidad detectada

## Documentación y Limpieza

- **Generar documentación del código (Doxygen):**
  ```bash
  make dox
  ```
- **Generar PDF de la teoría (LaTeX):**
  ```bash
  make pdf
  ```
- **Limpiar archivos generados:**
  ```bash
  make clean        # Limpia binarios y objetos
  make clean-all    # Limpia todo incluyendo documentación
  ```

## Ejemplos de Uso

### Usuario Final - Simulación Personalizada
```bash
make all
./bin/gravedad
# Seguir prompts interactivos
# Seleccionar herramienta de visualización
```

### Desarrollador - Testing Rápido
```bash
make test
./bin/testing
# Seleccionar opción 1 (sistema predefinido)
# Seleccionar opción 10 (probar todas las herramientas)
```

### Generación de Demo con GIF
```bash
make test
./bin/testing
# Opción 1: Elegir "Sistema de 3 cuerpos"
# Opción 8: Crear GIF con Python
```

## Notas Técnicas

- **Constante gravitacional:** Definida en `include/utilidades.h`
- **Algoritmo de integración:** Verlet de velocidad para estabilidad energética
- **Formato de datos:** Columnas estructuradas con tiempo, posiciones, velocidades y energías
- **Detección de dimensionalidad:** Umbral configurable para distinguir 2D/3D
- **Validación física:** Monitoreo continuo de conservación de energía

