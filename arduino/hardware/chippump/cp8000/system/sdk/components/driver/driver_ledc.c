/*************************************************************************************************
 * @file       driver_ledc.c
 * @author     BLE Group
 * @brief      LED Controller Driver Implementation
 * @version    1.0.1
 * @date       2025-03-23
 * 
 * @copyright Copyright (c) 2024, CHIP PUMP Microelectronics.
                 All rights reserved.
 * 
 ************************************************************************************************/
#include <stdint.h>
#include "mcu_reg_def.h"
#include "driver_gpio.h"
#include "driver_ledc.h"
#include "mcu.h"


#define MAX_TABLE_SIZE        16      // Maximum entries in DMA table

/* Variables */
uint32_t tbl_array[MAX_TABLE_SIZE];  // DMA transfer table buffer



/**
 * @brief Initialize RGB controller timing parameters
 * @param ledc_init_str Pointer to initialization structure containing:
 *        - chnum: Channel number (LEDC_CH0/LEDC_CH1)
 *        - pin: GPIO pin configuration
 *        - period: Total signal period
 *        - code_0_high: High duration for code 0
 *        - code_1_high: High duration for code 1
 */
void ledc_init(ledc_timing_init_typedef *ledc_init_str)
{
    //LEDC Clock_select
    SYS_CTRL->SYS_CLKSEL_b.REG_LEDC_CLK_SEL = 1; // Set LEDC clock to 24MHz

    //outpin init
    if(LEDC_CHANNEL0 == ledc_init_str->chnum)
	{
		gpio_set_func(ledc_init_str->pin,LEDC0_FUNC);
	}
    else if(LEDC_CHANNEL1 == ledc_init_str->chnum)
	{
		gpio_set_func(ledc_init_str->pin,LEDC1_FUNC);
	}
    
    //BIT0\BIT1 config
    LEDC_CTRL->BIT0_MODU_b.B0_P0_POL = 1;
    LEDC_CTRL->BIT0_MODU_b.B0_P0_LEN = ledc_init_str->code_0_high;
    LEDC_CTRL->BIT0_MODU_b.B0_P1_POL = 0;
    LEDC_CTRL->BIT0_MODU_b.B0_P1_LEN = ledc_init_str->period - ledc_init_str->code_0_high;

    LEDC_CTRL->BIT1_MODU_b.B1_P0_POL = 1;
    LEDC_CTRL->BIT1_MODU_b.B1_P0_LEN = ledc_init_str->code_1_high;
    LEDC_CTRL->BIT1_MODU_b.B1_P1_POL = 0;
    LEDC_CTRL->BIT1_MODU_b.B1_P1_LEN = ledc_init_str->period - ledc_init_str->code_1_high;
    // change num
    LEDC_CTRL->CHANGE_NUM1 = 2;
	LEDC_CTRL->CHANGE_NUM2 = 3;
	LEDC_CTRL->CHANGE_NUM3 = 4;
	LEDC_CTRL->CHANGE_NUM4 = 8;
	LEDC_CTRL->CHANGE_NUM5 = 16;
	LEDC_CTRL->CHANGE_NUM6 = 1;
   
    // repeat num
    LEDC_CTRL->REPEAT_NUM1 = 2;
    LEDC_CTRL->REPEAT_NUM2 = 3;
    LEDC_CTRL->REPEAT_NUM3 = 4;
	LEDC_CTRL->REPEAT_NUM4 = 8;
	LEDC_CTRL->REPEAT_NUM5 = 16;
    LEDC_CTRL->REPEAT_NUM6 = 1;
    // CTRL
    LEDC_CTRL->DMA_CTRL_b.LSB_FIRST = 0;//MSB first
    LEDC_CTRL->DMA_CTRL_b.LEVEL_INV = 0;
    LEDC_CTRL->DMA_CTRL_b.LEVEL_INIT = 0;
    LEDC_CTRL->DMA_CTRL_b.DMA_EN  = 1;
}

/**
 * @brief Configure DMA transfer for RGB controller channel
 * @param ledc_ch Channel selector (LEDC_CH0/LEDC_CH1)
 * @param pdata Pointer to data buffer
 */
