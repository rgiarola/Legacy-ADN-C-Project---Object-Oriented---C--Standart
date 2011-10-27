#include <INCVIDEO.H>

VIDEO_CRG_display_imagem_carregada(tela,num_imagem,flag_campos)
VIDEO_ESTMANUT *tela;
INT2            num_imagem,
               flag_campos;
{
 VIDEO_TABCRGTELA         *strtelacrg;
 VIDEO_IMAGEMTELA         *imagem;
 VIDEO_TELA_ENTRADA_DADOS *telaedit;
 INT2                      ret;

 strtelacrg             = PTR_CAST(VIDEO_TABCRGTELA,tela->strtelacrg);

 if ( num_imagem<=strtelacrg->contimagemsai && num_imagem)
    {
     INT2 auxflag=0;
     telaedit           = strtelacrg->telasai;
     telaedit->flagtela = FALSE;
     imagem             = strtelacrg->telasai->imagens + num_imagem - 1;

     switch( flag_campos )
       {
        case 2:
               auxflag|= VIDEO_TELA_ACCEPTCAMPOS;
        case 1:
               auxflag|= VIDEO_TELA_DISPCAMPOS;
        case 0:
               auxflag|= VIDEO_TELA_DISPIMAGEM;
               break;
       }
     imagem->flagimagem = (auxflag | VIDEO_TELA_STATUS);

     ret=VIDEO_NUCLEO_servidor_mspas(strtelacrg->nutelasai);

     return(ret);
    }
 return(FALSE);
}

