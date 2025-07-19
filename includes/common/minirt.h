/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 18:41:49 by katakada          #+#    #+#             */
/*   Updated: 2025/07/19 17:57:15 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "error.h"
# include "libft.h"
# include "mlx.h"
# include "settings.h"
# include <math.h>
# include <pthread.h>
# include <stdio.h>

// key code
# define KEY_ESC 65307
# define KEY_LEFT 65361
# define KEY_RIGHT 65363
# define KEY_UP 65362
# define KEY_DOWN 65364
# define KEY_PLUS 61
# define KEY_MINUS 45
# define KEY_SPACE 32
# define KEY_R 114
# define KEY_C 99
# define KEY_D 100
# define KEY_X 120
# define KEY_Y 121
# define KEY_Z 122
# define KEY_A 97

// mouse code
# define MOUSE_LEFT 1
# define MOUSE_MIDDLE 2
# define MOUSE_RIGHT 3
# define MOUSE_SCROLL_UP 4
# define MOUSE_SCROLL_DOWN 5

typedef enum e_bool
{
	FALSE = 0,
	TRUE = 1,
}							t_bool;

typedef enum e_binary_result
{
	FAILURE = -1,
	SUCCESS = 0,
}							t_binary_result;

/* ************************************************************************** */

typedef struct s_color
{
	float					r;
	float					g;
	float					b;
}							t_color;

typedef struct s_vect
{
	float					x;
	float					y;
	float					z;
}							t_vect;

/* ************************************************************************** */

typedef struct s_light
{
	t_vect pos; // coords;
	float					brightness;
	t_color					color;
	// struct s_light	*next;
	// t_obj_id		id;
}							t_light;

/* ************************************************************************** */
typedef struct s_hit		t_hit;

typedef struct s_texture
{
	// char				*name;
	size_t					width;
	size_t					height;
	t_color					*color;
}							t_texture;

typedef struct s_material
{
	t_color					color;
	float					speckv;
	float					specn;
	float					mirror;
	float					refract;
	t_texture				bump;
	t_texture				texture;
	t_bool					has_bump;
	t_bool					has_texture;
	t_bool					is_checkerboard;
}							t_material;

typedef struct s_plane
{
	// t_obj_id	id;
	t_vect pos; // coords;
	t_vect dir; // orient;
	t_vect					pos_initial;
	t_vect					dir_initial;
	// t_color		color;
}							t_plane;

typedef struct s_cylinder
{
	// t_obj_id	id;
	t_vect pos; // coords;
	t_vect dir; // orient;
	t_vect					pos_initial;
	t_vect					dir_initial;
	float					diameter;
	float					height;
	float					r2;
	t_vect					p1;
	t_vect					p2;
	t_vect					delta_p;
	// t_color		color;
}							t_cylinder;

typedef struct s_sphere
{
	// t_obj_id	id;
	t_vect pos; // coords;
	t_vect					pos_initial;
	float					diameter;
	float					r2;
	// t_color		color;
}							t_sphere;

typedef struct s_triangle
{
	// t_obj_id	id;
	t_vect c[3]; // triangleはinitial定義なし;
	t_vect					edge[3];
	t_vect					n;
	// t_color		color;
	float					area2;
}							t_triangle;

typedef struct s_cone
{
	// t_obj_id	id;
	t_vect pos; // coords;
	t_vect dir; // orient;
	t_vect					pos_initial;
	t_vect					dir_initial;
	float					h;
	float					h2;
	float					angle;
	float					cos2;
	t_vect					c1;
	t_vect					c2;
	float					r1;
	float					r2;
	// t_color		color;
}							t_cone;

typedef struct s_torus
{
	// t_obj_id	id;
	t_vect pos; // coords;
	t_vect dir; // orient;
	t_vect					pos_initial;
	t_vect					dir_initial;
	float					sml_r;
	float					sml_r2;
	float					big_r;
	float					big_r2;
	// t_color		color;
}							t_torus;

typedef union u_obj_shape
{
	t_sphere				sphere;
	t_plane					plane;
	t_cylinder				cylinder;
	t_cone					cone;
	t_triangle				triangle;
	t_torus					torus;
}							t_obj_shape;

typedef struct s_ray
{
	t_vect pos; // or;
	t_vect					dir;
}							t_ray;

typedef float				(*t_f_calc_cross_distance)(t_list *obj, t_ray *ray,
					float min_dist, float max_dist);
typedef t_vect				(*t_f_calc_normal)(t_list *obj, t_hit *hit);
typedef t_color				(*t_f_get_color)(t_list *obj, t_hit *hit);
typedef void				(*t_f_print_focused_obj)(t_list *obj);

