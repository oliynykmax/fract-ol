#include "../incl/fract-ol.h"

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
	int r, g, b;
	t = t < 0 ? 0 : (t > 1 ? 1 : t);
	switch (f->color_scheme)
	{
	case 0:
		classic_scheme(t, &r, &g, &b);
		break ;
	case 1:
		fire_scheme(t, &r, &g, &b);
		break ;
	case 3:
		psychedelic_scheme(t, &r, &g, &b);
		break ;
	default:
		classic_scheme(t, &r, &g, &b);
	}
	r = r < 0 ? 0 : (r > 255 ? 255 : r);
	g = g < 0 ? 0 : (g > 255 ? 255 : g);
	b = b < 0 ? 0 : (b > 255 ? 255 : b);
	*color = get_rgba(r, g, b, 255);
}
