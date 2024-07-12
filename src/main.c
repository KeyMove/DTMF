#include "mcuhead.h"
#include "ascii.h"

#define sysclk 24000000
#define uartbps 460800
#define uartcfg 0x0000142D

#define TIMTICK 575
#define TIMHALF 287



#define range(v,max,min) 	if(v>max)v=max;\
							else if(v<min)v=min;

const u32 initdata[]={
	0x40021004,0x00FF90FF,//RCC_ICSCR
	0x40021034,0x23,
	0x40021038,0x00000301,
	0x4002103C,0x08000002,
	0x40021040,0x00105801,
	
	//GPIOA GPIOB
	0x50000000,0xEBFFFFC5,//GPIOA_MODER
	0x50001400,0xFFFFFCFA,//GPIOF_MODER
	0x50001420,0x0088,//GPIOF_AFRL
	0x5000000C,0x24000010,//GPIOA_PUPDR

	
	//TIM3
	//0x40000428,0,//psc
	0x4000042C,sysclk/4000-1,//arr
	
	0x40000418,0x6868,
	0x4000041C,0x6868,
	0x40000420,0x1111,
	
	0x40000400,0xa0,//0xa1
	
	0x40000404,0x00000020,
	
	
	//adc
	0x40012408,0x00000010,
	0x40012414,0x02,
	0x40012428,0x00000080,//CHSELR
	0x4001240C,0x000014C3,//
	
	0x40013808,sysclk/uartbps,
	0x4001380c,0x0000202C,
};

void initmem(){
	u8 i;
	for(i=0;i<sizeof(initdata)/4;i++){
		*((vu32*)initdata[i])=initdata[i+1];
		i++;
	}
}

void SystemInit(){
	
}

const s8 ra[]={
				   0,  114,  100,  -26, -123,  -81,   51,  126,   59,  -74, -125,
        -35,   94,  117,    9, -109, -105,   17,  120,   88,  -42, -126,
        -67,   66,  126,   44,  -87, -121,  -18,  104,  110,   -7, -117,
        -95,   33,  124,   75,  -58, -126,  -52,   80,  123,   27,  -99,
       -114,   -1,  113,  101,  -24, -122,    0,  121,   73,  -76, -119,
          4,  122,   69,  -80, -117,    9,  123,   65,  -84, -116,   13,
        124,   61,  -87, -114,   18,  125,   57,  -90, -112,   23,  126,
         52,  -94, -109,   27,  126,   48,  -97, -107,   32,  126,   44,
       -100, -104,   36,  126,   39, -102, -102,   41,  126,   35, -105,
        -99,    0,  125,   43, -110,  -80,   82,  109,  -44, -124,    1,
        125,   41, -111,  -79,   83,  108,  -46, -124,    3,  125,   39,
       -112,  -77,   85,  107,  -48, -123,    5,  125,   37, -113,  -76,
         86,  106,  -50, -123,    7,  126,   35, -114,  -74,   88,  105,
        -52, -123,    9,  126,   33, -114,  -73,    0,  126,    6, -126,
        -12,  126,   18, -125,  -24,  123,   30, -122,  -36,  120,   42,
       -118,  -48,  116,   54, -113,  -59,  110,   65, -107,  -70,  103,
         75, -100,  -80,   96,   85,  -91,  -89,   87,   94,  -82,  -98,
         78,  102,  -73, -105,   67,  108,  -62, -112,   57,  114,  -51,
       -117,   45,    0,  116,  -93,  -40,  126,  -62,  -76,  123,  -23,
       -104,  108,   16, -121,   81,   55, -126,   46,   89, -118,    6,
        113,  -98,  -33,  125,  -68,  -70,  125,  -30, -100,  111,    9,
       -119,   86,   49, -126,   53,   83, -121,   13,  109, -102,  -26,
        124,  -73,  -64,  126,  -37,  -95,  114,    2,    0,  105, -117,
         24,   89, -124,   48,   70, -127,   70,   48, -124,   89,   24,
       -117,  105,    0, -105,  117,  -24,  -89,  124,  -48,  -70,  127,
        -70,  -48,  124,  -89,  -24,  117, -105,    0,  105, -117,   24,
         89, -124,   48,   70, -127,   70,   48, -124,   89,   24, -117,
        105,    0, -105,    0,   83, -125,  106,  -35,  -53,  115, -121,
         68,   18,  -96,  126,  -95,   16,   69, -122,  114,  -51,  -37,
        107, -125,   81,    1,  -84,  125, -105,   33,   54, -116,  121,
        -66,  -20,   97, -126,   93,  -14,  -71,  122, -114,   49,   39,
       -108,  125,  -80,   -3,   86, -126,  104,  -31,  -56,    0,   69,
       -116,  125,  -94,   32,   39,  -98,  126, -112,   62,    7,  -75,
        118, -124,   89,  -25,  -46,  103, -126,  109,  -56,  -14,   81,
       -121,  122,  -83,   18,   53, -107,  126, -105,   49,   22,  -86,
        123, -120,   77,  -10,  -59,  111, -126,  101,  -42,  -29,   91,
       -124,  117,  -72,    3
};

