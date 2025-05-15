/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maoliiny <maoliiny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 16:59:12 by maoliiny          #+#    #+#             */
/*   Updated: 2025/05/15 17:32:10 by maoliiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/fractal.h"

int	get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

static void	classic_scheme(double t, int *r, int *g, int *b)
{
	*r = (int)(9 * (1 - t) * t * t * t * 255);
	*g = (int)(15 * (1 - t) * (1 - t) * t * t * 255);
	*b = (int)(8.5 * (1 - t) * t * t * 255);
}

static void	fire_scheme(double t, int *r, int *g, int *b)
{
	*r = (int)(255 * t);
	*g = (int)(128 * t * t);
	*b = (int)(32 * t * t * t);
}

static void	psychedelic_scheme(double t, int *r, int *g, int *b)
{
	*r = (int)(255 * sin(2 * M_PI * t));
	*g = (int)(255 * sin(2 * M_PI * t + 2 * M_PI / 3));
	*b = (int)(255 * sin(2 * M_PI * t + 4 * M_PI / 3));
}

void	apply_color_scheme(t_fractal *f, double t, int *color)
{
	int	r;
	int	g;
	int	b;

	t = fmin(fmax(t, 0.0), 1.0);
	if (f->color_scheme == 1)
		fire_scheme(t, &r, &g, &b);
	else if (f->color_scheme == 2)
		psychedelic_scheme(t, &r, &g, &b);
	else
		classic_scheme(t, &r, &g, &b);
	r = (int)fmin(fmax(r, 0.0), 255.0);
	g = (int)fmin(fmax(g, 0.0), 255.0);
	b = (int)fmin(fmax(b, 0.0), 255.0);
	*color = get_rgba(r, g, b, 255);
}
