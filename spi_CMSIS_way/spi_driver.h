#include "stm32f10x.h" 

#define CS_ENABLE         GPIOA->BSRR = GPIO_BSRR_BR4;         
#define CS_DISABLE    	  GPIOA->BSRR = GPIO_BSRR_BS4; 

#define SPI_READ_WRITE 		spi_send();

#define BUFFER_SIZE 512
extern __IO unsigned char buffer1[BUFFER_SIZE]; 

// timers values
extern __IO uint32_t Timer;
static __IO uint32_t TimerDelay;

// setting SPI functions
void FCLK_SLOW(void);
void FCLK_FAST(void);
void spi_init(void);


// delay functions
void delay_ms(uint32_t nTime);
void SysTick_Handler();
