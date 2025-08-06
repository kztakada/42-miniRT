/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 18:41:49 by katakada          #+#    #+#             */
/*   Updated: 2025/08/06 18:53:00 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "error.h"
# include "libft.h"
# include "mlx.h"
# include "settings.h"
# include <float.h>
# include <math.h>
# include <stdio.h>

// calculation constants
# define EPSILON 0.0001F
# define GIMBAL_LOCK_THRESHOLD 0.001f

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
# define KEY_W 119
# define KEY_S 115
# define KEY_Q 113
# define KEY_E 101
# define KEY_O 111

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

typedef struct s_parse
{
	t_bool					ambient;
	t_bool					camera;
	t_bool					large_light;
	int						light_count;
}							t_parse;

/* ************************************************************************** */

typedef struct s_color
{
	float					r;
	float					g;
	float					b;
}							t_color;

typedef struct s_vector
{
	float					x;
	float					y;
	float					z;
}							t_vector;

/* ************************************************************************** */

typedef struct s_pos2d
{
	int						x;
	int						y;
}							t_pos2d;

typedef struct s_uv
{
	float					u;
	float					v;
}							t_uv;

typedef struct s_dir4
{
	int						left;
	int						right;
	int						up;
	int						down;
}							t_dir4;

typedef struct s_dir4_f
{
	float					left;
	float					right;
	float					up;
	float					down;
}							t_dir4_f;

typedef struct s_dir4_pos
{
	t_pos2d					left;
	t_pos2d					right;
	t_pos2d					up;
	t_pos2d					down;
}							t_dir4_pos;

/* ************************************************************************** */

typedef struct s_light
{
	t_vector pos; // coords;
	t_vector				pos_initial;
	float					brightness;
	float					brightness_initial;
	t_color					color;
	// struct s_light	*next;
	// t_obj_id		id;
}							t_light;

/* ************************************************************************** */
typedef struct s_hit		t_hit;
typedef struct s_obj		t_obj;

typedef enum e_obj_dir_type
{
	VECTOR_DIR,
	UV_DIR,
}							t_obj_dir_type;

typedef struct s_obj_dir
{
	t_obj_dir_type			type;
	t_vector				*dir;
	float					*rotate_y;
}							t_obj_dir;

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
	t_vector pos; // coords;
	t_vector dir; // orient;
	t_vector				pos_initial;
	t_vector				dir_initial;
	// t_color		color;
}							t_plane;

typedef struct s_cylinder
{
	// t_obj_id	id;
	t_vector pos; // coords;
	t_vector dir; // orient;
	t_vector				pos_initial;
	t_vector				dir_initial;
	float					diameter;
	float					height;
	float radius_pow2; // r2;
	t_vector				p1;
	t_vector				p2;
	t_vector				delta_p;
	// t_color		color;
}							t_cylinder;

typedef struct s_sphere
{
	// t_obj_id	id;
	t_vector pos; // coords;
	t_vector				pos_initial;
	float					diameter;
	float radius_pow2; // r2;
	float					rotation_y;
	// float					rotation_x;
	// t_color		color;
}							t_sphere;

typedef struct s_triangle
{
	// t_obj_id	id;
	t_vector c[3]; // triangleはinitial定義なし;
	t_vector				edge[3];
	t_vector				n;
	// t_color		color;
	float					area2;
}							t_triangle;

typedef struct s_cone
{
	// t_obj_id	id;
	t_vector pos; // coords;
	t_vector dir; // orient;
	t_vector				pos_initial;
	t_vector				dir_initial;
	float					h;
	float h2; // opposite
	float					angle;
	float					cos2;
	t_vector				c1;
	t_vector				c2;
	float					r1;
	float					r2;
	// t_color		color;
}							t_cone;

typedef struct s_torus
{
	// t_obj_id	id;
	t_vector pos; // coords;
	t_vector dir; // orient;
	t_vector				pos_initial;
	t_vector				dir_initial;
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
	t_vector pos; // or;
	t_vector				dir;
}							t_ray;

typedef t_hit				(*t_f_calc_obj_hit)(t_obj *obj, t_ray *pov_ray);
typedef t_vector			(*t_f_calc_normal)(t_obj *obj, t_hit *hit);
typedef t_color				(*t_f_get_color)(t_obj *obj, t_hit *hit);
typedef void				(*t_f_print_focused_obj)(t_obj *obj);
typedef void				(*t_f_reset_obj)(t_obj *obj);
typedef t_vector			*(*t_f_get_pos)(t_obj *obj);
typedef t_obj_dir			(*t_f_get_dir)(t_obj *obj);
typedef void				(*t_f_set_local_axes)(t_obj *obj,
					t_vector *camera_dir);

