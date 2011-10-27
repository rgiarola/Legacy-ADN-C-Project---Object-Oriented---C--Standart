#include <INCVIDEO.H>

INT2 VIDEO_quadro(coli,colf,lini,linf,tipo,cor)
INT2  coli ,colf,
      lini ,linf,
      tipo;
BYTE  cor;
{
   if (VIDEO_teste_4(coli,colf,lini,linf))
      {
       INT2 *aux1,*aux2,
            *aux3,*aux4,vet;
       
       if (!cor)
           VIDEO_setatrib(coli,colf,lini,linf,cor);

       if ((colf-coli+1) < (linf-lini+1))
          {
           aux1 = &lini;
           aux2 = &linf;
           aux3 = &coli;
           aux4 = &colf;
           vet = VIDEO_VET_V;
          }
        else
          {
           aux1 = &coli;
           aux2 = &colf;
           aux3 = &lini;
           aux4 = &linf;
           vet = VIDEO_VET_H;
          }
       do
        {
         VIDEO_tipo_vetor(*aux1,*aux2,*aux3,tipo,cor,vet);
        }while(++*aux3 <= *aux4);
       return(TRUE);
      }
 return (FALSE);
}
