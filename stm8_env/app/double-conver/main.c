

/* Includes ------------------------------------------------------------------*/
#include "stm8l15x.h"
#include "stm8l15x_clk.h"
#include "stm8l15x_gpio.h"
#include "stm8l15x_syscfg.h"
#include "stm8l15x_usart.h"
#include "stm8l15x_tim1.h"
#include "stm8l15x_itc.h"
#include "stm8l15x_dac.h"
// #include "stm8l_tuner.h"



/* Private function prototypes -----------------------------------------------*/
void Delay (uint16_t nCount);

static void CLK_Config(void);
static void USART_Config(void);
static void putchar(uint8_t);
static void TIM1_Config(void);
static void initialize(void);
static void enable_interrupts(void);
static void disable_interrupts(void);
static void DAC_Config(void);
static void GPIO_Config(void);

static void InitTunerSpi();
static void Write_Tuner2400_Reg(uint16_t,uint16_t);
static void Write_Tuner700_Reg(uint16_t,uint16_t);
static void SET_PIN_HIGH(GPIO_Pin_TypeDef);
static void SET_PIN_LOW(GPIO_Pin_TypeDef);


#define CLTMODE GPIO_Mode_Out_PP_Low_Slow
#define CNUMODE GPIO_Mode_Out_PP_High_Fast

#define GPIO_LINK_PORT GPIOB
#define GPIO_LINK_PIN GPIO_Pin_0

#define TUNER_SPI_PORT  (GPIOC)
//#define BUTTON (GPIOC)

//   tuner spi  programming
#define TUNER_SPI_PORT  (GPIOC)
#define CtrlData  (GPIO_Pin_1)
#define CtrlClk  (GPIO_Pin_2)
#define CtrlEn  (GPIO_Pin_3)
#define ButtonBit (GPIO_Pin_4)
#define CtrlEn2 (GPIO_Pin_0)

#define SET_CE_OUT()  {GPIO_Init(TUNER_SPI_PORT, (GPIO_Pin_TypeDef)CtrlEn, GPIO_Mode_Out_PP_Low_Fast );}//Output push-pull, low level, 10MHz 

#define SET_CE_OUT_2()  {GPIO_Init(TUNER_SPI_PORT, (GPIO_Pin_TypeDef)CtrlEn2, GPIO_Mode_Out_PP_Low_Fast );}//Output push-pull, low level, 10MHz    TUNER 2 

#define SET_SCL_OUT() {GPIO_Init(TUNER_SPI_PORT, (GPIO_Pin_TypeDef)CtrlClk, GPIO_Mode_Out_PP_Low_Fast );}

#define SET_SDA_OUT() {GPIO_Init(TUNER_SPI_PORT, (GPIO_Pin_TypeDef)CtrlData, GPIO_Mode_Out_PP_Low_Fast );}

//   
/* Private functions ---------------------------------------------------------*/
  

