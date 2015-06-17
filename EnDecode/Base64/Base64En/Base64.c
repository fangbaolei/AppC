#include <stdio.h>
#include <string.h>
const static char base64chars[]=
"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
void Base64Encode1( char *from, char *to, int len)
{
  while (len) {
    unsigned long k;
    int c;

    c = (len < 3) ? len : 3;
    k = 0;
    len -= c;
    while (c--)
      k = (k << 8) | *from++;
    *to++ = base64chars[ (k >> 18) & 0x3f ];
    *to++ = base64chars[ (k >> 12) & 0x3f ];
    *to++ = base64chars[ (k >> 6) & 0x3f ];
    *to++ = base64chars[ k & 0x3f ];
  }
  *to++ = 0;
}
void Base64Encode2(const char *InStr, char *OutStr)
{
    unsigned char ibuf[3] = {0};
    unsigned char obuf[4] = {0};
    int i = 0;
    int inputparts = 0;

    while(*InStr) 
    {   
        for (i =  0; i < 3; i++) 
        {   
            if(*InStr) 
            {   
                inputparts++;
                ibuf[i] = *InStr;
                InStr++;
            }   
            else
            {
                ibuf[i] = 0;
            }
        }

        obuf [0] = (ibuf [0] & 0xFC) >> 2;
        obuf [1] = ((ibuf [0] & 0x03) << 4) | ((ibuf [1] & 0xF0) >> 4);
        obuf [2] = ((ibuf [1] & 0x0F) << 2) | ((ibuf [2] & 0xC0) >> 6);
        obuf [3] = ibuf [2] & 0x3F;

          switch(inputparts)
          {
              case 1: /* only one byte read */
                  sprintf(OutStr, "%c%c==",
                      base64chars[obuf[0]],
                      base64chars[obuf[1]]);
                  break;
              case 2: /* two bytes read */
                  sprintf(OutStr, "%c%c%c=",
                      base64chars[obuf[0]],
                      base64chars[obuf[1]],
                      base64chars[obuf[2]]);
                  break;
              default:
                  sprintf(OutStr, "%c%c%c%c",
                      base64chars[obuf[0]],
                      base64chars[obuf[1]],
                      base64chars[obuf[2]],
                      base64chars[obuf[3]] );
              break;
        }
        OutStr += 4;
    }
    *OutStr=0;
}
char  BaseToChr( unsigned char n )   
{   
    n &= 0x3F;   
    if ( n < 26 )   
        return ( char )( n + 'A' );   
    else if ( n < 52 )   
        return ( char )( n - 26 + 'a' );   
    else if ( n < 62 )   
        return ( char )( n - 52 + '0' );   
    else if ( n == 62 )   
        return '+';   
    else   
        return '/';   
}   

/******************************
函数功能: Base64加密，用于附件内容的加密


*******************************/
int Base64Encode3( char * const aDest, const char * aSrc, int aLen )   
{   
    char        * p = aDest;   
    int           i;   
    unsigned char t;   
   
    for ( i = 0; i < aLen; i++ )   
    {   
        switch ( i % 3 )   
        {   
        case 0 :   
            *p++ = BaseToChr( *aSrc >> 2 );   
            t = ( *aSrc++ << 4 ) & 0x3F;   
            break;   
        case 1 :   
            *p++ = BaseToChr( t | ( *aSrc >> 4 ) );   
            t = ( *aSrc++ << 2 ) & 0x3F;   
            break;   
        case 2 :   
            *p++ = BaseToChr( t | ( *aSrc >> 6 ) );   
            *p++ = BaseToChr( *aSrc++ );   
            break;   
        }   
    }   
    if ( aLen % 3 != 0 )   
    {   
        *p++ = BaseToChr( t );   
        if ( aLen % 3 == 1 )   
            *p++ = '=';   
        *p++ = '=';   
    }   
    *p = 0;
    return ( p - aDest );
}   
int Base64Encode4(char *s,char *d)   
{   
        char CharSet[64]=   
        {   
                'A','B','C','D','E','F','G','H',   
                'I','J','K','L','M','N','O','P',   
                'Q','R','S','T','U','V','W','X',   
                'Y','Z','a','b','c','d','e','f',   
                'g','h','i','j','k','l','m','n',   
                'o','p','q','r','s','t','u','v',   
                'w','x','y','z','0','1','2','3',   
                '4','5','6','7','8','9','+','/'   
        };   
        unsigned char In[3];   
        unsigned char Out[4];   
        int cnt=0;   
        if(!s||!d) return 0;   
        for(;*s!=0;)   
        {   
                if(cnt+4>76)   
                {   
                        *d++='\n';   
                        cnt=0;   
                }   
                if(strlen((char*)s) >=3)   
                {   
                        In[0]=*s;   
                        In[1]=*(s+1);   
                        In[2]=*(s+2);   
                        Out[0]=In[0]>>2;   
                        Out[1]=(In[0]&0x03)<<4|(In[1]&0xf0)>>4;   
                        Out[2]=(In[1]&0x0f)<<2|(In[2]&0xc0)>>6;   
                        Out[3]=In[2]&0x3f;   
                        *d=CharSet[Out[0]];   
                        *(d+1)=CharSet[Out[1]];   
                        *(d+2)=CharSet[Out[2]];   
                        *(d+3)=CharSet[Out[3]];   
                        s+=3;   
                        d+=4;   
                }   
                else if(strlen((char*)s)==1)   
                {   
                        In[0]=*s;   
                        Out[0]=In[0]>>2;   
                        Out[1]=(In[0]&0x03)<<4|0;   
                        *d=CharSet[Out[0]];   
                        *(d+1)=CharSet[Out[1]];   
                        *(d+2)='=';   
                        *(d+3)='=';   
                        s+=1;   
                        d+=4;   
                }   
                else if(strlen((char*)s)==2)   
                {   
                        In[0]=*s;   
                        In[1]=*(s+1);   
                        Out[0]=In[0]>>2;   
                        Out[1]=(In[0]&0x03)<<4|(In[1]&0xf0)>>4;   
                        Out[2]=(In[1]&0x0f)<<2|0;   
                        *d=CharSet[Out[0]];   
                        *(d+1)=CharSet[Out[1]];   
                        *(d+2)=CharSet[Out[2]];   
                        *(d+3)='=';   
                        s+=2;   
                        d+=4;   
                }   
                cnt+=4;   
        }   
        *d='\0';   
        return 1;   
}  

int main(void)
{
	char Src[512] = "abd123:eds4487";
	char Dst[512] = {0};
	//unsigned char Src1[512] = "abd123:eds4487";
	//unsigned char Dst1[512] = {0};
	Base64Encode1(Src,Dst,strlen(Src));
	printf("Base64 encode1 :%s\n",Dst);
    memset(Dst,0,sizeof(Dst));
	Base64Encode2(Src,Dst);
	printf("Base64 encode2 :%s\n",Dst);
    memset(Dst,0,sizeof(Dst));
	Base64Encode3(Dst,Src,strlen(Src));
	printf("Base64 encode3 :%s\n",Dst);
    memset(Dst,0,sizeof(Dst));
	Base64Encode4(Src,Dst);
	printf("Base64 encode4 :%s\n",Dst);
	return 0;
}
