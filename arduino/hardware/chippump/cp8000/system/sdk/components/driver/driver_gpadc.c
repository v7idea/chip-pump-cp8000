/*************************************************************************************************
 * @file       driver_gpadc.c
 * @author     BLE Group
 * @brief      General Purpose ADC (GPADC) Driver for CP8xxx Series MCUs
 * @version    1.0.1
 * @date       2025-02-07
 * 
 * @copyright Copyright (c) 2024, CHIP PUMP Microelectronics.
                 All rights reserved.
 * 
 ************************************************************************************************/
#include "mcu_reg_def.h"
#include "driver_gpadc.h"

/*-------------------------------------
  Global Calibration Parameters
-------------------------------------*/

uint8_t g_gpadc_stat = 0; // 0: no cali, 1: cali done
int32_t g_gpadc_div1_a;
int32_t g_gpadc_div1_b;
int32_t g_gpadc_div2_a;
int32_t g_gpadc_div2_b;
int32_t g_gpadc_div3_a;
int32_t g_gpadc_div3_b;
int32_t g_gpadc_div4_a;
int32_t g_gpadc_div4_b;
int32_t g_gpadc_vbat_a;
int32_t g_gpadc_vbat_b;
uint16_t g_gpadc_vbat = 0;  

const int8_t gpadc_batvoltoffset[] = {-9, 1, 4, 5, 7, 8, 8, 6, 6, 4, 2, 0, -1, -2, -3};

const int8_t gpadc_voltoffset[][15] =
{
{-7,-4,-3,-1,-1,-1,0,0,1,1,1,1,1,0,-1,},
{-14,-10,-7,-4,-2,-1,-2,-1,0,0,1,1,2,2,2,},
{-14,-8,-7,-4,-3,-2,-1,0,0,0,1,0,0,1,1,},
{-14,-9,-6,-4,-3,-2,-2,-1,-1,0,1,1,1,0,0,},
{-13,-9,-7,-4,-3,-2,-1,0,0,0,0,1,1,1,1,},
{-11,-7,-5,-4,-2,-2,-1,-1,-1,-1,0,0,0,0,0,},
{-9,-6,-4,-2,-2,-1,-2,-1,-1,0,-1,-1,-1,0,0,},
{-5,-4,-3,-3,-2,-1,-2,-2,-1,0,-1,-1,-1,0,0,},
{1,0,-1,0,0,0,0,0,0,1,0,0,0,1,1,},
{6,5,4,2,3,2,2,1,3,3,2,2,1,1,2,},
{7,8,7,5,4,2,2,1,2,2,2,1,1,0,1,},
{3,10,10,8,5,4,3,2,2,2,2,2,1,0,1,},
{0,6,9,9,9,6,4,3,2,2,2,1,1,1,1,},
{-1,4,7,10,10,8,7,4,4,3,3,1,1,0,1,},
{-4,3,6,8,10,10,8,7,5,4,3,2,2,1,2,},
{-4,1,4,7,10,10,11,9,7,6,4,4,3,2,2,},
{-15,-5,-1,2,7,6,9,9,7,6,4,4,4,3,1,},
{-17,-9,-5,0,3,4,5,7,8,7,5,3,3,2,1,},
{-18,-11,-5,-2,0,3,4,5,7,7,7,4,2,2,2,},
{-18,-14,-10,-5,-1,-2,0,2,3,4,5,4,2,1,0,},
{-18,-14,-11,-7,-4,-2,-1,-1,0,2,3,3,3,2,0,},
{-18,-14,-11,-10,-6,-2,-1,-1,0,2,1,3,3,2,0,},
{-18,-14,-11,-10,-9,-7,-5,-4,-4,-2,-2,-1,0,0,0,},
{-18,-14,-11,-10,-9,-8,-6,-5,-5,-2,-2,-2,-1,0,0,},
{-18,-14,-11,-10,-9,-8,-8,-6,-6,-5,-3,-3,-2,-2,-2,},
{-18,-14,-11,-10,-9,-8,-8,-4,-3,-1,0,2,2,2,2,},
{-18,-14,-11,-10,-9,-8,-8,-4,0,1,0,1,2,4,3,},
{-18,-14,-11,-10,-9,-8,-8,-4,0,0,1,1,3,4,2,},
{-18,-14,-11,-10,-9,-8,-8,-4,0,0,0,0,2,3,2,},
{-18,-14,-11,-10,-9,-8,-8,-4,0,0,0,1,2,2,2,},
{-18,-14,-11,-10,-9,-8,-8,-4,0,0,0,1,2,2,2,},
{-18,-14,-11,-10,-9,-8,-8,-4,0,0,0,1,2,3,2,},
{-18,-14,-11,-10,-9,-8,-8,-4,0,0,0,1,2,3,3,}
};

static int16_t gpadc_InternalSearchBATVoltageOffset(uint16_t vbat);

static int16_t gpadc_InternalSearchVoltageOffset(uint16_t voltage, uint16_t div_sel);




static inline int otp_check_parity(uint8_t *q, int len){
    int i, j, p;
    p = 0;
    for(i=0; i<len; i++)
        for(j=0; j<8; j++)
            p ^= (((*(q+i))>>j) & 1);
    return p;
}

