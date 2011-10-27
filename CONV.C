#include <INCVIDEO.H>

int      contlinha = 0;
WORD     posbuffer = 0,flagfim  ;

FILE     *desc = VD_NULO;

DWORD    tamarq;

char *pegalinha(VD_VOID);
char arquivo[100],
     diretorio[50][15],
     diret[50],
     copia[50];
char buflinha[5000];

main()
{
 struct ffblk ff_arq,ff_dir;
 int          cont,contdir,desccp;
 char         *linha;

 cont = 0;

 if (!findfirst("*.*",&ff_dir,16))
    do
     {
      strcpy(diretorio[cont++],ff_dir.ff_name);
     }while(!findnext(&ff_dir));
    else
      exit(0);

 for (contdir = 0;contdir < cont;contdir++)
     {
      if (!strcmp(".",diretorio[contdir]))
         continue;

      if (!strcmp("..",diretorio[contdir]))
         continue;

      strcpy(diret,"C:\\ADN2\\");
      strcat(diret,diretorio[contdir]);

      if (chdir(diret))
         continue;

      mkdir(diretorio[contdir]);

      if (!findfirst("*.c",&ff_arq,0))
          do
           {
            strcpy(arquivo,ff_arq.ff_name);
            desc = (FILE *) 0;
            strcpy(copia,diretorio[contdir]);
            strcat(copia,"\\");
            strcat(copia,arquivo);
            if ((desccp = VD_cria(copia)) <= 0)
               {
                printf("ERRO OPEN %s\n",copia);
                exit(0);
               }
            do
             {
              if ((linha = pegalinha()) != VD_NULO)
                 {
                  testalinha(linha);
                  if (strlen(linha))
                     write(desccp,linha,strlen(linha));
                  write(desccp,"\15\12",2);
                 }
               else
                 break;
             }while(TRUE);
            fclose(desc);
            close(desccp);
           }while(!findnext(&ff_arq));

      if (!findfirst("*.h",&ff_arq,0))
          do
           {
            strcpy(arquivo,ff_arq.ff_name);
            desc = (FILE *) 0;
            strcpy(copia,diretorio[contdir]);
            strcat(copia,"\\");
            strcat(copia,arquivo);
            if ((desccp = VD_cria(copia)) <= 0)
               {
                printf("ERRO OPEN %s\n",copia);
                exit(0);
               }
            do
             {
              if ((linha = pegalinha()) != VD_NULO)
                 {
                  testalinha(linha);
                  if (strlen(linha))
                     write(desccp,linha,strlen(linha));
                  write(desccp,"\15\12",2);
                 }
               else
                 break;
             }while(TRUE);
            fclose(desc);
            close(desccp);
           }while(!findnext(&ff_arq));

      if (!findfirst("*.vdo",&ff_arq,0))
          do
           {
            strcpy(arquivo,ff_arq.ff_name);
            desc = (FILE *) 0;
            strcpy(copia,diretorio[contdir]);
            strcat(copia,"\\");
            strcat(copia,arquivo);
            if ((desccp = VD_cria(copia)) <= 0)
               {
                printf("ERRO OPEN %s\n",copia);
                exit(0);
               }
            do
             {
              if ((linha = pegalinha()) != VD_NULO)
                 {
                  testalinha(linha);
                  if (strlen(linha))
                     write(desccp,linha,strlen(linha));
                  write(desccp,"\15\12",2);
                 }
               else
                 break;
             }while(TRUE);
            fclose(desc);
            close(desccp);
           }while(!findnext(&ff_arq));

      if (!findfirst("*.adn",&ff_arq,0))
          do
           {
            strcpy(arquivo,ff_arq.ff_name);
            desc = (FILE *) 0;
            strcpy(copia,diretorio[contdir]);
            strcat(copia,"\\");
            strcat(copia,arquivo);
            if ((desccp = VD_cria(copia)) <= 0)
               {
                printf("ERRO OPEN %s\n",copia);
                exit(0);
               }
            do
             {
              if ((linha = pegalinha()) != VD_NULO)
                 {
                  testalinha(linha);
                  if (strlen(linha))
                     write(desccp,linha,strlen(linha));
                  write(desccp,"\15\12",2);
                 }
               else
                 break;
             }while(TRUE);
            fclose(desc);
            close(desccp);
           }while(!findnext(&ff_arq));
    }
}

char *pegalinha()
{
 int  lido,cont;
 char *fim,*ptr;

 if (!desc)
     if ((desc = fopen(arquivo,"rt")) == VD_NULO)
        {
         printf("ERRO NA ABERTURA DO ARQUIVO %s %d\n",arquivo,desc);
         exit(0);
        }

  if (feof(desc))
     return(VD_NULO);

  if ((ptr = fgets(buflinha,5000,desc)) == VD_NULO)
     return(VD_NULO);

  if (*ptr == 0X0D)
     ++ptr;

  if (*ptr == 0X0A)
     ++ptr;

  if ((fim = strchr(ptr,0X0D)) != VD_NULO)
     *fim = 0;

  if ((fim = strchr(ptr,0X0A)) != VD_NULO)
     *fim = 0;

  return(ptr);
}

testalinha(linha)
char *linha;
{
 char *ptr,buffer[200];

 if ((ptr = strstr(linha,"//")) != VD_NULO)
    {
     *(ptr+1) = '*';
     strcat(linha,"*/");
    }
}
