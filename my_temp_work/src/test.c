#include "test.h"

/*******************Create File**********************/
int Create_File
    (char *name,
    unsigned char* buf,
    long long write_size,
    int mode)
{
    if(0 == strlen(name))
    {
        PERROR("name is empty str");
    }
    int fd = open(name,O_RDWR|O_CREAT|O_APPEND,mode);
    if(fd < 0)
    {
        PERROR("open fail");
    }

    int ret ;
    while (1)
    {
        if(write_size>1024*1024)
        {
            ret = write(fd,buf,1024*1024);
            write_size -= 1024*1024;
        }
        else
        {
            ret = write(fd,buf,write_size);
            break;
        }
        if(ret < 0)
    	{
        	PERROR("write fail");
    	}   
    }
    
    close(fd);
    return 0;
}


/**************test_1**********************************
     * Description:The value of the
            - first byte of this file is 0
            - the value of the second byte
            - is 1, the value of the third
            - byte is 2,..., and the value
            - of the 256th byte is 255.
     * BUFSIZE = 256
*******************************************************/
int test_1(__FILES__ *file)
{
    memset(file->buf,0,sizeof(file->buf));
    strcpy(file->path,"../files/default/f");
    int i;
    for (i = 0;i<256;i++)
    {
        file->buf[i] = i;
    }
    file->WriteSize = 256;
}
/*************test_2************************************
     * Description:The file name is
            - 254 characters 'f'. The size
            - of the file is 200 Bytes and 
            - the content of the file is 
            - filled with character '[' 
     * BUFSIZE = 200
*******************************************************/
int test_2(__FILES__ *file)
{
    memset(file->buf,0,sizeof(file->buf));
    strcpy(file->path,"../files/default/");
    int i = strlen(file->path);
    int n = i;
    for (i; i < 254+n; i++)
    {
        file->path[i] = 'f';
    }
    file->path[i] = 0;
    for (i=0;i<200; i++)
    {
        file->buf[i] = '[';
    }
    file->buf[i] = 0;
    file->WriteSize = 200;
}
/***********test_3**************************************
     * Description:This file name 
            - contains all printable characters.
            - The content of this file is its
            - full path in this ROMFS image
     * BUFSIZE = 96
*******************************************************/
int test_3(__FILES__ *file)
{
    strcpy(file->path,"../files/default/abcdefghijklmnopq\
rstuvwxyz1234567890ABCDEFGHIJKLMNOPQRSTUVWXYZ `~1!@#$%^&*\
()-_=+[{]}\\|;:'\",<:.>?");
    strcpy(file->buf,"/abcdefghijklmnopqrstuvwxyz12345678\
90ABCDEFGHIJKLMNOPQRSTUVWXYZ `~1!@#$%^&*()-_=+[{]}\\|;:'\
\",<.>?");
    file->WriteSize = 96;
}
/************test_4*************************************
     * Description:The file size is 0.
            -In user-defined ROMFS image, this file has:
            - User ID (rf_uid or st_uid) is 1000.
            - Group ID (rf_gid or st_gid) is 1000.
            - Permission is 0664 in octal (part 
            - of the mode (rf_mode or st_mode) value 0x81B4).
            - The file size (rf_size or st_size) is 0.
     * BUFSIZE = 0;
********************************************************/
int test_4(__FILES__ *file)
{
    strcpy(file->path,"../files/default/empty_file.txt");
    memset(file->buf,0,sizeof(file->buf));
    file->WriteSize = 0;
    file->mode = 0664;
}
/*************test_5*************************************
     * Description:The content of file is a character '0'
     * BUFSIZE = 1 
********************************************************/

