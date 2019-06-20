/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rgb.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apickett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/29 14:58:56 by apickett          #+#    #+#             */
/*   Updated: 2018/09/29 14:58:58 by apickett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/*
** creates and puts our color
*/

void				rgb_pixelput(t_image img, t_rgb rgb, int x, int y)
{
	unsigned char	*split;

	split = img.begin + y * img.len + x * 4;
	*split++ = rgb.b;
	*split++ = rgb.g;
	*split++ = rgb.r;
}

t_rgb				set_color(int r, int g, int b)
{
	t_rgb			rgb;

	rgb.r = r;
	rgb.g = g;
	rgb.b = b;
	return (rgb);
}

/*
**changes colors to be used in infinite loop
*/

void				ft_seizure(t_view *view)
{
	if (view->animation)
	{
		view->depth_r = view->depth_r >= 10 ? 1 : view->depth_r + 3;
		view->depth_g = view->depth_g >= 10 ? 1 : view->depth_g + 7;
		view->depth_b = view->depth_b >= 10 ? 1 : view->depth_b + 1;
	}
}

/*
** key checks loop
*/

int					loop_check(t_view *view)
{
	t_helper	*head;

	head = malloc(sizeof(t_helper));
	head->check = view->move == RIGHT || view->move == LEFT ||
		view->move == DOWN || view->move == UP ||
		view->zoom || view->do_iter || view->animation;
	free(head);
	return (head->check);
}
