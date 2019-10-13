#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

char* OpenFile(char* configPath) {
    FILE*  config = fopen(configPath,"rt");
    char* myConfig ;
    char c;
    int i = 0;

    if(config != NULL){

        fseek(config,0,SEEK_END);
        int size = ftell(config)+1;
        rewind(config);

        myConfig =(char*) malloc(sizeof(char)*size);
        
        while((c=fgetc(config))!=EOF){
            myConfig[i] = c;
            i+=1;

        }
        myConfig[size] = '\0';

        fclose(config);
        return myConfig;

    } else {

            fprintf(stderr, "File not fond. Check your file path");
    }

    return NULL;
}

int main()
{
    char* configPath = "/Users/mohameddennoun/Desktop/scrappeur/config/Config.sconf";
    char* myConfig = OpenFile(configPath);
    int i = 0;


    if (myConfig != NULL) {
         while(myConfig[i] != EOF){

            printf("%c",myConfig[i]);
            i+=1;

        }
    } else {
        fprintf(stderr ,"config file is empty");

    }

   
    return 0;

}