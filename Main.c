#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>


/*

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
struct url_data {
    size_t size;
    char* data;
};

size_t write_data(void *ptr, size_t size, size_t nmemb, struct url_data *data) {
    size_t index = data->size;
    size_t n = (size * nmemb);
    char* tmp;

    data->size += (size * nmemb);

#ifdef DEBUG
    fprintf(stderr, "data at %p size=%ld nmemb=%ld\n", ptr, size, nmemb);
#endif
    tmp = realloc(data->data, data->size + 1); 

    if(tmp) {
        data->data = tmp;
    } else {
        if(data->data) {
            free(data->data);
        }
        fprintf(stderr, "Failed to allocate memory.\n");
        return 0;
    }

    memcpy((data->data + index), ptr, n);
    data->data[data->size] = '\0';

    return size * nmemb;
}

char *handle_url(char* url) {
    CURL *curl;

    struct url_data data;
    data.size = 0;
    data.data = malloc(4096); 
    if(NULL == data.data) {
        fprintf(stderr, "Failed to allocate memory.\n");
        return NULL;
    }

    data.data[0] = '\0';

    CURLcode res;

    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &data);
        res = curl_easy_perform(curl);
        if(res != CURLE_OK) {
                fprintf(stderr, "curl_easy_perform() failed: %s\n",  
                        curl_easy_strerror(res));
        }

        curl_easy_cleanup(curl);

    }
    return data.data;
}



int main(int argc, char* argv[]) {
    char* data;
    //fprintf(stderr, "test \n");

   
    data = handle_url("https://google.fr");

    if(data) {
        printf("test :  %s\n", data);
        free(data);
    }

    return 0;
}
 
 int main()
{

    
    char* configPath = "/Users/mohamed.dennoun/Desktop/scrappeur/config/Config.sconf";
    //char* myConfig = OpenFile(configPath);
    int i = 0;
    CURL *curl;
    CURLcode res;



    curl = curl_easy_init();
        if(curl) {
            fprintf(stderr ,"start test2");
            curl_easy_setopt(curl, CURLOPT_URL, "https://google.fr");
            fprintf(stderr ,"start test2");
            curl_easy_setopt(curl, CURLOPT_HTTP_VERSION, (long)3);
            fprintf(stderr ,"https://api.spacexdata.com/v3/launches/latest");

            
            curl_easy_setopt(curl, CURLOPT_TIMEOUT, 20L);
            
            res = curl_easy_perform(curl);
            fprintf(stderr ,"start test6");
           
            if(res != CURLE_OK) {
                fprintf(stderr ,"start test5");
                fprintf(stderr, "curl_easy_perform() failed: %s\n",
                curl_easy_strerror(res));
            }
            else {
                fprintf(stderr ,"start test4");
            }
            
        
            curl_easy_cleanup(curl);
        }

    if (myConfig != NULL) {
         while(myConfig[i] != EOF){

            //printf("%c",myConfig[i]);
            i+=1;

        }
        
        
    } else {
        fprintf(stderr ,"config file is empty");

    }


 
  


    return 0;

} 



struct MemoryStruct {
  char *memory;
  size_t size;
};
 
static size_t
WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
  size_t realsize = size * nmemb;
  struct MemoryStruct *mem = (struct MemoryStruct *)userp;
 
  char *ptr = realloc(mem->memory, mem->size + realsize + 1);
  if(ptr == NULL) {
    // out of memory! 
    printf("not enough memory (realloc returned NULL)\n");
    return 0;
  }
 
  mem->memory = ptr;
  memcpy(&(mem->memory[mem->size]), contents, realsize);
  mem->size += realsize;
  mem->memory[mem->size] = 0;
 
  return realsize;
}
 
int main(void)
{
  CURL *curl_handle;
  CURLcode res;
 
  struct MemoryStruct chunk;
 
  chunk.memory = malloc(1);  // will be grown as needed by the realloc above 
  chunk.size = 0;   
 
  curl_global_init(CURL_GLOBAL_ALL);
 
  // init the curl session 
  curl_handle = curl_easy_init();
 
  // specify URL to get 
  curl_easy_setopt(curl_handle, CURLOPT_URL, "https://www.google.com/");
 
  // send all data to this function  
  curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
 
  // we pass our 'chunk' struct to the callback function 
  curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, (void *)&chunk);
 
  // some servers don't like requests that are made without a user-agent
  // field, so we provide one 
  curl_easy_setopt(curl_handle, CURLOPT_USERAGENT, "libcurl-agent/1.0");
 
  // get it! 
  res = curl_easy_perform(curl_handle);
 
  // check for errors
  if(res != CURLE_OK) {
    fprintf(stderr, "curl_easy_perform() failed: %s\n",
            curl_easy_strerror(res));
  }
  else {
    
     // Now, our chunk.memory points to a memory block that is chunk.size
     // bytes big and contains the remote file.
     //
     // Do something nice with it!
     
     // Create repository in Mac OS
     system("mkdir -p ./Websites/Google");
     // Create repository in Windows
     //system("md /Websites/Google");
    char* configPath = "/Users/mohamed.dennoun/Desktop/scrappeur/Websites/Google/google.html";
    
    FILE* website = fopen(configPath,"wt+");
    if( website != NULL) {

        
        // mkdir("./helloworld", ACCESSPERMS);
        fputs(chunk.memory, website);
        printf("test passed");
        fclose(website);
        printf("%d", Search_in_File("/Users/mohamed.dennoun/Desktop/scrappeur/Websites/Google/google.html", "href=\""));
    } else {
        printf("file is null");
    }
    
    printf("\n%lu bytes retrieved\n", (unsigned long)chunk.size);
  }
 
  // cleanup curl stuff 
  curl_easy_cleanup(curl_handle);
 
  free(chunk.memory);
 
  // we're done with libcurl, so clean it up
  curl_global_cleanup();
 
  return 0;
}
*/


