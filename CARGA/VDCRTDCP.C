#include <INCVIDEO.H>

VD_VOID VIDEO_TELA_disp_campo(tabcampo,campos,param,servico,flaguser)
VIDEO_CAMPO_TELA  *tabcampo;
char              **campos;
VIDEO_NUCLEO_SERV **param;
INT2               servico,
                  flaguser;
{
 VIDEO_CAMPO_TELA *work;
 INT2              contcampo,
                  numcampos;

 numcampos = (*param)->VIDEO_numcampos;

 while(*campos)
  {
   contcampo = 0;
   work      = tabcampo;

   while(contcampo < numcampos)
    {
     if (!strcmp(work->dodacampo,*campos))
        {
         if (servico&VIDEO_FLAGPROTEGE_CAMPO)
             work->status |= VIDEO_EDITA_PROTEGIDO;

         if (servico&VIDEO_FLAGDESPROTEGE_CAMPO)
             work->status &= ~VIDEO_EDITA_PROTEGIDO;

         if (servico&VIDEO_FLAGMOSTRA_CAMPO)
             work->status &= ~VIDEO_EDITA_NAOMOSTRA;

         if (servico&VIDEO_FLAGNAOMOSTRA_CAMPO)
             work->status |= VIDEO_EDITA_NAOMOSTRA;

         if (servico&VIDEO_FLAGTROCA_CAMPO)
             work->status &= ~VIDEO_EDITA_NAOTROCA;

         if (servico&VIDEO_FLAGNAOTROCA_CAMPO)
             work->status |= VIDEO_EDITA_NAOTROCA;

         if (servico&VIDEO_DISPLAY_CAMPO)
             VIDEO_TELA_display_campos(work,1,*param,flaguser);
        }
     ++contcampo;
     ++work;
    }
   ++campos;
  }
}

