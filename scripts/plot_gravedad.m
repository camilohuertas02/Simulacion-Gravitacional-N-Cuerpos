% ====================================================================
% Script de Octave/MATLAB INTELIGENTE y CORREGIDO para N-cuerpos
% - No necesita argumentos.
% - Detecta 'N' y la dimensionalidad (2D/3D) automáticamente.
% - Maneja rutas relativas desde diferentes directorios.
% ====================================================================

% --- Limpieza del entorno ---
clear; clc; close all;

% --- Función para buscar archivo de datos ---
function filename = find_data_file()
    possible_paths = {
        "results/sim_data.dat",      % Desde directorio raíz
        "../results/sim_data.dat",   % Desde test/ o scripts/
        "../../results/sim_data.dat" % Desde subdirectorios anidados
    };
    
    filename = "";
    for i = 1:length(possible_paths)
        if exist(possible_paths{i}, 'file')
            filename = possible_paths{i};
            return;
        end
    end
end

% --- Función para encontrar directorio de resultados ---
function results_dir = find_results_dir()
    possible_dirs = {
        "results/",      % Desde directorio raíz
        "../results/",   % Desde test/ o scripts/
        "../../results/" % Desde subdirectorios anidados
    };
    
    results_dir = "";
    for i = 1:length(possible_dirs)
        if exist(possible_dirs{i}, 'dir')
            results_dir = possible_dirs{i};
            return;
        end
    end
    
    % Si no existe, intentar crear
    try
        mkdir("../results/");
        results_dir = "../results/";
    catch
        try
            mkdir("results/");
            results_dir = "results/";
        catch
            results_dir = "./"; % Último recurso
        end
    end
end

% --- Paso 1: Buscar archivo de datos ---
FILENAME = find_data_file();
if isempty(FILENAME)
    error('No se encontró el archivo de datos en ninguna ubicación.');
end

RESULTS_DIR = find_results_dir();
Z_THRESHOLD = 1e-6; 

disp(["Archivo de datos encontrado: ", FILENAME]);
disp(["Directorio de resultados: ", RESULTS_DIR]);
disp(["Script autosuficiente: Analizando archivo '", FILENAME, "'..."]);

% --- Paso 2: Calcular N automáticamente desde la cabecera ---
try
    fid = fopen(FILENAME, 'r');
    if (fid == -1)
        error(['No se pudo abrir el archivo: ', FILENAME]);
    end
    header_line = fgetl(fid);
    fclose(fid);
    
    columns = strsplit(strtrim(header_line(2:end))); 
    TOTAL_COLS = numel(columns);
    N_BODIES = (TOTAL_COLS - 4) / 4;
    
    if (mod(N_BODIES, 1) ~= 0 || N_BODIES <= 0)
        error('El número de cuerpos calculado desde la cabecera no es un entero positivo.');
    end
    
    disp(['Cuerpos detectados: N=', num2str(N_BODIES)]);
catch ME
    error(['No se pudo leer la cabecera del archivo para determinar N. Error: ', ME.message]);
end

% --- Paso 3: Cargar datos y detectar dimensionalidad ---
try
    data = dlmread(FILENAME, '', 1, 0); 
catch ME
    error(['No se pudo leer el archivo de datos. Error: ', ME.message]);
end

z_col_indices = 4:3:(1 + 3*N_BODIES);
z_data = data(:, z_col_indices);
z_range = max(z_data(:)) - min(z_data(:));
is_3d = z_range > Z_THRESHOLD;

if (is_3d)
    dim_string = '3D';
else
    dim_string = '2D';
end
disp(['Rango de Z detectado: ', num2str(z_range), '. El movimiento es ', dim_string, '.']);

% --- Paso 4: Graficar Trayectorias ---
figure('visible', 'off');
hold on;
colors = lines(N_BODIES); 
legends = {};

if (is_3d)
    disp('Generando gráfico de trayectorias 3D...');
    for i = 1:N_BODIES
        idx_x = 2 + 3*(i-1); idx_y = 3 + 3*(i-1); idx_z = 4 + 3*(i-1);
        plot3(data(:, idx_x), data(:, idx_y), data(:, idx_z), 'LineWidth', 2, 'Color', colors(i,:));
        legends{end+1} = ['Cuerpo ', num2str(i)];
    end
    xlabel('X'); ylabel('Y'); zlabel('Z');
    title(sprintf('Trayectorias (Vista 3D, N=%d Cuerpos)', N_BODIES));
    view(3);
    axis equal;
else
    disp('Generando gráfico de trayectorias 2D...');
    for i = 1:N_BODIES
        idx_x = 2 + 3*(i-1); idx_y = 3 + 3*(i-1);
        plot(data(:, idx_x), data(:, idx_y), 'LineWidth', 2, 'Color', colors(i,:));
        legends{end+1} = ['Cuerpo ', num2str(i)];
    end
    xlabel('X'); ylabel('Y');
    title(sprintf('Trayectorias (Vista 2D, N=%d Cuerpos)', N_BODIES));
    axis equal;
end
legend(legends);
grid on;
hold off;

output_path_traj = [RESULTS_DIR, sprintf('trayectorias_octave_%s_%d.png', dim_string, N_BODIES)];
print(output_path_traj, '-dpng');
disp(['Gráfica de trayectorias guardada en: ', output_path_traj]);

% --- Paso 5: Graficar Energías ---
col_k_idx = 1 + 4*N_BODIES + 1;
col_u_idx = col_k_idx + 1;
col_e_idx = col_k_idx + 2;

if col_e_idx <= size(data, 2)
    figure('visible', 'off');
    hold on;
    plot(data(:,1), data(:,col_k_idx), 'r', 'LineWidth', 2, 'DisplayName', 'Energía Cinética Total');
    plot(data(:,1), data(:,col_u_idx), 'b', 'LineWidth', 2, 'DisplayName', 'Energía Potencial Total');
    plot(data(:,1), data(:,col_e_idx), 'g', 'LineWidth', 2, 'DisplayName', 'Energía Total del Sistema');
    hold off;
    xlabel('Tiempo'); ylabel('Energía');
    title(sprintf('Energías del Sistema (N=%d Cuerpos)', N_BODIES));
    legend show;
    grid on;

    output_path_energy = [RESULTS_DIR, sprintf('energias_octave_%d.png', N_BODIES)];
    print(output_path_energy, '-dpng');
    disp(['Gráfica de energías guardada en: ', output_path_energy]);
else
    disp('No se encontraron columnas de energía en el archivo de datos.');
end

disp('Proceso de graficación completado.');
