#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <grp.h>
#include <pwd.h>


int main(int argc, char *argv[]){

  if(argc != 2){
    printf("ERROR: needs filename\n");
    exit(1);
  }

  //gid struct
  struct group *groupid;

  //uid struct
  struct passwd *pws;

  char *gid;
  char *uid;

  struct stat st;
  char *filename = argv[1];
  char time[40];
  time_t t;
  int err;
  char *isreg;

  printf("  File: %s\n", filename);
  err = stat(filename, &st);
  
  if (err == -1)
    {
        printf("\nstat Error\n");
	exit(1);
    }

  //get gid
  groupid = getgrgid(st.st_gid);
  gid = groupid->gr_name;

  //get uid
  pws = getpwuid(st.st_uid);
  uid = pws->pw_name;
  
  // display file size
  printf("  Size: %li bytes\t", st.st_size);

  printf("Blocks: %ld\t", st.st_blocks);

  printf("IO Block: %ld\t", st.st_blksize);

  isreg = ((S_ISREG(st.st_mode)) ? "regular file" : "directory");
  printf("%s\n", isreg);
    
  printf("Device: %lu\t", st.st_dev);

  printf("\tInode: %lu\t", st.st_ino);

  printf("Links: %lu\n", st.st_nlink);

  printf("Access: ");
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
  
  printf("\tUid: ( %u/\t%s)", st.st_uid, uid);

  printf("\tGid: ( %u/\t%s)\n", st.st_gid, gid);

  // get the last time file was accessed
  t = st.st_atime;
  strcpy(time,ctime(&t));
  printf("Access: %s",time);
  
  t = st.st_ctime;
  strcpy(time, ctime(&t));
  printf("Modify: %s",time);
	 
  // get modification date
  t = st.st_mtime;
  strcpy(time,ctime(&t));
  printf("Change: %s",time);
	 
  

  return 0;
}
