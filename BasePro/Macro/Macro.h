
#define STRNCPY(Des,Source,size)\
    if(Source){\
        strncpy(Des,Source,size);\
    }\
	else{;}


#define MEMCPY(Des,Source,size)\
    if(Source && Des) \
        memcpy(Des,Source,size)

#define FREE(P) if(0!=P){free(P); P=0;}
#define MALLOC(T) ((T *)malloc(sizeof( T )));


#define CLOSE_SOCK(sock) if(-1!=sock)\
	{ \
		shutdown(sock,2); \
		close(sock); \
		sock = -1;\
	}

#define MAX(max,min) ( max>min )?max:min
#define MIN(max,min) ( max<min )?max:min


