#include <INCVIDEO.H>

INT2 VIDEO_restaura_param_cor(atribfundo,corfundo,atribfrente,corfrente,config)
BYTE   *atribfundo,
       *corfundo,
       *atribfrente,
       *corfrente,
       config;
{
 BYTE  ret;
 ret = B(config & (VD_B7|VD_B6|VD_B5|VD_B4));
 *(atribfundo) = (ret & VD_B7);
 *(corfundo) = B(B(ret>>4) & B(VD_B0|VD_B1|VD_B2));
 ret = B(config & B(VD_B0|VD_B1|VD_B2|VD_B3));
 *(atribfrente) = B(ret & VD_B3);
 *(corfrente) = B(ret & B(VD_B0|VD_B1|VD_B2));
 return(TRUE);
} 

