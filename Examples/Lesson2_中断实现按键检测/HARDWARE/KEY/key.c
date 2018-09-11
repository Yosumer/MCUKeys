#include "key.h"
#include "sys.h"
#include "delay.h"
#include "exti.h"

extern eKEY_STATUS key_value = KEY_NONE;


/***********************************************************************
* �������ƣ� key_init
* �������ܣ� ��ʼ��������IO������
* ���������  ��	 
* �� �� ֵ��   ��
* ����˵���� ��
****************************************************************************/
void key_init(void )
{
  GPIO_InitTypeDef  GPIO_InitStructure;

  RCC_AHB1PeriphClockCmd(KEY1_RCC, ENABLE);//ʹ��GPIOʱ��

  GPIO_InitStructure.GPIO_Pin = KEY1_Pin;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;  //����
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����
  GPIO_Init(KEY1_GPIO, &GPIO_InitStructure);//��ʼ��GPIO

   EXTIX3_Init(); //�ⲿ�жϳ�ʼ��
    
}

/***********************************************************************
* �������ƣ� get_key1_value
* �������ܣ� ��ȡ������״̬
* ���������  ��	 
* �� �� ֵ��   �������·���1 ���򷵻�0
* ����˵���� ���ǹ涨���������·���PRESS ���򷵻�LIFT Ҫע��ʵ�ʵ�Ӳ���ӷ�����ҪʱҪ��һ���߼�ת�������籾����������һ���߼�ת��
****************************************************************************/
static uint8_t get_key1_value(void)
{
    uint8_t res  = 0;
    res = GPIO_ReadInputDataBit(KEY1_GPIO, KEY1_Pin);
    if(res == 0)
    {
        return PRESS;
    }
    else
    {
        return LIFT;
    }
}

/***********************************************************************
* �������ƣ� key_init
* �������ܣ� ��ʼ��������IO������
* ���������  ��	 
* �� �� ֵ��   ��
* ����˵���� ��
****************************************************************************/
uint8_t key_scan(void)
{

    uint8_t res = 0;
    res = get_key1_value();
    if(res == PRESS)
    {
        delay_ms(10);  //��ʱ�˲�
        res = get_key1_value();
        if(res == PRESS)
        {
            return KEY1_DOWN;
        }
    }
    return KEY_NONE;
}



//�ⲿ�ж�3�������
void EXTI3_IRQHandler(void)
{
     key_value = key_scan();
    
	 EXTI_ClearITPendingBit(EXTI_Line3);  //���LINE3�ϵ��жϱ�־λ  
}







