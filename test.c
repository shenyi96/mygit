#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void GetFileName11(char *buf,int num,int note)
{
    int i;
    char tempbuf[50];
    if(note == 0)
    {
        for (i = 1;i<= num;i++)
        {
            memset(tempbuf,0,sizeof(tempbuf));
            sprintf(tempbuf,"/max_path_depth_%d",i);
            strcpy(&buf[strlen(buf)],tempbuf);
        }
    }
    else if (note == 1)
    {
        for (i = num;i>=1;i--)
        {
            memset(tempbuf,0,sizeof(tempbuf));
            sprintf(tempbuf,"/max_path_depth_%d",i);
            strcpy(&buf[strlen(buf)],tempbuf);
        }
    }
    
    //return (OK);
}
typedef struct asdb{
	unsigned int 	rd_offset;	/* "inode" number of entry */
	unsigned char		rd_type;	/* file type from <sys/dirent.h> */
	unsigned char		rd_namelen;	/* length of string in rd_name */
	char		rd_name[255];	/* name of entry */
	} *rfdir_t,asd;

int main()
{
	int a = 0;
	switch(a)
	{
	case 3:
		printf("1");
		break;
	case 0:

	case 1:
		printf("1");
		break;
	case 2:
		printf("2");
		break;
	default:
		printf("defalut");
		break;
	}
}
