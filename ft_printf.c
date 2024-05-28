/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mserjevi <mserjevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 09:07:08 by mserjevi          #+#    #+#             */
/*   Updated: 2024/05/28 15:56:15 by mserjevi         ###   ########.fr       */
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

size_t	convert_num(char *num, size_t n, int sign, char X)
{
	size_t	l;

	l = 0;
	if (n == 0)
	{
		if (!sign)
		{
			num[0] = '0';
			num[1] = 'x';
			l = 2;
		}
	}
	else
	{
		l = convert_num(num, n / 16, sign, X);
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
	if (!arg)
	{
		write(1, "(nil)", 5);
		return (5);
	}
	//if (!sign)
		n = (size_t)arg;
	l = check_len(n);
	num = (char *) malloc(sizeof(char) * (l + 2));
	if (num == NULL)
		return (-1);
	l = convert_num(num, n, sign, X);
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
		return (ft_putchar_fd('%', 1), 1);
}

int	ft_printf(const char *str, ...)
{
	int		i;
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
			i += process_format(*str++, argptr);
		}
		else
			if (write(1, str++, 1))
				i++;
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
	//printf("%d\n",printf("small signed %x\n", -1534235));
	//printf("%d\n",ft_printf("small signed %x\n", -1534235));
	printf("%d\n",printf("big signed %\n", -1534235));
	printf("%d\n",ft_printf("big signed %\n", -1534235));
	printf("%d\n",printf("big signed %\t", -1534235));
	printf("%d\n",ft_printf("big signed %\t", -1534235));
	printf("%d\n",printf("big signed %%\n", -1534235));
	printf("%d\n",ft_printf("big signed %%\n", -1534235));
	printf("%d\n",printf("big signed %q 1a\n", -1534235));
	printf("%d\n",ft_printf("big signed %q 1a\n", -1534235));
	printf("%d\n",printf("b %   d\na", 1));
	printf("%d\n",ft_printf("b %   d\na", 1));
}
