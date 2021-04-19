/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncatrien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 10:39:08 by ncatrien          #+#    #+#             */
/*   Updated: 2021/04/19 14:19:26 by ncatrien         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "includes/miniRT.h"

int main(int argc, char **argv)
{
	t_scene		scene;

	if (!check_args(argc, argv))
		return (0);

	scene = scene_extractor(argv[1]);


	if (argc == 2)
	{
		display_something(scene);
		t_camera *cam = scene.cur_cam->content;
		print_camera(cam);
		print_objlist(scene);
	}
	else
	{
		printf("let's save the image!\n");
		prepare_output_file(&scene, argv[1]);
		free_all(&scene);
	}
}
