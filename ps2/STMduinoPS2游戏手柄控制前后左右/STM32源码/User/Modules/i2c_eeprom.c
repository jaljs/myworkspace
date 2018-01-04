/*
��Ȩ������
������С�����ͿƼ���СR�Ƽ������£�WIFI���������������˴��⹤���Ұ�Ȩ����www.wifi-robots.com
�����������޸ı����򣬲�Ӧ���������з�������С�������˼��������Ӳ�Ʒ�ϣ����ǽ�ֹ������ҵĲ����
СR�Ƽ����������������Ȩ��Ȩ����2016-4-1
BY WIFI���������������˴��⹤����
*/

#include "i2c_eeprom.h"

enum ENUM_I2C_EEPROM_REPLY
{
I2C_EEPROM_NACK=0
,I2C_EEPROM_ACK=1
};

enum ENUM_I2C_EEPROM_BUS_STATE
{
I2C_EEPROM_READY=0
,I2C_EEPROM_BUS_BUSY=1
,I2C_EEPROM_BUS_ERROR=2
};

void I2C_EEPROM_Init(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure; 
  
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
  
  // Configure I2C1 pins: SCL and SDA 
  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_6 | GPIO_Pin_7;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;  
  GPIO_Init(GPIOB, &GPIO_InitStructure);
  
}

/*
 * ��������delay_i2c
 * ����  ����ʱ
 * ����  ����
 * ���  ����
 * ����  �������е���
 */
void delay_i2c(void)
{ 
   u8 i=10; //i=10��ʱ1.5us//��������Ż��ٶ� ����������͵�5����д��
   while(i--); 
   
}

/*
 * ��������DelayMs
 * ����  ����ʱms
 * ����  ����
 * ���  ����
 * ����  �������е���
 */
void DelayMs(uint16_t ms)
{
 u8 i;
 u16 j;
 for(i = ms; i > 0; i--)
 {
  for(j = 11998; j > 0; j--); // ( (6*j+9)*i+15 ) / 72000000 
  
 }
}

/*
 * ��������I2C_EEPROM_Start
 * ����  ����ʼ�ź�
 * ����  ����
 * ���  ����
 * ����  �������е���
 */
u8 I2C_EEPROM_Start(void)
{
   SDAH;
   SCLH;
   delay_i2c();
   if(!SDAread)return I2C_EEPROM_BUS_BUSY; //SDA��Ϊ�͵�ƽ������æ,�˳�
   SDAL;
   delay_i2c();
   if(SDAread) return I2C_EEPROM_BUS_ERROR; //SDA��Ϊ�ߵ�ƽ�����߳���,�˳�
   SCLL;
   delay_i2c();
   return I2C_EEPROM_READY;
}

/*
 * ��������I2C_EEPROM_Stop
 * ����  ��ֹͣ�ź�
 * ����  ����
 * ���  ����
 * ����  �������е���
 */
void I2C_EEPROM_Stop(void)
{
   SDAL;
   SCLL;
   delay_i2c();
   SCLH;
   delay_i2c();
   SDAH;
   delay_i2c();
}

void I2C_EEPROM_Ack(void)
{ 
   SCLL;
   delay_i2c();
   SDAL;
   delay_i2c();
   SCLH;
   delay_i2c();
   SCLL;
   delay_i2c();
}

void I2C_EEPROM_NoAck(void)
{ 
   SCLL;
   delay_i2c();
   SDAH;
   delay_i2c();
   SCLH;
   delay_i2c();
   SCLL;
   delay_i2c();
}

/*
 * ��������I2C_EEPROM_WaitAck
 * ����  ���ȴ�Ӧ���ź�
 * ����  ����
 * ���  ����
 * ����  �������е���
 */
uint8_t I2C_EEPROM_WaitAck(void)   //����Ϊ:=1��ACK,=0��ACK
{
 SCLL;
 delay_i2c();
 SDAH;   
 delay_i2c();
 SCLH;
 delay_i2c();
 if(SDAread)
 {
          SCLL;
          return 0;
 }
 SCLL;
 return 1;
}

