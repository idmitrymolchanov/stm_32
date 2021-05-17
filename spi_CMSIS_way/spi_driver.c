#include "spi_driver.h" 

/**************************************************************************/
//function  data exchange via SPI1                                                          
//argument  none                                                             
//return    none 
/**************************************************************************/  
void FCLK_SLOW(void)
{
	// disable SPI
	SPI1->CR1 = (SPI1->CR1 & ~SPI_CR1_SPE);
	// set SPI_BaudRatePrescaler_256
	SPI1->CR1 = ( SPI1->CR1 | SPI_CR1_BR );
	// enable SPI
	SPI1->CR1    |= SPI_CR1_SPE;
}

/**************************************************************************/
//function  data exchange via SPI1                                                          
//argument  none                                                             
//return    none
/**************************************************************************/  
void FCLK_FAST(void)
{
	// disable SPI
	SPI1->CR1 = (SPI1->CR1 & ~SPI_CR1_SPE);
	// set SPI_BaudRatePrescaler_4
	SPI1->CR1 = (SPI1->CR1 & ~SPI_CR1_BR ) | SPI_CR1_BR_1;
	// enable SPI
	SPI1->CR1    |= SPI_CR1_SPE;
}

//*********************************************************************************************
//function  initializing SPI1                                                            //
//argument  none                                                                             //
//return    none                                                                             //
//*********************************************************************************************
void spi_init(void)
{
// enable clocking of alternative functions
  RCC->APB2ENR |=  RCC_APB2ENR_AFIOEN; 
// enable port A clocking
  RCC->APB2ENR |=  RCC_APB2ENR_IOPAEN; 
 
//SS: push-pull output, general purpose, 50MHz
  GPIOA->CRL   |=  GPIO_CRL_MODE4;    //
  GPIOA->CRL   &= ~GPIO_CRL_CNF4;     //
  GPIOA->BSRR   =  GPIO_BSRR_BS4;     //
 
//SCK: push-pull output, alternative function, 50MHz
  GPIOA->CRL   |=  GPIO_CRL_MODE5;    //
  GPIOA->CRL   &= ~GPIO_CRL_CNF5;     //
  GPIOA->CRL   |=  GPIO_CRL_CNF5_1;   //
 
//MISO: digital input with pull-up resistor, pull-up to positive
  GPIOA->CRL   &= ~GPIO_CRL_MODE6;    //
  GPIOA->CRL   &= ~GPIO_CRL_CNF6;     //
  GPIOA->CRL   |=  GPIO_CRL_CNF6_1;   //
  GPIOA->BSRR   =  GPIO_BSRR_BS6;     //
 
//MOSI: push-pull output, alternative function, 50MHz
  GPIOA->CRL   |=  GPIO_CRL_MODE7;    //
  GPIOA->CRL   &= ~GPIO_CRL_CNF7;     //
  GPIOA->CRL   |=  GPIO_CRL_CNF7_1;   //
 
//setting SPI
  RCC->APB2ENR |= RCC_APB2ENR_SPI1EN; // submit clocking
  SPI1->CR2     = 0x0000;             
  SPI1->CR1     = SPI_CR1_MSTR;       // master mode 
  SPI1->CR1    |= SPI_CR1_BR;         // prescaller SCK 72000kHz/256=281kHz < 400kHz
  SPI1->CR1    |= SPI_CR1_SSI;
  SPI1->CR1    |= SPI_CR1_SSM;

//	SPI1->CR1 &= SPI_CR1_CRCEN;
// enable SPI
  SPI1->CR1    |= SPI_CR1_SPE;
}

void delay_ms(uint32_t nTime){
    TimerDelay = nTime;
    while(TimerDelay != 0);
}

void SysTick_Handler() {
    if(TimerDelay != 0x00)
			TimerDelay--; 
		if(Timer != 0x00)
			Timer--;
}

