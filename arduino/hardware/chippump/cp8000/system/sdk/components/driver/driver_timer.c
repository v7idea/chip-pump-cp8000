/*************************************************************************************************
 * @file       driver_timer.c
 * @author     BLE Group
 * @brief      Timer and PWM Controller Driver for CP8xxx Series MCUs
 * @version    1.0.5
 * @date       2025-09-26
 * 
 * @copyright Copyright (c) 2024, CHIP PUMP Microelectronics.
                 All rights reserved.
 * 
 ************************************************************************************************/
#include <stdint.h>
#include "mcu_reg_def.h"
#include "driver_timer.h"

/**
 * @brief Enable timer peripheral
 * @param TIMERx Timer instance (TIMER0-TIMER7)
 * 
 * @note Accesses CTRL register at offset 0x08 per timer instance
 */
void timer_enable(ENUM_TIMER TIMERx)
{
	*(volatile uint32_t*)(TIMER_BASE + 0x08 + (TIMERx) * 0x14)  |= ENABLE ;
}

/**
 * @brief Disable timer peripheral
 * @param TIMERx Timer instance (TIMER0-TIMER7)
 */
void timer_disable(ENUM_TIMER TIMERx)
{
	*(volatile uint32_t*)(TIMER_BASE + 0x08 + (TIMERx) * 0x14)  &= ~ENABLE;
}


/**
 * @brief Enable timer interrupts
 * @param TIMERx Timer instance (TIMER0-TIMER7)
 * 
 * @note Clears interrupt mask bit in CTRL register
 */
void timer_int_enable(ENUM_TIMER TIMERx)
{
    *(volatile uint32_t*)(TIMER_BASE + 0x08 + (TIMERx * 0x14))  &= ~(TIMER_INTR_DISABLE);
}


/**
 * @brief Disable timer interrupts
 * @param TIMERx Timer instance (TIMER0-TIMER7)
 */
void timer_int_disable(ENUM_TIMER TIMERx)
{
	*(volatile uint32_t*)(TIMER_BASE + 0x08 + (TIMERx * 0x14))  |= (TIMER_INTR_DISABLE);
}

/*-------------------------------------
  Timer Configuration
-------------------------------------*/

/**
 * @brief Initialize timer parameters
 * @param TIMERx Timer instance (TIMER0-TIMER7)
 * @param timer_struct Configuration parameters:
 *        - Clock source (24MHz XTAL/PLL48M)
 *        - Clock divider (1-16)
 *        - Operation mode (Free-running/User-defined)
 *        - Load values (Main/Secondary)
 *        - PWM configuration
 * 
 * @sequence
 * 1. Disable timer during configuration
 * 2. Configure clock source and divider
 * 3. Set operation mode and load values
 * 4. Handle PLL clock special case
 */
void timer_param_init(ENUM_TIMER TIMERx,TIMER_InitTypeDef *timer_struct)
{
	timer_disable(TIMERx);
	uint16_t clk = *(volatile uint32_t*)(SYS_CTRL_BASE + 0x30) ;
	clk &= ~(0x3 << (TIMERx * 2));
	clk |= (timer_struct->timer_clk << (TIMERx * 2));
	*(volatile uint16_t*)(SYS_CTRL_BASE + 0x30) = clk;

	if(timer_struct->timer_clk == TIMER_CLK_SEL_PLL48M)
	{
		*(volatile uint8_t*)(0x42002000) |= 2;
	}

	uint32_t divide = *(volatile uint32_t*)(SYS_CTRL_BASE + 0x34) ;
	divide &= ~(0xf << (TIMERx * 4));
	divide |= (timer_struct->timer_clk_divide << (TIMERx * 4));
	*(volatile uint32_t*)(SYS_CTRL_BASE + 0x34) = divide;

	uint32_t tmpreg;
	tmpreg = timer_struct->timer_pwm_en | timer_struct->timer_pwm0n100_en | timer_struct->timer_mode;
	*(volatile uint32_t*)(TIMER_BASE + 0x08 + (TIMERx)* 0x14) &= 0x05;
	*(volatile uint32_t*)(TIMER_BASE + 0x08 + (TIMERx)* 0x14) |= tmpreg;
	*(volatile uint16_t*)(TIMER_BASE + 0x00 + (TIMERx)* 0x14) = timer_struct->timer_loadcount;
	if(timer_struct->timer_pwm_en == TIMER_PWM_ENABLE)
	*(volatile uint16_t*)(TIMER_BASE + 0xB0 + (TIMERx) * 0x4) = timer_struct->timer_loadcount2;
}

/**
 * @brief Set default timer parameters
 * @param timer_struct Pointer to timer configuration structure to initialize
 */
