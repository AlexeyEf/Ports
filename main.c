
#include "init.h"
  
int main()
{  
  
	//call function of configuration of ports timer module
	rcc_init();
	gpio_init();
  tim_init();   
 
 
  while(1);
   
}
