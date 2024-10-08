/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkrechun <rkrechun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 14:46:23 by rkrechun          #+#    #+#             */
/*   Updated: 2024/10/08 14:41:07 by rkrechun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

// gcc cub3d.c -I~/minilibx -L~/minilibx -lmlx -lX11 -lXext -lm -o cub3d

// Функция для загрузки текстуры
void load_texture(t_data *data, t_texture *texture, const char *file_path)
{
    texture->img = mlx_xpm_file_to_image(data->mlx, (char *)file_path, &texture->width, &texture->height);
    if (!texture->img)
    {
        fprintf(stderr, "Failed to load texture: %s\n", file_path);
        exit(EXIT_FAILURE);
    }
    texture->data = mlx_get_data_addr(texture->img, &texture->bpp, &texture->size_line, &texture->endian);
}

// Функция для очистки экрана определенным цветом
void clear_screen(t_data *data, int color)
{
    int x = 0;
    int y = 0;
    
    while (y < HEIGHT)
    {
        while (x < WIDTH)
        {
            ((int *)data->data)[y * WIDTH + x] = color;
            x++;
        }
        x = 0;
        y++;
    }
}

// Функция для непрерывного рендеринга и обработки событий
int game_loop(t_data *data)
{
    render(data);  // Рендеринг сцены
    mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);  // Отобразить изображение в окне
    return 0;
}

void initializeMap(int height, int width, int map[height][width])
{
    // Инициализация карты значениями
    int tempMap[5][5] =
    {
        {1, 1, 1, 1, 1},
        {1, 0, 0, 0, 1},
        {1, 0, 1, 0, 1},
        {1, 0, 1, 0, 1},
        {1, 1, 1, 1, 1}
    };
    // Копирование значений во внешний массив
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            map[i][j] = tempMap[i][j];
        }
    }
}

void init_data(t_data *data)
{
    data->mlx = mlx_init();
    if (!data->mlx)
        fprintf(stderr, "Failed to initialize MLX\n");
    data->win = mlx_new_window(data->mlx, WIDTH, HEIGHT, "Cub3D");
    if (!data->win) 
        fprintf(stderr, "Failed to create window\n");
    data->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
    if (!data->img)
        fprintf(stderr, "Failed to create image\n");
    data->data = mlx_get_data_addr(data->img, &data->bpp, &data->size_line, &data->endian);
    if (!data->data)
        fprintf(stderr, "Failed to get image data address\n");
}

int main()
{
    t_data data;

    init_data(&data);
    initializeMap(MAP_HEIGHT, MAP_WIDTH, data.map); // Инициализировать карту
    data.player_x = 2.5;  // Например, центр карты
    data.player_y = 1.5; // Например, направление на восток
    data.player_angle = 90;  
    load_texture(&data, &data.wall_texture, "wall.xpm"); // Одна текстура для всех стен
    // Зарегистрировать обработчик нажатий клавиш
    mlx_hook(data.win, 2, 1L << 0, handle_key_press, &data);  // 2 - событие нажатия клавиши
    // Зарегистрировать игровой цикл для непрерывного рендеринга и обработки событий
    mlx_loop_hook(data.mlx, game_loop, &data);
    // Запустить цикл событий
    mlx_loop(data.mlx);
    // Очистка
    mlx_destroy_image(data.mlx, data.img);
    mlx_destroy_window(data.mlx, data.win);
    mlx_destroy_display(data.mlx);
    free(data.mlx);
    return 0;
}
