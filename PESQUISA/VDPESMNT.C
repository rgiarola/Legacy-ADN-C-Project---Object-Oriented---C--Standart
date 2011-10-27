#include <INCVIDEO.H>

INT2 VIDEO_PESQUISA_manutencao(telapesq,param)
VIDEO_PESQUISA_PLANILHA **telapesq;
VIDEO_NUCLEO_SERV       **param;
{
 VIDEO_PESQUISA_PLANILHA  pesquisa;
 VIDEO_TELA_ENTRADA_DADOS *tela;
 VIDEO_CAMPO_TELA         *campo;

 if ((*telapesq)->flagplanilha&VIDEO_PESQUISA_MANUTENCAO)
    {
     pesquisa = **telapesq;

     tela = PTR_CAST(VIDEO_TELA_ENTRADA_DADOS,pesquisa.tela->tela);
     tela->imagem_accept = 0;
     tela->imagens->campos->VIDEO_inicial = 0;
     VIDEO_TELA_dispara_manutencao(&tela,VD_NULO);

     pesquisa.flagplanilha |= VIDEO_PESQUISA_INICIALIZA |
                              VIDEO_PESQUISA_DISPCAMPOS |
                              VIDEO_PESQUISA_DISPCURSOR;
     **telapesq = pesquisa;
    }
 return(TRUE);
}



