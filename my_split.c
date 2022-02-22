#include "./aqadil/minishell.h"


static int	free_thing(char **tab, int index)
{
	while (index >= 0)
	{
		free(tab[index]);
		index--;
	}
	return (0);
}

static int	count_word(const char *s, char *set)
{
	int	count;
    int i;

    i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] == set[0] && s[i + 1] == set[1])
		{
			count++;
		}
		i++;
	}
	count = count + 1;
	return (count);
}

static char	*create_word(const char *s, int start, int end)
{
	char	*word;
	int		i;
	int		word_len;

	i = 0;
	word_len = end - start;
	word = (char *)malloc((word_len * sizeof(char )) + 1);
	while (start < end)
		word[i++] = s[start++];
	word[i] = '\0';
	return (word);
}

static int	fill_the_splited_array(char **str, const char *s, char *set)
{
	int		start;
	int		end;
	int		i;
	int		k;

	i = 0;
	k = 0;
	while (s[i])
	{
		if ((s[i] != set[0] && s[i + 1] != set[1]) || (s[i] != set[0] && s[i + 1] == set[1] && s[i + 2] != set[1]))
		{
			start = i;
			while ((s[i]) && ((s[i] != set[0] && s[i + 1] != set[1]) || (s[i] != set[0] && s[i + 1] == set[1] && s[i + 2] != set[1]) || (s[i] == set[0] && s[i + 1] != set[1])))
			{
				if (s[i + 1] != set[0] && s[i + 2] == set[1])
					i++;
				i++;
			}
			end = i;
			str[k] = create_word(s, start, end);
			if ((str[k]) == NULL)
				return (free_thing(str, k));
			k++;
		}
		else
			i++;
	}
	str[k] = 0;
	return (1);
}

char	**ft_split22(char *s, char *set)
{
	char	**str;
	int		checker;

	checker = 1;
	if (!s)
		return (NULL);
	str = (char **)malloc(((count_word(s, set) + 1) * (sizeof(char *))));
	if (str == NULL)
		return (NULL);
	checker = fill_the_splited_array(str, s, set);
	
	if (checker == 0)
		return (NULL);
	return (str);
}

// int main()
// {
// 	char **str = ft_split22("ls > test.txt >> test1.txt", ">>");

// 	int i = 0;
// 	while (str[i])
// 		printf("%s\n", str[i++]);
// }