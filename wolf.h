/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroturea <mroturea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/06 17:32:54 by mroturea          #+#    #+#             */
/*   Updated: 2016/06/10 17:50:43 by mroturea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF_H
# define WOLF_H
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include "libft/libft.h"
# include <SDL2/SDL.h>
# define HGT 640
# define WDT 480

typedef struct s_struct
{
	SDL_Window *window;
	SDL_Renderer *rendu;
	SDL_Event event;
	double posx;
	double posy;
	double dirx;
	double diry;
	double planex;
	double planey;
	double time;
	double oldtime;
	double sideDistX;
	double sideDistY;
	int mapx;
	int mapy;
	int stepX;
	int stepY;
	int side;
	int hit;
	double camerax;
	double Rayposx;
	double Rayposy;
	double Raydirx;
	double Raydiry;
	double deltaDistx;
	double deltaDisty;
	double perpWallDist;
	int lineHeight;
	int drawStart;
	int drawEnd;
}            t_struct;

typedef struct t_colot
{
	int R;
	int G;
	int B;
}			s_color;

#endif