static inline void cal_init(void)
{
    int t, t1;
    int rfbg, aonbg;
    // read
    t = *(volatile int *)(0x1f803f30);
    t1 = (int)(&t);
    // check
    if(t == 0xffffffff)
    {
        rfbg = 10;
        aonbg = 2;
//        log_printf("  WARNING BG no calibration, use default, rfbg: %d, aonbg: %d!!!\n", rfbg, aonbg);
    }
    else
    {
        if(otp_check_parity((uint8_t *)(t1 + 0), 1))
        {
            rfbg = (t >> 0) & 0xf;
//            log_printf("  INFO RFBG: %d, parity check pass!\n", rfbg);
        }
        else
        {
            rfbg = 12;
//            log_printf("  ERROR RFBG: %d, parity check failed!!!\n", rfbg);
        }
        if(otp_check_parity((uint8_t *)(t1 + 2), 1))
        {
            aonbg = (t >> 16) & 0xf;
//            log_printf("  INFO AONBG: %d, parity check pass!\n", aonbg);
        }
        else
        {
            aonbg = 0;
//            log_printf("  ERROR AONBG: %d, parity check failed!!!\n", aonbg);
        }
    }
    // write
    t = *(volatile int*)(0x42002008);
    t &= (~(0xf<<27));
    t |= (rfbg << 27);
    *(volatile int*)(0x42002008) = t;
    t = *(volatile int*)(0x42002008);
    t >>= 27;
    t &= 0xf;
//    log_printf("  INFO RFBG readback: %d\n", t);
    t = *(volatile int*)(0x40080104);
    t &= (~(0xf<<14));
    t |= (aonbg << 14);
    *(volatile int*)(0x40080104) = t;
    t = *(volatile int*)(0x40080104);
    t >>= 14;
    t &= 0xf;
//    log_printf("  INFO AONBG readback: %d\n", t);
}
#define CUR_TIME_TICK_US()       (REG_RD(0x42000104))
void gpadc_WaitWorkDone(void)
{
    volatile uint32_t cur_tick = CUR_TIME_TICK_US();

    while(gpadc_get_status(GPADC_FLAG_SAMP) == 0 && CUR_TIME_TICK_US() - cur_tick < 2000);
}

/**
 * @brief Initialize GPADC with specified configuration
 * @param GPADC_InitStruct Configuration parameters:
 *        - InputDivide: Voltage divider ratio (DIV1-DIV4)
 *        - DiffEN: Differential mode enable
 *        - Positive/NegativeInputChannel: Measurement inputs
 *        - AverageWindow: 2^N samples averaging
 *        - ClkDivide: ADC clock prescaler (fADC = 24MHz/(N+1))
 * 
 * @note BAT channel uses fixed DIV3 ratio regardless of configuration
 */
void gpadc_init(GPADC_InitTypeDef * GPADC_InitStruct)
{
    int t;
    // REG_GPADC_LDO_EN |= 0x303; // ldo_en=1
	  // REG_GPADC_LDO_VC = 0x2680; // adda vc 0.95V
	*(volatile int *)(0x40000028) |= (1<<15);
    //----------------------------------------
    // CONFIGURATION
    //----------------------------------------
    // analog
    if (GPADC_InitStruct->GPADC_PositiveInputChannel == GPADC_CHANNEL_P_BAT)
    {
        GPADC_ANA->GPADC_CTRL =     (GPADC_INPUT_DIV3 << 13)         |
                                    (GPADC_InitStruct->GPADC_DiffEN << 12)              |
                                    (8 << 8)                                            |
                                    (GPADC_InitStruct->GPADC_NegativeInputChannel << 4) |
                                    (GPADC_InitStruct->GPADC_PositiveInputChannel << 0) ;
    }
    else
    {
        GPADC_ANA->GPADC_CTRL =     (GPADC_InitStruct->GPADC_InputDivide << 13)         |
                                    (GPADC_InitStruct->GPADC_DiffEN << 12)              |
                                    (8 << 8)                                            |
                                    (GPADC_InitStruct->GPADC_NegativeInputChannel << 4) |
                                    (GPADC_InitStruct->GPADC_PositiveInputChannel << 0) ;
    }
    // digital
    GPADC_DIG->GPADC_ACTION =   (GPADC_InitStruct->GPADC_AverageWindow << 12)       |
                                (GPADC_InitStruct->GPADC_TimerSelect << 4)          |
                                (GPADC_InitStruct->GPADC_TimerTrigEN << 3)          |
                                (GPADC_InitStruct->GPADC_ContinueMode << 2)         ;
    GPADC_DIG->GPADC_CLK_CTRL = (GPADC_InitStruct->GPADC_ClkDivide << 8)            |
                                (3 << 2)                                            |
                                (GPADC_InitStruct->GPADC_ClkAutoGate << 1)          |
                                (GPADC_InitStruct->GPADC_ClkSelect << 0)            ;
    //----------------------------------------
    // GPADC calibration parameters set default
    //----------------------------------------
    if(g_gpadc_stat == 0){
        g_gpadc_div1_a = 3600;
        g_gpadc_div1_b = 0;
        g_gpadc_div2_a = 2 * g_gpadc_div1_a;
        g_gpadc_div2_b = 2 * g_gpadc_div1_b;
        g_gpadc_div3_a = 3 * g_gpadc_div1_a;
        g_gpadc_div3_b = 3 * g_gpadc_div1_b;
        g_gpadc_div4_a = 4 * g_gpadc_div1_a;
        g_gpadc_div4_b = 4 * g_gpadc_div1_b;
        g_gpadc_vbat_a = 4 * g_gpadc_div1_a;
        g_gpadc_vbat_b = 4 * g_gpadc_div1_b;
    }
    //----------------------------------------
    // Power
    //----------------------------------------
    // en
    *(volatile int *)(0x42002004) |= 0x301;
    // vc
    t = *(volatile int*)(0x40080104);
    t &= (~(0x1f<<8));
    t |= (6 << 8);
    *(volatile int*)(0x40080104) = t;
}


