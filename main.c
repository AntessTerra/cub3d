/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phelebra <xhelp00@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 16:50:14 by jbartosi          #+#    #+#             */
/*   Updated: 2023/10/16 16:05:02 by phelebra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "cub3d.h"

/* Count_sprites

	Calculates how many sprites needs to be drawn each redraw
*/
int	count_sprites(t_box *box)
{
	int			counter;
	t_sprite	*sprites;

	sprites = box->sprites;
	if (!sprites)
		return (0);
	counter = 1;
	while (sprites->next)
	{
		sprites = sprites->next;
		counter++;
	}
	return (counter);
}

/* Mouse_visibility

	Hides or shows mouse on screen
*/
void mouse_visibility(t_box* box, bool hide)
{
	if (hide && !box->mouse_hidden)
	{
		mlx_mouse_hide(box->mlx, box->win);
		mlx_mouse_move(box->mlx, box->win, SCREENWIDTH / 2, SCREENHEIGHT / 2);
		box->mouse_hidden = 1;
	}
	else if (!hide && box->mouse_hidden)
	{
		mlx_mouse_show(box->mlx, box->win);
		box->mouse_hidden = 0;
	}
}

/*	Timer

	Function for calculating FPS and redrawing screen every iteration
*/
int	timer(t_box *box)
{
	gettimeofday(&box->time, NULL);
	if (box->game_state == IN_TITLE_MENU)
	{
		mouse_visibility(box, false);
		my_mlx_put_image_to_window(box, &box->textures[TITLE_MENU], 0, 0, -1);
		if (((int)((box->time.tv_usec / 100000.0) * 4) / 10) % 2 == 1)
			mlx_put_image_to_window(box->mlx, box->win, box->textures[TITLE_MENU].img, 400, 215, 0, 1000, 450, 450); //press start
		else
			mlx_put_image_to_window(box->mlx, box->win, box->textures[TITLE_MENU].img, 400, 215, 432, 1000, 450, 450); //press start 2
		if (((int)((box->time.tv_usec / 100000.0) * 8) / 10) % 2 == 1)
			mlx_put_image_to_window(box->mlx, box->win, box->textures[TITLE_MENU].img, 1000, 400, 950, 1030, 200, 200); //fly
		else
			mlx_put_image_to_window(box->mlx, box->win, box->textures[TITLE_MENU].img, 1000, 400, 950, 1250, 200, 200); //fly 2
		if (((int)((box->time.tv_usec / 100000.0) * 4) / 10) / 2 == 0)
			mlx_put_image_to_window(box->mlx, box->win, box->textures[TITLE_MENU].img, 275, -10 + ((int)((box->time.tv_usec / 100000.0) * 20) / 10), 280, 740, 800, 300); //logo going down
		else
			mlx_put_image_to_window(box->mlx, box->win, box->textures[TITLE_MENU].img, 275, 10 - ((int)((box->time.tv_usec / 100000.0) * 20) / 10), 280, 740, 800, 300); //logo going up
	}
	else if (box->game_state == IN_START_OPTIONS)
	{
		my_mlx_put_image_to_window(box, &box->textures[MENU_BACK], 0, 0, -1);
		mlx_put_image_to_window(box->mlx, box->win, box->textures[OPTIONS_MENU].img, 400, 100, 0, 0, 460, 480);
		mlx_mouse_get_pos(box->mlx, box->win, &box->mouse.x, &box->mouse.y);
		mlx_put_image_to_window(box->mlx, box->win, box->textures[OPTIONS_MENU].img, 500, 200, 0, 480, 100, 40); //SFX
		mlx_put_image_to_window(box->mlx, box->win, box->textures[OPTIONS_MENU].img, 500, 260, 0, 920, 100, 40); //MUSIC

		if (box->options_menu_choice == 1)
			mlx_put_image_to_window(box->mlx, box->win, box->textures[OPTIONS_MENU].img, 450, 200, 460, 50, 100, 100); //SFX HIGHLIGTH
		else if (box->options_menu_choice == 2)
			mlx_put_image_to_window(box->mlx, box->win, box->textures[OPTIONS_MENU].img, 450, 260, 460, 50, 100, 100); //MUSIC HIGHLIGTH

		mlx_put_image_to_window(box->mlx, box->win, box->textures[OPTIONS_MENU].img, 650, 200, 390, 480 + (32 * (int)(10 *  (1.0 - box->sound.sfx_volume))), 150, 32); //SFX VOLUME SLIDER

		mlx_put_image_to_window(box->mlx, box->win, box->textures[OPTIONS_MENU].img, 650, 260, 390, 480 + (32 * (int)(10 *  (1.0 - box->sound.music_volume))), 150, 32); //MUSIC VOLUME SLIDER
	}
	else if (box->game_state == IN_START_MENU)
	{
		mouse_visibility(box, false);
		my_mlx_put_image_to_window(box, &box->textures[MENU_BACK], 0, 0, -1);
		my_mlx_put_image_to_window(box, &box->textures[START_MENU], 0, 0, -1);
		mlx_mouse_get_pos(box->mlx, box->win, &box->mouse.x, &box->mouse.y);
		mlx_put_image_to_window(box->mlx, box->win, box->textures[START_MENU].img, 480, 120, 80, 800, 310, 100); //NEW RUN
		if (box->sprites)
			mlx_put_image_to_window(box->mlx, box->win, box->textures[START_MENU].img, 480, 200, 80, 920, 310, 100); //CONTINUE
		else
			mlx_put_image_to_window(box->mlx, box->win, box->textures[START_MENU].img, 480, 200, 420, 920, 310, 100); //CONTINUE GRAYED OUT
		mlx_put_image_to_window(box->mlx, box->win, box->textures[START_MENU].img, 500, 280, 80, 1040, 330, 110); //CHALLANGE
		mlx_put_image_to_window(box->mlx, box->win, box->textures[START_MENU].img, 510, 370, 80, 1160, 330, 110); //STATS
		mlx_put_image_to_window(box->mlx, box->win, box->textures[START_MENU].img, 520, 440, 80, 1280, 340, 150); //OPTIONS
		if (box->start_menu_choice == 1)
			mlx_put_image_to_window(box->mlx, box->win, box->textures[START_MENU].img, 430, 120, 20, 800, 50, 100);
		else if (box->start_menu_choice == 2 && box->sprites)
			mlx_put_image_to_window(box->mlx, box->win, box->textures[START_MENU].img, 440, 210, 20, 800, 50, 100);
		else if (box->start_menu_choice == 3)
			mlx_put_image_to_window(box->mlx, box->win, box->textures[START_MENU].img, 455, 300, 20, 800, 50, 100);
		else if (box->start_menu_choice == 4)
			mlx_put_image_to_window(box->mlx, box->win, box->textures[START_MENU].img, 470, 390, 20, 800, 50, 100);
		else if (box->start_menu_choice == 5)
			mlx_put_image_to_window(box->mlx, box->win, box->textures[START_MENU].img, 480, 480, 20, 800, 50, 100);

		my_mlx_put_image_to_window(box, &box->textures[ALPHA], 400, 100, ((int)((box->time.tv_usec / 100000.0) * 8) / 4) % 63);
		my_mlx_put_image_to_window(box, &box->textures[NUMERIC], 400, 200, ((int)((box->time.tv_usec / 100000.0) * 8) / 4) % 63);
		string_to_image(box, 100, 300, "012345!#$%&\()*+,-./:;<=>?@[\\]^_`{|}~");
	}
	else if (box->game_state == IN_PAUSE_OPTIONS)
	{
		mlx_put_image_to_window(box->mlx, box->win, box->textures[OPTIONS_MENU_DARK].img, 400, 100, 0, 0, 460, 480);
		mlx_mouse_get_pos(box->mlx, box->win, &box->mouse.x, &box->mouse.y);
		mlx_put_image_to_window(box->mlx, box->win, box->textures[OPTIONS_MENU_DARK].img, 500, 200, 0, 480, 100, 40); //SFX
		mlx_put_image_to_window(box->mlx, box->win, box->textures[OPTIONS_MENU_DARK].img, 500, 260, 0, 920, 100, 40); //MUSIC

		if (box->options_menu_choice == 1)
			mlx_put_image_to_window(box->mlx, box->win, box->textures[OPTIONS_MENU_DARK].img, 450, 200, 460, 50, 100, 100); //SFX HIGHLIGTH
		else if (box->options_menu_choice == 2)
			mlx_put_image_to_window(box->mlx, box->win, box->textures[OPTIONS_MENU_DARK].img, 450, 260, 460, 50, 100, 100); //MUSIC HIGHLIGTH

		mlx_put_image_to_window(box->mlx, box->win, box->textures[OPTIONS_MENU_DARK].img, 650, 200, 390, 480 + (32 * (int)(10 *  (1.0 - box->sound.sfx_volume))), 150, 32); //SFX VOLUME SLIDER

		mlx_put_image_to_window(box->mlx, box->win, box->textures[OPTIONS_MENU_DARK].img, 650, 260, 390, 480 + (32 * (int)(10 *  (1.0 - box->sound.music_volume))), 150, 32); //MUSIC VOLUME SLIDER
	}
	else if (box->game_state == IN_PAUSE_MENU)
	{
		mouse_visibility(box, false);
		mlx_put_image_to_window(box->mlx, box->win, box->textures[PAUSE_MENU].img, 400, 150, 0, 0, 480, 480);
		mlx_mouse_get_pos(box->mlx, box->win, &box->mouse.x, &box->mouse.y);
		if (box->pause_menu_choice == 1)
			mlx_put_image_to_window(box->mlx, box->win, box->textures[PAUSE_MENU].img, 500, 390, 475, 5, 30, 30);
		else if (box->pause_menu_choice == 2)
			mlx_put_image_to_window(box->mlx, box->win, box->textures[PAUSE_MENU].img, 480, 440, 475, 5, 30, 30);
		else if (box->pause_menu_choice == 3)
			mlx_put_image_to_window(box->mlx, box->win, box->textures[PAUSE_MENU].img, 505, 485, 475, 5, 30, 30);
	}
	else if (box->game_state == RUNNING)
	{
		mouse_visibility(box, true);
		mlx_mouse_get_pos(box->mlx, box->win, &box->mouse.x, &box->mouse.y);
		mlx_mouse_move(box->mlx, box->win, SCREENWIDTH / 2, SCREENHEIGHT / 2);
		redraw(box);
	}
	else if (box->game_state == LOSE)
	{
		box->player.frame = ((((box->time.tv_sec - box->fin_time.tv_sec) + ((box->time.tv_usec - box->fin_time.tv_usec) / 1000000.0)) * 10) * 16) / 10;
		mlx_put_image_to_window(box->mlx, box->win, box->textures[GRIM].img, 400, 100, 400, 0, 512, 512); //DEATH NOTE
		mlx_put_image_to_window(box->mlx, box->win, box->textures[GRIM].img, 650, 300, 64, 64, 64, 64); //POOP
		if (box->player.frame > 85)
			exit_hook(box);
	}
	else if (box->game_state == WIN)
	{
		box->player.frame = ((((box->time.tv_sec - box->fin_time.tv_sec) + ((box->time.tv_usec - box->fin_time.tv_usec) / 1000000.0)) * 10) * 16) / 10;
		my_mlx_put_image_to_window(box, &box->textures[YAY], 400, 100, -1);
		if (box->player.frame > 115)
			exit_hook(box);
	}
	return (0);
}

int	main(void)
{
	t_box	box;

	init_vals(&box);
	box.mlx = mlx_init();
	box.win = mlx_new_window(box.mlx, SCREENWIDTH, SCREENHEIGHT, "cub3d");
	init_textures(&box);
	new_image(box.mlx, &box.image, SCREENWIDTH, SCREENHEIGHT);
	new_image(box.mlx, &box.shaders, SCREENWIDTH, SCREENHEIGHT);
	init_sounds(&box);
	mlx_hook(box.win, 17, 0, exit_hook, &box);
	mlx_hook(box.win, 2, 1L << 0, key_press, &box);
	mlx_hook(box.win, 3, 1L << 1, key_release, &box);
	mlx_hook(box.win, 4, 1L << 2, mouse_press, &box);
	mlx_hook(box.win, 5, 1L << 3, mouse_release, &box);
	mlx_hook(box.win, 6, 1L << 6, mouse_move, &box);
	mlx_loop_hook(box.mlx, timer, &box);
	mlx_loop(box.mlx);
	return (0);
}
