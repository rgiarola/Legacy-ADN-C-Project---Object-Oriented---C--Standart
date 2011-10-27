#include <INCVIDEO.H>

VD_VOID VIDEO_quick_sort(esq,dir,testru,tchave,
                     offchave,compara_chave,troca_elemento,tabela)
INT2     esq,   dir, testru,
        tchave,offchave,
        (*compara_chave)(VD_VOID *destino,VD_VOID *origem,WORD tamanho);
VD_VOID (*troca_elemento)(VD_VOID *destino,VD_VOID *origem);
BYTE    *tabela;
{
 INT2  ind1,ind2,cont;
 BYTE *ptr1;

 ind1 = esq;
 ind2 = dir;

 ptr1 = tabela+(((esq + dir)/2)*testru);
 do
   {
     while ((compara_chave((tabela+(ind1*testru)+offchave),
            ptr1+offchave,tchave) < 0) && (ind1 < dir)) ind1++;

     while ((compara_chave((tabela+(ind2*testru)+offchave),
            ptr1+offchave,tchave) > 0) && (ind2 > esq)) ind2--;

     if (ind1 <= ind2)
        {
         (troca_elemento)(tabela+(ind1*testru),tabela+(ind2*testru));
         ++ind1;
         --ind2;
        }

   }while(ind1 <= ind2);

   if (esq < ind2)      
        VIDEO_quick_sort(esq,ind2,testru,tchave,
                         offchave,compara_chave,troca_elemento,tabela);
	   	     
   if (ind1 < dir)      
        VIDEO_quick_sort(ind1,dir,testru,tchave,
                         offchave,compara_chave,troca_elemento,tabela);
 }

