
#include <init.h>

void rcc_init(void)
  {
		RCC->CFGR |= RCC_CFGR_SW_HSI; //use HSI oscillator for system clock
		RCC->CR |= RCC_CR_HSION;  //turn on oscillator HSI for clocking ADC1
    while(!(RCC->CR&RCC_CR_HSIRDY)); //waiting for stabilization of HSI
	}
	
void gpio_init(void)
  {

  GPIO_InitTypeDef port;  //definition of variable of GPIO_InitTypeDef type to access to elements of structure GPIO_InitTypeDef to configure port GPIOE
  
  //clock configuration
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB,ENABLE); //enable clock of port B 
  
  //Ports configuration
  //configuration of port B6
  port.GPIO_Pin=GPIO_Pin_6;//change pins
  port.GPIO_Mode=GPIO_Mode_OUT;//this ports use as outputs
  port.GPIO_Speed=GPIO_Speed_40MHz;//set max rate via this pins
  port.GPIO_OType=GPIO_OType_PP;
  //call function to configure GPIOB Pin 6 and Pin 7
  GPIO_Init(GPIOB,&port);
  
  
  }


void tim_init(void)
  {
	
  TIM_TimeBaseInitTypeDef timer; //definition of variable of TimeBaseInitTypeDef type to access to elements of structure TimeBaseInitTypeDef to configure timer TIM6
  
	//clock configuration
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6,ENABLE); //enable clock of basic timer TIM6  
  
  
  //Timer configuration
  //configuration of elements of structure TimeBaseInitTypeDef
  timer.TIM_Prescaler=16000; //prescaller of system clock 16 MHz = 16000
  timer.TIM_Period=100;  //frequency=100 Hz
  //timer.TIM_Period=300;  //frequency=300 Hz
  
  /*if frequency=500 kHz,then
  timer.TIM_Prescaler=224;
  timer.TIM_Period=8;  */
  
  //call function to configure timer TIM6
  TIM_TimeBaseInit(TIM6,&timer);
  
  TIM6->DIER |= TIM_DIER_UIE;  //enable interrupt
  TIM_Cmd(TIM6,ENABLE);  //start counting
  NVIC_EnableIRQ(TIM6_IRQn);    //enable interrupt in NVIC controller
  }
  
void TIM6_IRQHandler(void)
  {
    TIM_ClearFlag(TIM6,TIM_IT_Update);   //clear interrupt flag
    GPIOB->ODR^=GPIO_Pin_6;   //invert state of pin
  }
