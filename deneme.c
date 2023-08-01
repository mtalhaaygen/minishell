#include "minishell.h"

Node	*sahte_nodes()
{
	Node *nodes;

	nodes = malloc(sizeof(Node));
	nodes->args = malloc(sizeof(char *) * 1);
	nodes->args[0] = malloc(sizeof(char) * 4);

	nodes->arg_count = 1;
	nodes->infile = NULL;
	nodes->outfile = NULL;
	nodes->args[0] = "pwd";
	// nodes->args[1] = ""
	// nodes->arg_count = 2;
	// nodes->infile = NULL;
	// nodes->outfile = NULL;
	// nodes->args[0] = "ls"
	// nodes->args[1] = "-la"

	return (nodes);
}