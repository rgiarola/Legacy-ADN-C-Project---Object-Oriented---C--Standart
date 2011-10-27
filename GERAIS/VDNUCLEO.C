#include <INCVIDEO.H>

#define NUCCAMPOS     param->VIDEO_campos
#define NUCNUMCAMPOS  param->VIDEO_numcampos
#define NUCTAMCAMPO   param->VIDEO_tamcampo
#define NUCINICIAL    param->VIDEO_inicial
#define NUCTABSERV    param->VIDEO_tabserv
#define NUCINICNVALID (NUCINICIAL > NUCNUMCAMPOS || !NUCINICIAL)
#define NUCPOSINICIAL PTR_CAST(VIDEO_TAB_FUNC,(CAST_BYTE(NUCCAMPOS) + \
                     (NUCINICIAL * NUCTAMCAMPO)))

INT2 VIDEO_NUCLEO_servidor_mspas(param)
VIDEO_NUCLEO_SERV  *param;
{
 VIDEO_TAB_FUNC *work;    /* POINTER PARA MANIPULACAO DE CAMPOS  */
 VIDEO_TABSERV  *tabserv; /* POINTER PARA TABELA DE SERVICOS     */
 INT2           conttab,contserv = 0,
                ret;
                
 work = NUCINICNVALID ? NUCCAMPOS : NUCPOSINICIAL;
 do
  {
   if (work->VIDEO_funcao)
      (*work->VIDEO_funcao)(work,param);

   tabserv = param->VIDEO_tabserv;
   ret = param->VIDEO_servrec;
   contserv = 0;
   do
    {
     conttab = 0;
     do
      {
       param->VIDEO_repdisp = FALSE;

       if (ret == *((tabserv->VIDEO_servico) + conttab))
          {
           if (tabserv->VIDEO_funcao)
              {
               if ((*tabserv->VIDEO_funcao)(&work,&param))
                   {
                    if (param->VIDEO_repdisp)
                       {
                        ret = param->VIDEO_servrec;
                        conttab = 0;
                        tabserv = param->VIDEO_tabserv;
                        continue;
                       }
                    break;
                   }
                 else
                   return(param->VIDEO_servrec);
              }
            else
              return(ret);
          }
       ++conttab;
      }while(*((tabserv->VIDEO_servico) + conttab));
     ++tabserv;
     ++contserv;
    }while(tabserv->VIDEO_servico);
  }while(TRUE);
}
