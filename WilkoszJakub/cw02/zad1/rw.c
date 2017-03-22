#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/times.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <linux/random.h>
#include <unistd.h>
#include "rw.h"

const int NUMS[2] = {1000, 3000};

const int VALS[4] = {4, 512, 4096, 8192};


void generate_sys (int chunksize, int chunknum, char * filename)
{
  int ptr, rnd;
  void *buf = malloc (chunksize);
  if ((ptr = open(filename, O_RDWR | O_CREAT))!=-1)
  {
    for (int i = 0; i < chunknum; i++)
    {
      read (rnd, buf, chunksize);
      write (ptr, buf, chunksize);
    }
  }
  free(buf);
  close(rnd);
  close(ptr);
  return;

}


void generate_lib (int chunksize, int chunknum, char * filename)
{
  FILE *f = fopen(filename, "a");
  if (f == NULL) return;
  FILE *rnd = fopen("/dev/urandom", "r");
  if (rnd == NULL) return;
  void *buf = malloc(chunksize);
  if (buf == NULL) return;
  for (int i = 0; i < chunknum; i++)
  {
    fread(buf, chunksize, 1, rnd);
    fwrite(buf, chunksize, 1, f);
  }
  fclose(rnd);
  fclose(f);
  free(buf);
  return;
}

void shuffle_lib (int chunksize, int chunknum, char * filename)
{
  FILE *f = fopen(filename, "r+t");
  if (f == NULL) return;
  void *buf1 = malloc(chunksize);
  if (buf1 == NULL) return;
  void *buf2 = malloc(chunksize);
  if (buf2 == NULL) return;
  for (int i = 0; i < chunknum - 2; i++)
  {
    fseek(f, i*chunksize, 0);
    fread(buf1, chunksize, 1, f);
    int pos = (rand()%(chunknum-i))+i;
    fseek(f, pos*chunksize, 0);
    fread(buf2, chunksize, 1, f);
    fseek(f, i*chunksize, 0);
    fwrite(buf2, chunksize, 1, f);
    fseek(f, pos*chunksize, 0);
    fwrite(buf1, chunksize, 1, f);
  }
  free(buf1);
  free(buf2);
  fclose(f);
}

void shuffle_sys (int chunksize, int chunknum, char * filename)
{
  int ptr;
  void *buf1 = malloc (chunksize);
  void *buf2 = malloc (chunksize);
  if ((ptr = open(filename, O_RDWR))!=-1)
  {
    for (int i = 0; i < chunknum - 2; i++)
    {
      lseek(ptr, i*chunksize, SEEK_SET);
      read(ptr, buf1, chunksize);
      int pos = (rand()%(chunknum-i))+i;
      lseek(ptr, pos*chunksize, SEEK_SET);
      read(ptr, buf2, chunksize);
      lseek(ptr, i*chunksize, SEEK_SET);
      write(ptr, buf2, chunksize);
      lseek(ptr, pos*chunksize, SEEK_SET);
      write(ptr, buf1, chunksize);
    }
  }
  free(buf1);
  free(buf2);
  close(ptr);
}

void bubble_sort_sys (int chunksize, int chunknum, char * filename)
{
  int ptr;

  if ((ptr = open(filename, O_RDWR))!=-1)
  {
    void *buf1 = malloc (chunksize);
    void *buf2 = malloc (chunksize);
    for(int n = chunknum; n > 1; n--){
      for(int i = 0; i < n-1; i++){
        lseek(ptr, i*chunksize, SEEK_SET);
        read(ptr, buf1, chunksize);
        read(ptr, buf2, chunksize);
        unsigned char *x = (void *)buf1;
        unsigned char *y = (void *)buf2;
        if (x[0]<y[0]) {
          lseek(ptr, i*chunksize, SEEK_SET);
          write(ptr, buf2, chunksize);
          write(ptr, buf1, chunksize);
        }
      }
    }
    free(buf1);
    free(buf2);

  }

  close(ptr);
}

void bubble_sort_lib (int chunksize, int chunknum, char * filename)
{
  FILE *ptr = fopen(filename, "r+t");
  if (ptr == NULL) return;
  void *buf1 = malloc (chunksize);
  void *buf2 = malloc (chunksize);


  for(int n = chunknum; n > 1; n--){
    for(int i = 0; i < n-1; i++){
      fseek(ptr, i*chunksize, 0);
      fread(buf1, chunksize, 1, ptr);
      fread(buf2, chunksize, 1, ptr);
      unsigned char *x = (void *)buf1;
      unsigned char *y = (void *)buf2;
      if (x[0]<y[0]) {
        fseek(ptr, i*chunksize, 0);
        fwrite(buf2, chunksize, 1, ptr);
        fwrite(buf1, chunksize, 1, ptr);
      }
    }
  }
  free(buf1);
  free(buf2);
  fclose(ptr);
}

