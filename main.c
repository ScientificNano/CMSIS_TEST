#include "stm32f407xx.h"
typedef enum {RESET = 0, SET = !RESET} FlagStatus, ITStatus;//нахуя это нужно?
void RCC_deinit(void){
RCC->CR|=RCC_CR_HSEON;
while((RCC->CR&(RCC_CR_HSERDY))==RESET){};
RCC->CR=(((RCC->CR) & ~(RCC_CR_HSITRIM))|0x80U);
RCC->CFGR=0x0;
while((RCC->CFGR&(RCC_CFGR_SWS))!=RESET){};
RCC->CR&=~RCC_CR_PLLON;
while((RCC->CR&(RCC_CR_PLLRDY))!=RESET){};
RCC->CR&=~(RCC_CR_HSEON|RCC_CR_CSSON);
while((RCC->CR&(RCC_CR_HSERDY))!=RESET){};
RCC->CR&=~RCC_CR_HSEBYP;
RCC->CSR|=RCC_CSR_RMVF;
RCC->CIR=0x0;
}

void RCC_init(void){
RCC->CR|=RCC_CR_HSEON;
while((RCC->CR&(RCC_CR_HSERDY))==RESET){};
FLASH->ACR&=~FLASH_ACR_PRFTEN;
FLASH->ACR|=FLASH_ACR_PRFTEN;
FLASH->ACR=(((FLASH->ACR) & (~(FLASH_ACR_LATENCY)))|FLASH_ACR_LATENCY_5WS);
RCC->CFGR=(((RCC->CFGR) & ~(RCC_CFGR_HPRE))|RCC_CFGR_HPRE_DIV1);
RCC->CFGR=(((RCC->CFGR) & ~(RCC_CFGR_PPRE1))|RCC_CFGR_PPRE1_DIV4);
RCC->CFGR=(((RCC->CFGR) & ~(RCC_CFGR_PPRE2))|RCC_CFGR_PPRE2_DIV2);
RCC->PLLCFGR=(((RCC->PLLCFGR)& ~(RCC_PLLCFGR_PLLSRC))|RCC_PLLCFGR_PLLSRC_HSE);
RCC->PLLCFGR=(((RCC->PLLCFGR)& ~(RCC_PLLCFGR_PLLQ))|0x7000000U);//тактирование usb
RCC->PLLCFGR=(((RCC->PLLCFGR)& ~(RCC_PLLCFGR_PLLP))|0x00U);// очистка битов не тоже самое??
RCC->PLLCFGR=(((RCC->PLLCFGR)& ~(RCC_PLLCFGR_PLLN))|RCC_PLLCFGR_PLLN_8|RCC_PLLCFGR_PLLN_6|RCC_PLLCFGR_PLLN_5|RCC_PLLCFGR_PLLN_3);//разные способы включения битов со строкой 29
RCC->PLLCFGR=(((RCC->PLLCFGR)& ~(RCC_PLLCFGR_PLLM))|RCC_PLLCFGR_PLLM_3);
RCC->CR|=RCC_CR_PLLON;
while((RCC->CR&(RCC_CR_PLLRDY))!=RCC_CR_PLLRDY){};
}
void delay(int ms)
{
   while (ms-- > 0) {
      volatile int x=500;
      while (x-- > 0)
         __asm("nop");
   }
}


int main(){
RCC_deinit();
RCC_init();
RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
GPIOA->MODER|=GPIO_MODER_MODER6_0;
while(1){
GPIOA->ODR ^= (1 << 6);
delay(5);
}
}