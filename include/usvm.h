// SPDX-License-Identifier: GPL-2.0

#ifndef _USVM_H
#define _USVM_H

#include <asm/svm.h>

struct usvm_state {
	struct vmcb *vmcb;
	unsigned long vmcb_paddr;
};

static inline void vmcb_set_intercept(struct vmcb_control_area *ctrl, u32 bit)
{
	__set_bit(bit, (unsigned long *)&ctrl->intercepts);
}
static inline void vmcb_clr_intercept(struct vmcb_control_area *ctrl, u32 bit)
{
	__clear_bit(bit, (unsigned long *)&ctrl->intercepts);
}



#endif // _USVM_H