// ローカル座標系
typedef struct s_local_axes
{
	t_vector				x;
	t_vector				y;
	t_vector				z;
}							t_local_axes;

struct						s_obj
{
	t_material				material;
	t_obj_shape				shape;
	t_bool					has_volume;
	t_local_axes			local;
	t_f_calc_obj_hit		calc_obj_hit;
	t_f_calc_normal			calc_normal;
	t_f_get_color			get_color;
	t_f_print_focused_obj	print_focused_obj;
	t_f_reset_obj			reset_obj;
	t_f_get_pos				get_pos;
	t_f_get_dir				get_dir;
	t_f_set_local_axes		set_local_xyz;

	// t_vector			coords; uv作成で使用するが、t_f_get_colorで初期化時に定義する
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
};

/* ************************************************************************** */

typedef struct s_quadratic_solution
{
	float					discriminant;
	float					t1;
	float					t2;
}							t_quadratic_solution;

/* ************************************************************************** */

struct						s_hit
{
	t_bool					is_hit;
	t_vector normal; // nhit;
	t_vector pos;    // phit;
	float					t;
	t_color					color;
	t_vector				pov_dir;
};

// pov_ray is the "point of view ray"
typedef struct s_raytracing
{
	t_ray pov_ray; // prime_ray;
	t_ray					to_light_src_ray;
	t_hit					hit;
	t_hit					blocking_hit;
	t_obj					*closest_obj;
	float					refract_index;
}							t_raytracing;

typedef struct s_lighting
{
	t_color					ambient;
	t_color					diffuse;
	t_color					specular;
	t_color					reflect;
	t_color					refract;
	// int						is_shadow;
}							t_lighting;

/* ************************************************************************** */

typedef struct s_scene		t_scene;

/* screen.pos is screen right up corner */
typedef struct s_screen
{
	// bool				res_set;
	size_t					width;
	size_t					height;
	t_color *dots; // *pixel;
	t_vector				pos;
	t_vector x_per_pixel; // ピクセル単位の変換用ベクトル
	t_vector y_per_pixel; // ピクセル単位の変換用ベクトル
	t_vector x_half;      // スクリーンの半分の水平方向の３次元的な傾き
	t_vector y_half;      // スクリーンの半分の垂直方向の３次元的な傾き
}							t_screen;

typedef struct s_sampling
{
	// bool				set;t
	int count;     // samp;
	int max_count; // max_samp;
					// int					recursion_depth;
					// double				cosine;
					// double				light;
					// bool				gamma_correction;
}							t_sampling;

