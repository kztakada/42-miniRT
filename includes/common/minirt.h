/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 18:41:49 by katakada          #+#    #+#             */
/*   Updated: 2025/08/11 17:02:27 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "error.h"
# include "libft.h"
# include "mlx.h"
# include "settings.h"
# include <math.h>
# include <stdio.h>

// calculation constants
# define EPSILON 0.0001F
# define GIMBAL_LOCK_THRESHOLD 0.001F
# define FLT_MAX 3.40282347e+38F
# define FLT_EPSILON 1.19209290e-7F

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
# define KEY_Z 122
# define KEY_A 97
# define KEY_W 119
# define KEY_S 115
# define KEY_Q 113
# define KEY_E 101
# define KEY_H 104
# define KEY_G 103
# define KEY_B 98
# define KEY_V 118

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
	t_vector				pos;
	t_vector				pos_initial;
	float					brightness;
	float					brightness_initial;
	t_color					color;
	t_color					color_initial;
}							t_light;

/* ************************************************************************** */
typedef struct s_hit		t_hit;
typedef struct s_obj		t_obj;

typedef enum e_obj_dir_type
{
	VECTOR_DIR,
	UV_DIR,
}							t_obj_dir_type;

typedef enum e_obj_size_type
{
	SIZE_HEIGHT_UP,
	SIZE_HEIGHT_DOWN,
	SIZE_DIAMETER_UP,
	SIZE_DIAMETER_DOWN,
}							t_obj_size_type;

typedef struct s_obj_dir
{
	t_obj_dir_type			type;
	t_vector				*dir;
	float					*rotate_y;
}							t_obj_dir;

typedef struct s_texture
{
	size_t					width;
	size_t					height;
	t_color					*color;
	char					*file_path;
}							t_texture;

typedef struct s_material
{
	t_color					color;
	float					speckv;
	float					specn;
	float					mirror;
	t_texture				bump;
	t_texture				texture;
	t_bool					has_bump;
	t_bool					has_texture;
	t_bool					is_checkerboard;
	t_bool					is_bonus;
}							t_material;

typedef struct s_plane
{
	t_vector				pos;
	t_vector				dir;
	t_vector				pos_initial;
	t_vector				dir_initial;
}							t_plane;

typedef struct s_cylinder
{
	t_vector				pos;
	t_vector				dir;
	t_vector				pos_initial;
	t_vector				dir_initial;
	float					diameter;
	float					diameter_initial;
	float					height;
	float					height_initial;
	float					radius_pow2;
}							t_cylinder;

typedef struct s_sphere
{
	t_vector				pos;
	t_vector				pos_initial;
	float					diameter;
	float					diameter_initial;
	float					radius_pow2;
	float					rotation_y;
}							t_sphere;

typedef struct s_cone
{
	t_vector				pos;
	t_vector				dir;
	t_vector				pos_initial;
	t_vector				dir_initial;
	float					h;
	float					h2;
	float					h_initial;
	float					h2_initial;
	float					angle;
	float					angle_initial;
}							t_cone;

typedef union u_obj_shape
{
	t_sphere				sphere;
	t_plane					plane;
	t_cylinder				cylinder;
	t_cone					cone;
}							t_obj_shape;

typedef struct s_ray
{
	t_vector				pos;
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
typedef void				(*t_f_print_rt)(t_obj *obj);
typedef t_bool				(*t_f_change_size)(t_obj *obj,
					t_obj_size_type size_type);

// local coordinate system
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
	t_f_change_size			change_size;
	t_f_reset_obj			reset_obj;
	t_f_get_pos				get_pos;
	t_f_get_dir				get_dir;
	t_f_set_local_axes		set_local_xyz;
	t_f_print_rt			print_rt;
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
	t_vector				normal;
	t_vector				pos;
	float					t;
	t_color					color;
	t_vector				pov_dir;
};

// pov_ray is the "point of view ray"
typedef struct s_raytracing
{
	t_ray					pov_ray;
	t_ray					to_light_src_ray;
	t_hit					hit;
	t_hit					blocking_hit;
	t_obj					*closest_obj;
}							t_raytracing;

typedef struct s_lighting
{
	t_color					ambient;
	t_color					diffuse;
	t_color					specular;
	t_color					reflect;
}							t_lighting;

/* ************************************************************************** */

typedef struct s_scene		t_scene;

/* screen.pos is screen right up corner */
// x_per_pixel: the vector to move one pixel right
// x_half: the half of the screen width from the center to the right up
// y_per_pixel: the vector to move one pixel down
// y_half: the half of the screen height from the center to the right up
typedef struct s_screen
{
	size_t					width;
	size_t					height;
	t_color					*dots;
	t_vector				pos;
	t_vector				x_per_pixel;
	t_vector				y_per_pixel;
	t_vector				x_half;
	t_vector				y_half;
}							t_screen;

typedef struct s_sampling
{
	int						count;
	int						max_count;
}							t_sampling;