void ledc_dma_set(ledc_ch_typedef ledc_ch,uint32_t *pdata)
{
    // tbl init

	tbl_array[0] = (int)(uintptr_t)(pdata);

    // tbl
    if(LEDC_CHANNEL0 == ledc_ch)
    {
        LEDC_CH0->TBL_SADDR = (uint16_t)(uintptr_t)(tbl_array) ;
        LEDC_CH0->TBL_EADDR = (uint16_t)(uintptr_t)(tbl_array);
    }
    else if(LEDC_CHANNEL1 == ledc_ch)
    {
        LEDC_CH1->TBL_SADDR = (uint16_t)(uintptr_t)(tbl_array) ;
        LEDC_CH1->TBL_EADDR = (uint16_t)(uintptr_t)(tbl_array );
    }
}

/**
 * @brief Configure DMA table for matrix data transfer
 * @param ledc_ch Channel selector (LEDC_CH0/LEDC_CH1)
 * @param pdata Pointer to data matrix
 * @param rows Number of rows in data matrix
 * @param cols Number of columns per row
 * @param len Number of valid entries to process (max 15)
 */
void ledc_dma_table_set(ledc_ch_typedef ledc_ch,void *pdata,int rows, int cols, uint32_t len)
{
    if(len >= MAX_TABLE_SIZE) return;
    len = (len > rows) ? rows : len;

    /* Populate DMA table with matrix addresses */
    for(int i = 0; i < len; i++) {
        tbl_array[i] = (uint32_t)pdata + i * (cols * sizeof(uint32_t));
    }

    /* Configure channel DMA pointers */
    volatile LEDC_CHANNEL_CTRL_Type *channel = (ledc_ch == LEDC_CHANNEL0) ? LEDC_CH0 : LEDC_CH1;
    channel->TBL_SADDR = (uint16_t)(uintptr_t)tbl_array;
    channel->TBL_EADDR = (uint16_t)(uintptr_t)&tbl_array[len-1];
}
/**
 * @brief Enable/disable DMA engine
 * @param en Enable control (1 = enable, 0 = disable)
 */
void ledc_dma_en(uint8_t en)
{
    LEDC_CTRL->DMA_CTRL_b.DMA_EN  = en;
}


/**
 * @brief Get channel register base pointer
 * @param ch Channel selection (LEDC_CH0/LEDC_CH1)
 * @return Pointer to channel control registers
 */
static volatile LEDC_CHANNEL_CTRL_Type* get_ledc_channel(ledc_ch_typedef ch)
{
    return (ch == LEDC_CHANNEL0) ? LEDC_CH0 : LEDC_CH1;
}

/**
 * @brief Start LED controller channel
 * @param ch Channel selection (LEDC_CH0/LEDC_CH1)
 */
void ledc_start(ledc_ch_typedef ch)
{
    get_ledc_channel(ch)->CTRL1 = 0x1; // Start command
}

/**
 * @brief Stop LED controller channel
 * @param ch Channel selection (LEDC_CH0/LEDC_CH1)
 */
void ledc_stop(ledc_ch_typedef ch)
{
    get_ledc_channel(ch)->CTRL1 = 0x2; // Stop command
}

/**
 * @brief Configure LED controller interrupts
 * @param ch Channel selection (LEDC_CH0/LEDC_CH1)
 * @param int_type Interrupt type mask
 */
void ledc_int_config(ledc_ch_typedef ch, ledc_int_typedef int_type)
{
    volatile LEDC_CHANNEL_CTRL_Type *channel = get_ledc_channel(ch);
    channel->DMA_IE = int_type;
    
    NVIC_SetPriority(LEDC_IRQn, IRQ_CRITICAL_PRIORITY);
    NVIC_EnableIRQ(LEDC_IRQn);
}

uint8_t ledc_int_status(ledc_ch_typedef ledc_ch)
{
    uint8_t ret =0;
    if(LEDC_CHANNEL0 == ledc_ch)
    {
        ret = LEDC_CH0->DMA_IS;
    }
    else if(LEDC_CHANNEL1 == ledc_ch)
    {
        ret = LEDC_CH1->DMA_IS;
    }
    return ret;
}

