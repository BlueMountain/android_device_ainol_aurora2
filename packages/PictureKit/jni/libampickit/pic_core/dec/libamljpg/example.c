#include "amljpeg.h"
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
//#include <malloc.h>
int main(int argc, const char *argv[])
{
    int width, height ,mode,flag,i;    
    char* outputdata;
    aml_image_info_t* image_info;
    if(argc < 5){        
        printf("Amlogic jpeg decoder API \n");
        printf("usage: output [filename] [width] [height] [mode] [flag]\n");
        printf("options :\n");
        printf("         filename : jpeg url in your root fs\n");
        printf("         width    : output width\n");
        printf("         height   : output height\n");
        printf("         mode     : 0/keep ratio  1/crop image 2/stretch image\n");
        printf("         flag     : 0/disable display 1/antiflicking disable&enable display  2/antiflicking enable&enable display \n ");
        return -1;    
    }else{
        printf("%s\n", argv[1]);
    }  
    width =  atoi(argv[2]);
    if((width <1)||(width > 1920)){
        printf("invalid width \n");
        return -1;    
    }
    height = atoi(argv[3]);
    if((height <1)||(height > 1080)){
        printf("invalid height \n");
        return -1;    
    }    
    mode  =  atoi(argv[4]);
    flag  =  atoi(argv[5]);    
    if((mode <0)||(mode > 2)){
        printf("invalid mode \n");
        return -1;    
    }    
    printf("url    is %s ;\n", argv[1]);
    printf("width  is %d ;\n", width);
    printf("height is %d ;\n", height);
    printf("mode   is %d ;\n", mode);
    if(amljpeg_init()<0 ) {
		printf("fucking cmem initing error, decode exited\n");
		exit(1);
	}
    image_info = read_jpeg_image((char*)argv[1],width,height,mode,flag,flag,0);
    if(image_info){
        printf("output image width is %d\n", image_info->width);
        printf("output image height is %d\n", image_info->height);
        printf("output image depth is %d\n", image_info->depth);
        printf("output image bytes_per_line is %d\n", image_info->bytes_per_line);
        printf("output image nbytes   is %d\n", image_info->nbytes);
    }
    if(image_info){
        free(image_info);    
        image_info = NULL;
    }
    amljpeg_exit();      
    return 0;   
}
