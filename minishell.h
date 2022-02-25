#include "libft.h"

typedef struct s_var
{
	char	*name;
	char	*value;
	size_t	name_len;
	size_t	value_len;
	t_bool	inherit;
	t_bool	env_var;
} t_var;

t_var	*get_var(t_dlist *lst_var, char *name);
t_dlist	*add_var(t_dlist **lst_var, t_var add_var);
void	del_var(t_dlist **lst_var, char *name);
void	free_var(void *dlst_content);
void	import_var(t_dlist **lst_var, char **envp);

char	*expand_tkn(t_dlist *lst_var, char *str);
