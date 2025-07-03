import numpy as np
import matplotlib.pyplot as plt
import matplotlib.animation as animation
import os

# --- Constantes y Configuración ---
Z_THRESHOLD = 1e-6  # Umbral para considerar el movimiento como 2D

def find_data_file():
    """Busca el archivo de datos en diferentes ubicaciones posibles."""
    possible_paths = [
        "results/sim_data.dat",      # Desde directorio raíz
        "../results/sim_data.dat",   # Desde test/ o scripts/
        "../../results/sim_data.dat" # Desde subdirectorios anidados
    ]
    
    for path in possible_paths:
        if os.path.exists(path):
            return path
    
    return None

def find_results_dir():
    """Encuentra el directorio results/ para guardar las gráficas."""
    possible_dirs = [
        "results/",      # Desde directorio raíz
        "../results/",   # Desde test/ o scripts/
        "../../results/" # Desde subdirectorios anidados
    ]
    
    for dir_path in possible_dirs:
        if os.path.exists(dir_path):
            return dir_path
    
    # Si no existe, crear en la ubicación más probable
    try:
        os.makedirs("../results/", exist_ok=True)
        return "../results/"
    except:
        try:
            os.makedirs("results/", exist_ok=True)
            return "results/"
        except:
            return "./"  # Último recurso: directorio actual

def get_num_bodies_from_header(filepath):
    """Lee la primera línea de un archivo de datos para determinar el número de cuerpos."""
    try:
        with open(filepath, 'r') as f:
            header = f.readline()
            num_cols = len(header.lstrip('#').split())
            num_bodies = (num_cols - 4) // 4
            return num_bodies
    except Exception as e:
        print(f"Error al leer la cabecera del archivo para determinar N: {e}")
        return None

