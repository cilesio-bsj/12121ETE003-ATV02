#include <stdlib.h>
#include <stdint.h>

#define STM32_RCC_BASE 				    0x40023800
#define STM32_GPIOA_BASE 			    0x40020000U //pág 54 datasheet
#define STM32_GPIOC_BASE 		    	0x40020800U //pág 54 datasheet
#define STM32_RCC_AHB1ENR_OFFSET	0x0030

#define STM32_GPIO_MODER_OFFSET 	0x0000
#define STM32_GPIO_OTYPER_OFFSET 	0x0004 
#define STM32_GPIO_PUPDR_OFFSET 	0x000c

#define STM32_GPIO_IDR_OFFSET 	  0x0010
#define STM32_GPIO_BSRR_OFFSET 		0x0018 

#define STM32_RCC_AHB1ENR			  (STM32_RCC_BASE+STM32_RCC_AHB1ENR_OFFSET)

#define STM32_GPIOA_MODER   (STM32_GPIOA_BASE+STM32_GPIO_MODER_OFFSET)
#define STM32_GPIOA_OTYPER  (STM32_GPIOA_BASE+STM32_GPIO_OTYPER_OFFSET)
#define STM32_GPIOA_PUPDR   (STM32_GPIOA_BASE+STM32_GPIO_PUPDR_OFFSET)
#define STM32_GPIOA_IDR     (STM32_GPIOA_BASE + STM32_GPIO_IDR_OFFSET)

#define STM32_GPIOC_MODER 			(STM32_GPIOC_BASE+STM32_GPIO_MODER_OFFSET)
#define STM32_GPIOC_OTYPER 			(STM32_GPIOC_BASE+STM32_GPIO_OTYPER_OFFSET)
#define STM32_GPIOC_PUPDR 			(STM32_GPIOC_BASE+STM32_GPIO_PUPDR_OFFSET)
#define STM32_GPIOC_BSRR 			  (STM32_GPIOC_BASE + STM32_GPIO_BSRR_OFFSET)

#define RCC_AHB1ENR_GPIOAEN 		(1 << 0)
#define RCC_AHB1ENR_GPIOCEN 		(1 << 2)

#define GPIO_MODER_INPUT 			  (0)
#define GPIO_MODER_OUTPUT 			(1)
#define GPIO_MODER_ALT 				  (2)
#define GPIO_MODER_ANALOG 			(3)

#define GPIO_MODER0_SHIFT  (0)
#define GPIO_MODER0_MASK 	(3 << GPIO_MODER0_SHIFT)

#define GPIO_MODER13_SHIFT 			(26)
#define GPIO_MODER13_MASK 			(3 << GPIO_MODER13_SHIFT)

#define GPIO_OTYPER_PP 	(0)
#define GPIO_OTYPER_OD 	(1)
#define GPIO_OT13_SHIFT (13)
#define GPIO_OT13_MASK 	(1 << GPIO_OT13_SHIFT)

#define GPIO_PUPDR_NONE 	(0)
#define GPIO_PUPDR_PULLUP 	(1)
#define GPIO_PUPDR_PULLDOWN (2)

#define GPIO_PUPDR0_SHIFT 	(0)
#define GPIO_PUPDR0_MASK   	(3 << GPIO_PUPDR13_SHIFT)

#define GPIO_PUPDR13_SHIFT 	(26)
#define GPIO_PUPDR13_MASK 	(3 << GPIO_PUPDR13_SHIFT)

#define GPIO_BSRR_SET(n) (1 << (n))
#define GPIO_BSRR_RST(n) (1 << (n + 16))


int main(int argc, char *argv[])
{
	
	
	uint32_t reg;

	// Ponteiros para registradores
	uint32_t *pRCC_AHB1ENR = (uint32_t *)STM32_RCC_AHB1ENR;
	
	uint32_t *pGPIOA_MODER = (uint32_t *)STM32_GPIOA_MODER;
	uint32_t *pGPIOA_OTYPER = (uint32_t *)STM32_GPIOA_OTYPER;
	uint32_t *pGPIOA_PUPDR = (uint32_t *)STM32_GPIOA_PUPDR;
	uint32_t *pGPIOA_IDR = (uint32_t *)STM32_GPIOA_IDR;

	uint32_t *pGPIOC_MODER = (uint32_t *)STM32_GPIOC_MODER;
	uint32_t *pGPIOC_OTYPER = (uint32_t *)STM32_GPIOC_OTYPER;
	uint32_t *pGPIOC_PUPDR = (uint32_t *)STM32_GPIOC_PUPDR;
	uint32_t *pGPIOC_BSRR = (uint32_t *)STM32_GPIOC_BSRR;

  	// Habilita clock GPIOA
	reg = *pRCC_AHB1ENR;
	reg |= RCC_AHB1ENR_GPIOAEN;
	*pRCC_AHB1ENR = reg;

	// Habilita clock GPIOC
	reg = *pRCC_AHB1ENR;
	reg |= RCC_AHB1ENR_GPIOCEN;
	*pRCC_AHB1ENR = reg;

	reg = *pGPIOA_MODER;
	reg &= ~(GPIO_MODER0_MASK);
	reg |= (GPIO_MODER_INPUT << GPIO_MODER0_SHIFT);
	*pGPIOA_MODER = reg;

	reg = *pGPIOC_MODER;
	reg &= ~(GPIO_MODER13_MASK);
	reg |= (GPIO_MODER_OUTPUT << GPIO_MODER13_SHIFT);
	*pGPIOC_MODER = reg;

	reg = *pGPIOC_OTYPER;
	reg &= ~(GPIO_OT13_MASK);
	reg |= (GPIO_OTYPER_PP << GPIO_OT13_SHIFT);
	*pGPIOC_OTYPER = reg;

	reg = *pGPIOA_PUPDR;
	reg &= ~(GPIO_PUPDR0_MASK);
	reg |= (GPIO_PUPDR_PULLUP << GPIO_PUPDR0_SHIFT);
	*pGPIOA_PUPDR = reg;

	reg = *pGPIOC_PUPDR;
	reg &= ~(GPIO_PUPDR13_MASK);
	reg |= (GPIO_PUPDR_NONE << GPIO_PUPDR13_SHIFT);
	*pGPIOC_PUPDR = reg;


  void Atrasar_ms(int t_ms)
  {
      for (uint32_t i = 0; i < 1323*t_ms; i++); //Medido no olho
  }

  int tempo_ms;
  while (1)
  {

	if ((*pGPIOA_IDR & (uint16_t)0x0001) != (uint16_t)0x0001) {
		tempo_ms  = 250;
	}else{
		tempo_ms  = 500;
	}
    *pGPIOC_BSRR = GPIO_BSRR_SET(13);
	  Atrasar_ms(tempo_ms);
    *pGPIOC_BSRR = GPIO_BSRR_RST(13);
	  Atrasar_ms(tempo_ms);
  }

	return EXIT_SUCCESS;
}