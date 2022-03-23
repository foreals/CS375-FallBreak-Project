#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define BUFF_SIZE 510
int main(int argc, char *argv[]) {
   int option;
   int E = 0, n = 0, s = 0;
   int print = 0;
   int line = 1;

   if(argc == 2)
     print = 1;

   while((option = getopt(argc, argv, "Ens")) != -1){ //get option from
                                                      //the getopt() method
     switch(option){
     case 'E':
       E = 1; print = 1;
       break;
     case 'n':
       n = 1; print = 1;
       break;
     case 's':
       s = 1; print = 1;
       break;
     default:
     case '?':
       fprintf(stderr, "usage: cat [-Ens] [-] [file ...]\n");
       exit(1);
     }
   }
   if(print){
     
     FILE *file;
     char c[BUFF_SIZE];
    
     // Open file
     file = fopen(argv[argc-1], "r");
     if (file == NULL)
       {
	 printf("Cannot open file \n");
	 exit(0);
       }
     
     // Read contents from file
     while (fgets(c, BUFF_SIZE, file))
       {
	 if(E)
	   {
	     char buf[BUFF_SIZE] = "";

	       strncpy(buf, c, strlen(c)-1);
	     int len = strlen(buf);
	     strcpy(buf+len, "$");
	     len += 1;
	     strcpy(buf+len, c+strlen(c)-1);

	     strcpy(c, buf);
	     printf("%s", c);
	   }
	 else if(n)
	   {
	     printf("%d  %s", line, c);
	     line++;
	   }
	 else if(s)
	   {
	     if(*c != '\n')
	       {
		 printf("%s", c);
	       }
	   }
	 else
	   {
	     printf("%s", c);
	   }
       }
     
     fclose(file);
   }
   return 0;
}
