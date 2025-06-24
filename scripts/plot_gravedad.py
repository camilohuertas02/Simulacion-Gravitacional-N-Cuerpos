import matplotlib.pyplot as plt
import sys
import numpy as np

def plot_data(filepath, num_bodies_str):
    """
    Genera gráficas de trayectorias y energías a partir de un archivo de datos.

    Args:
        filepath (str): Ruta al archivo de datos (ej: "results/datos_N.dat").
        num_bodies_str (str): Número de cuerpos como cadena (ej: "2").
    """
    try:
        num_bodies = int(num_bodies_str)
    except ValueError:
        print(f"Error: El número de cuerpos '{num_bodies_str}' no es un entero válido.")
        return

    try:
        data = np.loadtxt(filepath, comments='#')
    except FileNotFoundError:
        print(f"Error: No se encontró el archivo de datos '{filepath}'.")
        return
    except Exception as e:
        print(f"Error al leer el archivo de datos '{filepath}': {e}")
        return

    time = data[:, 0]

    # --- Gráfica de Trayectorias ---
    fig_traj, ax_traj = plt.subplots(subplot_kw={'projection': '3d' if num_bodies > 0 else None}) # 3D por defecto

    colors = plt.cm.get_cmap('tab10', num_bodies if num_bodies > 0 else 1)

    for i in range(num_bodies):
        # Columnas: t, x1,y1,z1, x2,y2,z2, ...
        idx_x = 1 + i * 3
        idx_y = 2 + i * 3
        idx_z = 3 + i * 3

        if idx_z < data.shape[1]: # Si hay datos de Z
            ax_traj.plot(data[:, idx_x], data[:, idx_y], data[:, idx_z], label=f'Cuerpo {i+1}', color=colors(i))
        elif idx_y < data.shape[1]: # Si solo hay X, Y (2D)
             if i == 0: # Solo configurar para 2D una vez
                ax_traj = fig_traj.gca() # Obtener eje 2D
                ax_traj.set_xlabel("X")
                ax_traj.set_ylabel("Y")
             ax_traj.plot(data[:, idx_x], data[:, idx_y], label=f'Cuerpo {i+1}', color=colors(i))


    if num_bodies > 0 and data.shape[1] > 3 + (num_bodies-1)*3 + 2 : # Si es 3D
        ax_traj.set_xlabel("X")
        ax_traj.set_ylabel("Y")
        ax_traj.set_zlabel("Z")

    ax_traj.set_title(f'Trayectorias Simulación N={num_bodies} Cuerpos')
    ax_traj.legend()
    ax_traj.grid(True)

    output_path_traj = f"results/trayectorias_py_{num_bodies}.png"
    try:
        plt.savefig(output_path_traj)
        print(f"Gráfica de trayectorias guardada en: {output_path_traj}")
    except Exception as e:
        print(f"Error al guardar la gráfica de trayectorias: {e}")
    plt.close(fig_traj)


    # --- Gráfica de Energías ---
    # Columnas de energía: K_total, U_total, E_total
    # K_total es N_BODIES*3 (pos) + N_BODIES*1 (vel) + 1 (tiempo) + 1 = (4*N_BODIES + 2) -1 para indexado python = 4*N_BODIES+1
    # U_total es (4*N_BODIES + 3) -1 = 4*N_BODIES+2
    # E_total es (4*N_BODIES + 4) -1 = 4*N_BODIES+3

    col_k_idx = 1 + num_bodies * 3 + num_bodies * 1
    col_u_idx = col_k_idx + 1
    col_e_idx = col_k_idx + 2

    if col_e_idx < data.shape[1]: # Verificar que las columnas de energía existan
        K_total = data[:, col_k_idx]
        U_total = data[:, col_u_idx]
        E_total = data[:, col_e_idx]

        fig_energy, ax_energy = plt.subplots()
        ax_energy.plot(time, K_total, label='Energía Cinética Total', color='red')
        ax_energy.plot(time, U_total, label='Energía Potencial Total', color='blue')
        ax_energy.plot(time, E_total, label='Energía Total del Sistema', color='green')

        ax_energy.set_xlabel("Tiempo")
        ax_energy.set_ylabel("Energía")
        ax_energy.set_title(f'Energías del Sistema (N={num_bodies} Cuerpos)')
        ax_energy.legend()
        ax_energy.grid(True)

        output_path_energy = f"results/energias_py_{num_bodies}.png"
        try:
            plt.savefig(output_path_energy)
            print(f"Gráfica de energías guardada en: {output_path_energy}")
        except Exception as e:
            print(f"Error al guardar la gráfica de energías: {e}")
        plt.close(fig_energy)
    else:
        print("No se encontraron columnas de energía en el archivo de datos.")


if __name__ == "__main__":
    if len(sys.argv) < 3:
        print("Uso: python plot_gravedad.py <ruta_archivo_datos> <numero_de_cuerpos>")
        print("Ejemplo: python scripts/plot_gravedad.py results/datos_2.dat 2")
        sys.exit(1)

    filepath_arg = sys.argv[1]
    num_bodies_arg = sys.argv[2]

    plot_data(filepath_arg, num_bodies_arg)
