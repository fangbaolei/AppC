#ifndef __MY_COMMON_H__
#define __MY_COMMON_H__




#define G_OS_UNIX

#ifndef	MIN
#define	MIN(a,b) (((a)<(b))?(a):(b))
#define   MAX(a,b) (((a)>(b))?(a):(b))
#endif

#define UNICODE_VALID(Char)                   \
    ((Char) < 0x110000 &&                     \
     (((Char) & 0xFFFFF800) != 0xD800))


typedef char   int8;
typedef short  int16;
typedef int      int32;
typedef long long int64;
typedef int8    boolean;

typedef unsigned char   uint8;
typedef unsigned short  uint16;
typedef unsigned int   uint32;
typedef unsigned long long uint64;

#define true                            1
#define false                           0
#define TRUE                          1
#define FALSE                         0
#define True                            1
#define False                           0




/* Define min and max constants for the fixed size numerical types */
#define G_MININT8	((int8)  0x80)
#define G_MAXINT8	((int8)  0x7f)
#define G_MAXUINT8	((uint8) 0xff)

#define G_MININT16	((int16)  0x8000)
#define G_MAXINT16	((int16)  0x7fff)
#define G_MAXUINT16	((uint16) 0xffff)

#define G_MININT32	((0x80000000)
#define G_MAXINT32	(0x7fffffff)
#define G_MAXUINT32	(0xffffffff)

#define G_GINT64_CONSTANT(val) (val##L)

#define G_MININT64	((int64) G_GINT64_CONSTANT(0x8000000000000000))
#define G_MAXINT64	G_GINT64_CONSTANT(0x7fffffffffffffff)
#define G_MAXUINT64	G_GINT64_CONSTANT(0xffffffffffffffffU)


#define GPOINTER_TO_INT(p) ((int32)  (int32) (p))
#define GPOINTER_TO_UINT(p) ((uint32) (uint32) (p))
#define GUINT_TO_POINTER(u) ((void*) (uint32) (u))
#define GINT_TO_POINTER(i) ((void*) (uint32) (i))

#define GUINT64_FROM_BE(val)		((uint64) (val))
#define GUINT64_TO_BE(val)		((uint64) (val))




#endif //end of __COMMON_H
