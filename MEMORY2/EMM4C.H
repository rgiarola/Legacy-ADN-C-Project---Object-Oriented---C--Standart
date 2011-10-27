/* emm4c.h */
int emmInit(int,int);
int emmDone(void);
int emmAlloc(int);
int emmFree(int);
int emmLock(int,unsigned int *);
int emmUnlock(int);
int emmPages(unsigned int *,unsigned int *);

#define MAKE_FAR_PTR(seg,off) ((void far *)(((unsigned long)(seg)<<16)|(unsigned)(off)))

#define ALREADY_INIT -1
#define NOT_INIT     -2
#define NO_HANDLES   -3
#define NO_PAGES     -4
#define NO_FRAMES    -5
#define MALLOC_FAILS -6
#define BAD_SIZE     -7
#define BAD_HANDLE   -8
#define BAD_PAGE     -9

#define MIN_CODE     -9
#define MAX_CODE     -1
