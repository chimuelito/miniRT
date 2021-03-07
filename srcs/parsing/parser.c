/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncatrien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/26 13:53:58 by ncatrien          #+#    #+#             */
/*   Updated: 2021/03/07 14:16:04 by ncatrien         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

t_bool	check_args(int argc, char **argv)
{
	t_bool	check;

	check = TRUE;
	if (argc < 2 || argc > 3)
		check = FALSE;
	else if (!check_extension(argv[1]))
	{
		printf("Invalid file extension.\t");
		check = FALSE;
	}
	else if (argc == 3 && ft_strncmp(argv[2], "--save", 6) != 0)
	{
		printf("Unknown option.\t");
		check = FALSE;
	}
	if (check == FALSE)
		printf("Usage: ./miniRT *file*.rt [--save]\n");
	return (check);
}

t_scene	scene_extractor(char *filename)
{
	int		fd;
	t_scene	scene;

	fd = open(filename, O_RDONLY);
	if (fd > 0)
		scene = parse_file(fd);
	else
	{
		scene.valid = FALSE;
		printf("Can't open file %s.\n", filename);
	}
	close(fd);
	if (!scene.valid)
	{
		free_all(scene);
		exit(1);
	}
	return (scene);
}

t_bool	check_extension(char *filename)
{
	int	i_dot;

	i_dot = ft_strlen(filename) - 3;
	if (ft_strncmp(&filename[i_dot], ".rt", 3) == 0)
		return (TRUE);
	else
		return (FALSE);
}

t_scene	parse_file(int fd)
{
	t_scene	scene;
	char	*line;
	int		num_line;

	scene = initialize_scene();
	num_line = 0;
	while (get_next_line(fd, &line) > 0 && scene.valid)
	{
		parse_line(line, &scene);
		num_line++;
		free(line);
	}
	if (scene.valid)
	{
		parse_line(line, &scene);
		num_line++;
	}
	if (!scene.valid)
		printf("Error at line %d: %s\n", num_line, scene.err_msg);
	free(line);
	return (scene);
}

void	parse_line(char *line, t_scene *scene)
{
	if (ft_strncmp(line, "R ", 2) == 0)
		parse_resolution(line, scene);
	else if (ft_strncmp(line, "A ", 2) == 0)
		parse_ambient_light(line, scene);
	else if (ft_strncmp(line, "c ", 2) == 0)
		parse_camera(line, scene);

	else if (ft_strncmp(line, "l ", 2) == 0)
		parse_light(line, scene);
	else if (ft_strncmp(line, "sp ", 3) == 0)
		parse_sphere(line, scene);
/*
	else if (ft_strncmp(line, "pl ", 3) == 0)
		parse_plane(line, scene);
	else if (ft_strncmp(line, "sq ", 3) == 0)
		parse_square(line, scene);
	else if (ft_strncmp(line, "cy ", 3) == 0)
		parse_cylinder(line, scene);
	else if (ft_strncmp(line, "tr ", 3) == 0)
		parse_triangle(line, scene);
*/
	else if (line[0] != '\0' && line[0] != '#')
	{
		scene->valid = FALSE;
		scene->err_msg = E_INVAL;
	}
}