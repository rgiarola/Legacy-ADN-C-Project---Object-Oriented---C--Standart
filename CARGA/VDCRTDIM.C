#include <INCVIDEO.H>

INT2 VIDEO_CRG_display_imagem(tela,num_imagem,flag_campos)
VIDEO_ESTMANUT *tela;
INT2           num_imagem,
               flag_campos;
{
 INT2 ret;

 if (VIDEO_CRG_carrega_objeto(tela,1) && VIDEO_CRG_prepara_tela(tela))
    {
     VIDEO_TABCRGTELA         *strtelacrg;
     VIDEO_IMAGEMTELA         *imagem;
     VIDEO_TELA_ENTRADA_DADOS *telaedit;

     strtelacrg = PTR_CAST(VIDEO_TABCRGTELA,tela->strtelacrg);
     if (num_imagem<=strtelacrg->contimagemsai && num_imagem)
        {
         INT2 auxflag;
         telaedit           = strtelacrg->telasai;
         telaedit->flagtela = FALSE;
         imagem             = strtelacrg->telasai->imagens + num_imagem - 1;

         auxflag = imagem->flagimagem & ~(VIDEO_TELA_ACCEPTCAMPOS|
                                          VIDEO_TELA_DISPCAMPOS  |
                                          VIDEO_TELA_DISPIMAGEM  );
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
         VIDEO_CRG_libera_tela(tela);
         return(ret);
        }
    }
 return(FALSE);
}


