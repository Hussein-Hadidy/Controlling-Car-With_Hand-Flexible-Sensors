/*
 * main.c
 *
 *  Created on: ???/???/????
 *      Author: dell
 */
#define receive  0
#define Motor_On 1
#define send     0
#define stopSensorVal 105
#define maxSensorVal 130
#define minSensorVal 112
#include "Projects.h"


int main()
{

#if receive==1

	    M_ADC_Void_ADCInit();
		H_LCD_Void_LCDInit();
		M_UART_Void_UARTInit();
		H_LED_Void_LedInit(LED0);
		H_LED_Void_LedInit(LED1);
		H_LED_Void_LedInit(LED2);
		H_Buzzer_Void_BuzzerInit();
		H_Buzzer_Void_BuzzerSetOff();
		M_UART_Void_UARTSetBaudRate(9600);
		H_DCMotor_Void_DCMotorInit();
		H_DCMotor_Void_DCMotorSetDirection(CW);
		H_DCMotor_Void_DCMotorStart();
	    H_LCD_Void_LCDClear();
		u8 recieved;

			while(1)
			{
				//93-->150
				recieved = 0;
				recieved=M_UART_Void_UARTRecBlock();

				if (recieved<stopSensorVal)
				{
					H_DCMotor_Void_DCMotorSetSpeed(0);
					H_DCMotor_Void_DCMotorStop();
					H_LED_Void_LedSetOff(LED0);
					H_LED_Void_LedSetOff(LED0);
					H_LED_Void_LedSetOff(LED0);
				}
				else if (recieved<minSensorVal)
				{
					H_LED_Void_LedSetOff(LED1);
					H_LED_Void_LedSetOff(LED2);
					H_DCMotor_Void_DCMotorSetSpeed(50);
					H_LED_Void_LedSetOn(LED0);
				}

				else if(recieved>=minSensorVal && recieved<maxSensorVal)
				{
					H_LED_Void_LedSetOff(LED0);
					H_LED_Void_LedSetOff(LED2);
					H_DCMotor_Void_DCMotorSetSpeed(75);
					H_LED_Void_LedSetOn(LED1);
				}
				else
				{
					H_LED_Void_LedSetOff(LED0);
					H_LED_Void_LedSetOff(LED1);
					H_DCMotor_Void_DCMotorSetSpeed(100);
					H_LED_Void_LedSetOn(LED2);
				}
			//H_LCD_Void_LCDWriteNumber(recieved);
			//_delay_ms(200);
			 //H_LCD_Void_LCDClear();
			//_delay_ms(200);
			}


#endif



#if Motor_On==1
	H_LCD_Void_LCDInit();
	H_LED_Void_LedInit(LED0);
	H_LED_Void_LedInit(LED1);
	H_LED_Void_LedInit(LED2);
	H_DCMotor_Void_DCMotorInit();
	H_DCMotor_Void_DCMotorSetDirection(CW);
	H_DCMotor_Void_DCMotorStart();
	while(1)
	{

		H_LED_Void_LedSetOn(LED0);
		H_DCMotor_Void_DCMotorSetSpeed(80);
		_delay_ms(3000);
		H_LED_Void_LedSetOff(LED0);
		H_LED_Void_LedSetOn(LED1);
		H_DCMotor_Void_DCMotorSetSpeed(90);
		_delay_ms(5000);
		H_LED_Void_LedSetOff(LED1);
		H_LED_Void_LedSetOn(LED2);
		H_DCMotor_Void_DCMotorSetSpeed(100);
		_delay_ms(5000);
		H_LED_Void_LedSetOff(LED2);
	}

#endif

#if send==1
	H_Flexible_SensorInit();
	H_LCD_Void_LCDInit();
	M_UART_Void_UARTInit();
	H_LED_Void_LedInit(LED0);
	H_LED_Void_LedInit(LED1);
	H_LED_Void_LedInit(LED2);
	H_Buzzer_Void_BuzzerInit();
	H_Buzzer_Void_BuzzerSetOff();
	M_UART_Void_UARTSetBaudRate(9600);
//	M_Timer_Void_PWMInit(TIMER0_CHANNEL);
//	M_Timer_Void_TimerStart(TIMER0_CHANNEL);

while(1)
{
	//u8_Read_Flexible_Sensor(SENSOR1_READING)
	u32 sum = 0;
		u32 mean = 0;
		int i = 0;
		for(i =0;i<10;i++)
		{
			sum += (u32)u8_Read_Flexible_Sensor(SENSOR1_READING);
		}
		mean = sum/10;
	M_UART_Void_UARTSend(mean);
   _delay_ms(200);
}

#endif

}
//End transmit
