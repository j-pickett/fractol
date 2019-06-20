/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fractols.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apickett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/29 14:59:13 by apickett          #+#    #+#             */
/*   Updated: 2018/09/29 14:59:16 by apickett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/*
**initializing a complex number
**z = x + yi  diff is we use z instead of out in val
**only portion of man set shown
*/

int				ft_julia(t_complex z, t_view *view)
{
	t_complex	out;
	t_complex	c;
	t_helper	*head;

	head = malloc(sizeof(t_helper));
	c.real = view->julia_arg.real;
	c.imag = view->julia_arg.real;
	head->iter = 0;
	while (head->iter++ < view->iter
		&& z.real * z.real + z.imag * z.imag <= 4)
	{
		out = z;
		z.real = out.real * out.real - out.imag * out.imag + c.real;
		z.imag = 2 * out.real * out.imag + c.imag;
	}
	free(head);
	return (head->iter - 1);
}

/*
** z_sub_(n+1)=z_n^2+C, father equation of both julia and ship
*/

int				ft_mandelbrot(t_complex c, t_view *view)
{
	t_complex	out;
	t_complex	in;
	t_helper	*head;

	head = malloc(sizeof(t_helper));
	head->dtmp = c.real - 0.25;
	if (sqrt(head->dtmp * head->dtmp + c.imag * c.imag) <
			0.5 - 0.5 * cos(atan2(c.imag, head->dtmp)))
		return (view->iter);
	out.real = 0;
	out.imag = 0;
	in = out;
	head->iter = 0;
	while (head->iter++ < view->iter
		&& in.real * in.real + in.imag * in.imag <= 4)
	{
		out = in;
		in.real = out.real * out.real - out.imag * out.imag + c.real;
		in.imag = 2 * out.real * out.imag + c.imag;
	}
	free(head);
	return (head->iter - 1);
}

/*
**only diff math here than mand is checking the outer real complx #
**with extra checks it only takes a portion of the man set
*/

int				ft_ship(t_complex c, t_view *view)
{
	t_complex	out;
	t_complex	in;
	t_helper	*head;

	head = malloc(sizeof(t_helper));
	out.real = 0;
	out.imag = 0;
	in = out;
	head->iter = 0;
	while (head->iter++ < view->iter
		&& in.real * in.real + in.imag * in.imag <= 4)
	{
		out = in;
		if (out.real < 0)
			out.real *= -1;
		if (out.imag < 0)
			out.imag *= -1;
		in.real = out.real * out.real - out.imag * out.imag + c.real;
		in.imag = 2 * out.real * out.imag + c.imag;
	}
	free(head);
	return (head->iter - 1);
}

/*
**create 6 threads, get math for steps of fractal
**then create thread, once done join all threads and put fractal to window
*/

void			ft_thread(t_view *view)
{
	t_view		tview[THREADS];
	t_helper	*head;

	head = malloc(sizeof(t_helper));
	mlx_clear_window(view->e.mlx, view->e.win);
	head->i = -1;
	head->start = 0;
	head->step = WW / THREADS;
	head->until = head->step;
	while (++head->i < THREADS)
	{
		tview[head->i] = *view;
		tview[head->i].x_start = head->start;
		head->start += head->step - 1;
		tview[head->i].x_until = head->until;
		head->until += head->step;
		pthread_create(&tview[head->i].pth, NULL, ft_putfrac, &tview[head->i]);
	}
	while (--head->i >= 0)
		pthread_join(tview[head->i].pth, NULL);
	free(head);
	mlx_put_image_to_window(view->e.mlx, view->e.win, view->img.ptr, 0, 0);
}
