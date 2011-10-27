#include <INCVIDEO.H>
/* ok*/
INT2 VIDEO_TELA_linha_anterior(campos,param)
VIDEO_CAMPO_TELA  **campos;
VIDEO_NUCLEO_SERV **param;
{
 VIDEO_CAMPO_TELA *campaux1, *campaux2, *campaux3,
                  *maior,     *menor,   *inicio, *fim;
 INT2              contcamp;

 inicio = fim = PTR_CAST(VIDEO_CAMPO_TELA,(*param)->VIDEO_campos);
 fim = PTR_CAST(VIDEO_CAMPO_TELA,(
       (PTR_CAST(BYTE,fim)+
       (*param)->VIDEO_tamcampo * ((*param)->VIDEO_numcampos - 1))));

 campaux1 = campaux2 = (*campos) == inicio ? fim : (*campos) - 1;

 for (contcamp = 0;(*campos)->lin == campaux2->lin &&
                          contcamp < (*param)->VIDEO_numcampos;++contcamp)
      campaux2 = campaux2 == inicio ? fim : --campaux2;

 if ((*campos)->lin == campaux2->lin)
    {
     (*campos) = campaux1;
     return(TRUE);
    }
 menor = VIDEO_NILL(VIDEO_CAMPO_TELA);
 campaux3 = maior = campaux2;
 for (contcamp = 0;campaux3->lin == campaux2->lin &&
                         contcamp < (*param)->VIDEO_numcampos;++contcamp)
     {
      if ((*campos)->col <= campaux2->col)
         maior = campaux2;
      if ((*campos)->col >= campaux2->col)
         {
          menor = campaux2;
          break;
         }
      campaux2 = campaux2 == (inicio) ? (fim) : --campaux2;
     }

 if (!menor)
    {
     (*campos) = maior;
     return(TRUE);
    }

 (*campos) = (((*campos)->col - menor->col) >=
                  (maior->col - (*campos)->col)) ?  maior : menor;
 return(TRUE);
}
