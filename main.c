/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroturea <mroturea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/06 17:33:34 by mroturea          #+#    #+#             */
/*   Updated: 2016/06/10 19:59:01 by mroturea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"



int	init_window(t_struct *s)
{
	SDL_Init(SDL_INIT_VIDEO);
	s->window = SDL_CreateWindow("An SDL2 window",0,0,HGT,WDT,SDL_WINDOW_OPENGL);
	if (s->window == NULL)
	{
		printf("Could not create window: %s\n", SDL_GetError());
		return 1;
	}
	s->rendu = SDL_CreateRenderer(s->window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	s->posx = 22;
	s->posy = 12;
	s->dirx = -1;
	s->diry = 0;
	s->planex = 0;
	s->planey = 0.66;
	s->time = 0;
	s->oldtime = 0;
	return (0);
}

void choose_color(t_struct *s, int worldMap[24][24], int x)
{
	int i = 0;
	if (worldMap[s->mapx][s->mapy] == 1)
		SDL_SetRenderDrawColor(s->rendu, 0, 0, 255, 255);
	if (worldMap[s->mapx][s->mapy] == 2)
		SDL_SetRenderDrawColor(s->rendu, 0, 255, 0, 255);
	if (worldMap[s->mapx][s->mapy] == 3)
		SDL_SetRenderDrawColor(s->rendu, 255, 144, 208, 255);
	if (worldMap[s->mapx][s->mapy] == 4)
		SDL_SetRenderDrawColor(s->rendu, 160, 160, 160, 255);
	SDL_RenderDrawLine(s->rendu, x, s->drawStart, x, s->drawEnd);
}

void trace(t_struct *s, int worldMap[24][24])
{
	int x;
	x = 0;
	
	while (x < WDT)
	{
		s->camerax = 2 * x / (double)WDT - 1;
		s->Rayposx = s->posx;
		s->Rayposy = s->posy;
		s->Raydirx = s->dirx + s->planex * s->camerax;
		s->Raydiry = s->diry + s->planey * s->planey;
		s->mapx = (int)s->Rayposx;
		s->mapy = (int)s->Rayposy;
		s->deltaDistx = sqrt(1 + (s->Raydiry * s->Raydiry) / (s->Raydirx * s->Raydirx));
		s->deltaDisty = sqrt(1 + (s->Raydirx * s->Raydirx) / (s->Raydiry * s->Raydiry));
		if (s->Raydirx < 0)
		{
			s->stepX = -1;
			s->sideDistX = (s->Rayposx - s->mapx) * s->deltaDistx;
		}
		else
		{
			s->stepX = 1;
			s->sideDistX = (s->mapx + 1.0 - s->Rayposx) * s->deltaDistx;
		}
		if (s->Raydiry < 0)
		{
			s->stepY = -1;
			s->sideDistY = (s->Rayposy - s->mapy) * s->deltaDisty;
		}
		else
		{
			s->stepY = 1;
			s->sideDistY =(s->mapy + 1.0 - s->Rayposy) * s->deltaDisty;
		}
		while (s->hit == 0)
		{
			if (s->sideDistX < s->sideDistY)
			{
				s->sideDistX += s->deltaDistx;
				s->mapx += s->stepX;
				s->side = 0;
			}
			else
			{
				s->sideDistY += s->deltaDisty;
				s->mapy += s->stepY;
				s->side = 1;
			}
			if (worldMap[s->mapx][s->mapy] > 0 )
				s->hit = 1;
		}
		if (s->side == 0)
			s->perpWallDist = (s->mapx - s->Rayposx + (1 - s->stepX) / 2) / s->Raydirx;
		else
			s->perpWallDist = (s->mapy - s->Rayposy + (1 - s->stepY) / 2) / s->Raydiry;
		s->lineHeight = (int)(HGT / s->perpWallDist);
		s->drawStart = -s->lineHeight / 2 + HGT / 2;
		if (s->drawStart < 0)
			s->drawStart = 0;
		s->drawEnd = s->lineHeight / 2 + HGT / 2;
		if (s->drawEnd >= HGT)
			s->drawEnd = HGT - 1;
		choose_color(s, worldMap, x);
		x++;
	}
}

int main(int ac, char **av)
{
	t_struct s;
	int i;
	
	int worldMap[24][24]=
	{
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
	{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
	{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
	};

	*av = NULL;
	ac = 0;
	init_window(&s);
	i = 0;
	while (!i)
	{
		while(SDL_PollEvent(&s.event))
		{
			if (s.event.type == SDL_QUIT || s.event.key.keysym.sym == SDLK_ESCAPE)
			i = 1;
		}
		SDL_SetRenderDrawColor(s.rendu, 0, 0, 0, 255);
		SDL_RenderClear(s.rendu);
		trace(&s, worldMap);
		SDL_RenderPresent(s.rendu);
	
	}
	SDL_DestroyRenderer(s.rendu);
	SDL_DestroyWindow(s.window);
	SDL_Quit();
	return 0;
}
