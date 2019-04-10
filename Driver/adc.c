#include "stm32f10x.h"
#include "adc.h"
__IO uint16_t ADC_ConvertedValue;

void ADC1_Init(void)
{
	ADC1_GPIO_Config();
	ADC1_Mode_Config();
}

static void ADC1_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_Init(GPIOB, &GPIO_InitStructure);	
}

static void ADC1_Mode_Config(void)
{
	ADC_InitTypeDef ADC_InitStructure;
	DMA_InitTypeDef DMA_InitStructure;
	
	/* DMAͨ������*/
  DMA_DeInit(DMA1_Channel1);
	DMA_InitStructure.DMA_PeripheralBaseAddr = ADC1_DR_Address; /*ADC ��ַ*/
	DMA_InitStructure.DMA_MemoryBaseAddr = (u32)&ADC_ConvertedValue; /*�ڴ��ַ*/
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC; /*����Ϊ����Դ*/
	DMA_InitStructure.DMA_BufferSize = 1;
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable; /*�ڴ��ַ�̶�*/
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Disable; /*�ڴ��ַ�̶�*/
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord; /*����*/
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular; /*ѭ������*/
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
	DMA_Init(DMA1_Channel1,&DMA_InitStructure);
	
	DMA_Cmd(DMA1_Channel1,ENABLE);
	
	/* ADCͨ������*/
	ADC_DeInit(ADC1); 
	ADC_InitStructure. ADC_Mode  = ADC_Mode_Independent;//ADC����ģʽ��ѡ�񣺶���ģʽ��˫ģʽ��Ӧ�Ĵ����ǣ�ADC_CR1��DUALMODλ�� 
	ADC_InitStructure. ADC_ScanConvMode = DISABLE; //�Ƿ�ѡ��ɨ�裬��ͨ��ѡ��DISABLE����ͨ��ѡ��ENABLE����Ӧ�Ĵ�����ADC_CR1��SCANλ 
	ADC_InitStructure. ADC_ContinuousConvMode = ENABLE; //�����������Զ�����ת�����ǵ���ת������Ӧ�Ĵ�����ADC_CR2��CONλ�� 
	ADC_InitStructure. ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;//�ⲿ����ѡ��,һ��ѡ�����������Ҳ���Ը�����Ŀ�������ô�����Դ����Ӧ�ļĴ�����ADC_CR2�е�17-20λ��EXTTRIG EXTSEL[2��0]; 
	ADC_InitStructure. ADC_DataAlign = ADC_DataAlign_Right;//���ݶ����ʽ������뻹���Ҷ��룬һ�����Ҷ��룬�Ĵ�����ADC_CR2�е�11λ��ALIGN�� 
	ADC_InitStructure. ADC_NbrOfChannel = 1; //ADת��ͨ������Ŀ��������Ҫ����ͨ������Ӧ�Ĵ�����ADC_CR1�е�AWDCH[4��0]; 
	ADC_Init(ADC1,&ADC_InitStructure); 
	RCC_ADCCLKConfig(RCC_PCLK2_Div8);
	
	ADC_RegularChannelConfig(ADC1,ADC_Channel_8, 1, ADC_SampleTime_55Cycles5);
	
	ADC_DMACmd(ADC1,ENABLE);//ʹ��ADC��DMA���� 
	ADC_Cmd(ADC1,ENABLE);//����ADC������ʼת�� 
	
	ADC_ResetCalibration(ADC1);//��ʼ��ADCУ׼�Ĵ��� 
	while(ADC_GetResetCalibrationStatus(ADC1));//�ȴ�У׼��ʼ����� 
	ADC_StartCalibration(ADC1);//ADC��ʼУ׼ 
	while(ADC_GetCalibrationStatus(ADC1));//�ȴ�У׼���
	
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);
}
