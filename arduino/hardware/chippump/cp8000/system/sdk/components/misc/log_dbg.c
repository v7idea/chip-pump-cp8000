/*************************************************************************************************
 * @file       log_dbg.c
 * @author     BLE Group
 * @brief 
 * @version    1.0.1
 * @date       2025-02-07
 * 
 * @copyright Copyright (c) 2024, CHIP PUMP Microelectronics.
                 All rights reserved.
 * 
 ************************************************************************************************/
#include <stdarg.h>
#include <string.h>
#include <stdint.h>
#include "config.h"
#include "log_dbg.h"
#include "driver_gpio.h"
#include "driver_uart.h"

#if(LOG_ENABLE)

static void print_string_to_buf(uint8_t* uartSndBuf, uint8_t* uartSndBufUseLen, uint8_t* buf, int len)
{
	for(uint8_t i = 0; i < len; i ++)
	{
		if(*uartSndBufUseLen >= DEBUG_STRING_LOG_SINGLE_LINE_MAX_SIZE)
		{
			return;
		}
		*(uartSndBuf + *uartSndBufUseLen) = buf[i];

		*uartSndBufUseLen = *uartSndBufUseLen+1;
	}
}

void dbg_print_string_raw(const char *format, va_list vaArgP)
{
	// For fast display log.
    //DEBUG_POINT_POLLING_PRINT();
    uint32_t ulIdx, ulValue, ulPos, ulCount, ulBase, ulNeg;
    char *pcStr, pcBuf[16], cFill;
    char HexFormat = 0;
    static const char* const g_pcHex1 = "0123456789abcdef";
    static const char* const g_pcHex2 = "0123456789ABCDEF";
    uint8_t uart_tx_buff[DEBUG_STRING_LOG_SINGLE_LINE_MAX_SIZE];
    uint8_t uart_tx_local_ptr = 0;

    while(*format)
    {
        // Find the first non-% character, or the end of the string.
        for(ulIdx = 0; (format[ulIdx] != '%') && (format[ulIdx] != '\0');ulIdx++)
        {}

        // Write this portion of the string.
        if(ulIdx>0)
        {
            print_string_to_buf(uart_tx_buff, &uart_tx_local_ptr, (uint8_t*)format, ulIdx);
        }

        format += ulIdx;

        if(*format == '%')
        {
            format++;

            // Set the digit count to zero, and the fill character to space
            // (i.e. to the defaults).
            ulCount = 0;
            cFill = ' ';

        again:
           switch(*format++)
            {
                case '0':
                case '1':
                case '2':
                case '3':
                case '4':
                case '5':
                case '6':
                case '7':
                case '8':
                case '9':
                {
                    if((format[-1] == '0') && (ulCount == 0))
                    {
                        cFill = '0';
                    }

                    ulCount *= 10;
                    ulCount += format[-1] - '0';

                    goto again;
                }

                case 'c':
                {
                    ulValue = va_arg(vaArgP, unsigned long);
                    print_string_to_buf(uart_tx_buff, &uart_tx_local_ptr, (uint8_t*)&ulValue, 1);
                    break;
                }

                case 'd':
                case 'z':
                {
                    ulValue = va_arg(vaArgP, unsigned long);
                    ulPos = 0;

                    if((long)ulValue < 0)
                    {
                        ulValue = -(long)ulValue;
                        ulNeg = 1;
                    }
                    else
                    {
                        ulNeg = 0;
                    }

                    ulBase = 10;
                    goto convert;
                }

                case 's':
                {
                    pcStr = va_arg(vaArgP, char *);

                    for(ulIdx = 0; pcStr[ulIdx] != '\0'; ulIdx++)
                    {}

                    print_string_to_buf(uart_tx_buff, &uart_tx_local_ptr, (uint8_t*)pcStr, ulIdx);

                    if(ulCount > ulIdx)
                    {
                        ulCount -= ulIdx;
                        while(ulCount--)
                        {
                            print_string_to_buf(uart_tx_buff, &uart_tx_local_ptr, (uint8_t*)" ", 1);
                        }
                    }
                    break;
                }

                case 'u':
                {
                    ulValue = va_arg(vaArgP, unsigned long);
                    ulPos = 0;
                    ulBase = 10;
                    ulNeg = 0;
                    goto convert;
                }


                case 'X':
                {
                    ulValue = va_arg(vaArgP, unsigned long);
                    ulPos = 0;
                    ulBase = 16;
                    ulNeg = 0;
                    HexFormat='X';
                    goto convert;
                }

                case 'x':
                case 'p':
                {
                    ulValue = va_arg(vaArgP, unsigned long);
                    ulPos = 0;
                    ulBase = 16;
                    ulNeg = 0;
                     HexFormat='x';

        convert:
                    for(ulIdx = 1;
                        (((ulIdx * ulBase) <= ulValue) &&
                         (((ulIdx * ulBase) / ulBase) == ulIdx));
                        ulIdx *= ulBase, ulCount--)
                    {
                    }

                    if(ulNeg)
                    {
                        ulCount--;
                    }

                    if(ulNeg && (cFill == '0'))
                    {
                        pcBuf[ulPos++] = '-';
                        ulNeg = 0;
                    }

                    if((ulCount > 1) && (ulCount < 16))
                    {
                        for(ulCount--; ulCount; ulCount--)
                        {
                            pcBuf[ulPos++] = cFill;
                        }
                    }

                    if(ulNeg)
                    {
                        pcBuf[ulPos++] = '-';
                    }

                    for(; ulIdx; ulIdx /= ulBase)
                    {
                        if(HexFormat=='x')  pcBuf[ulPos++] = g_pcHex1[(ulValue / ulIdx) % ulBase];//x
                        else    pcBuf[ulPos++] = g_pcHex2[(ulValue / ulIdx) % ulBase];//X
                    }

                    print_string_to_buf(uart_tx_buff, &uart_tx_local_ptr, (uint8_t*)pcBuf, ulPos);
                    break;
                }

                case '%':
                {
                    print_string_to_buf(uart_tx_buff, &uart_tx_local_ptr, (uint8_t*)format - 1, 1);
                    break;
                }
                case 'l':
                {
                    goto again;
                }

                default:
                {
                    print_string_to_buf(uart_tx_buff, &uart_tx_local_ptr, (uint8_t*)"ERROR", 5);
                    break;
                }
            }//switch
        }//if
    }//while
    // Send packet
    uart_send(LOG_UART, uart_tx_buff, uart_tx_local_ptr);
}

void log_dbg_init(void)
{
	gpio_set_func(LOG_UART_RX_PIN, LOG_UART_RX_FUNC|0x20);
    gpio_set_func(LOG_UART_TX_PIN, LOG_UART_TX_FUNC);
	
    uart_init(LOG_UART, LOG_UART_BAUDRATE);
}

size_t strlen(const char * str)
{
    int c = 0;

    while(str[c++] != '\0');

    return (c - 1);
}

int puts(const char * str)
{
    uart_send(LOG_UART, (void *)str, strlen(str));
    uart_send(LOG_UART, "\n", 1);

    return 0;
}

void log_printf(const char *format, ...)
{
	va_list ap;

	va_start(ap, format);

    dbg_print_string_raw(format, ap);

    va_end(ap);
}
#else
void log_dbg_init(void)
{
	
}

void log_printf(const char *format, ...)
{

}
#endif