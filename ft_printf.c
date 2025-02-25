/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mserjevi <mserjevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 09:07:08 by mserjevi          #+#    #+#             */
/*   Updated: 2024/05/29 16:01:48 by mserjevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_printf.h"

#include <stdio.h>
#include <unistd.h>
// #include <stdlib.h>
// #include <stdarg.h>
// #include <unistd.h>

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

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

static void	ft_put(int n, int fd, int sign)
{
	if (sign < 0)
	{
		if (n > -10)
		{
			ft_putchar_fd('0' + n * -1, fd);
			return ;
		}
		ft_put(n / 10, fd, sign);
		ft_putchar_fd(((n % 10) * -1) + '0', fd);
	}
	else
	{
		if (n < 10)
		{
			ft_putchar_fd('0' + n, fd);
			return ;
		}
		ft_put(n / 10, fd, sign);
		ft_putchar_fd(n % 10 + '0', fd);
	}
}

static int	check_len(int n)
{
	size_t	l;

	l = 1;
	if (n > 0)
		l--;
	while (n)
	{
		n /= 10;
		l++;
	}
	return (l);
}

static int	check_len_un(unsigned int n)
{
	size_t	l;

	l = 1;
	if (n > 0)
		l--;
	while (n)
	{
		n /= 10;
		l++;
	}
	return (l);
}

static int	check_len_pointer(size_t n)
{
	size_t	l;

	l = 1;
	if (n > 0)
		l--;
	while (n)
	{
		n /= 10;
		l++;
	}
	return (l);
}

int	ft_putnbr_fd(int n, int fd)
{
	int	sign;

	sign = 1;
	if (n == 0)
	{
		ft_putchar_fd('0', fd);
		return (1);
	}
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		sign *= -1;
	}
	ft_put(n, fd, sign);
	return (check_len(n));
}

void	ft_put_un(size_t n, int fd)
{
	if (n < 10)
	{
		ft_putchar_fd('0' + n, fd);
		return ;
	}
	ft_put_un(n / 10, fd);
	ft_putchar_fd(n % 10 + '0', fd);
}

int	ft_putnbr_un(unsigned int n, int fd)
{
	if (n == 0)
	{
		ft_putchar_fd('0', fd);
		return (1);
	}
	ft_put_un(n, fd);
	return (check_len_un(n));
}

unsigned int	convert_pointer(char *num, size_t n, char X)
{
	unsigned int	l;

	l = 0;

	if (n == 0)
	{
			num[0] = '0';
			num[1] = 'x';
			l = 2;
	}
	else
	{
		l = convert_pointer(num, n / 16, X);
		if ( n % 16 < 10)
			num[l] = '0' + (n % 16);
		else
			num[l] = X + (n % 16) - 10;
		l++;
	}
	num[l] = '\0';
	return (l);
}

unsigned int	convert_num(char *num, unsigned int n, char X)
{
	unsigned int	l;

	l = 0;

	if (n)
	{
		l = convert_num(num, n / 16, X);
		if ( n % 16 < 10)
			num[l] = '0' + (n % 16);
		else
			num[l] = X + (n % 16) - 10;
		l++;
	}
	num[l] = '\0';
	return (l);
}

int	ft_utob(va_list argptr,int sign, char X)
{
	int		l;
	char	*num;
	void	*arg;
	size_t	n;

	//if (sign)
	//	n = va_arg(argptr, int);
	//else
	arg = va_arg(argptr, void *);
	if (!sign && !arg)
	{
		write(1, "(nil)", 5);
		return (5);
	}
	//if (!sign)
	n = (size_t)arg;
	//printf("N %zu\n", n);
	if (sign && !(unsigned int)n)
	{
		write(1, "0", 1);
		l = 1;
	}
	else
	{
	if (sign)
		l = check_len_un(n);
	else
		l = check_len_pointer(n);
	num = (char *) malloc(sizeof(char) * (l + 3));
	if (num == NULL)
		return (-1);
	if (sign)
		l = convert_num(num, n, X);
	else
		l = convert_pointer(num, n, X);
	write(1, num, l);
	free(num);
	}
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
		return (6);
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
	else if (c == 'p')
		return (ft_utob(argptr, 0, 'a'));
	else if (c == 'd' || c == 'i')
	 	return (ft_putnbr_fd(va_arg(argptr, int), 1));
	else if (c == 'u')
		return (ft_putnbr_un(va_arg(argptr, size_t), 1));
	else if (c == 'x')
		return (ft_utob(argptr, 1, 'a'));
	else if (c == 'X')
		return (ft_utob(argptr, 1, 'A'));
	else if (c == '%')
		return (ft_putchar_fd('%', 1), 1);
	else if (c == ' ')
		return (ft_putchar_fd(' ', 1), 1);
	else if (c >= 9 && c <= 13)
		return (ft_putchar_fd('%', 1), ft_putchar_fd(c, 1), 2);
	else
		return (ft_putchar_fd('%', 1), -1);
}
static int	ft_isupper(int c)
{
	if (c >= 'A' && c <= 'Z')
		return (1);
	else
		return (0);
}

static int	ft_islower(int c)
{
	if (c >= 'a' && c <= 'z')
		return (1);
	else
		return (0);
}

int	ft_isalpha(int c)
{
	if (c < 0 || c > 255)
		return (0);
	if (ft_isupper(c) || ft_islower(c))
		return (1);
	else
		return (0);
}


int edit_format(char *str)
{
	int	i;

	i = 0;
	while(*str && !ft_isalpha(*str))
	{
		ft_putchar_fd(' ', 1);
		str++;
		i++;
	}
		return (i);
}

int	ft_printf(const char *str, ...)
{
	int		i;
	int		count;
	va_list	argptr;

	va_start(argptr, str);
	i = 0;
	if (!str[i])
		return (-1);
	while (*str)
	{
		if (*str == '%' )
		{
			if (*++str == '\0')
				return (-1);
			while (*str == ' ' && *(str + 1) == ' ')
					str++;
			if (*str == ' ')
				i += process_format(*str++, argptr);
			if ((*str == '-' || *str == '.' || (*str >= '0' && *str <= '9')) && ft_isalpha(*(str + 1)))
				str++;
			if (*str == '-' || *str == '.' || (*str >= '0' && *str <= '9'))
			{
				count = edit_format((char *)str);
				i += count;
				str += count;
			}
			count = process_format(*str++, argptr);
			if (count == -1)
				return (va_end(argptr), ++i);
			i += count;
		}
		else
			if (write(1, str++, 1))
				i++;
	}
	return (va_end(argptr), i);
}