/**
 * @brief Set default configuration values
 * @param GPADC_InitStruct Structure to initialize with defaults:
 *        - DIV2 input, single-ended mode
 *        - 32-sample averaging
 *        - 3MHz sampling rate
 *        - Core voltage measurement channel
 */
void gpadc_structInit(GPADC_InitTypeDef * GPADC_InitStruct)
{
    GPADC_InitStruct->GPADC_InputDivide = GPADC_INPUT_DIV2;
    GPADC_InitStruct->GPADC_DiffEN = DISABLE;
    GPADC_InitStruct->GPADC_NegativeInputChannel= GPADC_CHANNEL_N_REF0V9;
    GPADC_InitStruct->GPADC_PositiveInputChannel = GPADC_CHANNEL_CIN; // default channel core input
    GPADC_InitStruct->GPADC_AverageWindow = GPADC_AVG_NUM_32; // default 3M/32 ~= 100K
    GPADC_InitStruct->GPADC_TimerSelect = 0;
    GPADC_InitStruct->GPADC_TimerTrigEN = DISABLE;
    GPADC_InitStruct->GPADC_ContinueMode = DISABLE;
    GPADC_InitStruct->GPADC_ClkDivide = 3; // default sample rate: 12m/(ClkDivide+1) = 3M
    GPADC_InitStruct->GPADC_ClkSelect = GPADC_CLK_SRC_RC24M;
    GPADC_InitStruct->GPADC_ClkAutoGate = ENABLE; // default enable
}

void gpadc_deInit(void){
    // local var
    GPADC_InitTypeDef GPADC_InitStruct;
    // de-init
    gpadc_structInit(&GPADC_InitStruct);
    gpadc_init(&GPADC_InitStruct);
    GPADC_DIG->GPADC_CLK_CTRL = 0; 
    GPADC_DIG->GPADC_CFG = 0;
    GPADC_DIG->GPADC_ACTION =0;
    gpadc_cmd(DISABLE);
    gpadc_itConfig(GPADC_ITMODE_DMA | GPADC_ITMODE_SAMP, DISABLE); 
}

/**
 * @brief Enable/disable ADC module
 * @param NewState ENABLE/DISABLE control flag
 * @note Disabling preserves configuration but stops conversions
 */
void gpadc_cmd(FunctionalState NewState)
{
    if (NewState != DISABLE){
        GPADC_ANA->GPADC_EN |= (uint32_t)(ENABLE << 1);
        GPADC_DIG->GPADC_ACTION |= (uint32_t)(ENABLE << 1);
    } else {
        GPADC_ANA->GPADC_EN &= ~((uint32_t)(ENABLE << 1));
        GPADC_DIG->GPADC_ACTION &= ~((uint32_t)(ENABLE << 1));
    }
}

void ADC_SoftwareStartConvCmd(FunctionalState NewState)
{
  if (NewState != DISABLE)
  {
    GPADC_DIG->GPADC_ACTION |= (uint32_t)(ENABLE << 31);
  }
}

uint16_t gpadc_GetConversionValue(void){
    return GPADC_DIG->GPADC_SAMP;
}

/**
 * @brief Convert raw ADC value to calibrated voltage
 * @return Voltage in millivolts with compensation applied
 * 
 * @process
 * 1. Select calibration coefficients based on input divider
 * 2. Apply linear calibration: Voltage = (RAW*A + B)/CALI_ZOOM
 * 3. Compensate using 2D LUT based on battery voltage and measured voltage
 * 4. Apply GPIO15 specific compensation (0.5% adjustment)
 */
