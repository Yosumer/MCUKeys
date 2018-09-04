#ifndef _KEY__H
#define _KEY__H

#include "sys.h"

//KEY1 ����
#define KEY1_RCC    RCC_AHB1Periph_GPIOB
#define KEY1_GPIO   GPIOB
#define KEY1_Pin      GPIO_Pin_3


#define LIFT    (0)            /* ����̧�� */
#define PRESS   (!LIFT) /* �������� */

typedef enum
{
    KEY_NONE,
    
    KEY1_DOWN,
    KEY1_UP,
    
    KEY2_DOWN,
    KEY2_UP
}eKEY_STATUS;


extern eKEY_STATUS key_value;




void key_init(void);

/***********************************************************************
* �������ƣ� key_init
* �������ܣ� ��ʼ��������IO������
* ���������  ��	 
* �� �� ֵ��   ��
* ����˵���� ��
****************************************************************************/
uint8_t key_scan(void);

#endif


