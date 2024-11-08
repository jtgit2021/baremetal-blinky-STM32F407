
//for base registers look at 2.3 Memory Map, p 67
//define addresses for GPIO PG6 other ports etc

//typecasting pointers
#define GPIO_PORTG						0x40021800U
#define GPIO_PORTG_MODER			(*(volatile unsigned long *)(GPIO_PORTG + 0x0U))   
#define GPIO_PORTG_OTYPER			(*(volatile unsigned long *)(GPIO_PORTG + 0x04U))
#define GPIO_PORTG_OSPEEDR		(*(volatile unsigned long *)(GPIO_PORTG + 0x08U))
#define GPIO_PORTG_PUPDR			(*(volatile unsigned long *)(GPIO_PORTG + 0x0CU))
#define GPIO_PORTG_ODR				(*(volatile unsigned long *)(GPIO_PORTG + 0x14U))
#define GPIO_PORTG_BSRR				(*(volatile unsigned long *)(GPIO_PORTG + 0x18U))
#define RCC										0x40023800U
#define RCC_AHB1ENR						(*(volatile unsigned long *) (RCC+0x30U))	 

void portg_init(void);
void toggle_pin6(void);
void delay(void);

int main (void){
	portg_init();
	
	while(1){
		delay();
		toggle_pin6();
	}
}


void delay(void){
		static volatile int i; //short delay if not static if i has to be initialized every time
		i=0;

		while (i<100000) {
			i++;
		}
}

void toggle_pin6(void){	
    GPIO_PORTG_ODR ^= (1U << 6);  // Toggle LED
}

void portg_init(void){
		RCC_AHB1ENR |= 0x40U; //set clock for port g
		GPIO_PORTG_MODER &= 0xFFFFCFFF; // clear bits in portg
		GPIO_PORTG_MODER |= 0x1000U;  // set portg as output
		GPIO_PORTG_ODR |= 0x40U; // set pin 6 to high
}