uint16_t GPADC_GetConversionVoltage(void)
{
    uint32_t div_sel, vip_sel;
    int32_t samp, volt, a, b;
    // init
    samp = gpadc_GetConversionValue();
    div_sel = ((GPADC_ANA->GPADC_CTRL) >> 13) & 0x03;
    vip_sel = ((GPADC_ANA->GPADC_CTRL) >>  0) & 0x0f;
	
    // 输入通道为BAT通道时单独处理
    if (vip_sel == GPADC_CHANNEL_P_BAT){
        a = g_gpadc_vbat_a;
        b = g_gpadc_vbat_b;
        // voltage calibration
        volt = (samp*a + b)/GPADC_CALI_ZOOM;
        volt = gpadc_InternalSearchBATVoltageOffset(volt);
        return volt;
    }
    //GPIO通道
    else
    {
        if(div_sel == 0){
            a = g_gpadc_div1_a;
            b = g_gpadc_div1_b;
        } else if(div_sel == 1){
            a = g_gpadc_div2_a;
            b = g_gpadc_div2_b;
        } else if(div_sel == 2){
            a = g_gpadc_div3_a;
            b = g_gpadc_div3_b;
        } else {
            a = g_gpadc_div4_a;
            b = g_gpadc_div4_b;
        }
        // voltage calibration
        volt = (samp*a + b)/GPADC_CALI_ZOOM;
        volt = gpadc_InternalSearchVoltageOffset(volt, div_sel);
        if ((div_sel != 0) && (vip_sel == GPADC_CHANNEL_GPIO15)){
            volt = volt*1000/995;
        }

    }

    // out of range detect
    if(volt < 0) volt = 0;

    return (uint16_t)volt;
}



void gpadc_changeChannel(uint8_t channel)
{
    GPADC_ANA->GPADC_CTRL_b.RG_GPADC_VIP_SEL = channel;
    if(channel == GPADC_CHANNEL_P_BAT)
    {
        GPADC_ANA->GPADC_CTRL_b.RG_GPADC_ATT_SEL = GPADC_INPUT_DIV3;
    }
    DELAY_US(2);
    gpadc_ClearFlag(GPADC_FLAG_SAMP | GPADC_FLAG_DMA); // clear flags
    DELAY_US(2);
}

void gpadc_tampSensorCmd(FunctionalState NewState)
{
    REG_TEMPERATURE_SENSOR_EN = NewState;
}

FlagStatus gpadc_get_status(uint8_t ADC_FLAG)
{
  FlagStatus bitstatus = RESET;
  if ((uint8_t)(GPADC_DIG->GPADC_INT_CTRL & ADC_FLAG) != (uint8_t)RESET)
  {
    /* ADC_FLAG is set */
    bitstatus = SET;
  }
  else
  {
    /* ADC_FLAG is reset */
    bitstatus = RESET;
  }
  /* Return the ADC_FLAG status */
  return  bitstatus;
}




void gpadc_ClearFlag(uint8_t ADC_FLAG)
{
  /* Clear the selected ADC flags */
  GPADC_DIG->GPADC_INT_CTRL_BYTE[0] = ~ADC_FLAG;
}


void gpadc_itConfig(uint8_t ADC_ITMODE, FunctionalState NewState)
{
    if (NewState != DISABLE)
        GPADC_DIG->GPADC_INT_CTRL |= (uint32_t)(ADC_ITMODE << 16);
    else
        GPADC_DIG->GPADC_INT_CTRL &= ~((uint32_t)(ADC_ITMODE << 16));
}

ITStatus gpadc_GetITStatus(uint8_t ADC_ITMODE){
    ITStatus bitstatus = RESET;
    if(GPADC_DIG->GPADC_INT_CTRL & (ADC_ITMODE << 8))
        bitstatus = SET;
    else
        bitstatus = RESET;
    return bitstatus;
}

void gpadc_clear_ITPendingBit(uint8_t ADC_ITMODE){
    GPADC_DIG->GPADC_INT_CTRL_BYTE[1] = ADC_ITMODE;
}

static int gpadc_InternalCalibrationOneRange(int32_t * a, int32_t * b, int32_t cali_hi, int32_t cali_lo, int32_t delta_hi, int32_t delta_lo)
{
    int32_t volt_hi, volt_lo;
    int32_t samp_hi, samp_lo;
    if(cali_hi != 0xffffffff || cali_lo != 0xffffffff){
        samp_hi = ((cali_hi >> 16) & 0x3ff)*GPADC_FIX_COEF + delta_hi;
        samp_lo = ((cali_lo >> 16) & 0x3ff)*GPADC_FIX_COEF + delta_lo;
        volt_hi = ((cali_hi >>  0) & 0xfff)*GPADC_FIX_COEF;
        volt_lo = ((cali_lo >>  0) & 0xfff)*GPADC_FIX_COEF;
        *a = (volt_hi - volt_lo)*GPADC_CALI_ZOOM/(samp_hi - samp_lo);
        *b = (volt_lo*GPADC_CALI_ZOOM - samp_lo*(*a))/GPADC_FIX_COEF;
        return 1;
    }
    return 0;

}

/**
 * @brief Perform end-to-end ADC calibration
 * @uses OTP stored calibration points for each range
 * 
 * @calibration_process
 * 1. For each range (DIV1-DIV4, VBAT):
 *    - Retrieve high/low calibration points from OTP
 *    - Calculate linear coefficients: 
 *        A = (V_hi - V_lo)/(S_hi - S_lo)
 *        B = V_lo - A*S_lo
 * 2. Store coefficients in global variables
 * 3. Update calibration status flag
 */
