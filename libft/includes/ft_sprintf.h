/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sprintf.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 20:44:57 by darbib            #+#    #+#             */
/*   Updated: 2020/01/13 13:22:41 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SPRINTF_H
# define FT_SPRINTF_H

# include <stdarg.h>
# include <stdlib.h>
# include "ft_printf.h"

# define BUFOUT_SIZE	100000000

int		ft_sprintf(char *buf_out, const char *format, ...);

#endif
