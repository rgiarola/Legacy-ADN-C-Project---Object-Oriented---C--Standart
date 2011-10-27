#include <INCVIDEO.H>
/* ok*/
INT2 VIDEO_TELA_consiste_saida(campoedit,campo,buffer)
VIDEO_EDITA_CAMPO *campoedit;
VIDEO_CAMPO_TELA  *campo;
char              *buffer;
{
 char	*aux,
        buffer_aux[30],
        *ptrwork;
 INT2    tamaux,
        decimais;
 double doubleaux;

 decimais = 0;
 if (campoedit->tipo && campoedit->decimais)
    {
     decimais = campoedit->decimais;
     doubleaux = 1;
     while(decimais--)
           doubleaux *= 10;
     sprintf(buffer_aux,"%1.0f",atof(buffer) * doubleaux);
     ptrwork = buffer_aux;
    }
  else
    ptrwork = buffer;

 tamaux = strlen(ptrwork) + (decimais!=0);

 if (tamaux > campoedit->tamanho)
     VIDEO_copbloco(ptrwork,ptrwork+tamaux-campoedit->tamanho,
                                         campoedit->tamanho+1);
 switch(campo->tipo)
  {
   case VIDEO_CAMPO_BYTE:
        CBYTE(campo->buffer_binario)  = B(atoi(ptrwork));
        break;

   case VIDEO_CAMPO_WORD:
        CWORD(campo->buffer_binario)  = W(atol(ptrwork));
        break;

   case VIDEO_CAMPO_DWORD:
        CDWORD(campo->buffer_binario) = DW(strtoul(ptrwork,&aux,10));
        break;

   case VIDEO_CAMPO_SHINT:
        CCHAR(campo->buffer_binario)  = C(atoi(ptrwork));
        break;

   case VIDEO_CAMPO_INT:
        CINT(campo->buffer_binario)   = I(atoi(ptrwork));
        break;

   case VIDEO_CAMPO_LONG:
        CLONG(campo->buffer_binario)  = atol(ptrwork);
        break;

   case VIDEO_CAMPO_DOUBLE:
        doubleaux = 1;
        while(campoedit->decimais--)
             doubleaux *= 10;
        CDOUBLE(campo->buffer_binario) = atof(ptrwork);
        break;

   case VIDEO_CAMPO_DATA:
        CDWORD(campo->buffer_binario) = DW(strtoul(ptrwork,&aux,10));

   case VIDEO_CAMPO_CARACTER:
        *campo->buffer_binario = *ptrwork;
        break;

   case VIDEO_CAMPO_STRING:
        if ((aux = strchr(ptrwork,' ')) != VD_NULO)
           if (aux == ptrwork)
              {
               while(*++aux == ' ');
               if (*aux)
                   VIDEO_copbloco(ptrwork,aux,strlen(aux)+1);
                else
                   *ptrwork = '\0';
              }
        tamaux = strlen(ptrwork);
        aux = ptrwork + tamaux - (tamaux > 0);
        while(*aux == ' ' && aux != ptrwork)
             --aux;
        *(aux + 1) = '\0';
        tamaux = strlen(ptrwork);
        VIDEO_setmem(campo->buffer_binario,campoedit->tamanho+1,0);
        strcpy(campo->buffer_binario,ptrwork);
        break;
  }
 return(TRUE);
}

