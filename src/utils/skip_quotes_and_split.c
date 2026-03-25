/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skip_quotes_and_split.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmittelb <mmittelb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 14:59:46 by mmittelb          #+#    #+#             */
/*   Updated: 2025/12/08 13:26:43 by mmittelb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "utils.h"
#include "libft.h"

static int	ft_wordlen(char *s, int i, char c)
{
	int	count;
	int	start;

	start = i;
	count = 0;
	while (s[i] && s[i] != c)
	{
		if (s[i] == '"' || s[i] == '\'')
			i = skip_quotes(s, i, s[i]);
		else
			i++;
	}
	count = i - start;
	return (count);
}

static size_t	ft_skip_token(char *s, size_t i, char c)
{
	while (s[i] && s[i] != c)
	{
		if (s[i] == '"' || s[i] == '\'')
			i = skip_quotes(s, i, s[i]);
		else
			i++;
	}
	return (i);
}

static int	ft_stramount(char *s, char c)
{
	int		count;
	size_t	i;
	size_t	end;

	i = 0;
	count = 0;
	end = ft_strlen(s);
	if (end == 0)
		return (0);
	end--;
	while (end > 0 && s[end] == c)
		end--;
	while (s[i] && s[i] == c)
		i++;
	while (s[i] && i <= end)
	{
		i = ft_skip_token(s, i, c);
		count++;
		while (s[i] && s[i] == c)
			i++;
	}
	return (count);
}

char	**skip_quotes_and_split(t_general *general, char *s, char c)
{
	int		i;
	int		j;
	char	**ptr;

	i = 0;
	j = 0;
	ptr = gc_malloc(general, sizeof(char *) * (ft_stramount(s, c) + 1));
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i] == '\0')
			break ;
		ptr[j] = gc_substr(general, s, i, ft_wordlen(s, i, c));
		while (s[i] && s[i] != c)
		{
			if (s[i] == '"' || s[i] == '\'')
				i = skip_quotes(s, i, s[i]);
			else
				i++;
		}
		j++;
	}
	ptr[j] = NULL;
	return (ptr);
}
