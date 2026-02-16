#include <stdlib.h>

/* 
--------------------------------------------------------------------------------
  Cette fonction libere la memoire allouee par allocvec.
--------------------------------------------------------------------------------
*/
void freevec(void *ptr){
  free(ptr);
  ptr=NULL;
}
