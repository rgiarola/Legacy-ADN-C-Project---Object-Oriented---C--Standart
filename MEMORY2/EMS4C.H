/* ems.h */
extern int emsLoaded(void);
extern int emsGetStatus(void);
extern int emsGetFrame(int *);
extern int emsGetPages(int *,int *);
extern int emsAllocate(int ,int *);
extern int emsMapMemory(int, int, int);
extern int emsRelease(int);
extern int emsVersion(int *);
extern int emsSaveMap(int);
extern int emsRestoreMap(int);
extern int emsGetHandles(int *);
extern int emsOwnedPages(int ,int *);
extern int emsPageInfo(int *,int *);
extern int emsPageMap(int,char *,char *,int *);