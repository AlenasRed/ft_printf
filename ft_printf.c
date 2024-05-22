/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mserjevi <mserjevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 09:07:08 by mserjevi          #+#    #+#             */
/*   Updated: 2024/05/22 13:08:03 by mserjevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdarg.h>
#include <unistd.h>

size_t	ft_strlen(const char *s)
{
	size_t	l;

	if (!s)
		return (-1);
	l = 0;
	while (s[l])
		l++;
	return (l);
}

int	putlstr(char *arg)
{
	int	l;

	l = ft_strlen(arg);
	if (l == -1)
		return (l);
	write(1, arg, l);
	return (l);
}

int	process_format(char c, va_list argptr)
{
	char	*arg;

	arg = va_arg(argptr, char *);
	if (!arg)
		return (-1);
	if (c == 's')
		return (putlstr(arg));
	else
		return (-1);
}

int	ft_printf(const char *str, ...)
{
	int		i;
	int		arg_len;
	va_list	argptr;

	va_start(argptr, str);
	i = 0;
	arg_len = 0;
	if (!str[i])
		return (-1);
	while (*str)
	{
		if (*str == '%')
		{
			if (*++str == '\0')
				return (-1);
			arg_len = process_format(*str++, argptr);
			if (arg_len == -1 && !(++arg_len))
				write(1, "(null)", 6);
			i += arg_len;
		}
		else
			write(1, str++, 1);
	}
	va_end(argptr);
	return (i);
}

int	main(void)
{
	int i;
	char str[5] = "Milan";
	//ft_printf("sadas asdas %s asd\n", str);
	//ft_printf("  sadas asdas %s asd\n", NULL);
	//ft_printf("  %s\n",str);
	//printf("%d",ft_printf("  sadas asdas %", str));
	//printf("%d",ft_printf("  sadas asdas %", str));
	//ft_printf("asdas %s asdas %s%s\n", str, str, str);
	//ft_printf("asdas %s asdas %s%s\n", str, NULL , str);
}
