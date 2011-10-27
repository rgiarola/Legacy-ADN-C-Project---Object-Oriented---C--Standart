/***    Turbo C Memory manager header
        (c) R.J.Taylor 1993, 1994
***/

#ifndef MEMORY_IN
#define MEMORY_IN

#ifndef NULL
    #define NULL (void *)0
#endif

/***    Useful typedefs
***/
typedef unsigned mem_hand;

#ifndef ULONG_DEFINED
    typedef unsigned long ulong;
    #define ULONG_DEFINED
#endif

#ifndef BYTE_DEFINED
#ifndef NO_BYTE_REDEFINE
    typedef unsigned char byte;
    #define BYTE_DEFINED
#endif
#endif

/***    Memory manager access functions, allocate, free, put & get
***/
mem_hand    xalloc      (unsigned bytes,unsigned depth);
void        xfree       (mem_hand handle);
int         xput        (byte far *p,unsigned n,mem_hand handle);
byte far   *xget        (unsigned n,mem_hand handle);

/***    Memory handle information functions
***/
unsigned    get_linewidth(mem_hand hand);
unsigned    get_nlines   (mem_hand hand);
ulong       get_memsize  (mem_hand hand);
char       *mem_type     (mem_hand hand);

/***    Strategy selection
***/
int         setXMstrat  (char *s);
void        SetReadMode (mem_hand hand, int mode);

#define X_FAST 0
#define X_SAFE 1

#endif