int copy_file(char *old_filename, char  *new_filename)
{
		FILE  *ptr_old, *ptr_new;
		int  a;
    ptr_old = fopen(old_filename, "r+t");
    ptr_new = fopen(new_filename, "w+t");
		while(1)
		{
			a  =  fgetc(ptr_old);

			if(!feof(ptr_old))
				fputc(a, ptr_new);
			else
				break;
		}

		fclose(ptr_new);
		fclose(ptr_old);
		return  0;
}

void test()
{
  double sys_time_used, usr_time_used;
  struct tms *begins = malloc(sizeof(*begins));
  struct tms *ends = malloc(sizeof(*ends));
  char t[1];
  for (int j = 0; j<2; j++)
  {
    for (int i = 0; i<4; i++)
    {
      char tmp[128];
      char tmp2[128];
      char tmp3[128];
      strcpy(tmp, "test");
      char t[2];
      t[0] = '1'+j;
      strcat(tmp, t);
      strcat(tmp, "_");
      t[0] = '1'+i;
      strcat(tmp, t);
      strcat(tmp, "sort");
      generate_lib(VALS[i], NUMS[j], tmp);
      strcpy(tmp2, tmp);
      strcat(tmp2, "_lib");
      copy_file(tmp, tmp2);
      strcpy(tmp3, tmp);
      strcat(tmp3, "_sys");
      copy_file(tmp, tmp3);

      times(begins);
      bubble_sort_sys(VALS[i], NUMS[j], tmp3);
      times(ends);
      sys_time_used = (ends -> tms_stime - begins -> tms_stime)/sysconf(_SC_CLK_TCK);
      printf("%i x %ib system time sort sys: %f\n", NUMS[j], VALS[i], sys_time_used);
      usr_time_used = (ends -> tms_utime - begins -> tms_utime)/sysconf(_SC_CLK_TCK);
      printf("%i x %ib user time sort sys: %f\n", NUMS[j], VALS[i], usr_time_used);
      times(begins);
      bubble_sort_lib(VALS[i], NUMS[j], tmp2);
      times(ends);
      sys_time_used = (ends -> tms_stime - begins -> tms_stime)/sysconf(_SC_CLK_TCK);
      printf("%i x %ib system time sort lib: %f\n", NUMS[j], VALS[i], sys_time_used);
      usr_time_used = (ends -> tms_utime - begins -> tms_utime)/sysconf(_SC_CLK_TCK);
      printf("%i x %ib user time sort lib: %f\n", NUMS[j], VALS[i], usr_time_used);


      times(begins);
      shuffle_sys(VALS[i], NUMS[j], tmp3);
      times(ends);
      sys_time_used = (ends -> tms_stime - begins -> tms_stime)/sysconf(_SC_CLK_TCK);
      printf("%i x %ib system time shuffle sys: %f\n", NUMS[j], VALS[i], sys_time_used);
      usr_time_used = (ends -> tms_utime - begins -> tms_utime)/sysconf(_SC_CLK_TCK);
      printf("%i x %ib user time shuffle sys: %f\n", NUMS[j], VALS[i], usr_time_used);
      times(begins);
      shuffle_lib(VALS[i], NUMS[j], tmp2);
      times(ends);
      sys_time_used = (ends -> tms_stime - begins -> tms_stime)/sysconf(_SC_CLK_TCK);
      printf("%i x %ib system time shuffle lib: %f\n", NUMS[j], VALS[i], sys_time_used);
      usr_time_used = (ends -> tms_utime - begins -> tms_utime)/sysconf(_SC_CLK_TCK);
      printf("%i x %ib user time shuffle lib: %f\n", NUMS[j], VALS[i], usr_time_used);




    }
  }

}


int main (int argc, char* argv[])
{
  srand(time(NULL));
  if (argc<2) return 0;

  if ( strcmp(argv[1], "sys") == 0){
    if (strcmp (argv[2], "shuffle") == 0)
    {
      shuffle_sys(atoi(argv[3]), atoi(argv[4]), argv[5]);
    } else if (strcmp (argv[2], "sort") == 0)
    {
      bubble_sort_sys(atoi(argv[3]), atoi(argv[4]), argv[5]);
    } else if (strcmp (argv[2], "generate") == 0)
    {
      generate_sys(atoi(argv[3]), atoi(argv[4]), argv[5]);
    }
  } else if (strcmp(argv[1], "lib") == 0)
  {
    if (strcmp (argv[2], "shuffle") == 0)
    {
      shuffle_lib(atoi(argv[3]), atoi(argv[4]), argv[5]);
    } else if (strcmp (argv[2], "sort") == 0)
    {
      bubble_sort_lib(atoi(argv[3]), atoi(argv[4]), argv[5]);
    } else if (strcmp (argv[2], "generate") == 0)
    {
      generate_lib(atoi(argv[3]), atoi(argv[4]), argv[5]);
    }
  } else if (strcmp(argv[1], "test") == 0)
  {
    test();
  }





  return 0;
}
