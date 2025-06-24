% Script de Octave/MATLAB para graficar resultados de simulación N-cuerpos
% Se espera que se llame desde Octave, pasando el nombre del archivo y N como argumentos
% Ejemplo desde línea de comando (si el script está en el path de Octave):
% octave --eval "plot_gravedad('results/datos_2.dat', 2)"
% o desde C++: octave scripts/plot_gravedad.m results/datos_2.dat 2

function plot_gravedad(filename, N_bodies_str)
    if nargin < 2
        disp('Uso: plot_gravedad(filename, N_bodies_str)');
        disp('Ejemplo: plot_gravedad(''results/datos_2.dat'', ''2'')');
        return;
    end

    N_bodies = str2num(N_bodies_str);
    if isempty(N_bodies) || N_bodies <= 0
        error('El número de cuerpos debe ser un entero positivo.');
    end

    disp(['Cargando datos desde: ', filename]);
    try
        data = dlmread(filename, '', 1, 0); % Saltar la primera fila (cabecera)
    catch
        error(['No se pudo leer el archivo de datos: ', filename]);
    end

    tiempo = data(:, 1);

    % --- Gráfica de Trayectorias ---
    figure;
    hold on;
    colors = lines(N_bodies); % Obtener N colores distintos

    for i = 1:N_bodies
        % Columnas: t, x1,y1,z1, x2,y2,z2, ...
        idx_x = 1 + (i-1)*3 + 1; % +1 por la columna de tiempo
        idx_y = idx_x + 1;
        idx_z = idx_y + 1;

        if idx_z <= size(data, 2)
             plot3(data(:, idx_x), data(:, idx_y), data(:, idx_z), ...
                  'DisplayName', sprintf('Cuerpo %d', i), 'Color', colors(i,:));
        elseif idx_y <= size(data,2) % Caso 2D
            plot(data(:,idx_x), data(:,idx_y), ...
                 'DisplayName', sprintf('Cuerpo %d', i), 'Color', colors(i,:));
        else
            disp(['No hay suficientes columnas de posición para el cuerpo ', num2str(i)]);
        end
    end

    if idx_z <= size(data,2)
        xlabel('X');
        ylabel('Y');
        zlabel('Z');
        view(3); % Asegurar vista 3D
    else
        xlabel('X');
        ylabel('Y');
    end

    title(sprintf('Trayectorias Simulación N=%d Cuerpos', N_bodies));
    legend show;
    grid on;
    hold off;

    try
        print(sprintf('results/trayectorias_octave_%d.png', N_bodies), '-dpng');
        disp(sprintf('Gráfica de trayectorias guardada en: results/trayectorias_octave_%d.png', N_bodies));
    catch ME
        disp(['Error guardando gráfica de trayectorias: ', ME.message]);
    end


    % --- Gráfica de Energías ---
    % Columnas de energía: K_total, U_total, E_total
    % K_total es N_BODIES*3 (pos) + N_BODIES*1 (vel) + 1 (tiempo) + 1 = (4*N_BODIES + 2)
    % U_total es (4*N_BODIES + 3)
    % E_total es (4*N_BODIES + 4)

    col_k_idx = 1 + N_bodies*3 + N_bodies*1 + 1; % +1 por la columna de tiempo
    col_u_idx = col_k_idx + 1;
    col_e_idx = col_k_idx + 2;

    if col_e_idx <= size(data, 2)
        K_total = data(:, col_k_idx);
        U_total = data(:, col_u_idx);
        E_total = data(:, col_e_idx);

        figure;
        hold on;
        plot(tiempo, K_total, 'r', 'DisplayName', 'Energía Cinética Total');
        plot(tiempo, U_total, 'b', 'DisplayName', 'Energía Potencial Total');
        plot(tiempo, E_total, 'g', 'DisplayName', 'Energía Total del Sistema');
        hold off;

        xlabel('Tiempo');
        ylabel('Energía');
        title(sprintf('Energías del Sistema (N=%d Cuerpos)', N_bodies));
        legend show;
        grid on;

        try
            print(sprintf('results/energias_octave_%d.png', N_bodies), '-dpng');
            disp(sprintf('Gráfica de energías guardada en: results/energias_octave_%d.png', N_bodies));
        catch ME
            disp(['Error guardando gráfica de energías: ', ME.message]);
        end

    else
        disp('No se encontraron columnas de energía en el archivo de datos.');
    end

    % Para uso interactivo, se puede añadir 'pause;' aquí.
    % Si se ejecuta desde un script, Octave podría cerrarse inmediatamente.
end

% --- Manejo de argumentos de línea de comando para Octave ---
% Esto permite llamar al script como: octave scripts/plot_gravedad.m results/datos_N.dat N
args = argv();
if length(args) == 2
    plot_gravedad(args{1}, args{2});
elseif length(args) > 0 && ~strcmp(args{1}, "--eval") % Evitar conflicto si se llama con --eval
    disp("Llamada incorrecta al script desde línea de comando.");
    disp("Uso: octave plot_gravedad.m <ruta_archivo_datos> <numero_de_cuerpos>");
end
% Si no hay argumentos (o son de --eval), la función no se ejecuta automáticamente,
% lo cual está bien si se carga y luego se llama manualmente.
