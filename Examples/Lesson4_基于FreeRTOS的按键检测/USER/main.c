#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "stdlib.h"
#include "oled.h" 
#include "FreeRTOS.h"
#include "task.h"

//�������ȼ�
#define START_TASK_PRIO		1
//�����ջ��С	
#define START_STK_SIZE 		128  
//������
TaskHandle_t StartTask_Handler;
//������
void start_task(void *pvParameters);

//�������ȼ�
#define LED0_TASK_PRIO		2
//�����ջ��С	
#define LED0_STK_SIZE 		50  
//������
TaskHandle_t LED0Task_Handler;
//������
void led0_task(void *pvParameters);

//�������ȼ�
#define OLEDRefreshGramTask_PRIO		3
//�����ջ��С	
#define OLEDRefreshGramTask_STK_SIZE 		256  
//������
TaskHandle_t OLEDRefreshGramTask_Handler;
//������
void OLEDRefreshGramTask(void *pvParameters);

int main(void)
{ 
 
	delay_init(168);		  //��ʼ����ʱ����
	LED_Init();		        //��ʼ��LED�˿�
	OLED_Init();			//��ʼ��OLED  
	OLED_Clear();
	OLED_ShowString(0,0,"MCUKeys with FreeRTOS",16);

	//������ʼ����
    xTaskCreate((TaskFunction_t )start_task,            //������
                (const char*    )"start_task",          //��������
                (uint16_t       )START_STK_SIZE,        //�����ջ��С
                (void*          )NULL,                  //���ݸ��������Ĳ���
                (UBaseType_t    )START_TASK_PRIO,       //�������ȼ�
                (TaskHandle_t*  )&StartTask_Handler);   //������              
    vTaskStartScheduler();          //�����������
                
    return 0;
}



//��ʼ����������
void start_task(void *pvParameters)
{
    taskENTER_CRITICAL();           //�����ٽ���
    //����LED0����
    xTaskCreate((TaskFunction_t )led0_task,     	
                (const char*    )"led0_task",   	
                (uint16_t       )LED0_STK_SIZE, 
                (void*          )NULL,				
                (UBaseType_t    )LED0_TASK_PRIO,	
                (TaskHandle_t*  )&LED0Task_Handler);   
    //����LED1����
    xTaskCreate((TaskFunction_t )OLEDRefreshGramTask,     
                (const char*    )"OLED_Refresh_Gram_task",   
                (uint16_t       )OLEDRefreshGramTask_STK_SIZE, 
                (void*          )NULL,
                (UBaseType_t    )OLEDRefreshGramTask_PRIO,
                (TaskHandle_t*  )&OLEDRefreshGramTask_Handler);        

    vTaskDelete(StartTask_Handler); //ɾ����ʼ����
    taskEXIT_CRITICAL();            //�˳��ٽ���
}

//LED0������ 
void led0_task(void *pvParameters)
{
    while(1)
    {
        LED3=~LED3;
        vTaskDelay(100);
    }
}   

//OLEDˢ������
void OLEDRefreshGramTask(void *pvParameters)
{

    static portTickType xLastWakeTime;  
    const portTickType xFrequency = pdMS_TO_TICKS(20);  //50Hzˢ����
   
    // ʹ�õ�ǰʱ���ʼ������xLastWakeTime ,ע�����vTaskDelay()������ͬ 
    xLastWakeTime = xTaskGetTickCount();
 
    while(1)
    {
        OLED_Refresh_Gram();//������ʾ
        vTaskDelayUntil(&xLastWakeTime, xFrequency);
    }
}


 