void timer_param_default(TIMER_InitTypeDef *timer_struct)
{
	timer_struct->timer_pwm_en = TIMER_PWM_DISABLE;
	timer_struct->timer_pwm0n100_en = TIMER_PWM0N100_DISABLE;
	timer_struct->timer_mode = TIMER_MODE_FREE_RUNNING;
	timer_struct->timer_loadcount = 0xffff;
	timer_struct->timer_loadcount2= 0xffff;
	timer_struct->timer_clk = TIMER_CLK_SEL_XTAL24M;
	timer_struct->timer_clk_divide = TIMER_CLK_DIVIDE_2;
}




/**
 * @brief Get timer interrupt status
 * @param TIMERx Timer instance (TIMER0-TIMER7)
 * @return Non-zero if interrupt is pending, 0 otherwise
 */
uint8_t timer_get_it_status(ENUM_TIMER TIMERx)
{
  uint8_t ret = 0;

  if((TIMER ->TIMERS_INT_STATUS & (0x01 << (TIMERx))))
  {
    ret = 1;
  }

  return ret;
}

/**
 * @brief Clear all timer interrupts
 */
void timer_int_clear(void)
{
	*(volatile uint8_t*)(TIMER_BASE + 0xA4);
}


/**
 * @brief Clear timer interrupts
 * @param TIMERx Timer instance (TIMER0-TIMER7)
 */
void timerx_int_clear(ENUM_TIMER TIMERx)
{
	*(volatile uint8_t*)(TIMER_BASE + 0x0C + (TIMERx * 0x14));
}

/**
 * @brief Configure timer clock divider
 * @param TIMERx Timer instance (TIMER0-TIMER7)
 * @param divider Clock divider value
 */
void timer_divider_config(ENUM_TIMER TIMERx ,ENUM_TIMER_CLK_DIVIDE divider)
{
	uint32_t divide_val = *(volatile uint32_t*)(SYS_CTRL_BASE + 0x34) ;
	divide_val &= ~(0xf << (TIMERx<<2));
	divide_val |= (divider << (TIMERx<<2));
	*(volatile uint32_t*)(SYS_CTRL_BASE + 0x34) = divide_val;
}

/**
 * @brief  Calculate the frequency division and register count value based on the interrupt period.
 * @param   * @param timer_struct Configuration parameters
 * @param  period_us:  set timer interrupt period.   10 uS - 5592320 uS
 * @retval
 */
static void timer_div_calc(TIMER_InitTypeDef *timer_struct,uint32_t period_us)
{
	if(period_us > TIMER_MAX_PERIOD_US )
		return;
		
	ENUM_TIMER_CLK_DIVIDE divider = TIMER_CLK_DIVIDE_2;
	uint32_t divider_cnt = 0;
	uint32_t period_cnt = period_us*12;

	if(period_cnt > 0xffff)
	{
		divider_cnt = (period_cnt>>16);
		
		divider_cnt += (period_cnt % 0xFFFF)?1:0;
		
		for(uint8_t i=TIMER_CLK_DIVIDE_2;i< TIMER_CLK_DIVIDE_2048;i++)
		{
		  if(( 1<<(i+1) ) >= divider_cnt)
		  {
			divider = i+1;
			break;
		  }
		}
		period_cnt = period_cnt /(1<<(divider));
	}
	timer_struct->timer_clk_divide = divider;
	timer_struct->timer_loadcount = period_cnt;
}
/**
 * @brief  Initializes the Timer peripheral.
 * @param  timer_x: the timer_x channel @ref enum ENUM_TIMER
 * @param  period_us:  set timer interrupt period.range: 10 uS - 5592320 uS
 * @retval
 */
void timer_init(ENUM_TIMER timer_x,uint32_t period_us)
{
	IRQn_Type timer_irq = TIMER0_IRQn + timer_x ;
	TIMER_InitTypeDef timer_init_struct;

	NVIC_SetPriority(timer_irq, IRQ_HIGH_PRIORITY);
	NVIC_EnableIRQ(timer_irq);

	timer_param_default(&timer_init_struct);
	timer_init_struct.timer_mode = TIMER_MODE_USER_DEFINED;  //Timer mode
	timer_init_struct.timer_clk = TIMER_CLK_SEL_XTAL24M;    //Clock source,default is 24MHz
//  timer_init_struct.timer_clk_divide = TIMER_CLK_DIVIDE_2; //Clock divider,default is 2
//  timer_init_struct.timer_loadcount = 12*period_us;  
	timer_div_calc(&timer_init_struct,period_us);
	timer_init_struct.timer_loadcount2 = 0;
	timer_init_struct.timer_pwm_en = TIMER_PWM_DISABLE; 
	timer_disable(timer_x);
	timer_param_init(timer_x,&timer_init_struct);
	timer_int_enable(timer_x);
	timer_enable(timer_x);
}

