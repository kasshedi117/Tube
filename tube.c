#include<sys/types.h>
#include<sys/wait.h>
#include<sys/stat.h>
#include<unistd.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define R 0
#define W 1




int main( int argc, char * argv[])
{

int pid;
int fd[2];
char message[100];
int Nboctects;
char* phrase="Vendredi: VOICI MON MESSAGE POUR TOI PERE!?";


system("clear");


if (pipe(fd) == -1)
	{
	perror ("Creation du pipe a Echoué ");
	exit(1);
	}


//création du fils

pid=fork();
if(!pid) // fils ?
	{
	close(fd[R]);//fermeture du fichier de lecture par le fils



	if (write(fd[W],argv[1],strlen(argv[1])+1)== -1)
		{
            perror("write : Ecriture dans le pipe Ã  Ã©chouÃ© ");
            exit(4);
		}

	close(fd[W]);//fermeture du fichier d'Ã©criture par le fils
	//sleep(2);
	exit(3);
}



wait(NULL);
close(fd[W]);//fermeture du fichier de lecture par le pere
if (( Nboctects = read (fd[R],message, 100)) == -1)
	{
        perror ("read : Lecture Ã©chouÃ© ");
        exit(5);
	}
message[Nboctects]='\0';
printf("\n MESSAGE RECU = %s \n",message);
close(fd[R]);//fermeture du fichier d'Ã©criture par le pere
return 0;

}