typedef struct s_camera
{
	t_vector pos; // coords;
	t_vector dir; // orient;
	t_vector				pos_initial;
	t_vector				dir_initial;
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

struct						s_scene
{
	t_screen				screen;
	t_sampling				sampling;
	t_camera				camera;
	t_color					bg_color;
	t_ambient				ambient;

	t_list *lights; // t_light	*light;
	t_list *objs;   // t_obj	*objs;
					// t_thread_data			thread[MAX_THREADS];

	// int process; // レ��ダリング状況　heightで割って算出

	// int					lnum; データ解析用に別で定義す�������������������������
	// int					pnum; データ解析用に別で定義する

	// float					width;
	// float					height;
	// float					aspectratio;
	// float					cam_matrix[4][4];
	// t_event			event;
	// int				display_info; デバッグプリ�������������������ト���
	// char			*path;  .rt file path
	// t_bool			is_processing;
	// pthread_mutex_t	process_lock;　ブロック単位で書き込むことによって競合しないようにできる
	// size_t				num_objs; lst_count(objects);を使う
	// char				*process_text; Linux用のレンダリング����示は表示しない
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

typedef enum e_mode_select
{
	CAMERA_MODE = 0,
	LIGHT_MODE = 1,
	OBJECT_MODE = 2,
}							t_mode_select;

typedef struct s_key_control
{
	t_list					*first_index_obj;
	t_obj					*selected_obj;
	t_list					*first_index_light;
	int						selected_light_index;
	t_list					*selected_light;
	t_mode_select			mode;
}							t_key_control;

typedef struct s_scene_with_mlx
{
	void					*mlx;
	void					*mlx_win;
	t_image					*mlx_img;
	t_scene					*scene;
	t_key_control			key;
}							t_scene_with_mlx;

// set_default_scene
void						set_default_scene(t_scene *scene);

// create_scene
t_binary_result				create_scene(t_scene *scene, const char *file_path);

// key_controls
void						set_key_controls(t_scene_with_mlx *r_scene);
void						press_arrow_key(t_scene_with_mlx *r_scene,
								int keycode);
void						press_move_key(t_scene_with_mlx *r_scene,
								int keycode);
void						reset_selected_mode_target(t_scene_with_mlx *r_scene);
void						reset_scene_all(t_scene_with_mlx *r_scene);
void						select_next_light(t_scene_with_mlx *r_scene);
void						select_prev_light(t_scene_with_mlx *r_scene);
void						move_foward(t_vector *pos, t_scene *scene);
void						move_backward(t_vector *pos, t_scene *scene);
void						move_left(t_vector *pos, t_scene *scene);
void						move_right(t_vector *pos, t_scene *scene);
void						rotate_left(t_vector *dir, t_scene *scene);
void						rotate_right(t_vector *dir, t_scene *scene);
void						rotate_up(t_vector *dir, t_scene *scene);
void						rotate_down(t_vector *dir, t_scene *scene);
void						rotate_uv_right(float *rotate_y);
void						rotate_uv_left(float *rotate_y);
void						color_up(t_color *color);
void						color_down(t_color *color);

// render_scene_to_mlx
void						reset_rendering_scene(t_scene *scene);
t_binary_result				render_scene_to_mlx(t_scene *scene);
void						render_mlx_image(t_scene_with_mlx *r_scene);
t_color						raytracing(t_scene *scene, t_raytracing *rt,
								int depth);
t_color						raytrace_at_dot(t_scene *scene, t_vector dot_pos);
t_vector					convert_xy_pos_to_xyz_vector(float x, float y,
								t_scene *scene);
t_obj						*calc_closest_obj(t_list *objs, t_ray *pov_ray,
								t_hit *hit);
void						calc_lights_effect(t_scene *scene, t_raytracing *rt,
								t_lighting *lighting);
void						print_rendering_console(t_scene_with_mlx *r_scene);

// setup_scene
void						set_screen_pos(t_scene *scene);
void						setup_camera_screen(t_scene *scene);
void						setup_scene(t_scene *scene);
void						set_local_axes(t_scene *scene);

// which_use_mandatory_or_bonus
t_vector					calc_screen_dot_pos(t_scene *scene, int x, int y);
t_binary_result				run_renderer(t_scene *scene);
t_binary_result				set_material(t_obj *obj, char **line_element,
								int start_index);

// obj_funcs
t_vector					calc_sphere_normal(t_obj *obj, t_hit *hit);
t_vector					calc_sphere_bump_normal(t_obj *obj, t_hit *hit);
t_vector					calc_plane_normal(t_obj *obj, t_hit *hit);
t_vector					calc_plane_bump_normal(t_obj *obj, t_hit *hit);
t_vector					calc_cylinder_normal(t_obj *obj, t_hit *hit);
t_vector					calc_cylinder_bump_normal(t_obj *obj, t_hit *hit);
t_vector					calc_cone_normal(t_obj *obj, t_hit *hit);
t_vector					calc_cone_bump_normal(t_obj *obj, t_hit *hit);

t_hit						get_zero_hit(void);
t_hit						calc_sphere_obj_hit(t_obj *obj, t_ray *pov_ray);
t_hit						calc_plane_obj_hit(t_obj *obj, t_ray *pov_ray);
t_hit						calc_cylinder_obj_hit(t_obj *obj, t_ray *pov_ray);
t_hit						calc_cone_obj_hit(t_obj *obj, t_ray *pov_ray);

t_color						get_color(t_obj *obj, t_hit *hit);
t_color						get_sphere_texture_color(t_obj *obj, t_hit *hit);
t_color						get_plane_texture_color(t_obj *obj, t_hit *hit);
t_color						get_cylinder_texture_color(t_obj *obj, t_hit *hit);
t_color						get_cone_texture_color(t_obj *obj, t_hit *hit);
t_color						get_sphere_checker_color(t_obj *obj, t_hit *hit);
t_color						get_plane_checker_color(t_obj *obj, t_hit *hit);
t_color						get_cylinder_checker_color(t_obj *obj, t_hit *hit);
t_color						get_cone_checker_color(t_obj *obj, t_hit *hit);

void						print_focused_obj_sphere(t_obj *obj);
void						print_focused_obj_plane(t_obj *obj);
void						print_focused_obj_cylinder(t_obj *obj);
void						print_focused_obj_cone(t_obj *obj);

t_vector					*get_sphere_pos(t_obj *obj);
t_vector					*get_plane_pos(t_obj *obj);
t_vector					*get_cylinder_pos(t_obj *obj);
t_vector					*get_cone_pos(t_obj *obj);

t_obj_dir					get_sphere_dir(t_obj *obj);
t_obj_dir					get_plane_dir(t_obj *obj);
t_obj_dir					get_cylinder_dir(t_obj *obj);
t_obj_dir					get_cone_dir(t_obj *obj);

void						set_local_xyz_sphere(t_obj *obj,
								t_vector *camera_dir);
void						set_local_xyz_plane(t_obj *obj,
								t_vector *camera_dir);
void						set_local_xyz_cylinder(t_obj *obj,
								t_vector *camera_dir);
void						set_local_xyz_cone(t_obj *obj,
								t_vector *camera_dir);

void						calc_sphere_uv_map_xy(t_obj *obj,
								t_vector target_pos, float *uv_map);
void						calc_sphere_uv_map_equirectangular(t_obj *obj,
								t_vector hit_pos, float *uv, float rotation_y);
void						calc_plane_uv_map_xy(t_obj *obj,
								t_vector target_pos, float *uv_map);
void						calc_plane_uv_map_tiling(t_obj *obj,
								t_vector target_pos, float *uv);
void						calc_cylinder_uv_map_xy(t_obj *obj,
								t_vector target_pos, float *uv_map);
void						calc_stretch_mapping_uv(t_vector local_pos,
								t_vector axis, float height, float *uv);
void						calc_cone_uv_map_xy(t_obj *obj, t_vector target_pos,
								float *uv_map);
t_uv						calc_bump_effects(t_obj *obj, t_pos2d bump_dot,
								t_uv ref_scale);
t_vector					calc_bumped_normal(t_obj *obj,
								t_vector default_normal, t_uv bump_delta);
t_bool						handle_gimbal_lock_uv_axes(t_vector default_normal,
								t_vector *axis_u, t_vector *axis_v);

// util_foundation
t_vector					up_dir(void);
t_vector					right_dir(void);
t_vector					add_vectors(t_vector a, t_vector b);
t_vector					sub_vectors(t_vector a, t_vector b);
t_vector					scale_vector(float scalar, t_vector v);
t_vector					normalize_vector(t_vector v);
t_vector					cross_vector(t_vector a, t_vector b);
float						vector_len(t_vector v);
float						calc_distance(t_vector a, t_vector b);
float						vectors_dot(t_vector a, t_vector b);
t_vector					inverse_vector(t_vector v);
t_vector					get_ray_pos_at_t(t_ray ray, float t);
t_vector					calc_reflection_vector(t_vector incident,
								t_vector normal);
t_vector					calc_refraction_vector(t_vector incident,
								t_vector normal, float n1, float n2);
t_color						add_colors(t_color c1, t_color c2);
t_color						scale_color(float coefficient, t_color c1);
t_color						multiply_colors(t_color c1, t_color c2);
float						clamp_color(float color_value, float limit_min,
								float limit_max);
int							color_to_int_rgb(t_color color);
t_color						get_opposite_color(t_color color);
int							clamp_int(int value, int min, int max);
float						clampf(float value, float min, float max);

// parse
t_binary_result				parse(t_scene *scene, const char *file_path);
t_binary_result				recognize_type_identifiers(t_scene *scene,
								char *line, t_parse *format_info);
t_binary_result				set_color(t_color *color, char *str_color);
t_binary_result				set_vector(t_vector *vector, char *str_vector);
t_binary_result				set_material_common(t_obj *obj, char **line_element,
								int start_index);
t_binary_result				config_objs(t_scene *scene, char **line_element);
t_binary_result				config_sphere(char **line_element, t_obj *obj);
t_binary_result				config_plane(char **line_element, t_obj *obj);
t_binary_result				config_cylinder(char **line_element, t_obj *obj);
t_binary_result				set_spec_mirror(t_obj *obj, char *str);
t_binary_result				set_material_default(t_obj *obj);
t_binary_result				format_check_ambient(char **line_element,
								t_parse *format_info);
t_binary_result				format_check_camera(char **line_element,
								t_parse *format_info);
t_binary_result				format_check_light(char **line_element,
								t_parse *format_info);
t_binary_result				format_check_sphere(char **line_element);
t_binary_result				format_check_plane(char **line_element);
t_binary_result				format_check_cylinder(char **line_element);
t_binary_result				is_number_int(char *element);
t_binary_result				is_number_float(char *element);
t_binary_result				is_number_float_three_dimensional(char *element);
int							element_count(char **line_element);
t_color						mix_colors_by_ratio(t_color c1, t_color c2,
								float c1_ratio);
t_color						add_lighting(t_color base, t_color light,
								float intensity);

// utils
void						free_scene(t_scene *scene);
void						free_scene_with_mlx(t_scene_with_mlx *scene_with_mlx);
t_binary_result				put_out_failure(char *err_msg);
t_binary_result				put_out_format_error(char *type, char *err_msg);
t_vector					put_out_error_vector(char *err_msg);
t_color						put_out_error_color(char *err_msg);
t_hit						put_out_error_hit(char *err_msg);
t_obj						*get_obj(t_list *obj);
t_light						*get_light(t_list *light);

#endif