void Search_in_File(char *fname, char *str) {
	FILE *fp;
	int line_num = 1;
	int find_result = 0;
	char temp[512];
    int cursor = 0;
	
	if((fp = fopen(fname, "r")) == NULL) {
		return;
	}

	while(fgets(temp, 512, fp) != NULL) {
		if((strstr(temp, str)) != NULL) {
			printf("A match found on line: %d\n", line_num);
            printf("A match found on position: %d\n", cursor);
			printf("%s\n", temp);
			find_result++;
            
		}
        cursor++;
		line_num++;
	}

	if(find_result == 0) {
		printf("\nSorry, couldn't find a match.\n");
	}
	
	//Close the file if still open.
	if(fp) {
		fclose(fp);
	}
}

char* ImageFromHtml(char *fname) {
	
    char c;
    char temp[5];
    temp[4] = '\0';
    int iTemp = 0;
    char *pictureFname;
    int pictureFnameSize = strlen( fname ) + 1 +  strlen( ".Link.txt" ) + 1; 
    /* Memory allocation and copy */
    pictureFname = (char *) malloc( pictureFnameSize );
    strcpy( pictureFname, fname );
    strcat( pictureFname, ".Link.txt" );
    FILE *fpicture = fopen(pictureFname, "w");
    FILE *fhtml = fopen(fname, "r");
    
	


	if(fhtml != NULL){

        int srct = 0;
        int imgt = 0;
        int carriageAdd = 0;
        int domainAdd = 0;
        c=fgetc(fhtml);
        
        while(c != EOF){
            c=fgetc(fhtml);
            if(iTemp < 4){
                temp[iTemp] = c;
                iTemp += 1;
                
            } else {
              
                
                temp[0] = temp[1];
                temp[1] = temp[2];
                temp[2] = temp[3];
                temp[3] = c;
                iTemp += 1;
            }

            if(strcmp(temp,"<img") == 0){
                imgt = 1;
            }
            if(imgt == 1) {
                if(strcmp(temp," src") == 0){
                    
                    srct = 1;
                    fseek(fhtml,2,SEEK_CUR);
                    c=fgetc(fhtml);
                }
            }
            if(imgt == 1 && srct == 1) {
                
                if(c=='"') {
                    srct = 0;
                    imgt = 0;
                    carriageAdd = 1;
                    continue;
                }
                fputc(c,fpicture);
            }

            if(carriageAdd == 1 && imgt == 0 && srct == 0) {
                fputc('\n',fpicture);
                carriageAdd = 0;
            }




        }
        fclose(fhtml);
        fclose(fpicture);
        return pictureFname;

    } 
    fprintf(stderr, "File not fond. Check your file path");
    return NULL;
    
}


