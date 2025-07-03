# ====================================================================
# Script de Gnuplot para crear GIF animado de simulación N-cuerpos
# ====================================================================

# --- Configurar rutas por defecto ---
FILENAME = "results/sim_data.dat"
RESULTS_DIR = "results/"

print "Creando GIF animado con Gnuplot..."
print sprintf("Archivo de datos: %s", FILENAME)

# --- Verificar que el archivo existe ---
stats FILENAME using 1 nooutput

# --- Calcular N automáticamente ---
TOTAL_COLS = int(system(sprintf("head -n 1 %s | wc -w", FILENAME)))
N_BODIES = (TOTAL_COLS - 4) / 4

print sprintf("Cuerpos detectados N=%d", N_BODIES)

# --- Detectar dimensionalidad ---
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

print sprintf("Rango de Z: %.4g. Movimiento: %s", Z_RANGE, (Z_RANGE < Z_THRESHOLD ? "2D" : "3D"))

# --- Configurar terminal GIF ---
set terminal gif animate delay 8 loop 0 size 1000,800
set output sprintf("%ssimulacion_animada_gnuplot_%s_%d_cuerpos.gif", RESULTS_DIR, (Z_RANGE < Z_THRESHOLD ? "2D" : "3D"), N_BODIES)

# --- Obtener límites de datos ---
stats FILENAME using 2 nooutput
X_MIN = STATS_min
X_MAX = STATS_max

stats FILENAME using 3 nooutput
Y_MIN = STATS_min
Y_MAX = STATS_max

# Agregar margen
X_MARGIN = (X_MAX - X_MIN) * 0.1
Y_MARGIN = (Y_MAX - Y_MIN) * 0.1

set xrange [X_MIN - X_MARGIN : X_MAX + X_MARGIN]
set yrange [Y_MIN - Y_MARGIN : Y_MAX + Y_MARGIN]

if (Z_RANGE >= Z_THRESHOLD) {
    stats FILENAME using 4 nooutput
    Z_MIN = STATS_min
    Z_MAX = STATS_max
    Z_MARGIN = (Z_MAX - Z_MIN) * 0.1
    set zrange [Z_MIN - Z_MARGIN : Z_MAX + Z_MARGIN]
}

set grid
set xlabel "X"
set ylabel "Y"
if (Z_RANGE >= Z_THRESHOLD) { set zlabel "Z" }

# --- Obtener número total de frames ---
stats FILENAME using 1 nooutput
TOTAL_FRAMES = STATS_records

# Aumentar significativamente el número de frames para mejor visualización
FRAME_STEP = int(TOTAL_FRAMES / 150)  # Máximo 150 frames (era 50)
if (FRAME_STEP < 1) { FRAME_STEP = 1 }

print sprintf("Generando %d frames de %d datos totales (paso=%d)", int(TOTAL_FRAMES/FRAME_STEP), TOTAL_FRAMES, FRAME_STEP)

# --- Colores simplificados ---
color1 = "blue"
color2 = "red" 
color3 = "green"
color4 = "purple"

