#include "test.h"

int main ()
{
    add_list();
    __FILES__ test_file;
    for (int i=0;i<TEST_COUNT; i++)
    {
        memset(&test_file,0,sizeof(test_file));
        test_file.mode = 0444;
        if(test[i] == NULL)
        {
            printf("test sucess!\n");
            return 0;
        }
        test[i](&test_file);
        printf("%s\n",test_file.path);
        int err = Create_File(test_file.path,
                             test_file.buf,
                             test_file.WriteSize,
                             test_file.mode);
        if (err == -1)
        {
            PERROR("ERROR");
        }
    }
    return 0; 
}