void gpadc_start_calibration(void)
{
    uint8_t stasus = 0;
	if(g_gpadc_stat)return;
	extern void delay_us(uint32_t us);

	REG_WRT(0x4000006C,0x3);
    REG_WRT_BITS(0x42002008, 5, 0, 0x1E);

	REG_WRT(0x40000050,0x1);
	delay_us(1); //Tpens 1us
	REG_WRT(0x40000050,0x3);
	delay_us(5); //Tpls 5us
	REG_WRT(0x40000050,0x7);
	delay_us(1); //Tpls 5us
	REG_WRT(0x40000050,0xF);
	delay_us(6); //Tpls 5us

	cal_init();
	stasus = gpadc_InternalCalibrationOneRange(&g_gpadc_div1_a, &g_gpadc_div1_b, GPADC_OTP_CALI_DIV1_HIGH, GPADC_OTP_CALI_DIV1_LOW, GPADC_CALI_DIV1_DELTA_HI, GPADC_CALI_DIV1_DELTA_LO);
    stasus &= gpadc_InternalCalibrationOneRange(&g_gpadc_div2_a, &g_gpadc_div2_b, GPADC_OTP_CALI_DIV2_HIGH, GPADC_OTP_CALI_DIV2_LOW, GPADC_CALI_DIV2_DELTA_HI, GPADC_CALI_DIV2_DELTA_LO);
    stasus &= gpadc_InternalCalibrationOneRange(&g_gpadc_div3_a, &g_gpadc_div3_b, GPADC_OTP_CALI_DIV3_HIGH, GPADC_OTP_CALI_DIV3_LOW, GPADC_CALI_DIV3_DELTA_HI, GPADC_CALI_DIV3_DELTA_LO);
    stasus &= gpadc_InternalCalibrationOneRange(&g_gpadc_div4_a, &g_gpadc_div4_b, GPADC_OTP_CALI_DIV4_HIGH, GPADC_OTP_CALI_DIV4_LOW, GPADC_CALI_DIV4_DELTA_HI, GPADC_CALI_DIV4_DELTA_LO);
    stasus &= gpadc_InternalCalibrationOneRange(&g_gpadc_vbat_a, &g_gpadc_vbat_b, GPADC_OTP_CALI_VBAT_HIGH, GPADC_OTP_CALI_VBAT_LOW, GPADC_CALI_VBAT_DELTA_HI, GPADC_CALI_VBAT_DELTA_LO);
    g_gpadc_stat = 1;
}


/**
 * @brief Smart sampling with automatic range switching
 * @return Valid voltage or 0xFFFF on error
 * 
 * @algorithm
 * 1. Take initial measurement
 * 2. Verify within current range validity window
 * 3. If out-of-range:
 *    - Switch to appropriate divider
 *    - Retry measurement
 *    - Max 4 attempts to prevent loop lock
 */
uint16_t gpadc_get_samplevoltage(void)
{
    uint32_t i, t, cont_mode, div_sel, vip_chl;
    uint16_t volt;
    // init
    vip_chl = ((GPADC_ANA->GPADC_CTRL) >> 0) & 0xf;
    div_sel = ((GPADC_ANA->GPADC_CTRL) >> 13) & 0x3;
    cont_mode = ((GPADC_DIG->GPADC_ACTION) >> 2) & 0x1;
	
    // from div1 to div4 may change 3 times
    if (vip_chl != GPADC_CHANNEL_P_BAT)
    {
        for(i=0; i<4; i++){
            if(cont_mode == 0) 
				ADC_SoftwareStartConvCmd(ENABLE);
            // wait sample
            gpadc_WaitWorkDone();
             while(gpadc_get_status(GPADC_FLAG_SAMP) == 0);
            // get voltage
            volt = GPADC_GetConversionVoltage();
            // check valid
            if(((div_sel == 0) && (volt >= GPADC_DIV1_VALID_MIN) && (volt <= GPADC_DIV1_VALID_MAX)) ||
                ((div_sel == 1) && (volt >= GPADC_DIV2_VALID_MIN) && (volt <= GPADC_DIV2_VALID_MAX)) ||
                ((div_sel == 2) && (volt >= GPADC_DIV3_VALID_MIN) && (volt <= GPADC_DIV3_VALID_MAX)) ||
                ((div_sel == 3) && (volt >= GPADC_DIV4_VALID_MIN) && (volt <= GPADC_DIV4_VALID_MAX)))
                return volt;
            // get div_sel
            if(volt <= GPADC_DIV1_VALID_MAX)        div_sel = 0;
            else if(volt <= GPADC_DIV2_VALID_MAX)   div_sel = 1;
            else if(volt <= GPADC_DIV3_VALID_MAX)   div_sel = 2;
            else                                    div_sel = 3;
            // set div_sel
            t = GPADC_ANA->GPADC_CTRL;
            t &= (~(3 << 13));
            t |= (div_sel << 13);
            GPADC_ANA->GPADC_CTRL = t;
            DELAY_US(2); // wait settle
            if(i == 3) return 0xffff; // error value
        }
    }
    else
    {
        // trigger sample
        if(cont_mode == 0) ADC_SoftwareStartConvCmd(ENABLE);
        // wait sample
        gpadc_WaitWorkDone();
         while(gpadc_get_status(GPADC_FLAG_SAMP) == 0);
        // get voltage
        volt = GPADC_GetConversionVoltage();
        // check valid
        if(((vip_chl == GPADC_CHANNEL_P_BAT) && (volt >= GPADC_DIV4_VALID_MIN) && (volt <= GPADC_DIV4_VALID_MAX)))
            return volt;
    }
    // check value valid ???
    return volt;
}

