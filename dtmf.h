#ifndef _dtmf_H_
#define _dtmf_H_

#include "mcuhead.h"

typedef struct {
	void(*Init)(void);
	u8(*getCode)(void);
}dtmfBase;

extern const dtmfBase dtmf;

#endif
