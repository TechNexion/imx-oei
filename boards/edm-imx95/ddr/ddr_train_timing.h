#ifndef __DDR_TRAIN_TIMING_H__
#define __DDR_TRAIN_TIMING_H__

#include <ddr.h>
#include <ddr_retention.h>
#include "ddr_segmented_data.h"

unsigned int TN_Ddr_Phy_Cfg_Set(const struct config_info_t *cfg, const struct ddrphy_cfg_param *pool);
unsigned int TN_To_Ddr_Phy_Reg(struct ddrphy *ddrphy);

#endif /* __DDR_TRAIN_TIMING_H__ */