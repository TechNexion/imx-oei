#include timings


MULTI_DDR_CONFIGS := lpddr4x_multi lpddr5_multi
ifneq ($(filter $(MULTI_DDR_CONFIGS),$(DDR_CONFIG)),)
    FLAGS += -DSUPPORT_MULTI_DDR
endif

ifneq ($(findstring lpddr4x,$(DDR_CONFIG)),)
    FLAGS += -DLPDDR4X
else ifneq ($(findstring lpddr5,$(DDR_CONFIG)),)
    FLAGS += -DLPDDR5
endif


include $(ROOT_DIR)/boards/$(SOM)/ddr/Makefile

ifeq ($(TEST),1)
    FLAGS += -DDDR_MEM_TEST
    OBJS  += $(OUT)/memtest.o
endif

ifeq ($(IEE),1)
    FLAGS += -DDDR_IEE
    OBJS  += $(OUT)/iee.o
endif

OBJS += \
	$(OUT)/main.o \
	$(OUT)/ddr_init.o \
	$(OUT)/ddrphy_utils.o \
	$(OUT)/helper.o

OBJS  += \
	$(OUT)/ddrphy_qb.o \
	$(OUT)/ddrphy_train.o \
	$(OUT)/ddrphy_qb_gen.o \
	$(OUT)/romapi.o

VPATH += oei/ddr

IMG += oei-$(cpu)-ddr

include $(ROOT_DIR)/oei/makefiles/gcc_cross.mak
