#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>

typedef struct Node
{
	char		**args;

}   Node;

int main()
{
	Node *nodes;
	int fd[2];
	int pcount = 2;
	int i = 0;
	pid_t ret;


	nodes = malloc(sizeof(Node) * 3);
	// cat talha.txt | grep a
	nodes[0].args = malloc(sizeof(char *) * 3);
	nodes[0].args[0] = malloc(sizeof(char) * 9);
	nodes[0].args[1] = malloc(sizeof(char) * 10);
	nodes[1].args = malloc(sizeof(char *) * 3);
	nodes[1].args[0] = malloc(sizeof(char) * 14);
	nodes[1].args[1] = malloc(sizeof(char) * 1);

    nodes[0].args[0] = "/bin/cat";
    nodes[0].args[1] = "talha.txt";
    nodes[0].args[2] = NULL;
    nodes[1].args[0] = "/usr/bin/grep";
    nodes[1].args[1] = "a";
    nodes[1].args[2] = NULL;

    if (pipe(fd) == -1)
        perror("pipe error");
	
    while (i < pcount)
    {
		ret = fork(); // p c
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
				printf("grep deneme1\n");
				dup2(fd[0], STDIN_FILENO);
				printf("grep deneme2\n");
				close(fd[0]);
				printf("grep deneme3\n");
				close(fd[1]);
				printf("grep deneme4\n");
			}
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