/**
 * @brief Start timer with interrupt enabled
 * @param timer_x Timer instance (TIMER0-TIMER7)
 */
void timer_start(ENUM_TIMER timer_x)
{
	timer_int_enable(timer_x);
	timer_enable(timer_x);
}

/**
 * @brief Stop timer
 * @param timer_x Timer instance (TIMER0-TIMER7)
 */
void timer_stop(ENUM_TIMER timer_x)
{
	timer_disable(timer_x);
}

/**
 * @brief Set PWM output reverse mode
 * @param pwm_ch PWM channel
 * @param reverse_en Enable flag for reverse mode
 */
void pwm_reverse_set(ENUM_PWM pwm_ch,uint8_t reverse_en)
{
	uint32_t tmpreg_val = *(volatile uint32_t*) (TIMER_BASE + 0x08 + (pwm_ch)* 0x14); 
	if(reverse_en)
	{
		tmpreg_val |=0x1<<16;
	}
	else
	{
		tmpreg_val &= ~(1<<16);
	}
	*(volatile uint32_t*) (TIMER_BASE + 0x08 + (pwm_ch)* 0x14) = tmpreg_val;
}

/**
 * @brief Set PWM dead time
 * @param pwm_ch PWM channel
 * @param dead_time_cnt Dead time count value
 */
void pwm_dead_time_set(ENUM_PWM pwm_ch,uint16_t dead_time_cnt)
{
	uint32_t tmpreg_val = *(volatile uint32_t*) (TIMER_BASE + 0x08 + (pwm_ch)* 0x14); 
	uint16_t tmp_dead_time = 0;
	if(dead_time_cnt)
	{
		tmpreg_val |= 0x1<<5;
		if(dead_time_cnt <= 0x3f)
		{
			tmpreg_val |= 0x0<<14;
			tmpreg_val |= (dead_time_cnt&0x3F)<<8;
		}
		else if((dead_time_cnt>0x3f)&&(dead_time_cnt<=0xFF))
		{
			tmpreg_val |= 0x1<<14;
			tmp_dead_time = dead_time_cnt>>2;
			tmpreg_val |= (tmp_dead_time&0x3F)<<8;
		}
		else if((dead_time_cnt>0xff)&&(dead_time_cnt<=0x1FF))
		{
			tmpreg_val |= 0x2<<14;
			tmp_dead_time = dead_time_cnt>>3;
			tmpreg_val |= (tmp_dead_time&0x3F)<<8;
		}
		else
		{
			tmpreg_val |= 0x3<<14;
			tmp_dead_time = dead_time_cnt>>4;
			tmpreg_val |= (tmp_dead_time&0x3F)<<8;
		}
	}

  *(volatile uint32_t*) (TIMER_BASE + 0x08 + (pwm_ch)* 0x14) = tmpreg_val;
}


/*-------------------------------------
  PWM Operations
-------------------------------------*/

/**
 * @brief Initialize PWM channel
 * @param pwm_cfg PWM configuration parameters:
 *        - Channel selection
 *        - Cycle count
 *        - Duty cycle
 *        - Dead time
 *        - Reverse enable
 * 
 * @note Configures complementary PWM outputs with dead time
 */
void pwm_init(pwm_config_param_t *pwm_cfg)
{
	TIMER_InitTypeDef pwm_init_struct;
	pwm_init_struct.timer_mode = TIMER_MODE_USER_DEFINED;
	pwm_init_struct.timer_clk_divide = TIMER_CLK_DIVIDE_2;
	pwm_init_struct.timer_clk = TIMER_CLK_SEL_XTAL24M;
	pwm_init_struct.timer_loadcount = pwm_cfg->pwm_Cycle_CNT - pwm_cfg->pwm_Init_Duty_CNT -1;
	pwm_init_struct.timer_pwm_en = TIMER_PWM_ENABLE;
	pwm_init_struct.timer_loadcount2 = pwm_cfg->pwm_Init_Duty_CNT-1;
	pwm_init_struct.timer_pwm0n100_en = TIMER_PWM0N100_DISABLE;
	
	timer_disable(pwm_cfg->pwm_CH);
	timer_param_init(pwm_cfg->pwm_CH,&pwm_init_struct);
	
	if(PWM_COMP == pwm_cfg->pwm_Mode)
	{
		pwm_dead_time_set(pwm_cfg->pwm_CH,pwm_cfg->pwm_DT_CNT);
	}
	
	if(PWM_POS&pwm_cfg->pwm_Mode)
	{
		gpio_set_func(pwm_cfg->pwm_Pin,TIMER_PWM_FUNC);
	}
	if(PWM_NEG&pwm_cfg->pwm_Mode)
	{
		pwm_reverse_set(pwm_cfg->pwm_CH,1);
		gpio_set_func(pwm_cfg->pwm_N_Pin,TIMER_PWM_N_FUNC);
	}
	timer_int_disable(pwm_cfg->pwm_CH);
	timer_enable(pwm_cfg->pwm_CH);
}

