#ifndef _DIR_CRAWLER
#define _DIR_CRAWLER
void crawlDirs(char *dirPath, long fileSize);
void printStats(char *filePath, char *fileName);
int checkFileSize(char *filePath, long fileSize);
#endif
