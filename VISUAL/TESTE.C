#include <INCVIDE.H>

main()
{
 PTR_CAST((int * ()),teste)();

 return(TRUE);



teste:
 {
  printf("teste \n");

  return;
 }
}

