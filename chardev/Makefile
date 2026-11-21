# Buildroot location (full path, no ~)
BR := /home/student/abra/oriks/rpi-buildroot-2026.08

# What to cross compile for
ARCH := arm64
CROSS_COMPILE := $(BR)/output/host/bin/aarch64-linux-

# The kernel that runs on the Pi (Buildroot built it)
# find the exact name with:  ls -d $(BR)/output/build/linux-*
KDIR := $(BR)/output/build/linux-custom

# The module to build: hello.c -> hello.ko
obj-m := hello.o

PWD := $(shell pwd)

default:
	$(MAKE) -C $(KDIR) M=$(PWD) ARCH=$(ARCH) CROSS_COMPILE=$(CROSS_COMPILE) modules

clean:
	$(MAKE) -C $(KDIR) M=$(PWD) ARCH=$(ARCH) CROSS_COMPILE=$(CROSS_COMPILE) clean

.PHONY: default clean

