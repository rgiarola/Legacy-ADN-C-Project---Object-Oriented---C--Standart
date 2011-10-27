#include <INCVIDEO.H>

INT2 VIDEO_EDITA_campo_testanum(buffer,num,pos,ins,autos,tam)
char *buffer,
     num;
INT2  pos,
     ins,
     autos,
     tam;
{
 char  *aux  = buffer;
 BYTE  ponto,
       sinal;

 ponto = sinal = FALSE;

 while(tam--)
  {
   switch(*aux)
    {
     case '.': if (!autos&VIDEO_EDITA_EDPONTO)
                  return(FALSE);
               ponto = 1;
               break;

     case '-': if (!autos&VIDEO_EDITA_SINALMENOS)
                  return(FALSE);
               sinal = 1;
               break;

     case '+': if (!autos&VIDEO_EDITA_SINALMAIS)
                  return(FALSE);
               sinal = 1;
               break;
    }
    ++aux;
  }
 
 if (num == '.')
    {
     if (!(autos&VIDEO_EDITA_EDPONTO) || (sinal && !pos && ins) ||
         (ponto && ins) || (ponto && (*(buffer + pos) != '.')))
         return(FALSE);
    }	
  else
    if (num == '-')
       {
        if ((pos > 0) || (!pos && ins && sinal) ||
                  !(autos&VIDEO_EDITA_SINALMENOS))
           return(FALSE);
       }
     else
       if (num == '+')
          {
           if ((pos > 0) || (!pos && ins && sinal) ||
                        !(autos&VIDEO_EDITA_SINALMAIS))
              return(FALSE);
          }
        else
          {
           if (sinal && !pos && ins)
               return(FALSE);

           if (num > '9' || num < '0')
              return(FALSE);
          }
 return(TRUE);
}
