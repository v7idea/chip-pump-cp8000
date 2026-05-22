/*************************************************************************************************
 * @file       driver_timer.h
 * @author     BLE Group
 * @brief 
 * @version    1.0.5
 * @date       2025-09-26
 * 
 * @copyright Copyright (c) 2024, CHIP PUMP Microelectronics.
                 All rights reserved.
 * 
 ************************************************************************************************/

#ifndef __DRIVER_TIMER_H__
#define __DRIVER_TIMER_H__

#include "driver_gpio.h"

#define TIMER_MAX_PERIOD_US    5592320

#define TIMER_PWM_FUNC      (6)
#define TIMER_PWM_N_FUNC    (7)

#define TIMER_PWM0N100_ENABLE  (0X10)
#define TIMER_PWM0N100_DISABLE (0X00)
		
#define TIMER_MODE_USER_DEFINED  (0x02)
#define TIMER_MODE_FREE_RUNNING  (0x00)



#define TIMER_PWM_ENABLE   (0x08)
#define TIMER_PWM_DISABLE  (0x00) 



#define TIMER_INTR_ENABLE  (0x00)
#define TIMER_INTR_DISABLE (0x04)

#define PWM_OUTPUT_ENABLE          (0x1)
#define PWM_REVERSE_OUTPUT_ENABLE (0x2)
#define PWM_OUTPUT_ALL_ENABLE     (PWM_OUTPUT_ENABLE|PWM_REVERSE_OUTPUT_ENABLE)

typedef enum 
{
	TIMER0  = 0x00,
	TIMER1 ,
	TIMER2 ,
	TIMER3 ,
	TIMER4 ,
	TIMER5 ,
	TIMER6 ,
	TIMER7 ,
}ENUM_TIMER;

typedef enum 
{
	PWM0  = 0x00,
	PWM1 ,
	PWM2 ,
	PWM3 ,
	PWM4 ,
	PWM5 ,
	PWM6 ,
	PWM7 ,
}ENUM_PWM;

typedef enum 
{
	PWM0_PIN0  = 0,
	PWM1_PIN1,      
	PWM2_PIN2,        
	PWM3_PIN3,   
	PWM4_PIN4, 
	PWM5_PIN5,       
	PWM6_PIN6,      
	PWM7_PIN7,     
	PWM0_PIN8,      
	PWM1_PIN9,       
	PWM2_PIN10,     
	PWM3_PIN11,   
	PWM4_PIN12,        
	PWM5_PIN13,        
	PWM6_PIN14,        
	PWM7_PIN15,        
	PWM0_PIN16,     
	PWM1_PIN17,        
	PWM2_PIN18,      
	PWM3_PIN19,       
	PWM4_PIN20,        
	PWM5_PIN21,   
	PWM6_PIN22,        
	PWM7_PIN23       
}ENUM_PWM_PIN;

typedef enum 
{
	PWM7N_PIN0 = 0,
	PWM0N_PIN1,       
	PWM1N_PIN2,       
	PWM2N_PIN3,       
	PWM3N_PIN4,      
	PWM4N_PIN5,        
	PWM5N_PIN6,       
	PWM6N_PIN7,        
	PWM7N_PIN8,      
	PWM0N_PIN9,      
	PWM1N_PIN10,      
	PWM2N_PIN11,       
	PWM3N_PIN12,  
	PWM4N_PIN13,    
	PWM5N_PIN14,       
	PWM6N_PIN15,       
	PWM7N_PIN16,     
	PWM0N_PIN17,     
	PWM1N_PIN18,    
	PWM2N_PIN19,     
	PWM3N_PIN20,     
	PWM4N_PIN21,     
	PWM5N_PIN22,      
	PWM6N_PIN23
}ENUM_PWMN_PIN;

typedef enum 
{
	PWM_POS  = 0x1,
	PWM_NEG  = 0x2,
	PWM_COMP = 0x3
}ENUM_PWM_OUTPUT_MODE;

/*-------------------------------------
  Clock Configuration
-------------------------------------*/
/**
 * @brief Timer clock source selection
 * @note Clock frequency affects maximum PWM resolution
 */
typedef enum 
{
	TIMER_CLK_SEL_XTAL24M = 0X00,  ///< 24MHz crystal oscillator
	TIMER_CLK_SEL_RC24M,           ///< 24MHz internal RC oscillator
	TIMER_CLK_SEL_PLL48M,          ///< 48MHz PLL output
} ENUM_TIMER_CLK;

/**
 * @brief Clock prescaler options
 * @note Actual divider = 2^(n+1) for values 0-10
 */
typedef enum 
{
	TIMER_CLK_DIVIDE_2 = 0X00,
	TIMER_CLK_DIVIDE_4 ,
	TIMER_CLK_DIVIDE_8 ,
	TIMER_CLK_DIVIDE_16 ,
	TIMER_CLK_DIVIDE_32 ,
	TIMER_CLK_DIVIDE_64 ,
	TIMER_CLK_DIVIDE_128 ,
	TIMER_CLK_DIVIDE_256 ,
	TIMER_CLK_DIVIDE_512 ,
	TIMER_CLK_DIVIDE_1024 ,
	TIMER_CLK_DIVIDE_2048 ,
	TIMER_CLK_DIVIDE_4096 ,
	TIMER_CLK_NO_DIVIDE = 12
}ENUM_TIMER_CLK_DIVIDE;

