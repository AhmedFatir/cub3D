/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatir <afatir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 17:35:58 by afatir            #+#    #+#             */
/*   Updated: 2023/01/24 07:29:53 by afatir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	format_check(va_list args, char format)
{
	int		ln;

	ln = 0;
	if (format == '%')
		ln += ft_putchar('%');
	else if ((format == 'd') || (format == 'i'))
		ln += ft_put_deci(va_arg(args, int));
	else if (format == 'c')
		ln += ft_putchar(va_arg(args, int));
	else if (format == 's')
		ln += ft_putstr(va_arg(args, char *));
	else if (format == 'u')
		ln += ft_put_unsigned(va_arg(args, unsigned int));
	else if (format == 'x')
		ln += ft_put_hexa(va_arg(args, int), "0123456789abcdef");
	else if (format == 'X')
		ln += ft_put_hexa(va_arg(args, int), "0123456789ABCDEF");
	else if (format == 'p')
	{
		ln += ft_putstr("0x");
		ln += ft_put_ad(va_arg(args, size_t), "0123456789abcdef");
	}
	else
		ln += ft_putchar(format);
	return (ln);
}

int	ft_printf(const char *fr, ...)
{
	int		ln;
	int		i;
	va_list	args;

	va_start(args, fr);
	ln = 0;
	i = 0;
	while (fr[i])
	{
		if (fr[i] == '%')
		{
			if (!fr[i + 1])
				return (ln);
			ln += format_check(args, fr[i + 1]);
			i++;
		}
		else
			ln += ft_putchar(fr[i]);
		i++;
	}
	va_end(args);
	return (ln);
}
