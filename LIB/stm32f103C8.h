/*****************************************************************/
/****************** Name    : Karim Seif 	**********************/
/****************** Date    : 7/5/2021  	**********************/
/****************** Version : 1.0V       	**********************/
/****************** SWC     : stm32f10xx.h  **********************/
/*****************************************************************/
#ifndef STM32F103C8_H
#define STM32F103C8_H

/************************************ RCC Registers ******************************************/

#define RCC_u32_BASE_ADDRESS         0x40021000

typedef struct
{
	volatile u32 CR;
	volatile u32 CFGR;
	volatile u32 CIR;
	volatile u32 APB2RSTR;
	volatile u32 APB1RSTR ;
	volatile u32 AHBENR   ;
	volatile u32 APB2ENR  ;
	volatile u32 APB1ENR  ;
	volatile u32 BDCR	  ;
	volatile u32 CSR;
}RCC_RegDef_t;

#define RCC                     ((RCC_RegDef_t*)0x40021000)           

/*********************************************************************************************/

/************************************* GPIO Registers ****************************************/

#define GPIO_u32_GPIOA_BASE_ADDRESS    0x40010800
#define GPIO_u32_GPIOB_BASE_ADDRESS    0x40010C00
#define GPIO_u32_GPIOC_BASE_ADDRESS    0x40011000

typedef struct
{
	volatile u32 CRL;
	volatile u32 CRH;
	volatile u32 IDR;
	volatile u32 ODR;
	volatile u32 BSRR;
	volatile u32 BRR;
	volatile u32 LCKR;
}GPIO_RegDef_t;

#define GPIOA                         ((GPIO_RegDef_t*) GPIO_u32_GPIOA_BASE_ADDRESS)
#define GPIOB                         ((GPIO_RegDef_t*) GPIO_u32_GPIOB_BASE_ADDRESS)
#define GPIOC                         ((GPIO_RegDef_t*) GPIO_u32_GPIOC_BASE_ADDRESS)


/*********************************************************************************************/

/************************************ NVIC Registers *****************************************/

#define NVIC_u32_BASE_ADDRESS         0xE000E100

typedef struct
{
	volatile u32 ISER[8];
	volatile u32 Reserved1[24];
	volatile u32 ICER[8];
	volatile u32 Reserved2[24];
	volatile u32 ISPR[8];
	volatile u32 Reserved3[24];
	volatile u32 ICPR[8];
	volatile u32 Reserved4[24];
	volatile u32 IABR[8];
}NVIC_RegDef_t;

#define NVIC                       ((NVIC_RegDef_t*) NVIC_u32_BASE_ADDRESS)




/*********************************************************************************************/

#endif