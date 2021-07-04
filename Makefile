# SPDX-License-Identifier: GPL-2.0

obj-m 			:= usvm.o
usvm-y 			:= src/usvm-main.o
KMOD_DIR 		:= /lib/modules/$(shell uname -r)/build
EXTRA_CFLAGS 	:= -g -I$(CURDIR)/include

all:
	$(MAKE) -C $(KMOD_DIR) M=$(CURDIR) CFLAGS="$(CFLAGS)" \
		EXTRA_CFLAGS="$(EXTRA_CFLAGS)"
clean:
	$(MAKE) -C $(KMOD_DIR) M=$(CURDIR) clean
