# ====================================================================
# Script de Gnuplot INTELIGENTE y ROBUSTO para graficar N-cuerpos
# - No necesita argumentos.
# - Detecta 'N' contando columnas en el archivo de datos.
# - Detecta si la simulación es 2D o 3D analizando el rango del eje Z.
# - Usa comandos explícitos para máxima compatibilidad.
# ====================================================================

# --- Paso 1: Definir el nombre del archivo de datos ---
FILENAME = "results/sim_data.dat"

# --- Paso 2: Calcular N automáticamente ---
# Contamos las columnas en la cabecera para deducir N
TOTAL_COLS = int(system(sprintf("head -n 1 %s | wc -w", FILENAME)))
N_BODIES = (TOTAL_COLS - 4) / 4

print sprintf("Script autosuficiente: Archivo '%s', Cuerpos detectados N=%d", FILENAME, N_BODIES)

# --- Paso 3: Detectar la dimensionalidad del movimiento ---
print "Analizando dimensionalidad del movimiento..."
Z_MIN_GLOBAL = 1e38
Z_MAX_GLOBAL = -1e38

do for [i=1:N_BODIES] {
    z_col = 4 + 3*(i-1)
    stats FILENAME using z_col nooutput
    if (STATS_min < Z_MIN_GLOBAL) { Z_MIN_GLOBAL = STATS_min }
    if (STATS_max > Z_MAX_GLOBAL) { Z_MAX_GLOBAL = STATS_max }
}
Z_RANGE = Z_MAX_GLOBAL - Z_MIN_GLOBAL
Z_THRESHOLD = 1e-6
print sprintf("Rango de Z detectado: %.4g (min=%.4g, max=%.4g)", Z_RANGE, Z_MIN_GLOBAL, Z_MAX_GLOBAL)


# --- Paso 4: Graficar Trayectorias (2D o 3D) ---
set term pngcairo enhanced font "arial,10" size 800,600
set grid
colores = "blue red green purple orange brown black yellow magenta cyan"
getColor(i) = word(colores, i)

if (Z_RANGE < Z_THRESHOLD) {
    # --- LÓGICA PARA GRÁFICOS 2D ---
    print "Movimiento detectado como 2D. Generando gráfico 2D."
    set output sprintf("results/trayectorias_2D_%d_cuerpos.png", N_BODIES)
    set title sprintf("Trayectorias (Vista 2D, N=%d Cuerpos)", N_BODIES)
    set xlabel "X"
    set ylabel "Y"
    unset zlabel
    
    # Graficamos explícitamente para N=2. El '' reutiliza el nombre de archivo.
    plot FILENAME using 2:3 with lines title "Cuerpo 1" lw 2 lc rgb getColor(1), \
         '' using 5:6 with lines title "Cuerpo 2" lw 2 lc rgb getColor(2)
    # Nota: Si tuvieras N=3, añadirías: , '' using 8:9 with lines title "Cuerpo 3" lw 2 lc rgb getColor(3)

} else {
    # --- LÓGICA PARA GRÁFICOS 3D ---
    print "Movimiento detectado como 3D. Generando gráfico 3D."
    set output sprintf("results/trayectorias_3D_%d_cuerpos.png", N_BODIES)
    set title sprintf("Trayectorias (Vista 3D, N=%d Cuerpos)", N_BODIES)
    set xlabel "X"; set ylabel "Y"; set zlabel "Z"
    set ticslevel 0
    
    # Graficamos explícitamente para N=2 en 3D.
    splot FILENAME using 2:3:4 with lines title "Cuerpo 1" lw 2 lc rgb getColor(1), \
          '' using 5:6:7 with lines title "Cuerpo 2" lw 2 lc rgb getColor(2)
    # Nota: Si tuvieras N=3, añadirías: , '' using 8:9:10 with lines title "Cuerpo 3" lw 2 lc rgb getColor(3)
}


# --- Paso 5: Graficar Energías (siempre se genera) ---
set output sprintf("results/energias_%d_cuerpos.png", N_BODIES)
set title sprintf("Energías del Sistema (N=%d Cuerpos)", N_BODIES)
set xlabel "Tiempo"; set ylabel "Energía"
set key top right

COL_K = 4*N_BODIES + 2
COL_U = 4*N_BODIES + 3
COL_E = 4*N_BODIES + 4

plot FILENAME using 1:COL_K with lines title "Energía Cinética Total" lw 2 lc rgb "red", \
     FILENAME using 1:COL_U with lines title "Energía Potencial Total" lw 2 lc rgb "blue", \
     FILENAME using 1:COL_E with lines title "Energía Total del Sistema" lw 2 lc rgb "green"

print "Proceso de graficación completado."
