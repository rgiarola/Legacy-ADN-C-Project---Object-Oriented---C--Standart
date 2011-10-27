#include <INCVIDEO.H>

void far *VIDEO_free_mem_dos(buffer)
void far *buffer;
{
 _ES = FP_SEG(buffer);
 _AH = 0X49;
 geninterrupt(0X21);
 return(buffer);
}