typedef struct s_camera
{
	t_vector				pos;
	t_vector				dir;
	t_vector				pos_initial;
	t_vector				dir_initial;
	size_t					fov;
}							t_camera;

typedef struct s_ambient
{
	float					brightness;
	t_color					color;
}							t_ambient;

struct						s_scene
{
	t_screen				screen;
	t_sampling				sampling;
	t_camera				camera;
	t_color					bg_color;
	t_ambient				ambient;

	t_list					*lights;
	t_list					*objs;
	t_bool					is_bonus;
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
	t_bool					is_console;
	t_bool					is_modified;
}							t_key_control;

typedef struct s_scene_with_mlx
{
	void					*mlx;
	void					*mlx_win;
	t_image					*mlx_img;
	t_scene					*scene;
	t_key_control			key;
}							t_scene_with_mlx;

// create_scene
t_binary_result				create_scene(t_scene *scene, const char *file_path);
t_binary_result				parse_one_line_on_scene(t_scene *scene, char *line,
								t_parse *format_info);
t_binary_result				parse_ambient(t_scene *scene, char **line_element,
								t_parse *format_info);
t_binary_result				parse_camera(t_scene *scene, char **line_element,
								t_parse *format_info);
t_binary_result				parse_light(t_scene *scene, char **line_element,
								t_parse *format_info, t_bool is_bonus);

t_binary_result				set_color(t_color *color, char *str_color);
void						set_vector(t_vector *vector, char *str_vector);
t_binary_result				set_material_common(t_obj *obj, char **line_element,
								char *type);
t_binary_result				parse_obj(t_scene *scene, char **line_element);
t_binary_result				parse_obj_sphere(char **line_element, t_obj *obj,
								t_bool is_bonus);
t_binary_result				parse_obj_plane(char **line_element, t_obj *obj,
								t_bool is_bonus);
t_binary_result				parse_obj_cylinder(char **line_element, t_obj *obj,
								t_bool is_bonus);
t_binary_result				parse_obj_cone(char **line_element, t_obj *obj,
								t_bool is_bonus);

t_binary_result				set_spec_mirror(t_obj *obj, char *str);
t_binary_result				format_check_ambient(char **line_element,
								t_parse *format_info);
t_binary_result				format_check_camera(char **line_element,
								t_parse *format_info);
t_binary_result				format_check_light(char **line_element,
								t_parse *format_info);
t_binary_result				format_check_lights_bonus(char **line_element,
								t_parse *format_info);
t_binary_result				format_check_sphere(char **line_element,
								t_bool is_bonus);
t_binary_result				format_check_plane(char **line_element,
								t_bool is_bonus);
t_binary_result				format_check_cylinder(char **line_element,
								t_bool is_bonus);
t_binary_result				format_check_cone(char **line_element,
								t_bool is_bonus);

t_binary_result				is_number_int(char *element);
t_binary_result				is_positive_int(char *element);
t_binary_result				is_number_float(char *element);
t_binary_result				is_positive_float(char *element);
t_binary_result				is_number_float_three_dimensional(char *element);
t_binary_result				is_positive_float_three_dimensional(char *element);
t_binary_result				is_positive_int_three_dimensional(char *element);
int							element_count(char **line_element);
t_bool						is_valid_num_of_element(int num_element,
								int required, t_bool is_bonus);
t_color						mix_colors_by_ratio(t_color c1, t_color c2,
								float c1_ratio);
t_color						add_lighting(t_color base, t_color light,
								float intensity);

// key_controls
void						set_key_controls(t_scene_with_mlx *r_scene);
void						press_arrow_key(t_scene_with_mlx *r_scene,
								int keycode);
void						press_move_key(t_scene_with_mlx *r_scene,
								int keycode);
void						reset_selected_mode_target(
								t_scene_with_mlx *r_scene);
void						reset_scene_all(t_scene_with_mlx *r_scene);
void						select_next_light(t_scene_with_mlx *r_scene);
void						select_prev_light(t_scene_with_mlx *r_scene);
void						move_foward(t_vector *pos, t_scene *scene);
void						move_backward(t_vector *pos, t_scene *scene);
void						move_left(t_vector *pos, t_scene *scene);
void						move_right(t_vector *pos, t_scene *scene);
void						rotate_left(t_mode_select mode, t_vector *dir,
								t_scene *scene);
void						rotate_right(t_mode_select mode, t_vector *dir,
								t_scene *scene);
void						rotate_up(t_mode_select mode, t_vector *dir,
								t_scene *scene);
void						rotate_down(t_mode_select mode, t_vector *dir,
								t_scene *scene);
void						rotate_uv_right(float *rotate_y);
void						rotate_uv_left(float *rotate_y);
void						color_up(t_color *color);
void						color_down(t_color *color);
void						grighten_up(float *brightness);
void						grighten_down(float *brightness);
void						toggle_console(t_scene_with_mlx *r_scene);
void						press_utils_key(t_scene_with_mlx *r_scene,
								int keycode);

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
t_hit						set_hit_info(float t, t_ray *ray);
t_hit						get_nearest_hit(t_hit *hits, int hit_count);
t_hit						calc_disk_obj_hit(t_vector center, t_vector normal,
								float radius2, t_ray *ray);