/*
 * ��������I2C_EEPROM_SendByte
 * ����  ����������
 * ����  ����
 * ���  ����
 * ����  ���ⲿ����
 */
void I2C_EEPROM_SendByte(u8 SendByte) //���ݴӸ�λ����λ//
{
    u8 i=8;
    while(i--)
    {
        SCLL;
        delay_i2c();
        if(SendByte&0x80)
          SDAH;  
        else 
        SDAL;   
        SendByte<<=1;
        delay_i2c();
        SCLH;
        delay_i2c();
    }
    SCLL;
}

/*
 * ��������I2C_EEPROM_ReceiveByte
 * ����  ����������
 * ����  ����
 * ���  ����
 * ����  ���ⲿ����
 */
u8 I2C_EEPROM_ReceiveByte(void)  //���ݴӸ�λ����λ//
{ 
    u8 i=8;
    u8 ReceiveByte=0;
    SDAH;    
    while(i--)
    {
      ReceiveByte <<= 1;      
      SCLL;
      delay_i2c();
      SCLH;
      delay_i2c(); 
      if(SDAread)
      {
        ReceiveByte |= 0x01;
      }
    }
    SCLL;
    return ReceiveByte;
}

/*
 * ��������I2C_EEPROM_WriteByte
 * ����  ��д��һ���ֽ�
 * ����  ��д��1�ֽ�����           SendByte����д������    WriteAddress����д���ַ
 * ���  ��3д��ɹ���0д������ַ����1����æ��2����
 * ����  ���ⲿ����
 */ 
u8 I2C_EEPROM_WriteByte(u8 SendByte, u8 WriteAddress)
{  
    u8 i;
   // u16 j;
 i = I2C_EEPROM_Start();
    if(i)
   return i;
      
    I2C_EEPROM_SendByte( ADDR_24CXX & 0xFE);//д������ַ  д�룺��ַ���λ��0����ȡ����ַ���λ��1
    
 if(!I2C_EEPROM_WaitAck())
 {
   I2C_EEPROM_Stop(); 
   return 0;
 }
 
    I2C_EEPROM_SendByte(WriteAddress);   //������ʼ��ַ      
    I2C_EEPROM_WaitAck(); 
    I2C_EEPROM_SendByte(SendByte);           //д����
    I2C_EEPROM_WaitAck();   
    I2C_EEPROM_Stop(); 
 //ע�⣺��Ϊ����Ҫ�ȴ�EEPROMPROMд�꣬���Բ��ò�ѯ����ʱ��ʽ(10ms)
    DelayMs(20); //д����ʱ 12ms  д���ڴ���10ms����
    return 3;
}
 
/*
 * ��������I2C_EEPROM_WriteByte
 * ����  ������һ���ֽ�
 * ����  ���ֽڵ�ַ
 * ���  ��0д������ַ����1����æ��2����,
 * ����  ���ⲿ����
 */ 
