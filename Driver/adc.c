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
	
	/* DMA通道设置*/
  DMA_DeInit(DMA1_Channel1);
	DMA_InitStructure.DMA_PeripheralBaseAddr = ADC1_DR_Address; /*ADC 地址*/
	DMA_InitStructure.DMA_MemoryBaseAddr = (u32)&ADC_ConvertedValue; /*内存地址*/
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC; /*外设为数据源*/
	DMA_InitStructure.DMA_BufferSize = 1;
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable; /*内存地址固定*/
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Disable; /*内存地址固定*/
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord; /*半字*/
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular; /*循环传输*/
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
	DMA_Init(DMA1_Channel1,&DMA_InitStructure);
	
	DMA_Cmd(DMA1_Channel1,ENABLE);
	
	/* ADC通道设置*/
	ADC_DeInit(ADC1); 
	ADC_InitStructure. ADC_Mode  = ADC_Mode_Independent;//ADC工作模式的选择：独立模式，双模式对应寄存器是：ADC_CR1：DUALMOD位。 
	ADC_InitStructure. ADC_ScanConvMode = DISABLE; //是否选用扫描，单通道选择DISABLE，多通道选择ENABLE，对应寄存器是ADC_CR1：SCAN位 
	ADC_InitStructure. ADC_ContinuousConvMode = ENABLE; //配置是启动自动连续转换还是单次转换。对应寄存器是ADC_CR2：CON位。 
	ADC_InitStructure. ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;//外部触发选择,一般选择软件触发，也可以根据项目需求配置触发来源。对应的寄存器是ADC_CR2中的17-20位，EXTTRIG EXTSEL[2：0]; 
	ADC_InitStructure. ADC_DataAlign = ADC_DataAlign_Right;//数据对齐格式，左对齐还是右对齐，一般是右对齐，寄存器是ADC_CR2中的11位，ALIGN； 
	ADC_InitStructure. ADC_NbrOfChannel = 1; //AD转换通道的数目，看你需要几个通道，对应寄存器是ADC_CR1中的AWDCH[4：0]; 
	ADC_Init(ADC1,&ADC_InitStructure); 
	RCC_ADCCLKConfig(RCC_PCLK2_Div8);
	
	ADC_RegularChannelConfig(ADC1,ADC_Channel_8, 1, ADC_SampleTime_55Cycles5);
	
	ADC_DMACmd(ADC1,ENABLE);//使能ADC的DMA请求； 
	ADC_Cmd(ADC1,ENABLE);//开启ADC，并开始转换 
	
	ADC_ResetCalibration(ADC1);//初始化ADC校准寄存器 
	while(ADC_GetResetCalibrationStatus(ADC1));//等待校准初始化完成 
	ADC_StartCalibration(ADC1);//ADC开始校准 
	while(ADC_GetCalibrationStatus(ADC1));//等待校准完成
	
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);
}