const s8 rb[]={
			    127,   55,  -78, -124,  -30,   97,  116,    4, -112, -102,   21,
        121,   85,  -47, -126,  -63,   70,  125,   39,  -90, -119,  -13,
        107,  108,  -12, -119,  -91,   38,  125,   71,  -62, -126,  -48,
         84,  122,   23, -102, -112,    3,  115,   98,  -29, -123,  -79,
         54,  126,   57,  -76, -124,  -32,  127,   38, -103, -101,   42,
        126,   33, -106,  -98,   47,  126,   29, -108,  -95,   51,  126,
         24, -111,  -91,   55,  125,   20, -113,  -88,   59,  124,   15,
       -115,  -85,   63,  123,   10, -117,  -81,   67,  122,    6, -119,
        -78,   71,  121,    1, -120,  -74,   75,  120,   -3, -121,  -70,
         79,  127,   21, -119,  -62,   97,   96,  -64, -118,   23,  126,
         19, -120,  -61,   99,   95,  -66, -118,   25,  126,   17, -120,
        -59,  100,   93,  -68, -117,   27,  126,   15, -121,  -57,  101,
         92,  -69, -116,   29,  126,   13, -121,  -55,  102,   91,  -71,
       -115,   31,  126,   11, -122,  -54,  103,  127,    3, -126,   -9,
        126,   15, -125,  -21,  124,   27, -123,  -33,  121,   39, -119,
        -45,  117,   51, -114,  -57,  112,   62, -108,  -67,  105,   73,
       -102,  -78,   98,   82,  -94,  -87,   89,   91,  -85,  -96,   80,
        100,  -75, -103,   70,  107,  -65, -110,   59,  113,  -54, -116,
         48,  118,  127,  -51,  -85,  120,  -11, -110,  101,   28, -124,
         72,   66, -125,   35,   97, -114,   -4,  118,  -90,  -44,  126,
        -57,  -80,  122,  -18, -107,  105,   21, -123,   77,   60, -126,
         42,   92, -116,    1,  115,  -95,  -38,  126,  -63,  -74,  124,
        -25, -103,  109,   14, -121,   83,   54, -126,  127,  -70,  -48,
        124,  -89,  -24,  117, -105,    0,  105, -117,   24,   89, -124,
         48,   70, -127,   70,   48, -124,   89,   24, -117,  105,    0,
       -105,  117,  -24,  -89,  124,  -48,  -70,  127,  -70,  -48,  124,
        -89,  -24,  117, -105,    0,  105, -117,   24,   89, -124,   48,
         70, -127,   70,  127,  -95,   17,   68, -121,  115,  -52,  -36,
        107, -125,   82,    0,  -83,  125, -106,   34,   54, -116,  121,
        -67,  -19,   97, -126,   94,  -15,  -70,  122, -114,   50,   38,
       -108,  125,  -80,   -2,   85, -126,  105,  -32,  -55,  116, -120,
         65,   21,  -98,  126,  -93,   13,   72, -123,  113,  127, -106,
         51,   20,  -85,  122, -120,   79,  -12,  -58,  110, -126,  102,
        -44,  -27,   90, -124,  118,  -73,    5,   64, -113,  126,  -97,
         37,   34,  -95,  125, -115,   67,    1,  -70,  116, -125,   92,
        -30,  -41,  100, -126,  111,  -61,   -9,   76, -119,  123,  -87,
         23,   48, -104,  126
};
s32 sumra[8];
s32 sumrb[8];
s32 sumdec[8];
s32 sumft[8];
s32 sumcount=0;

