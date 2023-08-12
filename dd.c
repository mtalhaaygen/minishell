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
    // cat talha.txt | grep a > new.txt
	nodes[0].args = malloc(sizeof(char *) * 2);
	nodes[0].args[0] = malloc(sizeof(char) * 9);
	nodes[0].args[1] = malloc(sizeof(char) * 10);
	nodes[1].args = malloc(sizeof(char *) * 2);
	nodes[1].args[0] = malloc(sizeof(char) * 14);
	nodes[1].args[1] = malloc(sizeof(char) * 1);
	nodes[1].args[2] = malloc(sizeof(char) * 1);
	nodes[1].args[3] = malloc(sizeof(char) * 8);

    nodes[0].args[0] = "/bin/cat";
    nodes[0].args[1] = "talha.txt";
    nodes[1].args[0] = "/usr/bin/grep";
    nodes[1].args[1] = "a";
    nodes[1].args[2] = ">";
    nodes[1].args[3] = "new.txt";
    //  ">", "new.txt"
	int newtxt_fd = open("new.txt", O_RDWR);
    int fdn = open("talha.txt", O_WRONLY);
    if (pipe(fd) == -1)
        perror("pipe error");
	
    while (i < pcount)
    {
		is_redirection(node[i].args); // stdout > file    stdin < file
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
		
    
    // dup2(fdn, fd[1]);
    // // int fd_stdout = dup(STDOUT_FILENO);
    // write(1, "xxxxx", 5); // talha.txt nin içine yazacak
    // dup2(1, 1); // fd_stdout'u tekrardan standart çıkışa yönlendir
    // write(1, "talha\n", 6);
}