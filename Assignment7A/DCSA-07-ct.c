/**
 * DCSA Assignmen7 OPTIMIZING WEIGHTED COLOR TRANSFER USING COLOR DISTANCE
 * This program is used to doing color transfer of bmps.
 * 4104056004 資工四 李家駿
 * Usage: ./DCSA-07-ct [SOURCE_DIRECTORY_NAME] [TARGET_DIRECTORY_NAME]
*/
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include "mybmp.h"
int main(int argc, char *argv[])
{
    int i=1;
    DIR* src_bmp_dir,*tar_bmp_dir;
    char bmp_filename[80],*image_raw; 
    struct dirent *src_ptr,*tar_ptr;
    
    bmpfile src_bmp,tar_bmp;
    if(argc==2)
    {
        //No parameter
        printf("Please enter at least two parameter.\n\tUsage: ./PROGRAM_NAME [SOURCE_DIRECTORY_NAME] [TARGET_DIRECTORY_NAME]\n");
        return 0;
    }

    src_bmp_dir = opendir(argv[1]);     //Read the source dir.
    tar_bmp_dir = opendir(argv[2]);     //Read the target dir.
    if(!src_bmp_dir || !tar_bmp_dir)
    {
        printf("Open directory error.Please check if the directory exists.\n");
        return 0;
    }

    while((src_ptr=readdir(src_bmp_dir))!=NULL )//|| (tar_ptr=readdir(tar_bmp_dir))!=NULL)
    {
        tar_ptr=readdir(tar_bmp_dir);   //read target bmp file from directory.
        if(strlen(src_ptr->d_name)<=4 || is_bmp(src_ptr->d_name)!=0 
            || strlen(tar_ptr->d_name)<=4 || is_bmp(tar_ptr->d_name)!=0 ) continue; //無效檔案
        
        //read source bmp file.
        strcpy(bmp_filename,argv[1]);           //Combine the bmp source file name.
        strcat(bmp_filename,"/");
        strcat(bmp_filename,src_ptr->d_name);
        src_bmp=readbmp(bmp_filename);          //read bmp file.
        printf("read %s\n",bmp_filename);

        //read target bmp file.
        strcpy(bmp_filename,argv[2]);           //Combine the bmp target file name.
        strcat(bmp_filename,"/");
        strcat(bmp_filename,tar_ptr->d_name);
        tar_bmp=readbmp(bmp_filename);          //read bmp file.
        printf("read %s\n",bmp_filename);
        
        //color transfer
        bmp_GWcolortransfer(src_bmp,tar_bmp);

        //Free the memory to avoid memory overflow.
        free(src_bmp.image_raw);
        free(tar_bmp.image_raw);


        /*bmp header*/
        //copyheader_ftof(&res_bmp,src_bmp);

        //Output result to bmp file.
        //outputbmp(bmp_filename,"ct-result",res_bmp,res_bmp.image_raw);
        
        //Free the image raw memory.
    }

    //Close the DIR stream.
    closedir(src_bmp_dir);
    closedir(tar_bmp_dir);
    return 0;
}