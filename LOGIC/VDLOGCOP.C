#include <INCVIDEO.H>
#include <SIGNAL.H>
#include <LOGIC.H>

/*----------------------------------------------------------------------------
                              CONVERTE OPERANDO
----------------------------------------------------------------------------*/

int VIDEO_LOGIC_converte_operando(objeto,ptr)
VIDEO_LOGIC_OBJETO *objeto;
char			   **ptr;
{
 IDE_DODA *doda;
 int      tamanho,tipo;

 switch(objeto->tipoobjeto)
  {
   case VIDEO_LOGIC_CONST_STRING  :
		tamanho = strlen(objeto->objeto);
        if (VIDEO_ALLOC_MEM((*ptr),tamanho+1) == VD_NULO)
           {
//            printf("ERRO ALOCMEM 1 =  %u\n",tamanho+1);
            return(VIDEO_LOGIC_ALLOCMEM);
           }

		strcpy((*ptr),objeto->objeto);
        objeto->grupo =
		objeto->tipoobjeto = VIDEO_LOGIC_CONST_STRING;
		return(FALSE);

   case VIDEO_LOGIC_CONST_NUMERICA:
		if (VIDEO_ALLOC_MEM((*ptr),sizeof(double)) == VD_NULO)
           {
//            printf("ERRO ALOCMEM 2 =  %u\n",tamanho+1);
            return(VIDEO_LOGIC_ALLOCMEM);
           }

//        printf("Converte Operando %10.6f\n",CDOUBLE(objeto->objeto));
        CDOUBLE((*ptr))    = CDOUBLE(objeto->objeto);
        objeto->grupo =
		objeto->tipoobjeto = VIDEO_LOGIC_CONST_NUMERICA;
		return(FALSE);

   case VIDEO_LOGIC_DODA:
		if ((doda = CTREE_dodaend(objeto->objeto)) == VD_NULO)
			return(VIDEO_LOGIC_DODANDEF);

		if (VIDEO_ALLOC_MEM((*ptr),sizeof(double)) == VD_NULO)
           {
//            printf("ERRO ALOCMEM 3 =  %u\n",tamanho+1);
            return(VIDEO_LOGIC_ALLOCMEM);
           }

        tipo = VIDEO_LOGIC_CONST_NUMERICA;
        switch(doda->ftype)
         {
		  case CT_CHARU :CDOUBLE((*ptr)) = CBYTE(doda->fadr);
                    break;
          case CT_CHAR  :CDOUBLE((*ptr)) = D(*(PTR_CAST(signed char,doda->fadr)));
                    break;
		  case CT_INT2U :CDOUBLE((*ptr)) = CWORD(doda->fadr);
                    break;
		  case CT_INT2	:CDOUBLE((*ptr)) = CINT(doda->fadr);
                    break;
		  case CT_INT4U :CDOUBLE((*ptr)) = CDWORD(doda->fadr);
                    break;
		  case CT_INT4	:CDOUBLE((*ptr)) = CLONG(doda->fadr);
                    break;
		  case CT_SFLOAT:CDOUBLE((*ptr)) = CFLOAT(doda->fadr);
                    break;
		  case CT_DFLOAT:CDOUBLE((*ptr)) = CDOUBLE(doda->fadr);
                    break;
          case CT_TIME  :
		  case CT_DATE	:CDOUBLE((*ptr)) = CDWORD(doda->fadr);
                    break;
		  case 0 :	tipo = VIDEO_LOGIC_CONST_STRING;
					VIDEO_FREE_ALLOC_MEM((*ptr));
					if ((VIDEO_ALLOC_MEM((*ptr),(doda->flen+1))) == VD_NULO)
                       {
//                        printf("ERRO ALOCMEM 4 =  %u\n",tamanho+1);
                        return(VIDEO_LOGIC_ALLOCMEM);
                       }
					VIDEO_movbloco((*ptr),doda->fadr,doda->flen);
					*((*ptr)+doda->flen) = 0;
					break;

		  default :return(VIDEO_LOGIC_TIPODODA);
		 }

        objeto->grupo =
		objeto->tipoobjeto = tipo;
		return(FALSE);

   default:return(VIDEO_LOGIC_TIPOBJETO);
  }
}



