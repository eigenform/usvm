// SPDX-License-Identifier: GPL-2.0

#include <linux/module.h>
#include <linux/mm.h>
#include <asm/svm.h>

#include <usvm.h>

struct usvm_state global_state;

// Initialize the VMCB
static int init_vmcb(struct usvm_state *usvm)
{
	struct vmcb_control_area *ctrl = &usvm->vmcb->control;
	struct vmcb_save_area *save = &usvm->vmcb->save;
	vmcb_set_intercept(ctrl, INTERCEPT_CPUID);

	return 0;
}

static __init int usvm_init(void)
{
	int res;
	struct page *global_vmcb_page;

	// Get a page for the VMCB
	global_vmcb_page = alloc_page(GFP_KERNEL_ACCOUNT | __GFP_ZERO);
	if (!global_vmcb_page) {
		pr_err("usvm: couldn't allocate VMCB page\n");
		return -1;
	}
	global_state.vmcb = page_address(global_vmcb_page);
	global_state.vmcb_paddr = page_to_pfn(global_vmcb_page) << PAGE_SHIFT;
	res = init_vmcb(&global_state);

	return 0;
}

static __exit void usvm_exit(void)
{
	return;
}

module_init(usvm_init);
module_exit(usvm_exit);
MODULE_LICENSE("GPLv2");
