# Script de Gnuplot para graficar resultados de simulación N-cuerpos
# Se espera que se llame como: gnuplot plot_gravedad.gp N_BODIES FILENAME
# Ejemplo: gnuplot plot_gravedad.gp 2 results/datos_2.dat

# Argumentos del script
# ARG1 : N_BODIES (número de cuerpos)
# ARG2 : FILENAME (nombre del archivo de datos)
N_BODIES = ARG1
FILENAME = ARG2

set term pngcairo enhanced font "arial,10" size 800,600
set output sprintf("results/trayectorias_%s.png", N_BODIES)

set title sprintf("Trayectorias Simulación N=%s Cuerpos", N_BODIES)
set xlabel "X"
set ylabel "Y"
set zlabel "Z"
set grid
set ticslevel 0 # Para que el origen (0,0,0) se dibuje correctamente si es parte del rango

# Definir colores para las trayectorias (hasta 10 cuerpos, se pueden añadir más)
colores = "blue red green purple orange brown black yellow magenta cyan"
getColor(i) = word(colores, i)

# Descubrir cuántas columnas de posición hay
# Tiempo (1) + N*3 (posiciones) + N*1 (velocidades) + 3 (energías)
# Columna de x1 es 2, y1 es 3, z1 es 4
# Columna de x2 es 5, y2 es 6, z2 es 7
# ...
# Columna de x_i es 2 + (i-1)*3
# Columna de y_i es 3 + (i-1)*3
# Columna de z_i es 4 + (i-1)*3

# Para 2D (XY)
# plot for [i=1:N_BODIES] FILENAME using (column(2+(i-1)*3)):(column(3+(i-1)*3)) with lines title sprintf("Cuerpo %d", i) lc rgb getColor(i)

# Para 3D (XYZ)
splot for [i=1:N_BODIES] FILENAME using (column(2+(i-1)*3)):(column(3+(i-1)*3)):(column(4+(i-1)*3)) with lines title sprintf("Cuerpo %d", i) lc rgb getColor(i)


# Graficar Energías
set output sprintf("results/energias_%s.png", N_BODIES)
set title sprintf("Energías del Sistema (N=%s Cuerpos)", N_BODIES)
set xlabel "Tiempo"
set ylabel "Energía"
set grid
set key top right

# Columnas de energía:
# K_total es N_BODIES*3 (pos) + N_BODIES*1 (vel) + 1 (tiempo) + 1 = (4*N_BODIES + 2)
# U_total es (4*N_BODIES + 3)
# E_total es (4*N_BODIES + 4)
COL_K = 4*N_BODIES + 2
COL_U = 4*N_BODIES + 3
COL_E = 4*N_BODIES + 4

plot FILENAME using 1:COL_K with lines title "Energía Cinética Total" lc rgb "red", \
     FILENAME using 1:COL_U with lines title "Energía Potencial Total" lc rgb "blue", \
     FILENAME using 1:COL_E with lines title "Energía Total del Sistema" lc rgb "green"

print sprintf("Gráficas generadas: results/trayectorias_%s.png y results/energias_%s.png", N_BODIES, N_BODIES)
# Para ver las gráficas interactivamente, comenta 'set term' y 'set output' y usa 'pause -1' al final.
# pause -1 "Presiona Enter para salir de Gnuplot"