int test_5(__FILES__ *file)
{
    strcpy(file->path,"../files/default/1ByteSize_file");
    file->buf[0] = '0';
    file->WriteSize = 1;
}
/*************test_6  and test_7***************************
     * Description:The content of the file is encoded every
            4 continuous bytes with the following pattern:
            value = file_tag | X
            Where:
                - In default ROMFS image: file_tag=0x01800000 
            (0b0 0000 0011 << 23)
            - In user-defined ROMFS image: file_tag=0x01000000 
            (0b0 0000 0010 << 23)
            - X ranges from 0x0000 0000 to 0x0000 00F9 (249)

            In user-defined ROMFS image, this file has:
            - User ID (rf_uid or st_uid) is 1000.
            - Group ID (rf_gid or st_gid) is 1000.
            - Permission is 0664 in octal (part of the mode 
            (rf_mode or st_mode) value 0x81B4).
            - The file size (rf_size or st_size) is 1000.
     * BUFSIZE = 1000 
********************************************************/


int test_6(__FILES__ *file)
{
    strcpy(file->path,"../files/default/1000ByteSize_file");
    int file_tag = 0x01800000;
    int count = 249;
    int temp = 0;
    for (int i = 0; i < count; i++)
    {
        file->buf[temp] = file_tag | i;
        temp +=4;
    }
    file->WriteSize = 1000;
    file->mode = 0664;
}
int test_7(__FILES__ *file)
{
    strcpy(file->path,"../files/user/1000ByteSize_file");
    int file_tag = 0x01000000;
    int count = 249;
    int temp = 0;
    for (int i = 0; i < count; i++)
    {
        file->buf[temp] = file_tag | i;
        temp +=4;
    }
    file->WriteSize = 1000;
    file->mode = 0664;
}
/*************test_8  and test_9***************************
     * Description:The content is encoded every 4 continuous
            bytes with the following pattern:
            value = file_tag | X
            Where:
            - In default ROMFS image: file_tag=0x02800000 
            (0b0 0000 0101 << 23)
            - In user-defined ROMFS image: file_tag=0x02000000 
            (0b0 0000 0100 << 23)
            - X ranges from 0x0000 0000 to 0x0063 FFFF (6553599)

            In user-defined ROMFS image, this file has:
            - User ID (rf_uid or st_uid) is 1000.
            - Group ID (rf_gid or st_gid) is 1000.
            - Permission is 0664 in octal (part of the mode 
            (rf_mode or st_mode) value 0x81B4).
            - The file size (rf_size or st_size) is 26,214,400.
     * BUFSIZE = 25M 
********************************************************/
int test_8(__FILES__ *file)
{
    strcpy(file->path,"../files/default/25M_file.txt");
    int file_tag = 0x01800000;
    long long count = 6553599;
    long long temp = 0;
    for (int i = 0; i < count; i++)
    {
        file->buf[temp] = file_tag | i;
        temp +=4;
    }
    file->WriteSize = 26214400;
    file->mode = 0664;
}
extern int test_9(__FILES__ *file)
{
    strcpy(file->path,"../files/user/25M_file.txt");
    int file_tag = 0x02000000;
    long long count = 6553599;
    long long temp = 0;
    for (int i = 0; i < count; i++)
    {
        file->buf[temp] = file_tag | i;
        temp +=4;
    }
    file->WriteSize = 26214400;
    file->mode = 0664;
}
/*************test_10************************************
     * Description:The size of the named "file10" is 50 Bytes
     		, and the content of the file is filled with 
     		character 'z'.
     * BUFSIZE = 50 
********************************************************/

extern int test_10(__FILES__ *file)
{
    strcpy(file->path,"../files/default/dir1/dir2/\
dir3/dir4/dir5/dirl6/dir7/dir8/dir9/file10");
    long long count = 50;
    for (int i = 0; i < count; i++)
    {
        file->buf[i] = 'z';
    }
    file->WriteSize = 50;

}
/*************test_11*************************************
     * Description:The path depth is 512 levels, and the 
     		- last one is the file name. The content of 
     		- the file "max_path_depth_512" is filled 
     		- with characters ' max_path_depth_512'.
     * BUFSIZE = 44 
********************************************************/

