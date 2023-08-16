#include "stm32f407xx.h"
typedef enum {RESET = 0, SET = !RESET} FlagStatus, ITStatus;//нахуя это нужно?

void RCC_deinit(void){
RCC->CR|=RCC_CR_HSEON;
while(RCC->CR&(RCC_CR_HSERDY==RESET)){};
RCC->CR=(((RCC->CR) & ~RCC_CR_HSITRIM)|0x80U);
RCC->CFGR=0x0;
while(RCC->CFGR&(RCC_CFGR_SWS!=RESET)){};
RCC->CR&=~RCC_CR_PLLON;
while(RCC->CR&(RCC_CR_PLLRDY!=RESET)){};
RCC->CR&=~(RCC_CR_HSEON|RCC_CR_CSSON);
while(RCC->CR&(RCC_CR_HSERDY!=RESET)){};
RCC->CR&=~RCC_CR_HSEBYP;
RCC->CSR|=RCC_CSR_RMVF;
RCC->CIR=0x0;
}

void RCC_init(void){
RCC->CR|=RCC_CR_HSEON;
while(RCC->CR&(RCC_CR_HSERDY==RESET)){};
FLASH->ACR&=~FLASH_ACR_PRFTEN;
FLASH->ACR|=FLASH_ACR_PRFTEN;
FLASH->ACR=(((FLASH->ACR) & ~FLASH_ACR_LATENCY)|FLASH_ACR_LATENCY_4WS);
RCC->CFGR=(((RCC->CFGR) & ~RCC_CFGR_HPRE)|RCC_CFGR_HPRE_DIV1);
RCC->CFGR=(((RCC->CFGR) & ~RCC_CFGR_PPRE1)|RCC_CFGR_PPRE1_DIV4);
RCC->CFGR=(((RCC->CFGR) & ~RCC_CFGR_PPRE2)|RCC_CFGR_PPRE2_DIV2);
RCC->PLLCFGR=(((RCC->PLLCFGR)& ~RCC_PLLCFGR_PLLSRC)|RCC_PLLCFGR_PLLSRC_HSE);
}

int main(void){
RCC_deinit();
}