void ledc_int_clear(ledc_ch_typedef ledc_ch,ledc_int_typedef int_type)
{
    // LEDC_STATUS->STATUS;
    
    if(LEDC_CHANNEL0 == ledc_ch)
    {
        LEDC_CH0->DMA_IS = int_type;
    }
    else if(LEDC_CHANNEL1 == ledc_ch)
    {
        LEDC_CH1->DMA_IS = int_type;
    }
}


/**
 * @brief Create data command entry
 * @param a Pointer to command buffer
 * @param rpt Repeat count (0-31)
 * @param chg Change pattern index (0-15)
 * @param c ledc value (24-bit RGB)
 * @return Updated buffer pointer
 */
uint32_t* ledc_set_dat(uint32_t *a, int rpt, int chg, int c) 
{
    *a = (rpt<<27) + (chg<<24) + c;
	return a+1;
}

uint32_t* ledc_set_ctl(uint32_t *a, int last, int irq, int cmd, int len) 
{
    *a = (1<<30) + (last<<29) + (irq<<28) + (1<<20)+(cmd<<16) + len ; 
	return a+1;
}

/**
 * @brief Create special control command
 * @param a Pointer to command buffer
 * @param rpt Repeat count (0-31)
 * @param chg Change pattern index (0-15)
 * @param c ledc value (24-bit RGB)
 * @return Updated buffer pointer
 */
uint32_t* ledc_set_sdat(uint32_t *a, int rpt, int chg, int c) 
{
    *(a+0)= (2<<30) + (1<<27) + c;
    *(a+1)= (rpt<<16) + (chg<<0);
	return a+2;
}

/**
 * @brief Create memory transfer command
 * @param a Pointer to command buffer
 * @param loop Loop count (0-4095)
 * @param rpt Repeat count (0-4095)
 * @param ea End address (16-bit)
 * @param sa Start address (16-bit)
 * @return Updated buffer pointer
 */
uint32_t* ledc_set_mdat(uint32_t *a, int loop, int rpt, int ea, int sa) 
{
    *(a+0)= (2<<30) + (2<<27) + (0<<24) + (loop<<12) + rpt;
    *(a+1)= ((ea & 0xffff)<<16) + ((sa & 0xffff)<<0);
	return a+2;
}

uint32_t dma_buf_cmd[8]; 
/**
 * @brief Configure LED controller (LEDC) DMA transfer buffer
 * 
 * Sets up DMA transfer parameters based on data mode (24-bit or 32-bit), generates corresponding
 * control command sequences, and initiates DMA transfer.
 * 
 * @param ledc_ch      LEDC channel handle specifying hardware channel to configure
 * @param mode         Data transfer mode: LEDC_DATA_MODE_24BIT or LEDC_DATA_MODE_32BIT
 * @param pdata        Pointer to start address of data buffer
 * @param len          Data length (number of items in 24-bit mode, bytes in 32-bit mode)
 * @param interval_ms  Data transfer interval in milliseconds (will be converted to clock units by left-shifting)
 */
void ledc_dma_buffer_set(ledc_ch_typedef ledc_ch,ledc_data_mode mode,uint32_t *pdata,uint16_t len,uint16_t interval_ms)
{
    /* 24-bit data mode processing */
    if(LEDC_DATA_MODE_24BIT == mode)
    {
        uint32_t *array_buff = pdata;
        // Append control command at end of data buffer: set stop bit, maintain output, 4-clock interval
        array_buff = ledc_set_ctl((array_buff + len), 1, 1, 4, interval_ms<<1);
        // Configure DMA transfer starting address
        ledc_dma_set(ledc_ch,pdata);
    }
    /* 32-bit data mode processing */
    else if(LEDC_DATA_MODE_32BIT == mode)
    {
        uint32_t start_addr = (uint32_t) pdata;          // Data buffer start address
        uint32_t end_addr = start_addr + (len<<2); // Calculate end address (len*4 bytes)

        uint32_t *array_tbl= dma_buf_cmd;     // Use predefined DMA command buffer
        
        // Build DMA command sequence: configure memory transfer parameters
        array_tbl = ledc_set_mdat(array_tbl,0,0,end_addr,start_addr);
        // Append control command: set stop bit, maintain output, 4-clock interval
        array_tbl = ledc_set_ctl(array_tbl,1,1,4,interval_ms<<1);

        // Configure DMA transfer to use command buffer
        ledc_dma_set(ledc_ch,&dma_buf_cmd[0]);
    }
}