void main(void)
{


  uint16_t val1=6;
  uint32_t current_voltage_value = 1878;
  uint32_t last_freq_offset_voltage = current_voltage_value;
  int i=0;





  CLK_Config();
  USART_Config();
  TIM1_Config();
  DAC_Config();
  InitTunerSpi();


 /* GPIO PD0 (MASTER/SLAVE) */
  GPIO_Init(GPIOD, GPIO_Pin_0,  CLTMODE);
  //DAC_SetChannel1Data(DAC_Align_12b_R, cur·rent_voltage_value);




  if(GPIO_ReadInputDataBit(GPIO_LINK_PORT,GPIO_LINK_PIN))
  {
    putchar('Y');
    putchar('\n');
    putchar('\r');
  }
  else
  {
    putchar('N');
    putchar('\n');
    putchar('\r');
  }

   //-------- LO : dev 3    (reg1 =0x65 1683.34MHz)   (reg1=0x67 1716.67)  
  
  // UART1_SendStr("wr xx xx");


  for(i=0;i<10;i++)
  {
    // putchar('o');
    Delay(0xffff);
  }


  Write_Tuner2400_Reg((uint16_t)0x0000,(uint16_t)0x0094);                
  Delay(0xFFFF);
   
  Write_Tuner2400_Reg((uint16_t)0x0001,(uint16_t)0x0067); //431MHz 
  Delay(0xFFFF);

  Write_Tuner2400_Reg((uint16_t)0x0002,(uint16_t)0x0014);  
  Delay(0xFFFF);

  Write_Tuner2400_Reg((uint16_t)0x000b,(uint16_t)0x0001);                
  Delay(0xFFFF);
   
  Write_Tuner2400_Reg((uint16_t)0x000c,(uint16_t)0x0020); 
          

   //----------------------------------------//
   
   //-------- LO : 825MHz   
  Write_Tuner700_Reg((uint16_t)0x0000,(uint16_t)0x00b4);     
  Delay(0xFFFF);
   
  Write_Tuner700_Reg((uint16_t)0x0001,(uint16_t)0x0057);
          
  Delay(0xFFFF);
  Write_Tuner700_Reg((uint16_t)0x000b,(uint16_t)0x0001);     
  Delay(0xFFFF);
   
  Write_Tuner700_Reg((uint16_t)0x000c,(uint16_t)0x0020);





  // while(1)
  // {
  //   val1 = TIM1_GetCounter();
  //   putchar('-');
  //   putchar('>');
  //   // putchar(i+'0');
    
  //   putchar(((val1>>8)&0x07)+'0'); 
  //   putchar((val1&0x07) +'0');
 
  //   putchar('\n');
  //   putchar('\r');
  //   DAC_SetChannel1Data(DAC_Align_12b_R, i*30);

  //   Delay(0xffff);
  //   Delay(0xffff);
  //   Delay(0xffff);
  //   Delay(0xffff);
  //   Delay(0xffff);
  //   Delay(0xffff);
  //   Delay(0xffff);
  //   Delay(0xffff);
  //   Delay(0xffff);
  //   Delay(0xffff);
  //   Delay(0xffff);
  //   Delay(0xffff);
  //   i++;


  // }


  
}

/**
  * @brief  Inserts a delay time.
  * @param  nCount: specifies the delay time length.
  * @retval None
  */
static void GPIO_Config(void)
{
  GPIO_Init(GPIO_LINK_PORT, GPIO_LINK_PIN, GPIO_Mode_In_FL_IT);
}



static void DAC_Config(void)
{
  /* DAC Channel1 Config: 12bit right ----------------------------------------*/
  /* DAC deinitialize */
  DAC_DeInit();
  
  /* Fill DAC Init param DAC_Trigger_T4_TRGO and  DAC Channel1 Init */
  DAC_Init(DAC_Channel_1, DAC_Trigger_None, DAC_OutputBuffer_Disable);
  SYSCFG_RIDeInit();
  // RI->IOSR2 = RI_IOSR2_CH14E;
  //RI->IOSR1 = RI_IOSR1_CH13E;
   //RI->IOSR3 = RI_IOSR3_CH15E;
  //SYSCFG_RIIOSwitchConfig(RI_IOSwitch_13, ENABLE);
  //SYSCFG_RIIOSwitchConfig(RI_IOSwitch_14, ENABLE);
  SYSCFG_RIIOSwitchConfig(RI_IOSwitch_15, ENABLE);
  // RI->IOCMR1 = 0x10;


  /* Enable DAC Channel1 */
  DAC_Cmd(DAC_Channel_1, ENABLE);
  
  /* Enable DMA for DAC Channel1 */
  DAC_DMACmd(DAC_Channel_1, DISABLE);
}




