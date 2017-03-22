#include <stdlib.h>
#include <sys/stat.h>
#include <dirent.h>
#include <time.h>
#include <stdio.h>
#include <string.h>
#include "dirCrawler.h"

void crawlDirs(char *dirPath, long fileSize){
	struct stat stats;
	struct dirent* file;
	char filePath[PATH_MAX];
	char *fileName;

	DIR *root = opendir(dirPath);
	if(root==NULL){
		return;
	}

	while((file = readdir(root)) != NULL){
		fileName = file->d_name;
		snprintf(filePath, PATH_MAX, "%s/%s", dirPath, fileName);
		lstat(filePath, &stats);

		if(S_ISDIR(stats.st_mode)){
			if(strcmp(fileName, ".") != 0 && strcmp(fileName, "..") != 0) {
				int pathLen;
				char dir2Path[PATH_MAX];

				pathLen = snprintf(dir2Path, PATH_MAX, "%s/%s", dirPath, fileName);
				if(pathLen >= PATH_MAX) {
					printf("Path length is too long\n");
					exit(-1);
				}

				dir2Path[pathLen] = '\0';
				crawlDirs(dir2Path, fileSize);
			}
		}
		else if(S_ISREG(stats.st_mode)) {
			if(checkFileSize(filePath, fileSize) == 0){
				printStats(filePath, fileName);
			}
		}
	}
	closedir(root);
}

int checkFileSize(char *filePath, long fileSize)
{
	struct stat s;
	lstat(filePath, &s);

	if(fileSize >= (long) s.st_size)
		return 0;
	else
		return 1;
}

void printStats(char *filePath, char *fileName){
	char *fileRights = calloc(9, sizeof(char));

	struct stat s;
	lstat(filePath, &s);

	strcpy(fileRights, "---------");
    if (s.st_mode & S_IRUSR) fileRights[0] = 'r';
    if (s.st_mode & S_IWUSR) fileRights[1] = 'w';
    if (s.st_mode & S_IXUSR) fileRights[2] = 'x';
    if (s.st_mode & S_IRGRP) fileRights[3] = 'r';
    if (s.st_mode & S_IWGRP) fileRights[4] = 'w';
    if (s.st_mode & S_IXGRP) fileRights[5] = 'x';
    if (s.st_mode & S_IROTH) fileRights[6] = 'r';
    if (s.st_mode & S_IWOTH) fileRights[7] = 'w';
    if (s.st_mode & S_IXOTH) fileRights[8] = 'x';

    printf("File: %s\n", fileName);
    printf("Path: %s\n", filePath);
    printf("Size: %d\nLast modified: %sRights: %s\n\n", (int) s.st_size, ctime(&s.st_mtime), fileRights);
	free(fileRights);
}
