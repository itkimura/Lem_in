/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thle <thle@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 16:29:01 by itkimura          #+#    #+#             */
/*   Updated: 2022/11/09 10:37:47 by thle             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

char	*ft_strcat(char *s1, const char *s2)
{
	int	dstlen;
	int	i;

	i = 0;
	dstlen = ft_strlen(s1);
	while (s2[i])
	{
		s1[dstlen + i] = s2[i];
		i++;
	}
	s1[dstlen + i] = '\0';
	return (s1);
}
