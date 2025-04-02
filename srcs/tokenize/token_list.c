#include "../../includes/shell.h"

t_list *list_add_back(t_list *list, char *str);

t_list *list_add_back(t_list *list, char *str)
{
	t_list *node = malloc(sizeof(t_list)), *current;
	if(!node)
		return (NULL);
	node->next = NULL;
	node->token = ft_strdup(str);
	if(!list)
		return (node);
	current = list;
	while(current && current->next)
		current = current->next;
	current->next = node;
	return (list);
}
