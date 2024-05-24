/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mserjevi <mserjevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 09:07:08 by mserjevi          #+#    #+#             */
/*   Updated: 2024/05/24 09:47:24 by mserjevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdarg.h>
#include <unistd.h>

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

int	ft_atoi(const char *nptr)
{
	int	sign;
	int	res;

	sign = 1;
	res = 0;
	while (*nptr == '\t' || *nptr == '\f' || *nptr == ' ' || *nptr == '\v'
		|| *nptr == '\r' || *nptr == '\n')
		nptr++;
	if (*nptr == '+' || *nptr == '-')
	{
		if (*nptr == '-')
			sign *= -1;
		nptr++;
	}
	while (*nptr >= '0' && *nptr <= '9')
	{
		res = res * 10 + *nptr - '0';
		nptr++;
	}
	return (res * sign);
}

size_t	ft_strlen(const char *s)
{
	size_t	l;

	/*if (!s)
		return (-1);*/
	l = 0;
	while (s[l])
		l++;
	return (l);
}

int	putstr(va_list argptr)
{
	static int		l;
	char			*arg;

	arg = va_arg(argptr, char *);
	if (!arg)
	{
		write(1, "(null)", 6);
		return (0);
	}
	l = ft_strlen(arg);
	/*if (l == -1)
		return (l);*/
	write(1, arg, l);
	return (l);
}

int	process_format(char c, va_list argptr)
{
	if (c == 's')
		return (putstr(argptr));
	else if (c == 'c')
		return (ft_putchar_fd(va_arg(argptr, int), 1), 1);
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
	if (!str[i])
		return (-1);
	while (*str)
	{
		if (*str == '%')
		{
			if (*++str == '\0')
				return (-1);
			arg_len = process_format(*str++, argptr);
			i += arg_len;
		}
		else
		{
			write(1, str++, 1);
			i++;
		}
	}
	return (va_end(argptr), i);
}

int	main(int argc , char *argv[])
{
	char c;
	char *str;

	str = argv[1];
	c = argv[1][0];
	//ft_printf("sadas asdas %s asd\n", str);
	//ft_printf("  sadas asdas %s asd\n", NULL);
	//ft_printf("  %s\n",str);
	//printf("%d",ft_printf("  sadas asdas %", str));
	//printf("%d",ft_printf("  sadas asdas %", str));
	//ft_printf("asdas %s asdas %s%s\n", str, str, str);
	//ft_printf("asdas %s asdas %s%s\n", str, NULL , str);
 	//ft_printf("sadas asdas %c asd\n", c);
 	//printf("sadas asdas %c asd\n", c);
	//printf("%d \n",ft_printf("sadas asdas %c asd\n", NULL));
	//printf("%d \n",printf("sadas asdas %c asd\n", NULL));
}
