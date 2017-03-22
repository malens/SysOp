#define _XOPEN_SOURCE 500
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <dirent.h>
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <ftw.h>
#include "dirCrawler.h"



static long fileSize = 0;

int main (int argc, char* argv[])
{
	int flags = 0;
	flags |= FTW_PHYS;
	fileSize = atoi(argv[2]);
	struct FTW * ftw = malloc (sizeof(*ftw));
	nftw(argv[1], filter, 1, flags);
	return 0;
}

static int filter (const char *filePath, const struct stat * stats, int flags, struct FTW * ftw)
{
		if(checkFileSize(stats, fileSize) == 0){
				char *fileName = strrchr(filePath, '/')+1;
				printStats(stats, fileName, filePath);
		}
		return 0;
}

int checkFileSize(const struct stat * s, long fileSize)
{

	if(fileSize >= (long) s->st_size)
		return 0;
	else
		return 1;
}

void printStats(const struct stat * s, char * fileName, const char * filePath){
	char *fileRights = calloc(9, sizeof(char));

	strcpy(fileRights, "---------");
    if (s->st_mode & S_IRUSR) fileRights[0] = 'r';
    if (s->st_mode & S_IWUSR) fileRights[1] = 'w';
    if (s->st_mode & S_IXUSR) fileRights[2] = 'x';
    if (s->st_mode & S_IRGRP) fileRights[3] = 'r';
    if (s->st_mode & S_IWGRP) fileRights[4] = 'w';
    if (s->st_mode & S_IXGRP) fileRights[5] = 'x';
    if (s->st_mode & S_IROTH) fileRights[6] = 'r';
    if (s->st_mode & S_IWOTH) fileRights[7] = 'w';
    if (s->st_mode & S_IXOTH) fileRights[8] = 'x';

    printf("File: %s\n", fileName);
    printf("Path: %s\n", filePath);
    printf("Size: %d\nLast modified: %sRights: %s\n\n", (int) (s->st_size), ctime(&s->st_mtime), fileRights);
	free(fileRights);
}
