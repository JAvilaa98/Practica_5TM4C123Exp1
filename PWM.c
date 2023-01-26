
#include "lib/include.h"

extern void Configura_Reg_PWM1(uint16_t freq)
{
    SYSCTL->RCGCPWM |= (1<<0); // Enable reloj de modulo PWM1 pag 354 Habilitamos PWM0 correspondiente al experimento 1
    SYSCTL->RCGCGPIO |= (1<<1); //Habilitamos el GPIOB según lo requerido en el experimento 1 pág 340 y 1233
    SYSCTL->RCC &= ~(1<<20);  // Deshabilitamo el divisor según lo requerido en el experimento 1 
    GPIOB->AFSEL |= (1<<4); // Habilitamos el pin PB4 pág 672
    GPIOB->DIR = (1<<4); //Habilitamos PB4 como salida
    GPIOB->PCTL |= (GPIOB->PCTL&0xFFF0FFFF) | 0x00040000; /*Combinado con la tabla Pag 1351 y el registro PCTL le digo que es pwm Pag 689*/
    GPIOB->DEN |= (1<<4); /* para decirle si es digital o no Pag 682*/
    PWM0->_1_CTL = (0<<0);
    PWM0->_1_GENA = 0x0000008C; // Establecemos el modo de trabajo de cuenta regresiva pág 1285 y 1239
    PWM0->_1_LOAD = 5000; // Cuentas = (Frecuencia de reloj/Frecuencia PWM) Cuentas = (50000000/10000) = 5000
    PWM0->_1_CMPA = 4000; // Estoy utilizando el 80% del ciclo de trabajo (5000 - 100% ) x = ?
    PWM0->_1_CTL = (1<<0);// Se activa el generador 1 del PWM0
    PWM0->ENABLE = (1<<2); //Encedemos el PWM2 para trabajar con generador 1 según la tabla de la pág 1233 
}
