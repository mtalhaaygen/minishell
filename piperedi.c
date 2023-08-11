#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>

// '>' dosya oluşturulmadıysa dosyayı oluşturur, dosyanın içeriğinin üzerine yazar. Dosyayı açarken open() fonksiyonunda flag olarak O_TRUNC kullanmalıyız, bu dosyanın içeriğinin silinmesine neden olur

int		fd[2];

typedef struct Node
{
	char		**args;
	char		*infile;
	char		*outfile;
}	Node;

void	change_fd_i(Node node)
{
	int	fdnewtxt;
	// int sin;
	// node.outfile = node.args[index + 1];
	if (node.outfile != NULL) // >
	{
		fdnewtxt = open(node.outfile, O_RDWR | O_TRUNC | O_CREAT, 0777);
		dup2(fdnewtxt, STDOUT_FILENO);
		node.args = ft_newargs(node.args);
		node.args[2] = NULL;
		node.args[3] = NULL;
	}
}

int		contain_i(char **commands)
{
	int	index;

	index = 0;
	while (commands[index])
	{
		if (commands[index][0] == '>')
			return (index);
		index++;
	}
	return (0);
}

void	is_redirection(Node *nodes, int i)
{
	if(contain_i(nodes[i].args))
		change_fd_i(nodes[i]);
	// if((index = contain_ii(nodes[i].args)))
	// 	change_fd_ii(nodes[i], index);
	// if((index = contain_o(nodes[i].args)))
	// 	change_fd_o(nodes[i], index);
}

int main()
{
	Node *nodes;

	int pcount = 2;
	int i = 0;
	pid_t ret;

	nodes = malloc(sizeof(Node) * 3);
	// cat talha.txt | grep a > new.txt
	nodes[0].args = malloc(sizeof(char *) * 3);
	nodes[0].args[0] = malloc(sizeof(char) * 9);
	nodes[0].args[1] = malloc(sizeof(char) * 10);
	nodes[0].args[2] = NULL;
	nodes[0].infile = NULL;
	nodes[0].outfile = NULL;

	nodes[1].args = malloc(sizeof(char *) * 5);
	nodes[1].args[0] = malloc(sizeof(char) * 14);
	nodes[1].args[1] = malloc(sizeof(char) * 1);
	nodes[1].args[2] = malloc(sizeof(char) * 1);
	nodes[1].args[3] = malloc(sizeof(char) * 8);
	nodes[1].args[4] = NULL;
	nodes[1].infile = NULL;
	nodes[1].outfile = malloc(sizeof(char) * 8);
	nodes[1].outfile = "new.txt";

	nodes[0].args[0] = "/bin/cat";
	nodes[0].args[1] = "talha.txt";
	nodes[1].args[0] = "/usr/bin/grep";
	nodes[1].args[1] = "a";
	nodes[1].args[2] = ">";
	nodes[1].args[3] = "new.txt";
	
	//  ">", "new.txt"
	// int newtxt_fd = open("new.txt", O_RDWR);
	// int fdn = open("talha.txt", O_WRONLY);
	if (pipe(fd) == -1)
		perror("pipe error");
	
	while (i < pcount)
	{
		ret = fork();
		if (ret == 0)
		{
			if (i == 0)
			{
				dup2(fd[1], STDOUT_FILENO);
				close(fd[0]);
				close(fd[1]);
			}
			if (i == 1)
			{
				dup2(fd[0], STDIN_FILENO);
				close(fd[0]);
				close(fd[1]);
			}
			is_redirection(nodes, i);
			// printf("%s deneme\n", nodes[i].args[0]);
			if (execve(nodes[i].args[0], nodes[i].args, NULL))
				perror("execve perror ");
			exit(2);
		}
		i++;
	}
	if (ret > 0)
	{
		close(fd[0]);
		close(fd[1]);
		waitpid(ret, NULL, 0);
	}
}