void HtmlDownload(char *url, char *outputFilePath) {

    CURL *curl;
    FILE *fp;
    CURLcode res;
    // Create repository in Mac OS
    system("mkdir -p ./Websites/Google");
    url = url;
    outputFilePath = outputFilePath;
    curl = curl_easy_init();                                                                                                                                                                                                                                                           
    if (curl)
    {   
        fp = fopen(outputFilePath,"wb");
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, NULL);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
        fclose(fp);
    }   
}

size_t write_data(void *ptr, size_t size, size_t nmemb, FILE *stream) {
    size_t written = fwrite(ptr, size, nmemb, stream);
    return written;
}

char *CheckUrl(char *url, int size, char *domain, int domainSize) {

    if(url[0] == '/') {
        char *checkedUrl;
        checkedUrl = malloc((size + domainSize));
        checkedUrl[(size + domainSize)] = '\0';
        strcpy(checkedUrl, domain);
        strcpy(checkedUrl, url);
        free(checkedUrl);
        return checkedUrl;
    }
    if(url[size - 3] == ';') {
        printf("yes");
        char *checkedUrl;
        checkedUrl = malloc((size - 2));
        memcpy( checkedUrl, &url[0], (size-2) );
        checkedUrl[(size-3)] = '\0';
        free(checkedUrl);
        return checkedUrl;
    }
    return url;

}

void DownloadImages(char *filePath, char* domain, int domainSize) {
    CURL *curl;
    FILE *fp;
    CURLcode res;
    char c;
    char *outfilename = "/Users/mohamed.dennoun/Desktop/scrappeur/Websites/Google/saveimage.jpeg";
    
    

    FILE* file = fopen(filePath,"r");
    if(file != NULL){

        double start = 0;
        int size;
        int nbUrl = 0;

        

        c=fgetc(file);
        while((c)!=EOF){
            
            if(c =='\n') {
                nbUrl += 1;

            }
            c=fgetc(file);
        }
        
        rewind(file);


        c=fgetc(file);
        while((c)!=EOF){
            
            if(c =='\n') {
                size = ftell(file) - start;
                start =ftell(file);
                break;

            }
            c=fgetc(file);
        }
        printf("%d\n", size);

        int i = 0;
        char url [size];
        url[size] = '\0';
        printf("%lu\n",sizeof(url));
        rewind(file);
        while(i < size && c !=EOF){
            c = fgetc(file);
            url[i] = c;
            i += 1;
        }

        //tester
        char *checkUrl = CheckUrl(url, size, domain, domainSize);

        printf("%s\n",url);
        printf("%s\n",checkUrl);
        printf("%d\n", nbUrl);

        curl = curl_easy_init();
        if (curl) {
        fp = fopen(outfilename,"wb");
        curl_easy_setopt(curl, CURLOPT_URL, checkUrl);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
        res = curl_easy_perform(curl);
        /* always cleanup */
        curl_easy_cleanup(curl);
        fclose(fp);

        }


        
        
        

        fclose(file);

    } else {

        fprintf(stderr, "File not fond. Check your file path");
    }
}


int main(void)
{

    char *url = "https://www.google.com/search?hl=fr&biw=1200&bih=859&tbm=isch&sxsrf=ACYBGNRAMdspQa4mGT7-nOMeEU6zZ91eoA%3A1573652595473&sa=1&ei=cwjMXYG_HK-C1fAPxc686Ao&q=nature&oq=nature&gs_l=img.3..0l10.4362.6056..6249...1.0..0.119.388.6j1......0....1..gws-wiz-img.......35i39j0i67j0i131.euJCWi7oBlA&ved=0ahUKEwjBxM_fqOflAhUvQRUIHUUnD60Q4dUDCAc&uact=5";
    char *outputFilePath = "/Users/mohamed.dennoun/Desktop/scrappeur/Websites/Google/google.html";
    HtmlDownload(url,outputFilePath);
    char *cmd = "curl https://www.pexels.com/ | grep img | grep -o src=http.* | grep -o http.* | sed 's/\?.*//' > ./Websites/Google/googleLinks.txt";
    // system(cmd);

    char *imageUrl = "https://unicornify.pictures/avatar/51d623f33f8b83095db84ff35e15dbe8?s=128";

    char* pictureFname = ImageFromHtml(outputFilePath);
    printf("%s\n", pictureFname);
    if(pictureFname != NULL) {
        DownloadImages(pictureFname, "", 0);
    }
    

    

    
    
    return 0;
}