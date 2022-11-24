/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mawinter <mawinter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 03:09:40 by marius            #+#    #+#             */
/*   Updated: 2022/11/24 20:02:32 by mawinter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_H
# define INPUT_H

#include "../utility/utils.h"
#include "../objects/objects.h"
/*						Input Errors									*/

#define A_WRONG_NUM_FIELDS "Error\nAmbient Light: Wrong Number Of Fields\n"
#define C_WRONG_NUM_FIELDS "Error\nCamera: Wrong Number Of Fields\n"
#define L_WRONG_NUM_FIELDS "Error\nLight: Wrong Number Of Fields\n"
#define SP_WRONG_NUM_FIELDS "Error\nSphere: Wrong Number Of Fields\n"
#define PL_WRONG_NUM_FIELDS "Error\nPlane: Wrong Number Of Fields\n"
#define CY_WRONG_NUM_FIELDS "Error\nCylinder: Wrong Number Of Fields\n"


#define MANY_DECIMAL "Error\nNumber Can Only Contain One Decimal Point\n"
#define RANGE "Error\nNumber Not In Range\n"
#define MALLOC_FAIL "Error\nMalloc Fail\n"
#define TRAIL_DECIMAL_POINT "Error\nCan't Have Leading Or Trailing Decimal Points\n"
#define WRONG_CHAR "Error\nWrong Specifier\n"
#define NUM3 "Error\nColors Have To Be 3 Numbers\n"
#define	MINUS_POS "Error\nMinus At The Wrong Position\n"
#define	NO_FLOAT "Error\nNumber Needs To Be An Integer\n"
#define SPECIFIIER "Error\nWrong Element Type\n"
#define DECLAREDOUBLE "Error\nDouble Declaration Of Element Which Can Only Exist Once\n"
/*					input.c						*/
int	valid_input(char *filename);
/*					input_utils.c				*/
int	i_identifier(char **identifiers, char *identifier);
/*					input_check_element.c				*/
int	valid_ambient(char *line);
int	valid_camera(char *line);
int	valid_light(char *line);
int	valid_sphere(char *line);
int	valid_plane(char *line);
/*					input_check_element2.c				*/
int	valid_cylinder(char *line);
/*					ft_atod.c				*/
double   ft_atod(char *field);
/*					in_range.c				*/
int	in_range(double value, double min, double max);
/*					get_field.c				*/
int	fields_count(char **fields);
int	valid_triple_field(char *field, double min, double max, int is_in);
double	ret_num(int *dotcount, char *field, double range[2], int is_int);
double	get_num(char *field, double min, double max, int is_int);
/*					get_scene.c				*/

t_scene	*get_scene(char *filename);


//
void	ft_objadd_back(t_object **lst, t_object *new);
int	ft_objsfree(t_object *lst);
t_object	*ft_objnew();
t_object *ft_objat(t_object *head, int idx);
int	ft_lstsize(t_object *lst);


#endif