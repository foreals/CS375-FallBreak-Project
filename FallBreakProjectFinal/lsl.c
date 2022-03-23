#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include <grp.h>
#include <pwd.h>

int main(int argc, char *argv[])
{
  
  char *dirname;
  if(argc == 1)
    dirname = ".";
  else
    dirname = argv[1];
  DIR*p;
  //directory struct
  struct dirent *d;

  //stat struct
  struct stat st;

  //gid struct
  struct group *groupid;

  //uid struct
  struct passwd *pws;

  char time[40];
  time_t t;
  char *gid;
  char *uid;
  int isdir;
  
  p=opendir(dirname);
  if(p==NULL)
    {
      perror("Cannot find directory");
      exit(1);
    }
  while((d=readdir(p)) != NULL){
    if(d->d_name[0] != '.'){
      //get file access time
      stat(d->d_name, &st);
      t = st.st_ctime;
      //format time output
      strcpy(time,ctime(&t));
      if (time[strlen(time)-1] == '\n') time[strlen(time)-1] = '\0';
      //gid
      groupid = getgrgid(st.st_gid);
      gid = groupid->gr_name;
      //uid
      pws = getpwuid(st.st_uid);
      uid = pws->pw_name;

      //file type
      isdir = ((S_ISDIR(st.st_mode)) ? 2 : 1);

      printf( (S_ISDIR(st.st_mode)) ? "d" : "-");
      printf( (st.st_mode & S_IRUSR) ? "r" : "-");
      printf( (st.st_mode & S_IWUSR) ? "w" : "-");
      printf( (st.st_mode & S_IXUSR) ? "x" : "-");
      printf( (st.st_mode & S_IRGRP) ? "r" : "-");
      printf( (st.st_mode & S_IWGRP) ? "w" : "-");
      printf( (st.st_mode & S_IXGRP) ? "x" : "-");
      printf( (st.st_mode & S_IROTH) ? "r" : "-");
      printf( (st.st_mode & S_IWOTH) ? "w" : "-");
      printf( (st.st_mode & S_IXOTH) ? "x" : "-");
      
      printf(" %d %s %s %7.2li %s %s\n", isdir, uid, gid, st.st_size,
	     time, d->d_name);
    }
  }
}
