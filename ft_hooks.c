/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hooks.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apickett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/29 14:59:04 by apickett          #+#    #+#             */
/*   Updated: 2018/09/29 14:59:07 by apickett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/*
**checks key hooks
*/

int	key_hook(int key, t_view *view)
{
	if (key == ESC)
		my_exit(&view->e, view->img.ptr);
	else if (ARR(key))
		view->move = 0;
	else if (key == ITER || key == REVITER)
		view->do_iter = 0;
	else if (key == R)
		ft_defaults(view);
	else if (key == A)
		view->animation = view->animation ? 0 : 1;
	return (0);
}

/*
**checks for zoom, zoom math is abs val += our scale
** mult by (our  x or y (in out) -
**half window size and current abs val (middle point))
*/

int	mouse_hook(int key, int x, int y, t_view *view)
{
	if (key == 1)
	{
		if (view->fractal == TWO)
		{
			view->julia_arg.real = (x - HW) / (double)HW;
			view->julia_arg.imag = (-y + HH) / (double)HH;
			ft_thread(view);
		}
	}
	else if (key == SCRLUP && 1 / view->z > 0.000000001)
	{
		view->z *= 1.1;
		view->xabs -= 0.1 * (x - HW - view->xabs);
		view->yabs -= 0.1 * (y - HH - view->yabs);
		ft_thread(view);
	}
	else if (key == SCRLDN)
	{
		view->z *= 0.9;
		view->xabs += 0.1 * (x - HW - view->xabs);
		view->yabs += 0.1 * (y - HH - view->yabs);
		ft_thread(view);
	}
	return (0);
}

/*
**inf loop for ft_seizure movement zoom and iteration
*/

int	loop_hook(t_view *view)
{
	if (loop_check(view))
	{
		ft_seizure(view);
		if (view->move == RIGHT)
			view->xabs += 50;
		else if (view->move == LEFT)
			view->xabs -= 50;
		else if (view->move == UP)
			view->yabs -= 50;
		else if (view->move == DOWN)
			view->yabs += 50;
		if (view->zoom == -1)
			view->z /= 1.1;
		else if (view->zoom == 1)
			view->z *= 1.1;
		view->iter += 5 * view->do_iter;
		ft_thread(view);
	}
	return (0);
}

/*
**checks keys pressed
*/

int	key_release(int key, t_view *view)
{
	if (key == RIGHT)
		view->move = RIGHT;
	else if (key == LEFT)
		view->move = LEFT;
	else if (key == UP)
		view->move = UP;
	else if (key == DOWN)
		view->move = DOWN;
	else if (key == PLUS)
		view->zoom += 1;
	else if (key == MIN)
		view->zoom -= -1;
	else if (key == ITER)
		view->do_iter = 1;
	else if (key == REVITER)
		view->do_iter = -1;
	return (0);
}

/*
**math for moving mouse position on julia
*/

int	mouse_move(int x, int y, t_view *view)
{
	if (view->fractal == TWO)
	{
		view->julia_arg.real = (x - HW) / (double)HW;
		view->julia_arg.imag = (-y + HH) / (double)HH;
		ft_thread(view);
	}
	return (0);
}
