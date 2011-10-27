/* ems_err.c */
#include <stdio.h>

int emsError(ErrorNumber)
int ErrorNumber;
{unsigned char Error;
 Error = 0xff & (ErrorNumber>>8);
 /* display EMS error codes & text */
 printf("Error %d (%xH): ",Error,Error);
 switch(Error)
   {case 0x80:
      puts("Internal error in EMS software");
      break;
    case 0x81:
      puts("Malfunction in EMS hardware");
      break;
    case 0x83:
      puts("Invalid handle");
      break;
    case 0x84:
      puts("Undefined function");
      break;
    case 0x85:
      puts("No more handles available");
      break;
    case 0x86:
      puts("Error in mapping context");
      break;
    case 0x87:
      puts("Logical pages not available");
      break;
    case 0x88:
      puts("Logical pages not currently available");
      break;
    case 0x89:
      puts("Zero pages requested");
      break;
    case 0x8a:
      puts("Logical page not assigned to this handle");
      break;
    case 0x8b:
      puts("Physical page number invalid");
      break;
    case 0x8c:
      puts("Page-mapping hardware state save area full");
      break;
    case 0x8d:
      puts("Mapping context already associated");
      break;
    case 0x8e:
      puts("Save area has no context for handle");
      break;
    case 0x8f:
      puts("Subfunction not defined");
      break;
    case 0xa0:
      puts("EMS driver not loaded");
      break;
    case 0xa1:
      puts("Illegal library modification");
      break;
    case 0xa2:
      puts("emsLoaded not called");
      break;
    default:
      puts("Error not defined");
      break;
   }
 return(ErrorNumber);
} /* emsError */
