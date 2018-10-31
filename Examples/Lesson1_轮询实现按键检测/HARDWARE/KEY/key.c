/*----------------------------------------------------------------------------
 * Copyright (c) <2016-2018>, <xupenghu@outlook.com>
 * All rights reserved.
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 * 1. Redistributions of source code must retain the above copyright notice, this list of
 * conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice, this list
 * of conditions and the following disclaimer in the documentation and/or other materials
 * provided with the distribution.
 * 3. Neither the name of the copyright holder nor the names of its contributors may be used
 * to endorse or promote products derived from this software without specific prior written
 * permission.
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *---------------------------------------------------------------------------*/




#include "key.h"
#include "sys.h"
#include "delay.h"

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
        if(res == PRESS)
        {
            return KEY1_DOWN;
        }
    }
    return KEY_NONE;
}