typedef struct s_obj
{
	t_material				material;
	t_obj_shape				shape;
	t_f_calc_cross_distance	calc_cross_distance;
	t_f_calc_normal			calc_normal;
	t_f_get_color			get_color;
	t_f_print_focused_obj	print_focused_obj;

	// ローカル座標系
	t_vect					ex;
	t_vect					ey;
	t_vect					ez;

	// t_vect			coords; uv作成で使用するが、t_f_get_colorで初期化時に定義する
	// t_color					color;
	// t_color					color2;
	// float			h; uv作成で使用するが、t_f_get_colorで初期化時に定義する
	// float					pattern_len;
	// int						pattern_num;
	// float bump_f;     バリデーション用のtmp値
	// float texture_f;  バリデーション用のtmp値
	// t_obj_id			id;
	// t_bool				has_bump;
	// t_bool				has_texture;
	// t_texture			bump;
	// t_texture			texture;
	// float				speckv;
	// float				specn;
	// float				mirror;
	// float				refract;
	// struct s_obj		*next;
	// float				alpha; 未使用
}							t_obj;

/* ************************************************************************** */

struct						s_hit
{
	t_vect					nhit;
	t_vect					phit;
	float					t;
	t_color					color;
};

typedef struct s_raytracing
{
	t_ray samplingray; // prime_ray;
	t_ray					shadowray;
	t_hit					hit;
	t_hit					shadow_hit;
	t_obj					*closest_obj;
}							t_raytracing;

/* ************************************************************************** */

typedef struct s_scene		t_scene;

typedef struct s_screen
{
	// bool				res_set;
	int						width;
	int						height;
	t_color *dot; // *pixel;
	t_vect					pos;
	t_vect px; // ピクセル単位の変換用ベクトル
	t_vect py; // ピクセル単位の変換用ベクトル
	t_vect qx; // 画面水平方向基底ベクトル
	t_vect qy; // 画面垂直方向基底ベクトル
}							t_screen;

typedef struct s_sampling
{
	// bool				set;
	int count;     // samp;
	int max_count; // max_samp;
	// int					recursion_depth;
	// double				cosine;
	// double				light;
	// bool				gamma_correction;
}							t_sampling;

typedef struct s_camera
{
	t_vect pos; // coords;
	t_vect dir; // orient;
	t_vect					pos_initial;
	t_vect					dir_initial;
	size_t					fov;
	// float			scale;
	// t_obj_id	id;
}							t_camera;

typedef struct s_ambient
{
	float brightness; // lighting;
	t_color					color;
	// t_obj_id	id;
}							t_ambient;

typedef struct s_thread_data
{
	pthread_t				id;
	int						num;
	t_scene					*scene;
	void					*mlx_img;
}							t_thread;

struct						s_scene
{
	t_screen				screen;
	t_sampling				sampling;
	t_camera				camera;
	t_color					bg_color;
	t_ambient				ambient;

	t_list *lights; // t_light	*light;
	t_list *objs;   // t_obj	*objs;
	t_thread				thread[MAX_THREADS];

	int process; // レンダリング状況　heightで割って算出

	// int					lnum; データ解析用に別で定義する
	// int					pnum; データ解析用に別で定義する

	// float					width;
	// float					height;
	// float					aspectratio;
	// float					cam_matrix[4][4];
	// t_event			event;
	// int				display_info; デバッグプリント用
	// char			*path;  .rt file path
	// t_bool			is_processing;
	// pthread_mutex_t	process_lock;　ブロック単位で書き込むことによって競合しないようにできる
	// size_t				num_objs; lst_count(objects);を使う
	// char				*process_text; Linux用のレンダリング表示は表示しない
};

/* ************************************************************************** */
typedef struct s_image
{
	size_t					width;
	size_t					height;
	void					*img;
	char					*addr;
	int						bits_per_pixel;
	int						line_length;
	int						endian;
}							t_image;

typedef struct s_scene_with_mlx
{
	void					*mlx;
	void					*mlx_win;
	t_image					*mlx_img;
	t_scene					*scene;
}							t_scene_with_mlx;

// init_scene
void						init_scene(t_scene *scene);

// create_scene
t_binary_result				create_scene(t_scene *scene, const char *file_path);

// render_scene
t_binary_result				render_scene(t_scene *scene);
void						set_key_controls(t_scene_with_mlx *r_scene);
void						render_mlx_image(t_scene_with_mlx *r_scene);

// utils
void						free_scene(t_scene *scene);
void						free_scene_with_mlx(t_scene_with_mlx *scene_with_mlx);

#endif