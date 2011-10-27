#include <INCVIDEO.H>

INT2 VIDEO_CALC_intercepta_caracter(ascii,scan,flag)
BYTE *ascii,
     *scan;
INT2 flag;
{
 if (flag)
    {
     if (VIDEO_CALC_status&VIDEO_CALC_ERRO)
         if (!VIDEO_CALC_backascii)
            {
             VIDEO_CALC_status &= ~VIDEO_CALC_ERRO;
             VIDEO_CALC_backscan  = *scan;
             VIDEO_CALC_backascii = *ascii;
             *ascii = 'A';
             *scan  = ALT_A;
             VD_GETBUF(BCALC_status,char) = ' ';
             if (VIDEO_CALC_funcao_teclado)
                (*VIDEO_CALC_funcao_teclado)(ascii,scan,flag);
             return(TRUE);
            }

     if (VIDEO_CALC_status&VIDEO_CALC_REDISPLAY)
         if (!VIDEO_CALC_backascii)
             if (*scan)
                 if ((*ascii >= '0' && *ascii <= '9') ||
                     (*ascii == '.'))
                    {
                     VIDEO_CALC_backscan  = *scan;
                     VIDEO_CALC_backascii = *ascii;
                     *ascii = CTRL_Y;
                     *scan  = SCAN_Y;
                     VIDEO_CALC_status &= ~VIDEO_CALC_REDISPLAY;
                    }
    }
 if ((*ascii >= '0' && *ascii <= '9') ||
     (*ascii == '.'))
     VIDEO_CALC_status |= (VIDEO_CALC_DIGITACAO|VIDEO_CALC_NUMERO);

 if (VIDEO_CALC_funcao_teclado)
    (*VIDEO_CALC_funcao_teclado)(ascii,scan,flag);

 return(TRUE);
}

