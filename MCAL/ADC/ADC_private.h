/****************************************************************************************/
/****************************************************************************************/
/*************                AUTHOR :  Mohammed Gaafar        ***************************/
/*************                LAYER :   MCAL			      ***************************/
/*************                SWC :     ADC	              ***************************/
/*************                VERSION : 1.00		          ***************************/
/****************************************************************************************/
/****************************************************************************************/
#ifndef _ADC_PRIVATE_H
#define _ADC_PRIVATE_H



/*********Choose Reference Volt*************/
#define AREF    		0
#define AVCC    		1
#define INTERNAL_256    2
/*******************************************/
/*********Choose Resolution*************/
#define LEFT_ADJUST     0		//8Bit
#define RIGHT_ADJUST    1		//10Bit
/*******************************************/
/**************Choose Prescaler*************/
#define ADC_PRESCALER_MASK  0b11111000
#define ADC_DIV_BY_2        1
#define ADC_DIV_BY_4        2
#define ADC_DIV_BY_8        3
#define ADC_DIV_BY_16       4
#define ADC_DIV_BY_32       5
#define ADC_DIV_BY_64       6
#define ADC_DIV_BY_128      7
/*******************************************/
/**************Choose Channel*************/
#define ADC_CHANNEL_MASK        0b11100000
#define SINGLE_ADC0             0
#define SINGLE_ADC1             1
#define SINGLE_ADC2             2
#define SINGLE_ADC3             3
#define SINGLE_ADC4             4
#define SINGLE_ADC5             5
#define SINGLE_ADC6             6
#define SINGLE_ADC7             7
#define DIFF_ADC0_ADC0_10X      8                 //For testing Purpose
#define DIFF_ADC1_ADC0_10X      9
#define DIFF_ADC0_ADC0_200X     10               //For testing Purpose
#define DIFF_ADC1_ADC0_200X     11
#define DIFF_ADC2_ADC2_10X      12               //For testing Purpose
#define DIFF_ADC3_ADC2_10X      13
#define DIFF_ADC2_ADC2_200X     14               //For testing Purpose
#define DIFF_ADC3_ADC2_200X     15
#define DIFF_ADC0_ADC1_1X       16
#define DIFF_ADC1_ADC1_1X       17              //For testing Purpose
#define DIFF_ADC2_ADC1_1X       18
#define DIFF_ADC3_ADC1_1X       19
#define DIFF_ADC4_ADC1_1X       20
#define DIFF_ADC5_ADC1_1X       21
#define DIFF_ADC6_ADC1_1X       22
#define DIFF_ADC7_ADC1_1X       23
#define DIFF_ADC0_ADC2_1X       24
#define DIFF_ADC1_ADC2_1X       25
#define DIFF_ADC2_ADC2_1X       26              //For testing Purpose
#define DIFF_ADC3_ADC2_1X       27
#define DIFF_ADC4_ADC2_1X       28
#define DIFF_ADC5_ADC2_1X       29
/*******************************************/
#define CHAIN_ASYNCH    0
#define SINGLE_CHANNEL_ASYNCH   1



/*******************************************/
/*      Functions Like Macros   */
/**
*   @brief ADC voltage reference selection macros
    These macros are used to set the reference voltage for the ADC conversion.
    The available options are AREF (External reference),
    AVCC (Vcc as reference),
    and INTERNAL (Internal 1.1V reference).
*/
#define ADC_VOLT_USE_AREF()    do{ CLR_BIT(ADMUX,ADMUX_REFS0);\
                                 CLR_BIT(ADMUX,ADMUX_REFS1);\
                            }while(0)
#define ADC_VOLT_USE_AVCC()    do{ SET_BIT(ADMUX,ADMUX_REFS0);\
                                 CLR_BIT(ADMUX,ADMUX_REFS1);\
                            }while(0)
#define ADC_VOLT_USE_INTERNAL()    do{ SET_BIT(ADMUX,ADMUX_REFS0);\
                                     SET_BIT(ADMUX,ADMUX_REFS1);\
                            }while(0)

/**
*@def ADC_MASK_PRESCALER()
*@brief Mask the ADC prescaler to clear any previous setting
*/
#define ADC_MASK_PRESCALER()    (ADCSRA &= ADC_PRESCALER_MASK)
/**
*@def ADC_CHOOSE_PRESCALER()
*@brief Choose the prescaler for the ADC conversion clock
*/
#define ADC_CHOOSE_PRESCALER()  (ADCSRA |= ADC_PRESCALER)

#define ADC_CHOOSE_LEFT_ADJUST()    (SET_BIT(ADMUX,ADMUX_ADLAR))
#define ADC_CHOOSE_RIGHT_ADJUST()   (CLR_BIT(ADMUX,ADMUX_ADLAR))
/**
*   @brief ADC enable/disable macros
    These macros are used to enable or disable the ADC module.
*/
#define ENABLE_ADC()    (SET_BIT(ADCSRA,ADCSRA_ADEN))
#define DISABLE_ADC()    (CLR_BIT(ADCSRA,ADCSRA_ADEN))


/**
*@def ADC_MASK_CHANNEL()
*@brief Mask the ADC CHANNEL to clear any previous setting
*/
#define ADC_MASK_CHANNEL()    (ADMUX &=    ADC_CHANNEL_MASK)
/**
*@def ADC_CHOOSE_CHANNEL()
*@brief Choose the Channel for the ADC 
*/
#define ADC_CHOOSE_CHANNEL(Local_u8Channel)  (ADMUX |=    Local_u8Channel)
/**
*@def ADC_START_CONVERSION()
*@brief Start a new ADC conversion
*/
#define ADC_START_CONVERSION()  (SET_BIT(ADCSRA,ADCSRA_ADSC))
/**
*@def ADC_READ_FLAG()
*@brief Read the ADC conversion complete flag
*@return 1 if the conversion is complete, 0 otherwise
*/
#define ADC_READ_FLAG()         (GET_BIT(ADCSRA,ADCSRA_ADIF))
/**
*@def ADC_CLEAR_FLAG()
*@brief Clear the ADC conversion complete flag
*/
#define ADC_CLEAR_FLAG()        (CLR_BIT(ADCSRA,ADCSRA_ADIF))
/**
*@def ADC_ENABLE_INTERRUPT()
*@brief Enable the ADC interrupt
*/
#define ADC_ENABLE_INTERRUPT()  (SET_BIT(ADCSRA,ADCSRA_ADIE))
/**
*@def ADC_DISABLE_INTERRUPT()
*@brief Disable the ADC interrupt
*/
#define ADC_DISABLE_INTERRUPT() (CLR_BIT(ADCSRA,ADCSRA_ADIE))

typedef enum{
    BUSY,
    IDLE
}ADC_STATE;

#endif