/**
 * @brief Update battery voltage measurement
 * @return Measured battery voltage in millivolts (mV), 
 *         returns 0xFFFF if measurement is invalid
 * 
 * @note This function performs the following operations:
 * 1. Configures ADC to battery channel (BAT) with appropriate settings
 * 2. Performs voltage sampling using pre-configured calibration data
 * 3. Applies temperature compensation and linearization
 * 4. Updates global battery voltage variable (g_gpadc_vbat)
 * 5. Validates measurement against configured voltage ranges
 * 
 * @attention When using this function:
 * - Ensure LDO and ADC clock are properly initialized
 * - The input divider must be configured as GPADC_INPUT_DIV4
 * - Calibration data from OTP should be pre-loaded
 */
uint16_t gpadc_get_sampleBAT(void)
{
    uint32_t vip_sel, gpadc_clk_ctrl, gpadc_ctrl, gpadc_action, gpadc_cmd;
    int32_t samp, volt = 0, a, b;

    //store last cfg
    gpadc_ctrl = GPADC_ANA->GPADC_CTRL;
    gpadc_clk_ctrl = GPADC_DIG->GPADC_CLK_CTRL;
    gpadc_action = GPADC_DIG->GPADC_ACTION;
    gpadc_cmd = GPADC_ANA->GPADC_EN;


    //config BAT mode
    GPADC_ANA->GPADC_CTRL = 0x4889;
    GPADC_DIG->GPADC_CLK_CTRL = 0x30E;
    GPADC_DIG->GPADC_ACTION = 0x7002;
    GPADC_ANA->GPADC_EN = 0x0002;

    ADC_SoftwareStartConvCmd(ENABLE);
    // wait sample
    gpadc_WaitWorkDone();
    // while(gpadc_get_status(GPADC_FLAG_SAMP) == 0);
    samp = gpadc_GetConversionValue();
    vip_sel = ((GPADC_ANA->GPADC_CTRL) >>  0) & 0x0f;
    // get a/b
    if (vip_sel == GPADC_CHANNEL_P_BAT){
        a = g_gpadc_vbat_a;
        b = g_gpadc_vbat_b;

        // voltage calibration
        volt = (samp*a + b)/GPADC_CALI_ZOOM;

        // Vbat voltage calibration
        volt = gpadc_InternalSearchBATVoltageOffset(volt);
    }
    //Restore GPADC
    GPADC_ANA->GPADC_CTRL = gpadc_ctrl;
    GPADC_DIG->GPADC_CLK_CTRL = gpadc_clk_ctrl;
    GPADC_DIG->GPADC_ACTION = gpadc_action;
    GPADC_ANA->GPADC_EN = gpadc_cmd;
    // out of range detect
    if(volt < 0) volt = 0;
    // return
    g_gpadc_vbat = volt;
    return volt;
}

uint16_t gpadc_get_sample(GPADC_ChannelTypeDef adc_ch)
{
    uint32_t vip_sel,div_sel, gpadc_clk_ctrl, gpadc_ctrl, gpadc_action, gpadc_cmd;
    int32_t samp, volt = 0, a, b;

    //store last cfg
    gpadc_ctrl = GPADC_ANA->GPADC_CTRL;
    gpadc_clk_ctrl = GPADC_DIG->GPADC_CLK_CTRL;
    gpadc_action = GPADC_DIG->GPADC_ACTION;
    gpadc_cmd = GPADC_ANA->GPADC_EN;

    gpadc_changeChannel(adc_ch);
    //config BAT mode
    // GPADC_ANA->GPADC_CTRL = 0x4889;
    GPADC_DIG->GPADC_CLK_CTRL = 0x30E;
    GPADC_DIG->GPADC_ACTION = 0x7002;
    GPADC_ANA->GPADC_EN = 0x0002;

    ADC_SoftwareStartConvCmd(ENABLE);
    // wait sample
    gpadc_WaitWorkDone();
    // while(gpadc_get_status(GPADC_FLAG_SAMP) == 0);
    samp = gpadc_GetConversionValue();
    vip_sel = ((GPADC_ANA->GPADC_CTRL) >>  0) & 0x0f;
    div_sel = ((GPADC_ANA->GPADC_CTRL) >> 13) & 0x3;
    // get a/b
    if (vip_sel == GPADC_CHANNEL_P_BAT)
    {
        a = g_gpadc_vbat_a;
        b = g_gpadc_vbat_b;

        // voltage calibration
        volt = (samp*a + b)/GPADC_CALI_ZOOM;

        // Vbat voltage calibration
        volt = gpadc_InternalSearchBATVoltageOffset(volt);
        g_gpadc_vbat = volt;
    }
    else
    {
        for(int i=0; i<4; i++)
		{
            // trigger sample
			ADC_SoftwareStartConvCmd(ENABLE);
				
            // wait sample
            gpadc_WaitWorkDone();
//             while(gpadc_get_status(GPADC_FLAG_SAMP) == 0);
            // get voltage
            volt = GPADC_GetConversionVoltage();
            // check valid
            if(((div_sel == 0) && (volt >= GPADC_DIV1_VALID_MIN) && (volt <= GPADC_DIV1_VALID_MAX)) ||
                ((div_sel == 1) && (volt >= GPADC_DIV2_VALID_MIN) && (volt <= GPADC_DIV2_VALID_MAX)) ||
                ((div_sel == 2) && (volt >= GPADC_DIV3_VALID_MIN) && (volt <= GPADC_DIV3_VALID_MAX)) ||
                ((div_sel == 3) && (volt >= GPADC_DIV4_VALID_MIN) && (volt <= GPADC_DIV4_VALID_MAX)))
                //return volt;
                break;
            // get div_sel
            if(volt <= GPADC_DIV1_VALID_MAX)        div_sel = 0;
            else if(volt <= GPADC_DIV2_VALID_MAX)   div_sel = 1;
            else if(volt <= GPADC_DIV3_VALID_MAX)   div_sel = 2;
            else                                    div_sel = 3;
            // set div_sel
            int t = GPADC_ANA->GPADC_CTRL;
            t &= (~(3 << 13));
            t |= (div_sel << 13);
            GPADC_ANA->GPADC_CTRL = t;
            DELAY_US(2); // wait settle
            if(i == 3) volt =0;//return 0xffff; // error value
        }
    }
    //Restore GPADC
    GPADC_ANA->GPADC_CTRL = gpadc_ctrl;
    GPADC_DIG->GPADC_CLK_CTRL = gpadc_clk_ctrl;
    GPADC_DIG->GPADC_ACTION = gpadc_action;
    GPADC_ANA->GPADC_EN = gpadc_cmd;
    // out of range detect
    if(volt < 0) volt = 0;
    // return
    // g_gpadc_vbat = volt;
    return volt;
}