t_color						get_color(t_obj *obj, t_hit *hit);
t_color						get_sphere_texture_color(t_obj *obj, t_hit *hit);
t_color						get_plane_texture_color(t_obj *obj, t_hit *hit);
t_color						get_cylinder_texture_color(t_obj *obj, t_hit *hit);
t_color						get_cone_texture_color(t_obj *obj, t_hit *hit);
t_color						get_sphere_checker_color(t_obj *obj, t_hit *hit);
t_color						get_plane_checker_color(t_obj *obj, t_hit *hit);
t_color						get_cylinder_checker_color(t_obj *obj, t_hit *hit);
t_color						get_cone_checker_color(t_obj *obj, t_hit *hit);

float						solve_quadratic(float a, float b, float c);

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

void						reset_object_sphere(t_obj *obj);
void						reset_object_plane(t_obj *obj);
void						reset_object_cylinder(t_obj *obj);
void						reset_object_cone(t_obj *obj);

void						set_local_xyz_sphere(t_obj *obj,
								t_vector *camera_dir);
void						set_local_xyz_plane(t_obj *obj,
								t_vector *camera_dir);
void						set_local_xyz_cylinder(t_obj *obj,
								t_vector *camera_dir);
void						set_local_xyz_cone(t_obj *obj,
								t_vector *camera_dir);

void						print_rt_sphere(t_obj *obj);
void						print_rt_plane(t_obj *obj);
void						print_rt_cylinder(t_obj *obj);
void						print_rt_cone(t_obj *obj);

t_bool						change_sphere_size(t_obj *obj,
								t_obj_size_type type);
t_bool						change_plane_size(t_obj *obj, t_obj_size_type type);
t_bool						change_cylinder_size(t_obj *obj,
								t_obj_size_type type);
t_bool						change_cone_size(t_obj *obj, t_obj_size_type type);

void						calc_sphere_uv_map_xy(t_obj *obj,
								t_vector target_pos, float *uv_map);
void						calc_sphere_uv_map_equirectangular(t_obj *obj,
								t_vector hit_pos, float *uv, float rotation_y);
void						calc_plane_uv_map_xy(t_obj *obj,
								t_vector target_pos, float *uv_map);
void						calc_plane_uv_map_tiling(t_obj *obj,
								t_vector target_pos, float *uv);
void						calc_stretch_mapping_uv(t_vector local_pos,
								t_vector axis, float height, float *uv);
void						calc_cone_stretch_mapping_uv(t_cone *cone,
								float axis_projection, t_vector local_pos,
								float *uv);
t_uv						calc_bump_effects(t_obj *obj, t_pos2d bump_dot,
								t_uv ref_scale);
t_vector					calc_bumped_normal(t_obj *obj,
								t_vector default_normal, t_uv bump_delta);
t_bool						handle_gimbal_lock_uv_axes(t_vector default_normal,
								t_vector *axis_u, t_vector *axis_v);

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
void						set_default_scene_common(t_scene *scene);
void						set_screen_pos(t_scene *scene);
void						setup_camera_screen(t_scene *scene);
void						setup_scene(t_scene *scene);
void						set_local_axes(t_scene *scene);

// which_use_mandatory_or_bonus
t_vector					calc_screen_dot_pos(t_scene *scene, int x, int y);
t_binary_result				run_renderer(t_scene *scene);
t_binary_result				set_material(t_obj *obj, char **line_element,
								char *type);
void						print_console(t_scene_with_mlx *r_scene);

// util_foundation
t_vector					up_dir(void);
t_vector					right_dir(void);
t_vector					forward_dir(void);
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
t_vector					calc_rodrigues_rotation(t_vector current_dir,
								t_vector rotation_axis, float angle);
t_color						add_colors(t_color c1, t_color c2);
t_color						scale_color(float coefficient, t_color c1);
t_color						multiply_colors(t_color c1, t_color c2);
float						clamp_color(float color_value, float limit_min,
								float limit_max);
int							color_to_int_rgb(t_color color);
t_color						get_opposite_color(t_color color);
int							get_24bit_color(t_color *color);
t_color						get_rgb_color(int color);
void						print_rgb_color(t_color color);
void						print_rgb_color_info(t_color color);
int							clamp_int(int value, int min, int max);
float						clampf(float value, float min, float max);

// utils
void						free_scene(t_scene *scene);
void						free_scene_with_mlx(
								t_scene_with_mlx *scene_with_mlx);
t_binary_result				put_out_failure(char *err_msg);
t_binary_result				put_out_format_error(char *type, char *err_msg);
t_vector					put_out_error_vector(char *err_msg);
t_color						put_out_error_color(char *err_msg);
t_hit						put_out_error_hit(char *err_msg);
t_obj						*get_obj(t_list *obj);
t_light						*get_light(t_list *light);
t_bool						is_normal_range(t_vector normal);

#endif