/*-------------------------------------
  Configuration Structures
-------------------------------------*/
/**
 * @brief Timer initialization parameters
 * @note All values must be set before calling timer_param_init()
 */
typedef struct
{
    uint8_t timer_pwm_en; 	    ///< PWM enable/disable flag
	uint8_t timer_pwm0n100_en;  ///< Full range duty cycle enable
	uint8_t timer_mode;         ///< Operation mode selection
	uint16_t timer_loadcount;   ///< Main counter reload value
	uint16_t timer_loadcount2;  ///< Secondary reload value (PWM duty)
	uint16_t timer_clk;         ///< Clock source selection
	uint32_t timer_clk_divide;  ///< Clock prescaler setting
}TIMER_InitTypeDef;

/**
 * @brief PWM configuration parameters
 * @note Used for complementary PWM with dead time
 */
typedef struct 
{
	uint16_t pwm_Cycle_CNT;          ///< Total period in clock cycles
	uint16_t pwm_Init_Duty_CNT;      ///< Initial active phase cycles
	ENUM_PWM_OUTPUT_MODE pwm_Mode;   ///< Complementary output enable
	uint16_t pwm_DT_CNT;             ///< Dead time insertion (clock cycles)
	ENUM_PWM pwm_CH;                 ///< PWM channel selection
	ENUM_PWM_PIN pwm_Pin;            ///< Primary output GPIO pin
	ENUM_PWMN_PIN pwm_N_Pin;         ///< Complementary output GPIO pin
}pwm_config_param_t;

/*-------------------------------------
  Driver API Declarations
-------------------------------------*/

/**
 * @brief Initialize timer peripheral
 * @param timer_x Timer instance (TIMER0-TIMER7)
 * @param period_us Interrupt period in microseconds,10 uS - 5592320 uS
 * @note Configures NVIC interrupts and clock settings
 */
void timer_init(ENUM_TIMER timer_x,uint32_t period_us);

/**
 * @brief Enable timer peripheral
 * @param TIMERx Timer instance (TIMER0-TIMER7)
 * 
 * @note Accesses CTRL register at offset 0x08 per timer instance
 */
void timer_enable(ENUM_TIMER TIMERx);

/**
 * @brief Disable timer peripheral
 * @param TIMERx Timer instance (TIMER0-TIMER7)
 */
void timer_disable(ENUM_TIMER TIMERx);

/**
 * @brief Enable timer interrupts
 * @param TIMERx Timer instance (TIMER0-TIMER7)
 * 
 * @note Clears interrupt mask bit in CTRL register
 */
uint8_t timer_get_it_status(ENUM_TIMER TIMERx);

/**
 * @brief Clear timer interrupts
 */
void timer_int_clear(void);

/**
 * @brief Configure timer clock divider
 * @param TIMERx Timer instance (TIMER0-TIMER7)
 * @param divider Clock divider value
 */
void timer_divider_config(ENUM_TIMER TIMERx ,ENUM_TIMER_CLK_DIVIDE divider);

/**
 * @brief Clear timer interrupts
 * @param TIMERx Timer instance (TIMER0-TIMER7)
 */
void timerx_int_clear(ENUM_TIMER TIMERx);

/**
 * @brief Enable PWM output channel
 * @param pwm_cfg Pointer to PWM configuration structure
 * @note Handles GPIO multiplexing and dead time configuration
 */
void pwm_init(pwm_config_param_t *pwm_cfg);

/**
 * @brief Set PWM duty cycle
 * @param pwm_ch PWM channel (PWM0-PWM7)
 * @param duty_cnt Active high period in clock cycles
 * 
 * @note Maintains total period while updating active/inactive phases
 */
void pwm_duty_set(ENUM_PWM pwm_ch,uint16_t duty_cnt);

/**
 * @brief Set PWM Reverse duty cycle
 * @param pwm_ch PWM channel (PWM0-PWM7)
 * @param duty_cnt Active high period in clock cycles
 * 
 * @note Maintains total period while updating active/inactive phases
 */
void pwm_n_duty_set(ENUM_PWM pwm_ch,uint16_t duty_cnt);

/**
 * @brief Get PWM duty cycle
 * @param pwm_ch PWM channel (PWM0-PWM7)
 * @return Current duty cycle value
 */
uint16_t pwm_duty_get(ENUM_PWM pwm_ch);

/**
 * @brief Get PWM negative duty cycle
 * @param pwm_ch PWM channel (PWM0-PWM7)
 * @return Current negative duty cycle value
 */
uint16_t pwm_n_duty_get(ENUM_PWM pwm_ch);

#endif
