#ifndef _TEST_H_
#define _TEST_H_
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#define PERROR(LOG) do{perror(LOG);return -1;}while(0)
#define BUFSIZE 1024*1024
#define NAMESIZE 1024*1024
#define TEST_COUNT 100
typedef struct files
{
    unsigned char buf[BUFSIZE];
    char path[NAMESIZE];
    long long WriteSize;
    int mode;
}__FILES__;
int (*test[TEST_COUNT])(__FILES__ *file);

extern int Create_File(char *name,unsigned char* buf,long long write_size,int mode);

extern int test_1(__FILES__ *);

extern int test_2(__FILES__ *);

extern int test_3(__FILES__ *);

extern int test_4(__FILES__ *);

extern int test_5(__FILES__ *);

extern int test_6(__FILES__ *);

extern int test_7(__FILES__ *);

extern int test_8(__FILES__ *);

extern int test_9(__FILES__ *);

extern int test_10(__FILES__ *);

extern int test_11();

extern int test_12(__FILES__ *);

extern int test_13(__FILES__ *);

extern int test_14(__FILES__ *);

extern int test_15(__FILES__ *);

extern int add_list();
#endif