static void initialize(void)
{
  // sys_clk_high = 0;
  // state = State_Calc_Falling_Edge_1;

  /* Set Find Discovery Win interrupt to the highest priority */
  ITC_SetSoftwarePriority(EXTI1_IRQn, ITC_PriorityLevel_1);

  // /* Set TIM3 generate pulse routine to the lowest priority */
  // ITC_SetSoftwarePriority(TIM2_UPD_OVF_TRG_BRK_IRQn, ITC_PriorityLevel_3);

  //  Set TIM3 generate pulse routine to the lowest priority 
  // ITC_SetSoftwarePriority(TIM3_CC_IRQn, ITC_PriorityLevel_2);

  // /* Set RF ATTENNA switch routine to the lowest priority */
  // ITC_SetSoftwarePriority(EXTI4_IRQn, ITC_PriorityLevel_3);
}


#define TIM1_Prescaler_1 0
static void TIM1_Config(void)
{

  // GPIO_Init(GPIOD, GPIO_Pin_3, GPIO_Mode_In_FL_No_IT);

  TIM1_TimeBaseInit(TIM1_Prescaler_1, TIM1_CounterMode_Up, 0xFFFF, 0);

  TIM1_ETRClockMode2Config(TIM1_ExtTRGPSC_OFF, TIM1_ExtTRGPolarity_NonInverted, 0);
  //Configures the TIM1 External clock Mode2.
  TIM1_SelectInputTrigger(TIM1_TRGSelection_ETRF);

  // Enable or Disable the Tim1 peripheral
  TIM1_Cmd(ENABLE);
}



static void CLK_Config(void)
{
  CLK_SYSCLKDivConfig(CLK_SYSCLKDiv_1);
  CLK_SYSCLKSourceSwitchCmd(ENABLE);
  CLK_SYSCLKSourceConfig(CLK_SYSCLKSource_HSI);

  while (CLK_GetSYSCLKSource() != CLK_SYSCLKSource_HSI) {}

  /* Enable TIM1 clock */
  CLK_PeripheralClockConfig(CLK_Peripheral_TIM1, ENABLE);

  /* Enable TIM2 clock */
  // CLK_PeripheralClockConfig(CLK_Peripheral_TIM2, ENABLE);

  /* Enable TIM3 clock */
  // CLK_PeripheralClockConfig(CLK_Peripheral_TIM3, ENABLE);

  /* Enable TIM4 CLK */
  // CLK_PeripheralClockConfig(CLK_Peripheral_TIM4, ENABLE);

  /* Enable USART clock */
  CLK_PeripheralClockConfig(CLK_Peripheral_USART1, ENABLE);

  /* Enable Clocks of DAC */
  CLK_PeripheralClockConfig(CLK_Peripheral_DAC, ENABLE);
  CLK_PeripheralClockConfig(CLK_Peripheral_COMP, ENABLE);
}


static void USART_Config(void)
{
  GPIO_Init(GPIOC, GPIO_Pin_5, GPIO_Mode_Out_PP_Low_Fast);
  GPIO_Init(GPIOC, GPIO_Pin_6, GPIO_Mode_In_FL_No_IT);
  SYSCFG_REMAPPinConfig(REMAP_Pin_USART1TxRxPortC, ENABLE);
  // SYSCFG_REMAPPinConfig(REMAP_Pin_USART1Clk, ENABLE);
  USART_DeInit(USART1);
  USART_Init(
    USART1,
    (uint32_t)9600,
    USART_WordLength_8b,
    USART_StopBits_1,
    USART_Parity_No,
    USART_Mode_Rx | USART_Mode_Tx
  );


}

static void putchar(uint8_t c)
{
  while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);
  USART_SendData8(USART1, c);
  while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);
}




void SET_PIN_HIGH(GPIO_Pin_TypeDef GPIO_PIN)
{
  GPIO_SetBits ( TUNER_SPI_PORT,GPIO_PIN );
}

void SET_PIN_LOW(GPIO_Pin_TypeDef GPIO_PIN)
{
  GPIO_ResetBits ( TUNER_SPI_PORT,GPIO_PIN );
}