def create_animated_gif():
    """Función principal que carga los datos y genera un GIF animado."""
    
    # Buscar archivo de datos
    data_file = find_data_file()
    if data_file is None:
        print(f"Error: No se encontró el archivo de datos en ninguna ubicación.")
        return

    # Buscar directorio de resultados
    results_dir = find_results_dir()
    
    print(f"Archivo de datos encontrado: {data_file}")
    print(f"Directorio de resultados: {results_dir}")

    num_bodies = get_num_bodies_from_header(data_file)
    if num_bodies is None or num_bodies <= 0:
        print(f"No se pudo determinar un número válido de cuerpos desde '{data_file}'.")
        return
        
    print(f"Creando GIF animado: Archivo '{data_file}', Cuerpos detectados N={num_bodies}")
    
    # Cargar datos
    data = np.loadtxt(data_file, comments='#')
    time = data[:, 0]
    
    # Detectar dimensionalidad
    z_column_indices = [3 + i * 3 for i in range(num_bodies)]
    z_data = data[:, z_column_indices]
    z_range = np.ptp(z_data)
    is_3d = z_range > Z_THRESHOLD
    
    print(f"Rango de Z detectado: {z_range:.4g}. El movimiento es {'3D' if is_3d else '2D'}.")
    
    # Configurar la figura
    if is_3d:
        fig = plt.figure(figsize=(10, 8))
        ax = fig.add_subplot(111, projection='3d')
        ax.set_zlabel("Z")
    else:
        fig, ax = plt.subplots(figsize=(10, 8))
    
    ax.set_xlabel("X")
    ax.set_ylabel("Y")
    ax.set_title(f'Simulación Gravitacional Animada (N={num_bodies} Cuerpos)')
    
    # Configurar colores
    colors = plt.cm.tab10(np.linspace(0, 1, num_bodies))
    
    # Configurar límites de los ejes
    x_indices = [1 + i * 3 for i in range(num_bodies)]
    y_indices = [2 + i * 3 for i in range(num_bodies)]
    
    all_x = data[:, x_indices].flatten()
    all_y = data[:, y_indices].flatten()
    
    x_margin = (np.max(all_x) - np.min(all_x)) * 0.1
    y_margin = (np.max(all_y) - np.min(all_y)) * 0.1
    
    ax.set_xlim(np.min(all_x) - x_margin, np.max(all_x) + x_margin)
    ax.set_ylim(np.min(all_y) - y_margin, np.max(all_y) + y_margin)
    
    if is_3d:
        all_z = data[:, z_column_indices].flatten()
        z_margin = (np.max(all_z) - np.min(all_z)) * 0.1
        ax.set_zlim(np.min(all_z) - z_margin, np.max(all_z) + z_margin)
    
    # Inicializar líneas y puntos para cada cuerpo
    lines = []
    points = []
    trails = []
    
    for i in range(num_bodies):
        if is_3d:
            line, = ax.plot([], [], [], color=colors[i], alpha=0.3, linewidth=1)
            point, = ax.plot([], [], [], 'o', color=colors[i], markersize=8, label=f'Cuerpo {i+1}')
        else:
            line, = ax.plot([], [], color=colors[i], alpha=0.3, linewidth=1)
            point, = ax.plot([], [], 'o', color=colors[i], markersize=8, label=f'Cuerpo {i+1}')
        
        lines.append(line)
        points.append(point)
        trails.append([])
    
    ax.legend()
    ax.grid(True, alpha=0.3)
    
    # Texto para mostrar tiempo
    if is_3d:
        # Para 3D, usar text2D o coordenadas 3D específicas
        time_text = fig.text(0.02, 0.98, '', fontsize=12,
                           verticalalignment='top', bbox=dict(boxstyle='round', facecolor='wheat', alpha=0.5))
    else:
        # Para 2D funciona normalmente
        time_text = ax.text(0.02, 0.98, '', transform=ax.transAxes, fontsize=12,
                           verticalalignment='top', bbox=dict(boxstyle='round', facecolor='wheat', alpha=0.5))
    
    def animate(frame):
        """Función de animación para cada frame."""
        trail_length = min(50, frame + 1)  # Mostrar hasta 50 puntos de historia
        start_idx = max(0, frame - trail_length + 1)
        
        for i in range(num_bodies):
            x_idx = 1 + i * 3
            y_idx = 2 + i * 3
            
            if is_3d:
                z_idx = 3 + i * 3
                # Actualizar trayectoria
                lines[i].set_data(data[start_idx:frame+1, x_idx], data[start_idx:frame+1, y_idx])
                lines[i].set_3d_properties(data[start_idx:frame+1, z_idx])
                # Actualizar posición actual
                points[i].set_data([data[frame, x_idx]], [data[frame, y_idx]])
                points[i].set_3d_properties([data[frame, z_idx]])
            else:
                # Actualizar trayectoria
                lines[i].set_data(data[start_idx:frame+1, x_idx], data[start_idx:frame+1, y_idx])
                # Actualizar posición actual
                points[i].set_data([data[frame, x_idx]], [data[frame, y_idx]])
        
        # Actualizar texto de tiempo
        time_text.set_text(f'Tiempo: {time[frame]:.2f}')
        
        return lines + points + [time_text]
    
    # Crear animación
    print("Generando animación... Esto puede tomar unos momentos.")
    
    # Reducir el número de frames para hacer el GIF más manejable
    step = max(1, len(time) // 200)  # Máximo 200 frames
    frames = range(0, len(time), step)
    
    anim = animation.FuncAnimation(fig, animate, frames=frames, interval=50, blit=False, repeat=True)
    
    # Guardar como GIF
    output_path = os.path.join(results_dir, f"simulacion_animada_{'3D' if is_3d else '2D'}_{num_bodies}_cuerpos.gif")
    
    print(f"Guardando GIF: {output_path}")
    print("Esto puede tomar varios minutos dependiendo de la duración de la simulación...")
    
    try:
        anim.save(output_path, writer='pillow', fps=20, dpi=80)
        print(f"✅ GIF creado exitosamente: {output_path}")
        
        # Mostrar información del archivo
        file_size = os.path.getsize(output_path) / (1024 * 1024)  # MB
        print(f"📊 Tamaño del archivo: {file_size:.1f} MB")
        print(f"🎬 Frames: {len(frames)}, Duración estimada: {len(frames)/20:.1f} segundos")
        
    except Exception as e:
        print(f"❌ Error al crear el GIF: {e}")
        print("Asegúrate de tener instalado Pillow: pip install Pillow")
    
    plt.close(fig)

if __name__ == "__main__":
    create_animated_gif()