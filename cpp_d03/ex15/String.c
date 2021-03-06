/*
** String.c for String in /home/guillaume2.roux/rendu/cpp_d03/ex00
** 
** Made by Guillaume Roux
** Login   <guillaume2.roux@epitech.net>
** 
** Started on  Fri Jan  6 08:03:36 2017 Guillaume Roux
** Last update Fri Jan  6 08:03:38 2017 Guillaume Roux
*/

#include "String.h"
#include <string.h>
#include <unistd.h>

void	StringInit(String *this, char const *s)
{
	if (!this)
		return;
	this->str = NULL;
	if (s)
		this->str = strdup(s);
	this->assign_s = &assign_s;
	this->assign_c = &assign_c;
	this->append_s = &append_s;
	this->append_c = &append_c;
	this->at = &at;
	this->clear = &clear;
	this->size = &size;
	this->compare_s = &compare_s;
	this->compare_c = &compare_c;
	this->copy = &copy;
	this->c_str = &c_str;
	this->empty = &empty;
	this->find_s = &find_s;
	this->find_c = &find_c;
	this->insert_s = &insert_s;
	this->insert_c = &insert_c;
	this->to_int = &to_int;
	this->split_s = &split_s;
	this->split_c = &split_c;
	this->dump = &dump;
}

void	StringDestroy(String *this)
{
	if (this && this->str)
	{
		free(this->str);
		this->str = NULL;
	}
}

void	assign_s(String *this, String const *str)
{
	if (this && str)
		assign_c(this, str->str);
}

void	assign_c(String *this, char const *s)
{
	if (!this || !s)
		return;
	if (this->str)
		free(this->str);
	this->str = strdup(s);
}

void	append_s(String *this, String const *ap)
{
	if (this && ap)
		append_c(this, ap->str);
}

void	append_c(String *this, char const *aps)
{
	size_t	len;
	size_t	len_ap;

	len = 0;
	if (!this || !aps)
		return;
	if (this->str)
		len = strlen(this->str);
	len_ap = strlen(aps); 
	this->str = realloc(this->str, len + len_ap + 1);
	memset(this->str + len, 0, len_ap + 1);
	if (!this->str)
		free(this->str);
	this->str = strcat(this->str, aps);
}

char	at(String *this, size_t pos)
{
	if (!this || !this->str || pos > strlen(this->str) - 1)
		return (-1);
	return (this->str[pos]);
}

void	clear(String *this)
{
	int 	i;

	i = 0;
	if (!this || !this->str)
		return;
	while (this->str[i] != '\0')
	{
		this->str[i] = '\0';
		i++;
	}
}

int 	size(String *this)
{
	if (!this || !this->str)
		return (-1);
	return (strlen(this->str));
}

int 	compare_s(String *this, const String *str)
{
	if (!this && !str)
		return (0);
	if (str)
		return (compare_c(this, str->str));
	return (compare_c(this, NULL));
}

int 	compare_c(String *this, char const *str)
{
	if (!this)
		return (-1);
	if (this->str && !str)
		return (1);
	if (!this->str && str)
		return (-1);
	if (!this->str && !str)
		return (0);
	return (strcmp(this->str, str));
}

size_t	copy(String *this, char *s, size_t n, size_t pos)
{
	size_t	i;
	size_t	len;

	i = 0;
	if (!this || !s || !this->str)
		return (0);
	len = strlen(this->str);
	while (i + pos < len && i < n)
	{
		s[i] = this->str[i + pos];
		i++;
	}
	if (strlen(s) < n)
		s[i++] = 0;
	return (i);
}

char const	*c_str(String *this)
{
	if (!this)
		return (NULL);
	return (this->str);
}

int 	empty(String *this)
{
	if (!this || !this->str)
		return (1);
	if (strlen(this->str) == 0)
		return (1);
	return (-1);
}

int 	find_s(String *this, const String *str, size_t pos)
{
	if (!this || !str || !this->str || !str->str)
		return (-1);
	return (find_c(this, str->str, pos));
}

int 	find_c(String *this, char const *str, size_t pos)
{
	char	*str_pos;

	if (!this || !str || !this->str)
		return (-1);
	if (pos > strlen(this->str) - 1)
		return (-1);
	str_pos = strstr(this->str + pos, str);
	if (!str_pos)
		return (-1);
	return (str_pos - this->str);
}

void	insert_s(String *this, size_t pos, String const *str)
{
	if (!this || !str || !str->str)
		return;
	return (insert_c(this, pos, str->str));
}

void	insert_c(String *this, size_t pos, char const *str)
{
	char	*tmp;
	size_t	len;

	if (!this || !str)
		return;
	len = 0;
	if (this->str)
		len = strlen(this->str);
	if (len < pos)
		pos = len;
	tmp = malloc(sizeof(char) * (len + strlen(str) + 1));
	strncpy(tmp, this->str, pos);
	strcat(tmp, str);
	if (pos != strlen(this->str))
		strcat(tmp, this->str + pos);
	free(this->str);
	this->str = tmp;
}

int 	to_int(String *this)
{
	if (!this || !this->str)
		return (0);
	return (atoi(this->str));
}

int     is_alnum(char c, char sep)
{
  if (c != sep)
    return (1);
  return (0);
}

int	word_count(char *str, char sep)
{
  int	i;
  int	word;

  word = 0;
  i = 0;
  while (str[i])
    {
      if (is_alnum(str[i], sep) == 1 && is_alnum(str[i + 1], sep) == 0)
        word++;
      i++;
    }
  return (word);
}

char	**my_strn_to_wordtab(char *str, char sep)
{
  int	j;
  int	i;
  int	len;
  char	**wordtab;

  j = 0;
  len = 0;
  i = 0;
  wordtab = malloc((word_count(str, sep) + 1) * sizeof(char *));
  while (str[i])
    {
      if (is_alnum(str[i], sep))
	len++;
      if (is_alnum(str[i], sep) == 1 && is_alnum(str[i + 1], sep) == 0)
	{
	  wordtab[j] = malloc(len + 1);
	  strncpy(wordtab[j], &str[i - len + 1], len);
	  len = 0;
	  j++;
	}
      i++;
    }
  wordtab[j] = NULL;
  return (wordtab);
}

String		*split_s(String* this, char separator)
{
  size_t	i;
  char		**tab;
  String	*str_ing;

  i = 0;
  if (!this || !this->str)
    return (NULL);
  tab = split_c(this, separator);
  str_ing = NULL;
  for (i = 0; tab && tab[i]; ++i)
    {
      str_ing = realloc(str_ing, (i + 1) * sizeof(String));
      StringInit(&str_ing[i], tab[i]);
    }
  str_ing = realloc(str_ing, (i + 1) * sizeof(String));
  StringInit(&str_ing[i], 0x0);
  return (str_ing);
}

char	**split_c(String *this, char separator)
{
	if (!this || !this->str)
    return (NULL);
  return (my_strn_to_wordtab(this->str, separator));
}

void 	aff(String *this)
{
	if (!this || !this->str)
		return;
	write(1, this->str, strlen(this->str));	
}