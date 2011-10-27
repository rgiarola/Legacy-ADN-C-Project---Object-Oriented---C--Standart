#include <INCVIDEO.H>

VIDEO_keypos(col,lin,ascii,scan)
INT2   col,
      lin;
BYTE  *ascii,
      *scan;
{
 VD_gtxy(col,lin);
 *ascii = *scan = B(0);
 return(VIDEO_getkey(ascii,scan));
}
