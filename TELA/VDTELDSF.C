#include <INCVIDEO.H>

VD_VOID VIDEO_TELA_display_faixa(mensagem)
char *mensagem;
{
 INT2 tamanho;
 char mensfaixa[80];

 strcpy(mensfaixa,VIDEO_texto_faixa);

 strcat(mensfaixa,mensagem);
 tamanho = strlen(mensfaixa);
 mensfaixa[tamanho]   = '>';
 mensfaixa[tamanho+1] = 0;
 VIDEO_mostra_mens_erro(mensfaixa,TRUE);
}
