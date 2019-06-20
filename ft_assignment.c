/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_assignment.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apickett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/29 14:59:23 by apickett          #+#    #+#             */
/*   Updated: 2018/09/29 14:59:25 by apickett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

#define IMG view->img
#define SRGB set.rgb
#define PUTX x + set.x_split
#define COORD set.y_coord

/*
** set_options gives inits our vals in the set struct for use in the program
** step is steps in fractal, rgb for color of steps
**x&y vals are for stepping through the fractal , and where to split the steps
*/

static void		set_options(t_view *view, t_set *set)
{
	set->step = 1 / view->z;
	set->rgb = set_color(0, 0, 0);
	set->x_split = HW + view->xabs;
	set->y_split = HH + view->yabs;
	set->x_max = HW - view->xabs + view->x_until - WW;
	set->y_max = HH - view->yabs;
	set->y = -HH - view->yabs;
	set->y_coord = set->y + set->y_split;
}

/*
** gets math to set up for fractol chosen by putfrac, step through
** math to set steps, cehck fractal and put pixel based on checker
*/

static void		ft_setfractol(t_view *view)
{
	/* t_helper	*head; */
	t_complex	c;
	t_set		set;
	int 		x;

	/* head = malloc(sizeof(t_helper)); */
	set_options(view, &set);
	c.imag = set.y / view->z;
	while (++set.y < set.y_max)
	{
		x = -set.x_split + view->x_start;
		c.imag += set.step;
		set.y_coord++;
		c.real = x / view->z;
		while (++x < set.x_max)
		{
			c.real += set.step;
			if (!((set.res = view->checker(c, view)) == view->iter))
				rgb_pixelput(view->img, set_color(pow(set.res, view->depth_r),
						pow(set.res, view->depth_g),
						pow(set.res, view->depth_b)),
						x + set.x_split, set.y_coord);
			else
				rgb_pixelput(IMG, SRGB, PUTX, COORD);
		}
	}
}

/*
** puts fractol based on user input
*/

void			*ft_putfrac(void *arg)
{
	t_view	*view;

	view = (t_view *)arg;
	if (view->fractal == ONE)
		view->checker = ft_mandelbrot;
	else if (view->fractal == TWO)
		view->checker = ft_julia;
	else if (view->fractal == THREE)
		view->checker = ft_ship;
	ft_setfractol(view);
	return (NULL);
}

/*
**init vals for view struct including abs for zoom and pos
**and depth for color of steps etc
*/

void			ft_defaults(t_view *view)
{
	view->z = 500;
	view->iter = 50;
	view->xabs = (view->fractal == ONE || view->fractal == THREE) ?
		150 : 0;
	view->yabs = (view->fractal == THREE) ? 325 : 0;
	view->x_old = 0;
	view->y_old = 0;
	view->move = 0;
	view->zoom = 0;
	view->depth_r = 5;
	view->depth_g = 5;
	view->depth_b = 0;
	view->animation = 0;
	view->julia_arg.real = -0.55;
	view->julia_arg.imag = -0.55;
	view->do_iter = 0;
	ft_thread(view);
}
