#include "wwdg.h"


u8 WWDG_Counter = 0x6F;//��6λ��0x2F=101111(2)=47(10)





/** --------------------------------------------------------------------------
  * @brief  ���ڿ��Ź���ʼ��
  
  * @retval None
  
  * @param	None
			
  * @note	������ֵ�����ϴ���ֵ�ͱ�ˢ�� �� 0x40����Ϊ0x3Fʱ��λ
			�´���ֵʱ�̶��ģ�Ϊ0x40�����ϴ���ֵ�������ã�
			��ǰֵΪ0x40ʱ�����жϷ�����
			Ҫ�ڼ���ֵ����0x40=�´���<����ֵ<=�ϴ���<=0x7Fʱ����ι��ˢ�¼���ֵ��
			���ȼ�0-0
 -------------------------------------------------------------------------- **/
void WWDG_Configuration(void)
{
    NVIC_InitTypeDef NVIC_InitStructure;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_WWDG, ENABLE);

    //��ʱʱ��Ϊ4096*2^WWDG_Prescaler*(T[5:0]+1)/42M=4096*2^2*(0x2F + 1)/42M=18.72ms
    WWDG_SetPrescaler(WWDG_Prescaler_2);    											// ����Ԥ��Ƶϵ����
    WWDG_SetWindowValue(0x7F);              											// �����ϴ���ֵ��<=0x7F,��
    WWDG_Enable(WWDG_Counter);              											// ʹ�ܴ��ڿ��Ź�,ֵ��0x40-0x7F֮��

    NVIC_InitStructure.NVIC_IRQChannel 						= WWDG_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelCmd 					= ENABLE;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority 	= 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority 			= 0;
    NVIC_Init(&NVIC_InitStructure);

    WWDG_ClearFlag();
    WWDG_EnableIT();																	// ʹ���ж�
}

