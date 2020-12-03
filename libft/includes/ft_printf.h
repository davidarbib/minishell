/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 18:01:05 by darbib            #+#    #+#             */
/*   Updated: 2020/01/18 19:13:56 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdlib.h>

# define INTMAX		2147483647
# define INTMIN		-2147483648
# define LOWERHEX	"0123456789abcdef"
# define UPPERHEX	"0123456789ABCDEF"
# define BUF_SIZE	4096
# define STDOUT		1

# define FLAGS_S	"cspdiouxXfeEgGpn# 0-+.*"
# define CONV_S		"cspdiuxX"
# define CONV_NB	9
# define OPTS_TRUE	".-0+#* "
# define OPTS_MY	"-0."
# define OPTIONS_NB	3
# define DOT		4
# define ZERO		2
# define MINUS		1

/*
** buffer to print
*/

typedef struct	s_buf
{
	size_t	count;
	size_t	i;
	char	s[BUF_SIZE];
}				t_buf;

/*
** conversion data
** have 2 possible options flags
*/

typedef struct	s_conv
{
	int		lmc;
	int		prec;
	char	*size;
	int		flags;
}				t_conv;

int				ft_printf(const char *format, ...);

int				atoi_spe(const char **str);
long			atol_spe(const char **str);
void			add_option(char c, t_conv *conv);
char			is_true_option(char c);
int				star_post_process(t_conv *conv);

void			init_buf(t_buf *buf);
void			buf_flush(t_buf *buf);
void			check_full(t_buf *buf);
void			write_into(t_buf *buf, char **str);
void			fill_buffer(t_buf *buf, size_t nb, char c);

void			conv_parse(const char **format, va_list args,
				t_conv *current_conv);
int				conv_make(const char **format, va_list args,
				t_conv *conv, t_buf *buf);

int				c_convert(t_buf *buf, t_conv *conv, va_list args);
int				s_convert(t_buf *buf, t_conv *conv, va_list args);
int				p_convert(t_buf *buf, t_conv *conv, va_list args);
int				di_convert(t_buf *buf, t_conv *conv, va_list args);
int				u_convert(t_buf *buf, t_conv *conv, va_list args);
int				x_convert(t_buf *buf, t_conv *conv, va_list args);
int				bigx_convert(t_buf *buf, t_conv *conv, va_list args);
int				pct_convert(t_buf *buf, t_conv *conv, va_list args);
int				no_convert(t_buf *buf, t_conv *conv, char c);
#endif
