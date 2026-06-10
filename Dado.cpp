#include "Dado.h"
#include <cstdlib>

int Dado::tirar()
{
 return rand () %6+1;
}