/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmittelb <mmittelb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 18:30:00 by jnieders          #+#    #+#             */
/*   Updated: 2025/12/10 11:34:23 by mmittelb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "libft.h"
#include "utils.h"

static int	cast_and_mod_256(int sign, unsigned long long num)
{
	long long			result;
	unsigned long long	limit_llong_min;

	limit_llong_min = (unsigned long long)LLONG_MAX + 1;
	if (sign == 1)
		result = (long long)num;
	else
	{
		if (num == limit_llong_min)
			result = LLONG_MIN;
		else
			result = -(long long)num;
	}
	if (result >= 256 || result < 0)
	{
		result = result % 256;
		if (result < 0)
			result += 256;
	}
	return ((int)result);
}

static int	exit_parse_number(const char *str, int sign,
		unsigned long long limit, int *code)
{
	int					i;
	unsigned long long	num;
	int					digit;

	i = 0;
	num = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		digit = str[i] - '0';
		if (num > limit / 10)
			return (0);
		if (num == limit / 10 && (unsigned long long)digit > limit % 10)
			return (0);
		num = num * 10 + (unsigned long long)digit;
		i++;
	}
	if (str[i] != '\0')
		return (0);
	*code = cast_and_mod_256(sign, num);
	return (1);
}

static int	ft_exit_atoi(const char *str, int *code)
{
	int					i;
	int					sign;
	unsigned long long	limit;

	i = 0;
	sign = 1;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	if (str[i] == '\0')
		return (0);
	if (sign == 1)
		limit = (unsigned long long)LLONG_MAX;
	else
		limit = (unsigned long long)LLONG_MAX + 1;
	return (exit_parse_number(str + i, sign, limit, code));
}

static void	exit_numeric_error(t_general *general, char *arg)
{
	if (isatty(STDIN_FILENO))
		write(2, "exit\n", 5);
	write3(general, "minishell: exit: ", arg, ": numeric argument required\n");
	exit_with_status_and_cleanup(general, 2);
}

int	builtin_exit(t_general *general, char **argv)
{
	int	argc;
	int	code;

	argc = count_args(argv);
	if (argc == 1)
	{
		if (isatty(STDIN_FILENO))
			write(2, "exit\n", 5);
		exit_with_status_and_cleanup(general, general->exit_status);
		return (0);
	}
	if (!ft_exit_atoi(argv[1], &code))
		exit_numeric_error(general, argv[1]);
	if (argc > 2)
	{
		write(2, "minishell: exit: too many arguments\n", 36);
		general->exit_status = 1;
		return (1);
	}
	if (isatty(STDIN_FILENO))
		write(2, "exit\n", 5);
	exit_with_status_and_cleanup(general, code);
	return (0);
}
