

ifeq ($(TN_DDR_SUPPORT_MULTI_DDR), 1)
    OBJS  += $(OUT)/ddr_train_timing.o
    OBJS  += $(OUT)/ddr_segmented_data.o
else
    DDR_CONFIG ?= XIMX95LPD5EVK19_6400mbps_train_timing_a1
    OBJS  += $(OUT)/$(DDR_CONFIG).o
endif

VPATH += boards/edm-imx95/ddr
VPATH += boards/edm-imx95
VPATH += oei/ddr
