/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyahyao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 14:05:56 by anyahyao          #+#    #+#             */
/*   Updated: 2019/07/02 22:27:04 by anyahyao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# include "op.h"
# include "../ft_printf/includes/ft_printf.h"
# include "../ft_printf/libft/inc/libft.h"
# include "get_next_line.h"
# include <limits.h>
# include <fcntl.h>

# define NUMBERMAX_ERROR 5
# define BUFFER_TOKENS 100
# define BUFFER_LABELS CHAMP_MAX_SIZE / 2
# define SIZEMAX_STRING 2048

typedef struct		s_op
{
	char			*operation;
	int				number_param;
	int				tab[3];
	int				id;
	int				cycle;
	char			*comment;
	int				val1;
	int				val2;
	int				val3;
}					t_op;

typedef struct		s_fichier
{
	int				fd_in;
	int				fd_out;
	char			*file_name;
	char			*line;
	int				line_nb;
}					t_fichier;

typedef enum		e_type
{
	NAME,
	COMMENT,
	STRING,
	LABEL,
	INSTRUCTION,
	SEPARATOR,
	REGISTER,
	DIRECT_LABEL,
	DIRECT,
	INDIRECT,
	INDIRECT_LABEL,
	UNKNOWN,
	EMPTY,
}					t_type;

typedef union		u_value
{
	t_op			*operation;
	int				number;
	char			*data;
}					t_value;

typedef struct		s_token
{
	t_type			type;
	t_value			value;
	int				line;
	int				pos;
	struct s_token	*param[3];
}					t_token;

typedef struct		s_champion
{
	header_t		*header;
	t_token			**tokens;
	int				number_token;

	int				labels[BUFFER_LABELS];
	int				number_labels;

	int				instructions[CHAMP_MAX_SIZE];
	int				number_instructions;

	int				size;
	int				hasname;
	int				hascomment;
	int				number_error;
	int				number_warning;

	unsigned char	prog[CHAMP_MAX_SIZE * 2];
}					t_champion;

extern				t_op g_op_tab[17];

/*
** Autres
*/

int					size_token(int t, int id);
int					get_instruction(t_champion *champion, unsigned char *prog);

/*
**=======================PROTO========================
** libft a ajoute
*/

char				*ft_strnjoin(char *s1, char *s2, int size);
int					manage_label_param(t_champion *champion, char *str);

/*
** test.c
*/

# define MODETOKEN 1
# define MODEREEL 2

int					affichetype(int type);
int					test_champion(t_champion *champion, int mode);
int					affichelabels(t_champion *champion);

/*
** write_champion.c
*/

int					create_champion(t_fichier *file, t_champion *champion);
int					already_label(t_champion *c, char *str, int s);
long long			convert_bigendian(long long val, unsigned int size);

/*
** write_champion.c
*/

int					write_champion_prog(t_champion *champion, char *str);

/*
** error.c
*/

void				malloc_error(char *str);
void				exit_msg(char *str);

/*
** init.c
*/

t_fichier			*init_file();
t_champion			*init_champion();
header_t			*init_header(t_champion *champion);

/*
** check.c
*/

int					check_instruction(t_champion *c, t_token *token, int pos,
											int tok_line);
int					verify_champion_line(t_champion *c, int t, int deb,
											int tok_line);
void				check_label(t_champion *c, t_token *t, int deb,
											int tok_line);

/*
** token.c
*/

t_token				*add_token_operation(t_token *token, char *s);
t_token				*add_token_string(t_token *token, char *str);
t_token				*add_token_integer(t_token *token, int value);
t_token				*create_token(t_champion *champion, int line_nb, int type);
void				add_token(t_token *token, t_champion *champion);
int					size_token(int t, int id);

/*
** get_token.c
*/

t_token				*get_direct_token(t_champion *champion, int line, char *s);
t_token				*get_token(t_champion *c, char *s, int end, int line_nb);
int					move_token(t_token **token, t_token **t);

/*
** verify.c
*/

int					search_label(t_champion *c, char *s);
int					verify_champion(t_champion *c);
int					error_champion(t_champion *champion, char *s, int line);
void				delete_token(t_token *token);
int					warning_champion(t_champion *champion, char *s, int line);

/*
** recognize.c
*/

int					islabel(char *s);
int					isdirect(char *s);
int					isintruction(char *s);
int					isindirect_label(char *s);
int					isregister(char *s);
int					ft_isinteger(char *s);
int					compose_withthese_letters(char *word, char *letters);

/*
** parsing.c
*/

int					parsing(t_fichier *file, t_champion *champion);
char				*string_exeption(t_fichier *f, char *line);

/*
** free.c
*/

void				free_token(t_token **token);
void				free_file(t_fichier **file);
void				free_champion(t_champion **champion);

#endif