extern int test_11()
{
	char all_name[1024*1024] = "../files/default/";
	char name[50] = {0};
	for(int i = 1;i<=512;i++)
	{
		sprintf(name,"max_path_depth_%d/",i);
		strcpy(&all_name[strlen(all_name)],name);
		mkdir(all_name,0777);
		memset(name,0,sizeof(name));
	}
	strcpy(&all_name[strlen(all_name)],"max_path_depth_512");
	char buf[44] = "max_path_depth_512max_pa\
th_depth_512max_path";
	int fd = open(all_name,O_RDWR|O_CREAT,0444);
    if(fd < 0)
    {
        PERROR("open fail");
    }
	int ret = write(fd,buf,sizeof(buf));
    
    if(ret < 0)
  	{
        PERROR("write fail");
    }
}
/*************test_12*************************************
     * Description:The content of the file is filled with
     			- character sequence 'read-write'.
				The permission of the file is 0666 in 
				octal (part of the mode (rf_mode or st_mode
				) value 0x81B6).  
     * BUFSIZE = 10 
********************************************************/
extern int test_12(__FILES__ *file)
{
	strcpy(file->path,"../files/default/permission/readW\
ritePermission");
    strcpy(file->buf,"read-write");
    file->WriteSize = 10;
    file->mode = 0666;
}
/*************test_13*************************************
     * Description:This file name contains all printable 
     			characters. The content of this file is 
     			its full path in this ROMFS image. 
     * BUFSIZE = 10 
********************************************************/
extern int test_13(__FILES__ *file)
{
	strcpy(file->path,"../files/default/DirWithAllPossi\
bleCharFile/abcdefghijklmnopqrstuvwxyz1234567890ABCDEFGH\
IJKLMNOPQRSTUVWXYZ`~1!@#$%^&*()-_=+[{]}\\|;:'\",<.>?");
    strcpy(file->buf,"/DirWithAllPossibleCharFile/abcdef\
ghijklmnopqrstuvwxyz1234567890ABCDEFGHIJKLMNOPQRSTUVWXYZ\
`~1!@#$%^&*()-_=+[{]}\\|;:'\",<.>?");
    file->WriteSize = 128;
}
/*************test_14*************************************
     * Description:The value of the first byte of this file
     			is 1, the value of the second byte is 2, 
     			the value of the third byte is 3, ..., and
     			the value of the 128th byte is 128. 
     * BUFSIZE = 128
********************************************************/
extern int test_14(__FILES__ *file)
{
	mkdir("../files/default/DirWithShortestFileName",0777);
	strcpy(file->path,"../files/default/DirWithShortestFileName/f");
	int i;
    for (i = 0;i<128;i++)
    {
        file->buf[i] = i;
    }
    file->WriteSize = 128;
}
/*************test_15*************************************
     * Description:The file name is 254 characters 'f'. The
     			size of the file is 200 Bytes, and the 	
     			content of the file is filled with character
     			 ']'.
     * BUFSIZE = 128
********************************************************/
extern int test_15(__FILES__ *file)
{
	mkdir("../files/default/DirWithLongestFileName",0777);
	strcpy(file->path,"../files/default/DirWithLongestFileName/");
	int i = strlen(file->path);
    int n = i;
    for (i; i < 254+n; i++)
    {
        file->path[i] = 'f';
    }
    file->path[i] = 0;
    for (i=0;i<200; i++)
    {
        file->buf[i] = '[';
    }
    file->buf[i] = 0;
    file->WriteSize = 200;
}



int add_list()
{
    test[0] = test_1;test[1] = test_2;
    test[2] = test_3;test[3] = test_4;
    test[4] = test_5;test[5] = test_6;
    test[6] = test_7;test_11();
    /*test[7] = test_8;
    test[8] = test_9;*/
    test[7] = test_10;test[8] = test_12;
    test[9] = test_13;test[10] = test_14;
    test[11] = test_15;
    
}




















