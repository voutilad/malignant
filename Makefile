# SPDX-License-Identifier: ISC
#
# Copyright (C) 2023 Dave Voutila <voutilad@gmail.com>. All rights reserved.

KERNELRELEASE ?= $(shell uname -r)
KERNELDIR ?= /lib/modules/$(KERNELRELEASE)/build
DEPMOD ?= depmod
PWD := $(shell pwd)

all: module
debug: module-debug

module:
	@$(MAKE) -C $(KERNELDIR) M=$(PWD) modules

module-debug:
	@$(MAKE) -C $(KERNELDIR) M=$(PWD) modules

clean:
	@$(MAKE) -C $(KERNELDIR) M=$(PWD) clean

install:
	@$(MAKE) -C $(KERNELDIR) M=$(PWD) modules_install
	@$(DEPMOD) -A $(KERNELRELEASE)

.PHONY: all module-debug module-install install clean
