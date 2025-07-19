/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 19:52:58 by katakada          #+#    #+#             */
/*   Updated: 2025/07/19 14:16:50 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_mandatory.h"

int	main(int argc, char **argv)
{
	static t_scene	scene;

	printf(F_MSG);
	// 引数チェック
	if (argc != 2 || !argv[1])
	{
		ft_putstr_fd(ERR_PREFIX, STDERR_FILENO);
		ft_putstr_fd(ERR_INVALID_ARG, STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	// 初期化
	init_scene(&scene);
	// 引数のrtファイルからシーンデータを作成
	if (create_scene(&scene, argv[1]) == FAILURE)
	{
		free_scene(&scene);
		return (EXIT_FAILURE);
	}
	// セットアップ
	// setup_scene(&scene);
	// 描画処理 minilibXはload_sceneの中だけで定義される
	if (render_scene(&scene) == FAILURE)
	{
		free_scene(&scene);
		return (EXIT_FAILURE);
	}; // loop処理なので以降の処理は実行されない?
	free_scene(&scene);
	return (EXIT_SUCCESS);
}
