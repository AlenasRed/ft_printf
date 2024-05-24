/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mserjevi <mserjevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 09:07:08 by mserjevi          #+#    #+#             */
/*   Updated: 2024/05/24 15:04:26 by mserjevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <unistd.h>

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

static int	check_len(size_t n)
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

int	ft_putnbr_un(size_t n, int fd)
{
	if (n == 0)
	{
		ft_putchar_fd('0', fd);
		return (1);
	}
	ft_put_un(n, fd);
	return (check_len(n));
}

size_t	convert_num(char *num, size_t n)
{
	size_t	l;

	l = 0;
	//printf("First n = %zu\n", n);
	if (n == 0)
	{
		num[0] = '0';
		num[1] = 'x';
		l = 2;
	}
	else
	{
		l = convert_num(num, n / 16);
		//printf("N = %zu \n", n % 16);
		if ( n % 16 < 10)
			num[l] = '0' + (n % 16);
		else
			num[l] = 'a' + (n % 16) - 10;
		l++;
	}
	num[l] = '\0';
	return (l);
}

int	ft_utob(va_list argptr)
{
	int		l;
	char	*num;
	void	*arg;
	size_t	n;

	arg = va_arg(argptr, void *);
	if (!arg)
	{
		write(1, "(nil)", 5);
		return (5);
	}
	n = (size_t)arg;
	l = check_len(n);
	num = (char *) malloc(sizeof(char) * (l + 2));
	if (num == NULL)
		return (-1);

	//printf("n = %zu \n runed l = %d \n", n, l);
	l = convert_num(num, n);
	//printf("runed l = %d \n", l);
	write(1, num, l);
	free(num);
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
	else if (c == 'p')
		return (ft_utob(argptr));
	else if (c == 'd' || c == 'i')
	 	return (ft_putnbr_fd(va_arg(argptr, int), 1));
	else if (c == 'u')
		return (ft_putnbr_un(va_arg(argptr, size_t), 1));
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
	void *pointer;
	int	 integer;

	integer = 012;
	str = argv[1];
	c = argv[1][0];
	pointer = argv[1];
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
	//printf("%d\n",printf("sadas asdas %p asd %p\n", pointer, pointer + 1));
	//printf("%d\n",ft_printf("sadas asdas %p asd %p\n", pointer, pointer + 1));
	//printf("%d\n",printf("decimal %d\n integer %i\n", 012, 012));
	//printf("%d\n",ft_printf("decimal %d\n integer %i\n", 012, 012));
	//printf("%d\n",printf("unsigned %u", -012));
	//printf("%d\n",ft_printf("unsigned %u", -012));
}
//handle % with no sign after it(not at end)
