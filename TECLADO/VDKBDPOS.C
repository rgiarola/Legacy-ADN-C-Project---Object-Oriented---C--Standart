#include <INCVIDEO.H>

INT2 VIDEO_lepos(col,lin,ascii,scan)
INT2   col,
      lin;
BYTE  *ascii,
      *scan;
{
 VD_gtxy(col,lin);
 *ascii = *scan = B(0);
 VIDEO_getkbd(ascii,scan);
 return(TRUE);
}

