/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molesen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 16:11:51 by molesen           #+#    #+#             */
/*   Updated: 2022/07/01 16:11:53 by molesen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/lemin.h"

static int	below_max_int(char *str, int len)
{
	if (len > 10 || (len == 10 && ft_strncmp(str, "2147483647", len) > 0))
		return (FALSE);
	return (TRUE);
}

static int	only_digits(char *str, int *i)
{
	if (ft_strcmp("0", str) == 0 || ft_strcmp("\0", str) == 0)
		return (error(NO_ANTS));
	if (below_max_int(str, ft_strlen(str)) == FALSE)
		return (error(TOO_MANY_ANTS));
	while (*str != '\0')
	{
		if (ft_isdigit(*str) == 0)
			return (error(NON_DIGIT_ANTS));
		str++;
	}
	(*i)++;
	return (TRUE);
}

static int	is_comment(char *str)
{
	int	i;

	i = 0;
	while (str[i] == '#')
		++i;
	if (i < 1)
		return (FALSE);
	return (i);
}

static int	is_digit_and_below_max_int(char *str, int *i)
{
	(*i)++;
	if (below_max_int(&str[*i], ft_strlen_stop(&str[*i], ' ')) == FALSE)
		return (FALSE);
	while (str[*i] != ' ' && str[*i] != '\0')
	{
		if (ft_isdigit(str[*i]) == 0)
			return (FALSE);
		(*i)++;
	}
	return (TRUE);
}

static int	is_coordinates(char *str)
{
	int	i;

	if (*str == 'L' || *str == ' ')
		return (FALSE);
	if (ft_word_count(str, ' ') != 3)
		return (FALSE);
	i = 0;
	while (str[i] != ' ')
		++i;
	if (is_digit_and_below_max_int(str, &i) == FALSE)
		return (FALSE);
	if (is_digit_and_below_max_int(str, &i) == FALSE)
		return (FALSE);
	return (TRUE);
}

static int is_connection(char *str)
{
	int	count;
	int	i;

	if (ft_word_count(str, '-') < 2)
		return (FALSE);
	count = 0;
	i = 0;
	if (str[i] == 'L' || *str == ' ')
		return (FALSE);
	while (str[i] != '\0')
	{
		if (str[i] == '-')
			++count;
		else if (str[i] == ' ')
			return (FALSE);
		++i;
	}
	if (count < 1)
		return (FALSE);
	return (TRUE);
}

static int	first_start_or_end(char *str, int i, int *command)
{
	if (ft_strcmp(str, "##start") == 0)
	{
		if (*command == TRUE || i > 1)
			return (ERROR);
		else
			*command = TRUE;
	}
	else if (ft_strcmp(str, "##end") == 0)
	{
		if (*command == TRUE || i > 1)
			return (ERROR);
		else
			*command = TRUE;
	}
	return (TRUE);
}

static int	check_if_valid(char *str, int *i, int *total, int *command)
{
	int	comment;

	comment = is_comment(str);
	if (*i == 0 && only_digits(str, i) == TRUE)
		return (TRUE);
	else if (comment >= TRUE)
	{
		if (first_start_or_end(str, *i, command) == ERROR)
			return (error(COMMAND));
		return (TRUE);
		//## start and end has to be done at coordinates and can only happen once.
		// so if it has already been found it is an error
		ft_printf("call function to collect comment if it contains ##start or ##end\n");
	}
	else if (*i == 1 && is_coordinates(str) == TRUE)
	{
		(*total)++;
		ft_printf("room count: %d\n", *total);
	}
	else if (*i > 0 && is_connection(str) == TRUE && *total > 1)
	{
		(*i)++;
		ft_printf("call function to collect connections\n");
	}
	else
	{
		free(str);
		if (*i == 1)
			return (error(COORDINATES));
		else if (*i > 1)
			return (error(CONNECTION));
		else
			return (error(-1));
	}
	if (*command == TRUE)
		*command = FALSE;
	return (TRUE);
}

int	parsing_phase(int *total)
{
	int		ret;
	int		i;
	int		command;
	char	*line;

	ret = 1;
	line = NULL;
	i = 0;
	command = FALSE;
	while (ret == 1)
	{
		ret = get_next_line(0, &line);
		if (ret == ERROR)
			return (0);
		if (!line)
			break ;
		if (check_if_valid(line, &i, total, &command) == ERROR)
			return (ERROR);
		ft_printf("[%s]\n", line);
		free(line);
	}
	return (0);
}

// how to check if path is valid?