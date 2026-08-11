
DDR_CONFIG ?= XIMX95LPD5EVK19_6400mbps_train_timing_a1

ifeq ($(DDR_CONFIG),lpddr4x_multi)
    # LPDDR4X multi DDR
    OBJS += $(OUT)/lpddr4x_train_timing.o
    OBJS += $(OUT)/lpddr4x_segmented_data.o
else ifeq ($(DDR_CONFIG),lpddr5_multi)

    # LPDDR5 multi DDR
    OBJS += $(OUT)/lpddr5_train_timing.o
    OBJS += $(OUT)/lpddr5_segmented_data.o

else
    DDR_CONFIG_FILE := $(ROOT_DIR)/boards/$(SOM)/ddr/$(DDR_CONFIG).c
    ifeq ($(wildcard $(DDR_CONFIG_FILE)),)
        $(error DDR configuration file not found: $(DDR_CONFIG_FILE))
    endif

    OBJS += $(OUT)/$(DDR_CONFIG).o

endif

VPATH += boards/edm-imx95/ddr
VPATH += boards/edm-imx95
VPATH += oei/ddr