void InitTunerSpi()
{
  SET_CE_OUT();
  SET_SCL_OUT();
  SET_SDA_OUT();
  SET_CE_OUT_2();

}


void Write_Tuner2400_Reg(uint16_t REG_ADD,uint16_t REG_DATA)
{
  uint16_t i;
  
  uint16_t BafferData=(uint16_t)0x0000;
  uint16_t BafferSetData=(uint16_t)0x0000;//SDA data 
  
  BafferData=(uint16_t)REG_ADD|(uint16_t)0x0000;
  BafferData=BafferData<<11;
  BafferSetData=BafferSetData|BafferData;
  
  BafferData=(uint16_t)REG_DATA|(uint16_t)0x0000;
  BafferData=BafferData<<3;
  BafferSetData=BafferSetData|BafferData;//bit15~bit3 is the spi sda 
  


  
  SET_PIN_HIGH(CtrlClk);      
    Delay(0x00FF);
    Delay(0x00FF);
    SET_PIN_LOW(CtrlClk);
  
  SET_PIN_HIGH(CtrlEn);//SET en high
  
  
  
  for( i=1;i<=15;i++)
  {
    //DATA CONTROL
    Delay(0x00FF);
    
    if(((uint16_t)BafferSetData&(uint16_t)0x8000)==(uint16_t)0x0000)
    {
      SET_PIN_LOW(CtrlData);
    }
    else
    {
      SET_PIN_HIGH(CtrlData);
    }
    Delay(0x00FF);
    
    
    //CLOCK CONTROL
  
    SET_PIN_HIGH(CtrlClk);      
    Delay(0x00FF);
    Delay(0x00FF);
    SET_PIN_LOW(CtrlClk);
    BafferSetData=BafferSetData<<1;
    if(i==13)
      SET_PIN_LOW(CtrlEn);//SET en LOW
  }
  
  
}


void Write_Tuner700_Reg(uint16_t REG_ADD,uint16_t REG_DATA)
{
  uint16_t i;
  
  uint16_t BafferData=(uint16_t)0x0000;
  uint16_t BafferSetData=(uint16_t)0x0000;//SDA data 
  
  BafferData=(uint16_t)REG_ADD|(uint16_t)0x0000;
  BafferData=BafferData<<11;
  BafferSetData=BafferSetData|BafferData;
  
  BafferData=(uint16_t)REG_DATA|(uint16_t)0x0000;
  BafferData=BafferData<<3;
  BafferSetData=BafferSetData|BafferData;//bit15~bit3 is the spi sda 
  

  
  SET_PIN_HIGH(CtrlClk);      
    Delay(0x00FF);
    Delay(0x00FF);
    SET_PIN_LOW(CtrlClk);
  
  SET_PIN_HIGH(CtrlEn2);//SET en high
  
  
  
  for( i=1;i<=15;i++)
  {
    //DATA CONTROL
    Delay(0x00FF);
    
    if(((uint16_t)BafferSetData&(uint16_t)0x8000)==(uint16_t)0x0000)
    {
      SET_PIN_LOW(CtrlData);
    }
    else
    {
      SET_PIN_HIGH(CtrlData);
    }
    Delay(0x00FF);
    
    
    //CLOCK CONTROL
  
    SET_PIN_HIGH(CtrlClk);      
    Delay(0x00FF);
    Delay(0x00FF);
    SET_PIN_LOW(CtrlClk);
    BafferSetData=BafferSetData<<1;
    if(i==13)
      SET_PIN_LOW(CtrlEn2);//SET en LOW
  }
  
  
}




void Delay(__IO uint16_t nCount)
{
  /* Decrement nCount value */
  while (nCount != 0)
  {
    nCount--;
  }
}

static void enable_interrupts(void)
{
  __asm__("rim\n");
}

static void disable_interrupts(void)
{
  __asm__("sim\n");
}


#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *   where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* Infinite loop */
  while (1)
  {}
}
#endif

