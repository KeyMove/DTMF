#ifndef _mcuhead_H_
#define _mcuhead_H_

#include "py32f0xx.h"

#define u8 unsigned char
#define u16 unsigned short
#define u32 unsigned long

#define s8 signed char
#define s16 signed short
#define s32 signed long

#define vu8 volatile u8
#define vu16 volatile u16
#define vu32 volatile u32


#define BIT0 1
#define BIT1 2
#define BIT2 4
#define BIT3 8
#define BIT4 0x10
#define BIT5 0x20
#define BIT6 0x40
#define BIT7 0x80
#define BIT8 0x100
#define BIT9 0x200
#define BIT10 0x400
#define BIT11 0x800
#define BIT12 0x1000
#define BIT13 0x2000
#define BIT14 0x4000
#define BIT15 0x8000
#define BIT16 0x10000

#define SETBIT(x,y) (x)|=(y)
#define CLRBIT(x,y) (x)&=~(y)
#define CPLBIT(x,y) (x)^=(y);

union u2i{
	vu32 l;
	vu16 li[2];
	vu8 lc[4];
	vu16 i;
	vu8 c[2];
};

#define _16T8H(x) (((union u2i*)&x)->c[1])//??16??8?
#define _16T8L(x) (((union u2i*)&x)->c[0])//??16??8?

#define _32T16H(x) (((union u2i*)&x)->li[1])//??32??16?
#define _32T16L(x) (((union u2i*)&x)->li[0])//??32??16?

#define _32T8HH(x) (((union u2i*)&x)->lc[3])//??32??8?
#define _32T8H(x) (((union u2i*)&x)->lc[2])//??32???8?
#define _32T8L(x) (((union u2i*)&x)->lc[1])//??32???8?
#define _32T8LL(x) (((union u2i*)&x)->lc[0])//??32?8?

#define XBIT(x) (((x>>21)&BIT7)|((x>>18)&BIT6)|((x>>15)&BIT5)|((x>>12)&BIT4)|((x>>9)&BIT3)|((x>>6)&BIT2)|((x>>3)&BIT1)|((x)&BIT0))
#define BIN(X) XBIT(0x##X)

#define BINWORD(b1,b2) ((BIN(b1)<<8)|BIN(b2))
#define BINDWORD(b1,b2,b3,b4) ((BIN(b1)<<24)|(BIN(b2)<<16)|(BIN(b3)<<8)|BIN(b4))


#define GPIO_EN(x) SETBIT(RCC->AHBENR,RCC_AHBENR_##x##EN)

#define Mask   (u32)0x3
#define PPMODE (u32)0x1
#define PUMODE (u32)0x0
#define AFMODE (u32)0x2
#define AIMODE (u32)0x3

#define HT4(x,y,z) (((x&(1<<y))!=0)*(z<<2*y))
#define HT16(x,y) (HT4(x,0,y)|HT4(x,1,y)|HT4(x,2,y)|HT4(x,3,y)|HT4(x,4,y)|HT4(x,5,y)|HT4(x,6,y)|HT4(x,7,y))
#define HT32(x,y,v) (~((HT16(x,v)<<16)|(HT16(y,v))))
#define HV32(x,y,v) ((HT16(x,v)<<16)|(HT16(y,v)))

#define _GPIO_PP(io,b1,b2) io->MODER&=HT32(b1,b2,Mask);io->MODER|=HV32(b1,b2,PPMODE);io->PUPDR&=HT32(b1,b2,Mask);
#define GPIO_PP(io,b1,b2) _GPIO_PP(io,BIN(b1),BIN(b2))

#define _GPIO_PU(io,b1,b2) io->MODER&=HT32(b1,b2,Mask);io->MODER|=HV32(b1,b2,PUMODE);io->PUPDR&=HT32(b1,b2,Mask);io->PUPDR|=HV32(b1,b2,PPMODE);
#define GPIO_PU(io,b1,b2) _GPIO_PU(io,BIN(b1),BIN(b2))

#define _GPIO_AF(io,b1,b2) io->MODER&=HT32(b1,b2,Mask);io->MODER|=HV32(b1,b2,AFMODE);
#define GPIO_AF(io,b1,b2) _GPIO_AF(io,BIN(b1),BIN(b2))

#define _GPIO_AI(io,b1,b2) io->MODER&=HT32(b1,b2,Mask);io->MODER|=HV32(b1,b2,AIMODE);io->PUPDR&=HT32(b1,b2,Mask);
#define GPIO_AI(io,b1,b2) _GPIO_AI(io,BIN(b1),BIN(b2))

#endif