u8 fb[128];
u8 fi;
u8 powfb[8]={20,20,20,20,40,25,40};
void calfreq(u8 *buff){
	u8 i,j,k;
	s32 val,offset;
	s32 r[8];
	sumcount++;

	for(i=0;i<50;i++){
		val=buff[i];
		val-=127;
		offset=i;
		for(j=0;j<8;j++)
		{
			sumra[j]+=val*ra[offset];
			sumrb[j]+=val*rb[offset];
			offset+=50;
		}
	}

	
	for(i=0;i<8;i++){
		sumra[i]=(sumra[i]>0?sumra[i]:-sumra[i])+(sumrb[i]>0?sumrb[i]:-sumrb[i]);
		//sumdec[i]=(sumra[i]+sumdec[i]*255)>>8;
	}
	#if 0
	if(sumcount<10){
		for(i=0;i<8;i++){
			sumdec[i]=(sumra[i]+sumdec[i]*3)>>2;
		}
	}
	#endif
	for(i=0;i<8;i++){
		sumft[i]=(sumra[i]+sumft[i]*3)>>2;
		sumdec[i]=sumft[i]>>10;
		//r[i]=sumft[i]-sumdec[i];
	}
	val=0;
	j=4;
	for(i=0;i<4;i++){
		if(sumdec[i]>val){val=sumdec[i];j=i;}
	}
	val=0;
	k=0;
	for(;i<8;i++){
		if(sumdec[i]>val){val=sumdec[i];k=i;}
	}
	
	for(i=0;i<8;i++){
		sumra[i]=sumrb[i]=0;
	}
	if(sumdec[j]<powfb[j]||sumdec[k]<powfb[k])return;
	for(i=0;i<8;i++){
		if(i!=k&&i!=j)
			if(sumdec[i]>15)
				return;
	}
	fb[fi++]=j*4+k-4;
	fi&=0x7f;
}

u8 adcbuff[150];
void DMA1_Channel1_IRQHandler(){
	if(DMA1->ISR&BIT1){
		DMA1->IFCR=0xff;
		calfreq(adcbuff+50);
	}
	else{
		DMA1->IFCR=0xff;
		calfreq(adcbuff);
	}
	
	//if(skip){skip=0;return;}
	//calfreq((s8*)adcbuff);
	//skip=1;
}


const s8 testval[]={
 -9,  -9, -12,  -5,  -7,  -7,  -9, -11, -13,  -9,  -2,  -1,   3,
          7,   8,  10,   9,   9,   7,   5,   9,  11,  18,  27,  33,  33,
         41,  41,  39,  35,  29,  28,  26,  22,  25,  27,  24,  20,  14,
          9,   1, -10, -16, -24, -27, -24, -23, -27, -29, -25};
int main(){
	initmem();
#if 1
	DMA1_Channel1->CMAR=(u32)&adcbuff;
	DMA1_Channel1->CPAR=(u32)(&ADC1->DR)+1;
	DMA1_Channel1->CNDTR=100;
	DMA1_Channel1->CCR=0x0A7;
	NVIC_SetPriority(DMA1_Channel1_IRQn,1);
	NVIC_EnableIRQ(DMA1_Channel1_IRQn);
#else
	DMA1_Channel1->CMAR=(u32)&USART1->DR;
	DMA1_Channel1->CPAR=(u32)(&ADC1->DR)+1;
	DMA1_Channel1->CNDTR=1;
	DMA1_Channel1->CCR=0x023;
#endif
	SETBIT(ADC1->CFGR1,ADC_CFGR1_ALIGN);
	SETBIT(ADC1->CR,ADC_CR_ADEN);
	SETBIT(ADC1->CR,ADC_CR_ADEN|ADC_CR_ADCAL);
	while(ADC1->CR&ADC_CR_ADCAL);
	SETBIT(ADC1->CR,ADC_CR_ADEN|ADC_CR_ADSTART);
	ADC1->ISR=0xff;

	SETBIT(TIM3->CR1,TIM_CR1_CEN);
	
	
	
	//calfreq((s8*)testval);
	//calfreq((s8*)testval);
	//calfreq((s8*)testval);
	//calfreq((s8*)testval);
	while(1){
		
	}
	return 0;
}

