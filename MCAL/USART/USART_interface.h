/****************************************************************************************/
/****************************************************************************************/
/*************                AUTHOR :  Mohammed Gaafar        ***************************/
/*************                LAYER :   MCAL			      ***************************/
/*************                SWC :     USART	              ***************************/
/*************                VERSION : 1.00		          ***************************/
/****************************************************************************************/
/****************************************************************************************/
#ifndef _USART_INTERFACE_H
#define _USART_INTERFACE_H

typedef struct{
    u32 USART_BaudRate;
    u8 USART_Synchronization;
    u8 USART_Parity;
    u8 USART_StopBits;
}USART_t;

ES_t USART_Init(USART_t *Copy_USART);

/*      Synchronous Functions   */
ES_t USART_SendCharSynch(u8 Copy_u8Value);
ES_t USART_ReceiveCharSynch(u8 *pu8Data);
ES_t USART_SendBufferSynch(u8* Copy_pu8Buffer, u8 Copy_u8BufferSize);
ES_t USART_ReceiveBufferSynch(u8* Copy_pu8Buffer, u16 Copy_u16Length);      //Not applicable

/*      ASynchronous Functions   */
ES_t USART_SendCharASynch(u8 *Copy_pu8Reading, void(*LocalPtr)(void));
ES_t USART_ReceiveCharASynch(u8 *Copy_pu8Reading, void(*LocalPtr)(void));
ES_t USART_SendBufferASynch(u8* Copy_pu8Buffer, u8 Copy_u8BufferSize);
ES_t USART_ReceiveBufferASynch(u8 *buffer, u8 size, void(*LocalPtr)(void));




#endif
