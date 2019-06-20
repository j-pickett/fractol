/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apickett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/29 14:58:33 by apickett          #+#    #+#             */
/*   Updated: 2019/02/26 15:25:08 by apickett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static int		set_fractal(char c)
{
	if (c < 53)
		return (c - 31);
	return (0);
}

void			my_exit(t_env *e, void *ptr)
{
	mlx_destroy_image(e->mlx, ptr);
	mlx_destroy_window(e->mlx, e->win);
	exit(0);
}

static void		set_graph(t_view *view, char c)
{
	view->e.mlx = mlx_init();
	view->e.win = mlx_new_window(view->e.mlx, WW, WH, "FRACTOL");
	view->img.ptr = mlx_new_image(view->e.mlx, WW, WH);
	view->img.len = WW;
	view->img.bpp = 4;
	view->img.begin = mlx_get_data_addr(view->img.ptr,
			&view->img.bpp, &view->img.len, &view->img.end);
	view->fractal = set_fractal(c);
	ft_defaults(view);
	ft_thread(view);
	mlx_key_hook(view->e.win, &key_hook, view);
	mlx_mouse_hook(view->e.win, &mouse_hook, view);
	mlx_hook(view->e.win, 2, 1L << 0, &key_release, view);
	mlx_hook(view->e.win, 6, 1L << 6, &mouse_move, view);
	mlx_loop_hook(view->e.mlx, &loop_hook, view);
	mlx_loop(view->e.mlx);
}

static void		usage(void)
{
	ft_putendl("Usage: ./fractol [<f_id>]");
	ft_putendl("f_id's list:");
	ft_putendl("1 - Mandelbrot");
	ft_putendl("2 - Julia");
	ft_putendl("3 - Burning Ship");
	exit(0);
}

int				main(int ac, char **av)
{
	t_view	view;

	if (ac == 2)
	{
		if (ft_strlen(av[1]) == 1 &&
				*av[1] >= 49 && *av[1] <= 51)
			set_graph(&view, *av[1]);
		else
			usage();
	}
	else
		usage();
	return (0);
}
