#include <INCVIDEO.H>

void far *VIDEO_alloc_mem_dos(tam)
INT2 tam;
{
 _BX = (tam+15)>>4;
 _AH = 0X48;
 geninterrupt(0X21);
 if (_FLAGS&VIDEO_DOS_FLAG_CARRY)
     tam = 0;
    else
     tam = _AX; // SegMento Alocado ...

// Aten‡„o Existe Erro Nesta Fun‡„o -> Tam N„o era Inicializado ...
 return(MK_FP(tam,0x0000));
}
