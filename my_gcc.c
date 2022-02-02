
/*
 * compiler command :
 *	gcc -S -o hello_world.s hello_world.c
 *
 * assembler command
 *
 *	as -o hello_world.o hello_world.s
 * 
 * Linker command
 *
 *      ld -o hello_world -lc -dynamic-linker /lib64/ld-linux-x86-64-so.2 hell
 *      _world.o -e main
 *
 *
 * */
/////////////////////////////////////////////////////////////////////////////
//
//	Function name : comamnd()
//	Description :   to execute comamnds  
//	input arguments : const char * command
//	output : 	execute shell
//	Author :	Sahil Rajendra Lokhande
//	Date :		1 dec 2021
//
/////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>

int d,a;
char str[200];
char str1[20];
int command(const char *);
void  no_option(char *,char *);
void option_c(char *,char *);
void option_s(char*,char*);
//struct stat sb;

int command(const char * cmd)
{
	pid_t child_pid;
	child_pid = fork();
	int status = 0 ;
	switch(child_pid)
	{
		case -1:
			perror("fork");
			return -1;
		case 0:
			execl("/bin/sh","sh","-c",cmd,(char*)NULL);
			
		default:
			wait(&status);
			break;

	}
	printf("cmd return value is %d\n",status >> 8);
	return 0;
}
int main(int argc,char**argv)
{
	 if(argc==2)
         {
           no_option(argv[1],NULL);
         }
	 else if(argc==4)
       	 {
		no_option(argv[2],argv[3]);
	 }
	   while((a = getopt(argc,argv,"cSo")) != -1)

		{
			switch(a)
			{
				case 'S':
                                         if(argc==5)
                                         {
                                                 option_s(argv[3],argv[4]);
                                         }
                                         else
                                         {
                                                 option_s(argv[2],NULL);
                                         }
                                         break;


				case 'c':
					 if(argc==5)
					 {
						 option_c(argv[3],argv[4]);
					 }
					 else
					 { 
				        	option_c(argv[2],NULL);
					 }
					break;
				case '?':
					fprintf(stderr, "Unknown option -%c.\n",optopt);
					break;
				default:
					printf("in default");
					
			}

		}

}

void no_option(char *str1,char *str2)
{
	if(str2==NULL)
	{
                sprintf(str,"gcc -S -o hello_world.s %s",str1);
                command(str);


                //now next command

                sprintf(str,"as -o hello_world.o hello_world.s");
                command(str);

                sprintf(str,"ld -o a.out -lc -dynamic-linker /lib64/ld-linux-x86-64.so.2 hello_world.o -e main");
                command(str);
                remove("hello_world.s");
                remove("hello_world.o");

                exit(EXIT_SUCCESS);
	}	
	else
	{
		printf("\tdone\n");
		sprintf(str,"gcc -S -o hello_world.s %s",str2);
		command(str);

		sprintf(str,"as -o hello_world.o hello_world.s");
		command(str);

		sprintf(str,"ld -o %s -lc -dynamic-linker /lib64/ld-linux-x86-64.so.2 hello_world.o -e main",str1);
		command(str);
		remove("hello_world.s");
		remove("hello_world.o");

		exit(EXIT_SUCCESS);

	}
}

void option_c(char *str3,char *str4)
{
	char str[200];
	if(str4==NULL)
	{
		sprintf(str,"gcc -S -o hello_world.s %s",str3);
		command(str);

		//next command
		sprintf(str,"as -o hello_world.o hello_world.s");
		command(str);

		exit(EXIT_SUCCESS);
	}
	else
	{
		sprintf(str,"gcc -S -o hello_world.s %s",str4);
		command(str);
		printf(".s created\n");
		sprintf(str,"as -o %s hello_world.s",str3);
		printf(".o created\n");
		command(str);
		remove("hello_world.s");
		
	}
}


void option_s(char *str3,char *str4)
{
	char str[200];
	if(str4==NULL)
	{
		sprintf(str,"gcc -S -o hello_world.s %s",str3);
		command(str);
		printf("hello_world.s created");
		exit(EXIT_SUCCESS);
	}
	else
	{
		sprintf(str,"gcc -S -o %s %s",str3,str4);
		command(str);
		exit(EXIT_SUCCESS);
	}
}