# --- Generar animación ---
do for [frame=1:TOTAL_FRAMES:FRAME_STEP] {
    
    set title sprintf("Simulación Gravitacional (Frame %d/%d, t=%.2f)", frame, TOTAL_FRAMES, frame*0.01)
    
    # Aumentar significativamente la trayectoria visible
    trail_length = int(TOTAL_FRAMES * 0.15)  # 15% del total de datos
    trail_start = (frame > trail_length) ? frame - trail_length : 1
    
    if (Z_RANGE < Z_THRESHOLD) {
        # --- Animación 2D con más trayectoria ---
        if (N_BODIES == 1) {
            plot FILENAME every ::trail_start::frame using 2:3 with lines lw 2 lc rgb color1 notitle, \
                 '' every ::frame::frame using 2:3 with points pt 7 ps 3 lc rgb color1 title "Cuerpo 1"
        } else {
            if (N_BODIES == 2) {
                plot FILENAME every ::trail_start::frame using 2:3 with lines lw 2 lc rgb color1 notitle, \
                     '' every ::trail_start::frame using 5:6 with lines lw 2 lc rgb color2 notitle, \
                     '' every ::frame::frame using 2:3 with points pt 7 ps 3 lc rgb color1 title "Cuerpo 1", \
                     '' every ::frame::frame using 5:6 with points pt 7 ps 3 lc rgb color2 title "Cuerpo 2"
            } else {
                if (N_BODIES == 3) {
                    plot FILENAME every ::trail_start::frame using 2:3 with lines lw 2 lc rgb color1 notitle, \
                         '' every ::trail_start::frame using 5:6 with lines lw 2 lc rgb color2 notitle, \
                         '' every ::trail_start::frame using 8:9 with lines lw 2 lc rgb color3 notitle, \
                         '' every ::frame::frame using 2:3 with points pt 7 ps 3 lc rgb color1 title "Cuerpo 1", \
                         '' every ::frame::frame using 5:6 with points pt 7 ps 3 lc rgb color2 title "Cuerpo 2", \
                         '' every ::frame::frame using 8:9 with points pt 7 ps 3 lc rgb color3 title "Cuerpo 3"
                } else {
                    # Para 4+ cuerpos
                    plot FILENAME every ::trail_start::frame using 2:3 with lines lw 2 lc rgb color1 notitle, \
                         '' every ::trail_start::frame using 5:6 with lines lw 2 lc rgb color2 notitle, \
                         '' every ::trail_start::frame using 8:9 with lines lw 2 lc rgb color3 notitle, \
                         '' every ::trail_start::frame using 11:12 with lines lw 2 lc rgb color4 notitle, \
                         '' every ::frame::frame using 2:3 with points pt 7 ps 3 lc rgb color1 title "Cuerpo 1", \
                         '' every ::frame::frame using 5:6 with points pt 7 ps 3 lc rgb color2 title "Cuerpo 2", \
                         '' every ::frame::frame using 8:9 with points pt 7 ps 3 lc rgb color3 title "Cuerpo 3", \
                         '' every ::frame::frame using 11:12 with points pt 7 ps 3 lc rgb color4 title "Cuerpo 4"
                }
            }
        }
    } else {
        # --- Animación 3D con más trayectoria ---
        if (N_BODIES == 1) {
            splot FILENAME every ::trail_start::frame using 2:3:4 with lines lw 2 lc rgb color1 notitle, \
                  '' every ::frame::frame using 2:3:4 with points pt 7 ps 3 lc rgb color1 title "Cuerpo 1"
        } else {
            if (N_BODIES == 2) {
                splot FILENAME every ::trail_start::frame using 2:3:4 with lines lw 2 lc rgb color1 notitle, \
                      '' every ::trail_start::frame using 5:6:7 with lines lw 2 lc rgb color2 notitle, \
                      '' every ::frame::frame using 2:3:4 with points pt 7 ps 3 lc rgb color1 title "Cuerpo 1", \
                      '' every ::frame::frame using 5:6:7 with points pt 7 ps 3 lc rgb color2 title "Cuerpo 2"
            } else {
                if (N_BODIES == 3) {
                    splot FILENAME every ::trail_start::frame using 2:3:4 with lines lw 2 lc rgb color1 notitle, \
                          '' every ::trail_start::frame using 5:6:7 with lines lw 2 lc rgb color2 notitle, \
                          '' every ::trail_start::frame using 8:9:10 with lines lw 2 lc rgb color3 notitle, \
                          '' every ::frame::frame using 2:3:4 with points pt 7 ps 3 lc rgb color1 title "Cuerpo 1", \
                          '' every ::frame::frame using 5:6:7 with points pt 7 ps 3 lc rgb color2 title "Cuerpo 2", \
                          '' every ::frame::frame using 8:9:10 with points pt 7 ps 3 lc rgb color3 title "Cuerpo 3"
                } else {
                    # Para 4+ cuerpos
                    splot FILENAME every ::trail_start::frame using 2:3:4 with lines lw 2 lc rgb color1 notitle, \
                          '' every ::trail_start::frame using 5:6:7 with lines lw 2 lc rgb color2 notitle, \
                          '' every ::trail_start::frame using 8:9:10 with lines lw 2 lc rgb color3 notitle, \
                          '' every ::trail_start::frame using 11:12:13 with lines lw 2 lc rgb color4 notitle, \
                          '' every ::frame::frame using 2:3:4 with points pt 7 ps 3 lc rgb color1 title "Cuerpo 1", \
                          '' every ::frame::frame using 5:6:7 with points pt 7 ps 3 lc rgb color2 title "Cuerpo 2", \
                          '' every ::frame::frame using 8:9:10 with points pt 7 ps 3 lc rgb color3 title "Cuerpo 3", \
                          '' every ::frame::frame using 11:12:13 with points pt 7 ps 3 lc rgb color4 title "Cuerpo 4"
                }
            }
        }
    }
}

unset output
print sprintf("GIF creado: %ssimulacion_animada_gnuplot_%s_%d_cuerpos.gif", RESULTS_DIR, (Z_RANGE < Z_THRESHOLD ? "2D" : "3D"), N_BODIES)
print "¡Animación completada! El archivo será más grande pero mostrará mejor el comportamiento dinámico."