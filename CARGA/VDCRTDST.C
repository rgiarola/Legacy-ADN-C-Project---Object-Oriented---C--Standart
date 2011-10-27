#include <INCVIDEO.H>

INT2 VIDEO_CRG_dispara_tela(tela)
VIDEO_ESTMANUT *tela;
{
 VIDEO_TABCRGTELA *strtelacrg;
 VIDEO_IMAGEMTELA *imagem;
 INT2              cont,ret;

 strtelacrg = PTR_CAST(VIDEO_TABCRGTELA,tela->strtelacrg);
 imagem = strtelacrg->imagemsai;

 for (cont = 0;cont < strtelacrg->contimagemsai;cont++,imagem++)
     {
      imagem->flagimagem |= (VIDEO_TELA_DISPIMAGEM |
                             VIDEO_TELA_DISPCAMPOS |
                             VIDEO_TELA_STATUS     |
                             VIDEO_TELA_INICIMAGEM |
                             VIDEO_TELA_ACCEPTCAMPOS);
      imagem->seqdisp     = 0;

     }

 strtelacrg->telasai->seqdisp       = 0;
 strtelacrg->telasai->flagtela      = VIDEO_TELA_SALVATELA|
                                      VIDEO_TELA_FLAGPOPWIN;
 strtelacrg->telasai->imagem_accept = 0;

/*
 do
  {
   ret = I(VIDEO_NUCLEO_servidor_mspas(strtelacrg->nutelasai));
   switch(ret)
    {
     case I(VIDEO_TELA_EXECUTA_CAMPOS)  :
     case I(VIDEO_TELA_EXECUTA_MENU)    :
     case I(VIDEO_TELA_EXECUTA_PESQUISA):
     case I(VIDEO_TELA_EXECUTA_FIMAGEM) :
     case I(VIDEO_TELA_EXECUTA_FCAMPO)  :
     case I(VIDEO_TELA_EXECUTA_FCONS)   :
     case I(VIDEO_TELA_EXECUTA_MANUT)   :

     default: return(ret);
    }
  }while(TRUE);
*/
 return(I(VIDEO_NUCLEO_servidor_mspas(strtelacrg->nutelasai)));
}

#define VIDEO_TELA_EXECUTA_CAMPOS   VD_MTTECLA(0XFF,0XFF)
#define VIDEO_TELA_EXECUTA_MENU     VD_MTTECLA(0XFE,0XFF)
#define VIDEO_TELA_EXECUTA_PESQUISA VD_MTTECLA(0XFD,0XFF)
#define VIDEO_TELA_EXECUTA_FIMAGEM  VD_MTTECLA(0XFC,0XFF)
#define VIDEO_TELA_EXECUTA_FCAMPO   VD_MTTECLA(0XFB,0XFF)
#define VIDEO_TELA_EXECUTA_FCONS    VD_MTTECLA(0XFA,0XFF)
#define VIDEO_TELA_EXECUTA_MANUT    VD_MTTECLA(0XF9,0XFF)


