/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apickett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/29 14:59:46 by apickett          #+#    #+#             */
/*   Updated: 2019/02/26 20:17:07 by apickett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "minilibx_macos/mlx.h"
# include <math.h>
# include "libft/libft.h"
# include <stdlib.h>
# include <pthread.h>

# define WW 1920
# define WH 1080
# define HW 960
# define HH 540
# define THREADS 16

/*
**key code macros
*/
# define R 15
# define ESC 53
# define PLUS 69
# define MIN 78
# define UP 126
# define DOWN 125
# define LEFT 123
# define RIGHT 124
# define SCRLUP 4
# define SCRLDN 5
# define ITER 49
# define REVITER 8
# define A 0
# define ONE 18
# define TWO 19
# define THREE 20
# define J 38
# define S 1

# define ARR(key) key == RIGHT || key == LEFT || key == UP || key == DOWN
# define NU1(key) key == ONE || key == TWO || key == THREE

typedef struct		s_env
{
	void			*mlx;
	void			*win;
}					t_env;

typedef struct		s_helper
{
	int				iter;
	int				checkey;
	int				start;
	int				step;
	int				until;
	int				check;
	int				i;
	int				x;
	double			dtmp;
}					t_helper;

typedef struct		s_image
{
	void			*begin;
	void			*ptr;
	int				bpp;
	int				len;
	int				end;
}					t_image;

typedef struct		s_complex
{
	double			real;
	double			imag;
}					t_complex;

typedef struct		s_rgb
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
}					t_rgb;

typedef struct		s_set
{
	t_rgb			rgb;
	int				y_coord;
	int				y_max;
	int				x_max;
	int				y_split;
	int				x_split;
	int				res;
	int				y;
	double			step;

}					t_set;

typedef struct		s_view
{
	pthread_t		pth;
	t_env			e;
	t_image			img;
	t_complex		julia_arg;
	int				fractal;
	int				x_old;
	int				y_old;
	int				x_start;
	int				x_until;
	int				depth_r;
	int				depth_g;
	int				depth_b;
	int				iter;
	int				animation;
	int				move;
	int				zoom;
	int				do_iter;
	int				(*checker)(t_complex, struct s_view *);
	double			xabs;
	double			yabs;
	double			z;
}					t_view;

t_rgb				set_color(int r, int g, int b);
void				my_exit(t_env *e, void *ptr);
void				ft_seizure(t_view *view);
void				ft_thread(t_view *view);
void				rgb_pixelput(t_image im, t_rgb color, int x, int y);
void				ft_defaults(t_view *view);
void				*ft_putfrac(void *arg);
int					ft_mandelbrot(t_complex c, t_view *view);
int					ft_julia(t_complex c, t_view *view);
int					ft_ship(t_complex c, t_view *view);
int					key_hook(int k, t_view *view);
int					mouse_hook(int k, int x, int y, t_view *view);
int					loop_hook(t_view *view);
int					key_release(int k, t_view *view);
int					mouse_move(int x, int y, t_view *view);
int					loop_check(t_view *view);
#endif
