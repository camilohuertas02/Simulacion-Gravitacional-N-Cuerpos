# Simulación Gravitacional N-Cuerpos

Este proyecto es una simulación numérica del problema de N-cuerpos, donde el movimiento de un conjunto de masas puntuales se calcula bajo la influencia de su mutua atracción gravitacional según la ley de Newton. El simulador está implementado en C++11 con un enfoque en la programación orientada a objetos y la validación física de los resultados.

## Features Principales

- **Motor de Simulación:** Implementación del problema de N-cuerpos utilizando el robusto algoritmo de integración numérica **Verlet de velocidad**.
- **Diseño Orientado a Objetos:** Código modular y extensible en C++11.
- **Entrada de Datos Interactiva:** Interfaz de consola para configurar todos los parámetros de la simulación, con validación de datos para prevenir errores.
- **Validación Física:** Cálculo y registro continuo de las energías cinética, potencial y total del sistema para verificar la conservación de la energía.
- **Suite de Visualización Completa:** Incluye scripts en **Gnuplot, Python y Octave** que son totalmente **autosuficientes**:
    - Detectan automáticamente el número de cuerpos (`N`) y dimensionalidad (2D/3D)
    - **Gráficas estáticas:** Trayectorias y evolución de energías
    - **Animaciones GIF:** Visualización dinámica del comportamiento temporal
- **Sistema de Testing:** Herramientas de desarrollo y validación para programadores
- **Gestión Automatizada:** Makefile completo para compilación, documentación y limpieza

## Estructura del Proyecto

```
Simulacion-Gravitacional-N-Cuerpos/
├── bin/          # Ejecutables compilados
├── src/          # Código fuente C++
├── include/      # Archivos de cabecera
├── scripts/      # Scripts de visualización
├── test/         # Sistema de testing (para desarrolladores)
├── results/      # Datos y gráficas generadas
├── documents/    # Documentación y configuraciones
└── Makefile      # Automatización de tareas
```

## Requisitos

### Básicos (requeridos)
- Compilador C++11 (ej. `g++`)
- `make`

### Para Visualización (al menos uno)
- **Gnuplot:** `sudo apt install gnuplot`
- **Python3:** 
  ```bash
  sudo apt install python3 python3-pip
  pip3 install numpy matplotlib pillow
  ```
- **Octave:** `sudo apt install octave`

### Opcional
- **Doxygen:** `sudo apt install doxygen` (documentación del código)
- **LaTeX:** `sudo apt install texlive-full` (documentación teórica)

## Uso Rápido

### 1. Compilar
```bash
make all
```

### 2. Ejecutar Simulación
```bash
./bin/gravedad
```

### 3. Seguir los Prompts
- Introducir número de cuerpos
- Definir masas, radios, posiciones y velocidades
- Configurar parámetros de simulación (dt, tiempo total)
- Seleccionar herramienta de visualización

### 4. Revisar Resultados
- **Datos:** [`results/sim_data.dat`](results/sim_data.dat )
- **Gráficas:** [`results/trayectorias_*.png`](results/trayectorias_*.png ), [`results/energias_*.png`](results/energias_*.png )
- **Animaciones:** [`results/simulacion_animada_*.gif`](results/simulacion_animada_*.gif )

## Características de Visualización

### Gráficas Estáticas
- **Detección automática 2D/3D** según el rango de movimiento
- **Trayectorias completas** de todos los cuerpos
- **Evolución de energías** (cinética, potencial, total)
- **Escalado automático** de ejes

### Animaciones GIF
- **Trayectorias dinámicas** con estela histórica
- **Marcadores de posición** actual de cada cuerpo
- **Información temporal** en tiempo real
- **Optimización automática** de frames para archivos manejables

## Herramientas Disponibles

| Herramienta | Gráficas Estáticas | Animaciones GIF |
|-------------|-------------------|-----------------|
| **Gnuplot** | ✅ | ✅ |
| **Python** | ✅ | ✅ |
| **Octave** | ✅ | ❌ |

## Ejemplos de Uso

### Simulación Simple - Sistema Tierra-Luna
```bash
make all
./bin/gravedad
# Introducir: 2 cuerpos, masas apropiadas, órbita circular
# Seleccionar: Crear GIF animado (Python)
```

### Solo Datos (Sin Visualización)
```bash
./bin/gravedad
# Configurar simulación
# Seleccionar: "No graficar"
# Analizar results/sim_data.dat manualmente
```

### Testing y Desarrollo
Sistema de pruebas que incluye simulaciones predefinidas (órbitas circulares, sistemas de 3-4 cuerpos, colisiones) y validación automática de todas las herramientas de visualización disponibles (Python, Gnuplot, Octave) con generación de gráficas estáticas y animaciones GIF.

```bash
make test-build
./test/testing
```
o simplemente
```bash
make test
```

## Comandos Útiles

```bash
# Compilación
make all              # Compilar programa principal
make test             # Compilar y ejecutar sistema de testing

# Documentación
make dox              # Generar documentación HTML
make pdf              # Generar documentación PDF

# Limpieza
make clean            # Limpiar binarios y objetos
```

## Validación Física

El simulador incluye monitoreo continuo de la conservación de energía:
- **Energía Cinética:** K = ½mv²
- **Energía Potencial:** U = -Gm₁m₂/r
- **Energía Total:** E = K + U (debe conservarse)

La estabilidad de la energía total es un indicador clave de la precisión numérica de la simulación.

## Algoritmo de Integración

Se utiliza el **algoritmo Verlet de velocidad** por su excelente conservación de energía:

1. **Posiciones:** r(t+dt) = r(t) + v(t)dt + ½a(t)dt²
2. **Velocidades:** v(t+dt) = v(t) + ½[a(t) + a(t+dt)]dt
3. **Fuerzas:** F = Gm₁m₂/r² (Ley de Gravitación Universal)

## Estructura de Datos

### Archivo de Salida: [`results/sim_data.dat`](results/sim_data.dat )
```
# t x1 y1 z1 vx1 vy1 vz1 x2 y2 z2 vx2 vy2 vz2 ... K U E
0.00 1.0 0.0 0.0 0.0 1.0 0.0 -1.0 0.0 0.0 0.0 -1.0 0.0 1.0 -0.5 0.5
0.01 ...
```

- **t:** Tiempo
- **x,y,z:** Posiciones de cada cuerpo
- **vx,vy,vz:** Velocidades de cada cuerpo
- **K:** Energía cinética total
- **U:** Energía potencial total
- **E:** Energía total (K+U)
 
## Notas Técnicas

- **Constante gravitacional:** En este caso tomado como G = 1 para sencillez al realizar los cálculos
- **Unidades:** SI (metros, kilogramos, segundos)
- **Precisión:** double (64 bits)
- **Detección 2D/3D:** Umbral Z < 1e-6 para considerar movimiento plano

