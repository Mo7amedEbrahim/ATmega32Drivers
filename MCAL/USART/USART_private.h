/****************************************************************************************/
/****************************************************************************************/
/*************                AUTHOR :  Mohammed Gaafar        ***************************/
/*************                LAYER :   MCAL			      ***************************/
/*************                SWC :     USART	              ***************************/
/*************                VERSION : 1.00		          ***************************/
/****************************************************************************************/
/****************************************************************************************/

#ifndef USART_PRIVATE_H
#define USART_PRIVATE_H

//Defining USART I/O Data Register
#define UDR                 *((volatile u8 *)(0x2C))

//Defining USART Control and Status Register A
#define UCSRA               *((volatile u8 *)(0x2B))
#define UCSRA_RXC           7
#define UCSRA_TXC           6
#define UCSRA_UDRE          5
#define UCSRA_FE            4
#define UCSRA_DOR           3
#define UCSRA_PE            2
#define UCSRA_U2X           1
#define UCSRA_MPCM          0

//Defining USART Control and Status Register B
#define UCSRB               *((volatile u8 *)(0x2A))
#define UCSRB_RXCIE         7
#define UCSRB_TXCIE         6
#define UCSRB_UDRIE         5
#define UCSRB_RXEN          4
#define UCSRB_TXEN          3
#define UCSRB_UCSZ2         2
#define UCSRB_RXB8          1
#define UCSRB_TXB8          0

//Defining USART Control and Status Register C
#define UCSRC               *((volatile u8 *)(0x40))
#define UCSRC_URSEL         7
#define UCSRC_UMSEL         6
#define UCSRC_UPM1          5
#define UCSRC_UPM0          4
#define UCSRC_USBS          3
#define UCSRC_UCSZ1         2
#define UCSRC_UCSZ0         1
#define UCSRC_UCPOL         0

//Defining USART Baud Rate Registers
#define UBRRL *((volatile u8 *)(0x29))
#define UBRRH *((volatile u8 *)(0x40))




#define USART_ASYNCH            0
#define USART_SYNCH             1

#define USART_NOPARITY          0
#define USART_EVEN_PARITY       1
#define USART_ODD_PARITY        2


#define USART_1STOPBITS          0
#define USART_2STOPBITS          1

#define SINGLE_CHAR_SEND              0
#define BUFFER_SEND                   1

#define SINGLE_CHAR_RECEIVE      0
#define BUFFER_RECEIVE           1

typedef enum{
    USART_IDLE,
    USART_BUSY
}USART_STATE;





#endif