/**
 * @brief Configure LED controller data repeat parameters
 * 
 * This function generates LED controller command sequences, configures repeat counts and interval timing,
 * and writes parameters to specified data buffer.
 * 
 * @param data_buff  Pointer to data buffer (uint32_t array type) for storing generated command sequences
 * @param data       24-bit LED control data (lower 24 bits are valid)
 * @param repeat_count Number of data repeat transmissions (0 indicates single transmission)
 * @param interval_ms  Repeat interval duration (unit: milliseconds, actual hardware uses 0.5ms timebase)
 */
void ledc_data_repeat_func(void *data_buff,uint32_t data,uint16_t repeat_count,uint16_t interval_ms)
{
	uint32_t *array0 = data_buff;

    /* Configure hardware repeat counter */
	LEDC_CTRL->REPEAT_NUM1 = repeat_count;

	array0 = ledc_set_dat(array0, 1, 0, data&0xFFFFFF);
    array0 = ledc_set_ctl(array0, 1, 0, 4, interval_ms<<1);
}

/**
 * @brief LED controller data gradual change configuration function
 * 
 * Configures LED controller to achieve gradual transition effect from source to destination data. 
 * Generates control command sequence in the data buffer with specified transition steps and timing.
 * 
 * @param data_buff Pointer to data buffer for storing generated control command sequence
 * @param src Source data value (starting value for transition)
 * @param dst Destination data value (target value for transition)
 * @param chg_count Number of transition steps (controls smoothness of change)
 * @param interval_ms Transition interval duration in milliseconds (time between steps)
 */
void ledc_data_gradual_chg_func(void *data_buff,uint32_t src ,uint32_t dst,uint16_t chg_count,uint16_t interval_ms)
{
	uint32_t *array0 = data_buff;
	LEDC_CTRL->CHANGE_NUM1 = chg_count;

	array0 = ledc_set_dat(array0, 7, 0, src);
	array0 = ledc_set_dat(array0, 0, 1, dst);
    array0 = ledc_set_ctl(array0, 1, 0, 4, interval_ms<<1);
}

/**
 * @brief Generate LED waterflow effect control sequence
 * 
 * This function creates a dynamic waterflow effect by sequentially turning off LEDs from both ends 
 * towards the center while maintaining the first LED lit. The effect is built using special data commands.
 * 
 * @param data_buff Pointer to data buffer for storing generated control sequence (uint32_t array)
 * @param data      Main LED display data value (color/brightness) for the first position LED
 * @param count     Number of LEDs/effect iterations (valid range 0-1000)
 * @param interval_ms Effect interval duration in milliseconds (actual interval = interval_ms * 2)
 */
void ledc_data_waterflow_func(void *data_buff,uint32_t data,uint32_t count,uint16_t interval_ms)
{
	uint32_t *array0 = data_buff;
	if((count<0)||(count>1000))
		return;
	for(int j = 0;j<count;j++)
	{
		array0 = ledc_set_sdat(array0, (count-1)-j, 0, 0x000000);
		array0 = ledc_set_sdat(array0, 0, 0, data);
		array0 = ledc_set_sdat(array0, j, 0, 0x000000);
		array0 = ledc_set_ctl(array0, 0, 0, 4, interval_ms<<1);
	}
	array0 = ledc_set_sdat(array0, 0, 0, data); 
	array0 = ledc_set_sdat(array0, count, 0, 0x000000);
    array0 = ledc_set_ctl(array0, 1, 0, 4, interval_ms<<1);
}