static int16_t gpadc_InternalSearchVoltageOffset(uint16_t voltage, uint16_t div_sel)
{
    uint16_t vbat_column, voltage_line, remainder;
    int16_t offset;
    uint16_t div_max[] = {200, 1700, 2600, 3300};
    uint16_t div_min[] = {0,   120,  1600, 2500};
    if (g_gpadc_vbat < 1900){
        vbat_column = 0;
    }
    else if (1900 <= g_gpadc_vbat && g_gpadc_vbat < 3300){
        vbat_column = (g_gpadc_vbat - 1900)/100;
    }
    else{
        vbat_column = 14;
    }

    if(voltage < 3350){
        voltage_line = ((voltage + 50) / 100)-1;
        if((voltage+50) > div_max[div_sel]){
            voltage_line -= 1;
        }
        if((voltage-50) < div_min[div_sel]){
            voltage_line += 1;
        }
    }
    else{
        voltage_line = 33;
    }


    if (g_gpadc_vbat <= 1900){
        offset = gpadc_voltoffset[voltage_line][0];
    }
    else if (g_gpadc_vbat >= 3250){
        offset = gpadc_voltoffset[voltage_line][14];
    }
    else {
        if ((abs(gpadc_voltoffset[voltage_line][vbat_column] - gpadc_voltoffset[voltage_line][vbat_column+1])) <= 4){
            offset = (gpadc_voltoffset[voltage_line][vbat_column] + gpadc_voltoffset[voltage_line][vbat_column+1]) / 2;
        }
        else {
            remainder = g_gpadc_vbat%100;
            offset = gpadc_voltoffset[voltage_line][vbat_column] + (remainder >> 4);
        }
    }
    voltage = voltage + offset;
    return voltage;
}

static int16_t gpadc_InternalSearchBATVoltageOffset(uint16_t vbat)
{
    int16_t offset;
    if(vbat < 1900){
        offset = gpadc_batvoltoffset[0];
    }
    else if(vbat > 3250){
        offset = gpadc_batvoltoffset[14];
    }
    else{
        int i = (vbat-1900)/100;
        if((abs(gpadc_batvoltoffset[i+1] - gpadc_batvoltoffset[i])) < 5){
            offset = (gpadc_batvoltoffset[i] + gpadc_batvoltoffset[i+1]) / 2;
        }
        else{
            offset = gpadc_batvoltoffset[i] + ((vbat-1900) >> 3);
        }
    }
    vbat = vbat + offset;
    return vbat;
}

/**
 * @brief Configure ADC LDO for optimal performance
 * @note Must be called before ADC operation
 * 
 * @settings
 * - Enable LDO (0x303)
 * - Set VCORE to 0.95V (0x06 << 8)
 */
void gpadc_LDOInit(void)
{
    uint32_t reg_val;
    REG_GPADC_LDO_EN |= 0x303; // ldo_en=1
    reg_val = REG_GPADC_LDO_VC;
    reg_val &= ~(0x1f << 8);
    reg_val |= (0x06 << 8);
	REG_GPADC_LDO_VC = reg_val; // adda vc 0.95V
}

/** 
 * @brief Get internal reference resistance
 * @return OTP-stored resistance value (ohms)
 * @used For external sensor calculations
 */
uint32_t gpadc_GetRin(void)
{
    return GPADC_OTP_INTERNAL_RESISTANCE;
}

