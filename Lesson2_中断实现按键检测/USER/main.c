#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "key.h"
#include "stdlib.h"
#include "oled.h" 

int main(void)
{  
     eKEY_STATUS key_status = KEY_NONE;
	delay_init(168);		  //��ʼ����ʱ����
	LED_Init();		        //��ʼ��LED�˿�
    key_init();                 //��ʼ������
	OLED_Init();			//��ʼ��OLED  
	OLED_Clear();
	OLED_ShowString(0,0,"   KEY TEST",16);
    while(1)
    {
        key_status = key_value;
        if(key_status != KEY_NONE)
        {
            switch(key_status)
            {
                case KEY1_DOWN:
                {
                    OLED_ShowString(0,16,"KEY1 DOWN",16);
                    delay_ms(200);
                    key_value = KEY_NONE;   //���
                }break;
                default:
                {
                    
                }break;
            }
        }
        OLED_ShowString(0,16,"                   ",16);
     }
}


	

 



