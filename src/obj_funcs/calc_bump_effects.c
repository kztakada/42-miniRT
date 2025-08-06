/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_bump_effects.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 23:15:24 by katakada          #+#    #+#             */
/*   Updated: 2025/08/06 16:53:02 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_color	get_texture_color(t_texture tx, int x, int y)
{
	int	i;

	if (!tx.color || tx.width == 0 || tx.height == 0)
		return (put_out_error_color(ERR_INVALID_GC_ARGS));
	// 境界チェック
	if (x < 0)
		x = 0;
	if (x >= (int)tx.width)
		x = (int)tx.width - 1;
	if (y < 0)
		y = 0;
	if (y >= (int)tx.height)
		y = (int)tx.height - 1;
	i = x + y * (int)tx.width;
	if (i >= (int)tx.width * (int)tx.height)
		return (put_out_error_color(ERR_INVALID_GC_ARGS));
	return (tx.color[i]);
}

static float	get_bump_height(t_texture tx, int x, int y)
{
	t_color	color;

	color = get_texture_color(tx, x, y);
	// グレースケール値として扱う（輝度値）
	return (0.299F * color.r + 0.587F * color.g + 0.114F * color.b);
}

t_uv	calc_bump_effects(t_obj *obj, t_pos2d bump_dot, t_uv ref_scale)
{
	t_dir4_pos	bump;
	t_dir4_f	bump_hight;
	t_uv		bump_delta;

	// 中央差分法のためのサンプル点を計算
	// 水平方向の境界処理（正距円筒図法は水平方向で周期的） 水平方向の境界処理（円筒なので折り返し）
	bump.left.x = ((int)((float)bump_dot.x - ref_scale.u)
			+ obj->material.bump.width) % obj->material.bump.width;
	bump.right.x = (int)((float)bump_dot.x + ref_scale.u)
		% obj->material.bump.width;
	// 垂直方向は境界も周期的に繰り返す
	bump.up.y = ((int)((float)bump_dot.y - ref_scale.v)
			+ obj->material.bump.height) % obj->material.bump.height;
	bump.down.y = ((int)((float)bump_dot.y + ref_scale.v)
			+ obj->material.bump.height) % obj->material.bump.height;
	// 4方向の高さ値をサンプル
	bump_hight.left = get_bump_height(obj->material.bump, bump.left.x,
			bump_dot.y);
	bump_hight.right = get_bump_height(obj->material.bump, bump.right.x,
			bump_dot.y);
	bump_hight.up = get_bump_height(obj->material.bump, bump_dot.x, bump.up.y);
	bump_hight.down = get_bump_height(obj->material.bump, bump_dot.x,
			bump.down.y);
	// 中央差分法で勾配を計算
	bump_delta.u = -(bump_hight.right - bump_hight.left) / (2.0F * ref_scale.u)
		* BUMP_HEIGHT_SCALE;
	bump_delta.v = -(bump_hight.down - bump_hight.up) / (2.0F * ref_scale.v)
		* BUMP_HEIGHT_SCALE;
	return (bump_delta);
}

t_bool	handle_gimbal_lock_uv_axes(t_vector default_normal, t_vector *axis_u,
		t_vector *axis_v)
{
	// U方向（経度方向）: 法線とY軸の外積
	*axis_u = cross_vector(default_normal, up_dir());
	if (vector_len(*axis_u) < GIMBAL_LOCK_THRESHOLD)
	{
		// 極付近では別の軸を使用
		*axis_u = cross_vector(default_normal, right_dir());
		if (vector_len(*axis_u) < GIMBAL_LOCK_THRESHOLD)
			return (FALSE);
	}
	*axis_u = normalize_vector(*axis_u);
	// V方向（緯度方向）: U方向と法線の外積
	*axis_v = normalize_vector(cross_vector(*axis_u, default_normal));
	return (TRUE);
}

t_vector	calc_bumped_normal(t_obj *obj, t_vector default_normal,
		t_uv bump_delta)
{
	t_vector	tmp_normal;
	t_vector	axis_u_dir;
	t_vector	axis_v_dir;

	// 引数の検証
	if (!obj)
		return (default_normal);
	// du, dvが極端に小さい場合は元の法線を返す
	if (fabsf(bump_delta.u) < EPSILON && fabsf(bump_delta.v) < EPSILON)
		return (default_normal);
	if (!handle_gimbal_lock_uv_axes(default_normal, &axis_u_dir, &axis_v_dir))
		return (default_normal);
	// 法線を摂動（du, dvの値を制限して過度な変化を防ぐ）
	// bump_delta.u = clampf(bump_delta.u, -BUMP_MAX_RANGE, BUMP_MAX_RANGE);
	// bump_delta.v = clampf(bump_delta.v, -BUMP_MAX_RANGE, BUMP_MAX_RANGE);
	tmp_normal = add_vectors(default_normal, scale_vector(bump_delta.u,
				axis_u_dir));
	tmp_normal = add_vectors(tmp_normal, scale_vector(bump_delta.v,
				axis_v_dir));
	// 正規化して返す
	return (normalize_vector(tmp_normal));
}