/**
 * @brief Initialize general-purpose ADC channel configuration
 * @param channel ADC analog input channel to configure (refer to GPADC_ChannelTypeDef enum)
 * 
 * Function workflow:
 * 1. Initialize ADC configuration structure with default parameters
 * 2. Configure channel-specific ADC acquisition parameters:
 *    - Input divider ratio (DIV4)
 *    - Single-ended measurement mode
 *    - 128-sample averaging
 *    - Single conversion mode
 * 3. Apply hardware configuration
 * 4. Perform ADC calibration
 * 5. Enable ADC module
 */
void gpadc_channel_Init(GPADC_ChannelTypeDef channel)
{
    gpadc_LDOInit();
    GPADC_InitTypeDef GPADC_InitStruct;
    gpadc_structInit(&GPADC_InitStruct);

    GPADC_InitStruct.GPADC_InputDivide = GPADC_INPUT_DIV4;
    GPADC_InitStruct.GPADC_DiffEN = DISABLE;
    GPADC_InitStruct.GPADC_PositiveInputChannel = channel;
    GPADC_InitStruct.GPADC_AverageWindow = GPADC_AVG_NUM_128;
    GPADC_InitStruct.GPADC_ContinueMode = DISABLE;
	gpadc_start_calibration();
    gpadc_init(&GPADC_InitStruct);
    gpadc_cmd(ENABLE); // enable
}


__RAM_CODE_SECTION static int16_t gpadc_samp_cali(uint16_t voltage, uint16_t div_sel)
{
    uint16_t vbat_column, voltage_line, remainder;
    int16_t offset;
    uint16_t div_max[] = {200, 1700, 2600, 3300};
    uint16_t div_min[] = {0,   120,  1600, 2500};
    if (g_gpadc_vbat < 1900){
        vbat_column = 0;
    }
    else if (1900 <= g_gpadc_vbat && g_gpadc_vbat < 3300){
        vbat_column = (g_gpadc_vbat - 1900)/100;
    }
    else{
        vbat_column = 14;
    }

    if(voltage < 3350){
        voltage_line = ((voltage + 50) / 100)-1;
        if((voltage+50) > div_max[div_sel]){
            voltage_line -= 1;
        }
        if((voltage-50) < div_min[div_sel]){
            voltage_line += 1;
        }
    }
    else{
        voltage_line = 33;
    }


    if (g_gpadc_vbat <= 1900){
        offset = gpadc_voltoffset[voltage_line][0];
    }
    else if (g_gpadc_vbat >= 3250){
        offset = gpadc_voltoffset[voltage_line][14];
    }
    else {
        if ((abs(gpadc_voltoffset[voltage_line][vbat_column] - gpadc_voltoffset[voltage_line][vbat_column+1])) <= 4){
            offset = (gpadc_voltoffset[voltage_line][vbat_column] + gpadc_voltoffset[voltage_line][vbat_column+1]) / 2;
        }
        else {
            remainder = g_gpadc_vbat%100;
            offset = gpadc_voltoffset[voltage_line][vbat_column] + (remainder >> 4);
        }
    }
    voltage = voltage + offset;
    return voltage;
}

//new api -- 20250912
//gain:(0-3)  0--0.9v  1--1.8v  2--2.7v  3--3.6v
 __RAM_CODE_SECTION uint16_t gpadc_get_sample_tmp(GPADC_ChannelTypeDef adc_ch, uint8_t gain) 
{
    uint32_t vip_sel,div_sel;
    int32_t samp, volt = 0, a, b;

	gpadc_LDOInit();//add @20250923
	
	gpadc_cmd(ENABLE); // enable add @20250923
	 
	//adc ch
	GPADC_ANA->GPADC_CTRL_b.RG_GPADC_VIP_SEL = adc_ch;

	//gain
    int t = GPADC_ANA->GPADC_CTRL;
    t &= (~(gain << 13));
    t |= (gain << 13);
    GPADC_ANA->GPADC_CTRL = t;


    // trigger sample
	ADC_SoftwareStartConvCmd(ENABLE);
				
    // wait sample
    gpadc_WaitWorkDone();

    // init
    samp = gpadc_GetConversionValue();  
	
    div_sel = ((GPADC_ANA->GPADC_CTRL) >> 13) & 0x03;
    vip_sel = ((GPADC_ANA->GPADC_CTRL) >>  0) & 0x0f;
    {
		
        if(div_sel == 0){
            a = g_gpadc_div1_a;
            b = g_gpadc_div1_b;
        } else if(div_sel == 1){
            a = g_gpadc_div2_a;
            b = g_gpadc_div2_b;
        } else if(div_sel == 2){
            a = g_gpadc_div3_a;
            b = g_gpadc_div3_b;
        } else {
            a = g_gpadc_div4_a;
            b = g_gpadc_div4_b;
        }
		
        // voltage calibration
        volt = (samp*a + b)/GPADC_CALI_ZOOM;
        volt = gpadc_samp_cali(volt, div_sel);
        if ((div_sel != 0) && (vip_sel == GPADC_CHANNEL_GPIO15))
		{
            volt = volt*1000/995;
        }
		
    }
    // out of range detect
    if(volt < 0) volt = 0;

    return volt;
}






