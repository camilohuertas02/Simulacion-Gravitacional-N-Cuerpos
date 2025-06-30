import numpy as np
import matplotlib.pyplot as plt
import os

# --- Constantes y Configuración ---
FILENAME = "results/sim_data.dat"
Z_THRESHOLD = 1e-6 # Umbral para considerar el movimiento como 2D

def get_num_bodies_from_header(filepath):
    """
    Lee la primera línea de un archivo de datos para determinar el número de cuerpos.
    """
    try:
        with open(filepath, 'r') as f:
            header = f.readline()
            num_cols = len(header.lstrip('#').split())
            num_bodies = (num_cols - 4) // 4
            return num_bodies
    except Exception as e:
        print(f"Error al leer la cabecera del archivo para determinar N: {e}")
        return None

def plot_simulation_data():
    """
    Función principal que carga los datos y genera todas las gráficas.
    """
    if not os.path.exists(FILENAME):
        print(f"Error: El archivo de datos '{FILENAME}' no fue encontrado.")
        return

    num_bodies = get_num_bodies_from_header(FILENAME)
    if num_bodies is None or num_bodies <= 0:
        print(f"No se pudo determinar un número válido de cuerpos desde '{FILENAME}'.")
        return
        
    print(f"Script autosuficiente: Archivo '{FILENAME}', Cuerpos detectados N={num_bodies}")
    
    data = np.loadtxt(FILENAME, comments='#')
    time = data[:, 0]

    z_column_indices = [3 + i * 3 for i in range(num_bodies)]
    z_data = data[:, z_column_indices]
    z_range = np.ptp(z_data)
    is_3d = z_range > Z_THRESHOLD

    print(f"Rango de Z detectado: {z_range:.4g}. El movimiento es {'3D' if is_3d else '2D'}.")

    # --- Gráfica de Trayectorias ---
    if is_3d:
        fig = plt.figure(figsize=(8, 6))
        ax_traj = fig.add_subplot(111, projection='3d')
        ax_traj.set_zlabel("Z")
        print("Generando gráfico de trayectorias 3D...")
    else:
        fig, ax_traj = plt.subplots(figsize=(8, 6))
        print("Generando gráfico de trayectorias 2D...")

    # Corrección para eliminar la advertencia de 'deprecation'
    colors = plt.get_cmap('tab10', num_bodies)

    for i in range(num_bodies):
        idx_x = 1 + i * 3
        idx_y = 2 + i * 3
        if is_3d:
            idx_z = 3 + i * 3
            ax_traj.plot(data[:, idx_x], data[:, idx_y], data[:, idx_z], label=f'Cuerpo {i+1}', color=colors(i), lw=2)
        else:
            ax_traj.plot(data[:, idx_x], data[:, idx_y], label=f'Cuerpo {i+1}', color=colors(i), lw=2)

    ax_traj.set_xlabel("X")
    ax_traj.set_ylabel("Y")
    ax_traj.set_title(f'Trayectorias (N={num_bodies} Cuerpos)')
    ax_traj.legend()
    ax_traj.grid(True)
    ax_traj.set_aspect('equal', adjustable='box')
    
    output_path_traj = f"results/trayectorias_py_{'3D' if is_3d else '2D'}_{num_bodies}.png"
    plt.savefig(output_path_traj)
    print(f"Gráfica de trayectorias guardada en: {output_path_traj}")
    plt.close(fig)

    # --- Gráfica de Energías ---
    col_k_idx = 1 + num_bodies * 4 
    col_u_idx = col_k_idx + 1
    col_e_idx = col_k_idx + 2
    
    if col_e_idx < data.shape[1]:
        fig_energy, ax_energy = plt.subplots(figsize=(8, 6))
        ax_energy.plot(time, data[:, col_k_idx], label='Energía Cinética Total', color='red', lw=2)
        ax_energy.plot(time, data[:, col_u_idx], label='Energía Potencial Total', color='blue', lw=2)
        ax_energy.plot(time, data[:, col_e_idx], label='Energía Total del Sistema', color='green', lw=2)

        ax_energy.set_xlabel("Tiempo")
        ax_energy.set_ylabel("Energía")
        ax_energy.set_title(f'Energías del Sistema (N={num_bodies} Cuerpos)')
        ax_energy.legend()
        ax_energy.grid(True)

        output_path_energy = f"results/energias_py_{num_bodies}.png"
        plt.savefig(output_path_energy)
        print(f"Gráfica de energías guardada en: {output_path_energy}")
        plt.close(fig_energy)
    
if __name__ == "__main__":
    plot_simulation_data()