u8 I2C_EEPROM_ReadByte( u8 ReadAddress)
{  
    u8 i,temp;
    i = I2C_EEPROM_Start();
    if(i)
   return i;
     
    I2C_EEPROM_SendByte((ADDR_24CXX & 0xFE));//д������ַ����ִ��һ��αд���� 
    if(!I2C_EEPROM_WaitAck())
 {
   I2C_EEPROM_Stop(); 
   return 0;
 }
    I2C_EEPROM_SendByte(ReadAddress);   //������ʼ��ַ      
    I2C_EEPROM_WaitAck();
    I2C_EEPROM_Start();
    I2C_EEPROM_SendByte((ADDR_24CXX & 0xFE)|0x01);    //��������ַ    д�룺��ַ���λ��0����ȡ����ַ���λ��1
    I2C_EEPROM_WaitAck();
   
    //*pDat = I2C_EEPROM_ReceiveByte();
    temp = I2C_EEPROM_ReceiveByte();
    
    I2C_EEPROM_NoAck();
     
    I2C_EEPROM_Stop();
    return temp;//���ص������0��1��2������������ͬ�ˣ��ٿ���һ��
}
/***************************************************************************
��24c256��д����ֽ�
psrc_data��ָ��Ҫд�����������ָ��
adr��24c256��Ҫд�����ݵ��׵�ַ
nbyte��д����ֽ���
����ֵ:  0��ִ����ϣ�1��ִ�г��ִ���
�β��У�C02ֻ��һ����ַadr��C256���и�λ��ַhadr�͵�λ��ַladr
***************************************************************************/
u8 I2C_EEPROM_BufferWrite(u8 *psrc_data,u8 adr,u8 nbyte)
{
   u8 i;
  
 for(;nbyte!=0;nbyte--)
 {
  i = I2C_EEPROM_Start();
        if(i)
     return i;
         
        I2C_EEPROM_SendByte( ADDR_24CXX & 0xFE);//д������ַ 
    
     if(!I2C_EEPROM_WaitAck())
     {
       I2C_EEPROM_Stop(); 
       return 0;
     }
 
        I2C_EEPROM_SendByte(adr);   //������ʼ��ַ      
        I2C_EEPROM_WaitAck(); 
        I2C_EEPROM_SendByte(*psrc_data);           //д����
        I2C_EEPROM_WaitAck();   
        psrc_data++;    //ָ���д���ݵ�ָ���1
  adr++;    //��24C08�Ĳ�����ַ��1 
        I2C_EEPROM_Stop(); 
  //ע�⣺��Ϊ����Ҫ�ȴ�EEPROMPROMд�꣬���Բ��ò�ѯ����ʱ��ʽ(10ms)
        DelayMs(12); //д����ʱ 12ms  д���ڴ���10ms����
        
 }
 return 0;
}

/***************************************************************************
��24c02������ֽ�
pdin_data��ָ��Ҫ����������ݵ������ָ��
adr��24c02��Ҫ�������ݵ��׵�ַ
nbyte���������ֽ���
����ֵ:  0��ִ����ϣ�1��ִ�г��ִ���
***************************************************************************/
u8 I2C_EEPROM_BufferRead(u8 *pdin_data,u8 adr,u8 nbyte)
{
   u8 i;
    i = I2C_EEPROM_Start();
    if(i)
   return i;
     
    I2C_EEPROM_SendByte((ADDR_24CXX & 0xFE));//д������ַ����ִ��һ��αд���� 
    if(!I2C_EEPROM_WaitAck())
 {
   I2C_EEPROM_Stop(); 
   return 0;
 }
 I2C_EEPROM_SendByte(adr);   //������ʼ��ַ      
    I2C_EEPROM_WaitAck();
    I2C_EEPROM_Start();
    I2C_EEPROM_SendByte((ADDR_24CXX & 0xFE)|0x01);    //��������ַ    д�룺��ַ���λ��0����ȡ����ַ���λ��1
    I2C_EEPROM_WaitAck();
 while(nbyte!=1)                 //����ǰ(nbyte-1)���ֽ�
 {
  *pdin_data = I2C_EEPROM_ReceiveByte(); //ѭ����24C02�ж����ݣ�����pdin_data��ָ�Ĵ洢����
  I2C_EEPROM_Ack();   //IICӦ��
  pdin_data++;  //ָ��洢�������ݵĴ洢��ָ���1
  nbyte--;  //ʣ��Ҫ������ֽڼ�1
 };
 *pdin_data = I2C_EEPROM_ReceiveByte();  //�������һ���ֽ�
 I2C_EEPROM_NoAck();      //IIC��Ӧ�����
     
    I2C_EEPROM_Stop();   
 
 return 0;
}

