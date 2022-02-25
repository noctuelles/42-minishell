typedef struct s_var
{
	char	*name;
	char	*value;
	t_bool	inherit;
	t_bool	env_var;
} t_var;

char	*get_var_value(t_dlist *lst_var, char *name);
t_dlist	*add_var(t_dlist **lst_var, t_var add_var);
void	del_var(t_dlist **lst_var, char *name);
void	free_var(void *dlst_content);
void	import_var(t_dlist **lst_var, char **envp);
