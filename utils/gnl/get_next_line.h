/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlinarez <jlinarez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 11:11:10 by jlinarez          #+#    #+#             */
/*   Updated: 2024/08/12 12:40:01 by jlinarez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42 
# endif

# include <stdlib.h>
# include <unistd.h>
# include <limits.h>

/*
** Funciones auxiliares para manipulación de cadenas
*/
int		ft_strlen12(char *s);
char	*ft_strchr12(char *s, int c);
void	*ft_calloc12(size_t count, size_t size);
char	*ft_strjoin12(char *s1, char *s2);

/*
** Función principal para obtener la siguiente línea de un descriptor de archivo
*/
char	*get_next_line(int fd);

#endif