/**
 * @brief Set PWM duty cycle
 * @param pwm_ch PWM channel (PWM0-PWM7)
 * @param duty_cnt Active high period in clock cycles
 * 
 * @note Maintains total period while updating active/inactive phases
 */
void pwm_duty_set(ENUM_PWM pwm_ch,uint16_t duty_cnt)
{
	uint16_t pwm_cycle = (*(volatile uint16_t*)(TIMER_BASE + 0x00 + (pwm_ch)* 0x14) )+(*(volatile uint16_t*)(TIMER_BASE + 0xB0 + (pwm_ch) * 0x4))+2;
	uint32_t tmpreg = *(volatile uint32_t*)(TIMER_BASE + 0x08 + (pwm_ch)* 0x14);
	
	uint16_t pwm_high_ouput_count = 0;
	uint16_t pwm_low_ouput_count = 0;
	if((duty_cnt == 0)||(duty_cnt == pwm_cycle))
	{
		tmpreg |= TIMER_PWM0N100_ENABLE;
		
		pwm_high_ouput_count = (duty_cnt)?(pwm_cycle -2):0;
		pwm_low_ouput_count =  (duty_cnt)?0:(pwm_cycle -2);
	}
	else 
	{
		tmpreg &= ~TIMER_PWM0N100_ENABLE;
		pwm_high_ouput_count = duty_cnt -1;
		pwm_low_ouput_count = pwm_cycle - duty_cnt -1;
	}
	*(volatile uint32_t*)(TIMER_BASE + 0x08 + (pwm_ch)* 0x14) = tmpreg;
	*(volatile uint16_t*)(TIMER_BASE + 0x00 + (pwm_ch)* 0x14) = pwm_low_ouput_count;
	*(volatile uint16_t*)(TIMER_BASE + 0xB0 + (pwm_ch) * 0x4) = pwm_high_ouput_count;
}

/**
 * @brief Set PWM Reverse duty cycle
 * @param pwm_ch PWM channel (PWM0-PWM7)
 * @param duty_cnt Active high period in clock cycles
 * 
 * @note Maintains total period while updating active/inactive phases
 */
void pwm_n_duty_set(ENUM_PWM pwm_ch,uint16_t duty_cnt)
{
	uint16_t pwm_cycle = (*(volatile uint16_t*)(TIMER_BASE + 0x00 + (pwm_ch)* 0x14) )+(*(volatile uint16_t*)(TIMER_BASE + 0xB0 + (pwm_ch) * 0x4))+2;

	uint32_t tmpreg = *(volatile uint32_t*)(TIMER_BASE + 0x08 + (pwm_ch)* 0x14);
	  
	uint16_t pwm_high_ouput_count = 0;
	uint16_t pwm_low_ouput_count = 0;
	if((duty_cnt == 0)||(duty_cnt == pwm_cycle))
	{
		tmpreg |= TIMER_PWM0N100_ENABLE;
		
		pwm_high_ouput_count = (duty_cnt)?(pwm_cycle -2):0;
		pwm_low_ouput_count =  (duty_cnt)?0:(pwm_cycle -2);
	}
	else 
	{
		tmpreg &= ~TIMER_PWM0N100_ENABLE;
		pwm_high_ouput_count = duty_cnt -1;
		pwm_low_ouput_count = pwm_cycle - duty_cnt -1;
	}
	*(volatile uint32_t*)(TIMER_BASE + 0x08 + (pwm_ch)* 0x14) = tmpreg;
	*(volatile uint16_t*)(TIMER_BASE + 0x00 + (pwm_ch)* 0x14) = pwm_high_ouput_count;
	*(volatile uint16_t*)(TIMER_BASE + 0xB0 + (pwm_ch) * 0x4) = pwm_low_ouput_count; 
}

/**
 * @brief Get PWM duty cycle
 * @param pwm_ch PWM channel (PWM0-PWM7)
 * @return Current duty cycle value
 */
uint16_t pwm_duty_get(ENUM_PWM pwm_ch)
{
	return (*(volatile uint16_t*)(TIMER_BASE + 0xB0 + (pwm_ch) * 0x4))+1;
}

/**
 * @brief Get PWM negative duty cycle
 * @param pwm_ch PWM channel (PWM0-PWM7)
 * @return Current negative duty cycle value
 */
uint16_t pwm_n_duty_get(ENUM_PWM pwm_ch)
{
	return (*(volatile uint16_t*)(TIMER_BASE + 0x00 + (pwm_ch) * 0x14))+1;
}