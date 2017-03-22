#ifndef _DIR_CRAWLER
#define _DIR_CRAWLER
static int filter (const char *filePath, const struct stat * stats, int flags, struct FTW * ftw);
void printStats(const struct stat * s, char * fileName, const char * filePath);
int checkFileSize(const struct stat *s, long fileSize);
#endif
