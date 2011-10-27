#include <INCVIDEO.H>
#include <SIGNAL.H>
#include <LOGIC.H>

/*----------------------------------------------------------------------------
                     TESTE DE ERRO DE FUNCAO DE PONTO FLUTUANTE
----------------------------------------------------------------------------*/
VD_VOID VIDEO_LOGIC_float_error(VD_VOID)
{
 VIDEO_LOGIC_erro_float_ = TRUE;
 _fpreset();
}


