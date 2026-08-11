#ifndef __DDR_SEGMENTED_DATA_H__
#define __DDR_SEGMENTED_DATA_H__
#include <stdint.h>

#include <ddr.h>

struct segment_t { uint16_t start; uint16_t count; };
struct config_info_t { const struct segment_t *segments; uint16_t seg_count; };

#define MAX_DDR_DDRC_CFG_LEN 36
extern const struct config_info_t ddr_ddrc_cfg_configs[];
extern const struct ddrc_cfg_param pool_ddr_ddrc_cfg[];

#define MAX_DDR_DRAM_FSP0_DDRC_CFG_LEN 15
extern const struct config_info_t ddr_dram_fsp0_ddrc_cfg_configs[];
extern const struct ddrc_cfg_param pool_ddr_dram_fsp0_ddrc_cfg[];

#define MAX_DDR_PHY_FSP0_CFG_LEN 326
extern const struct config_info_t ddr_phy_fsp0_cfg_configs[];
extern const struct ddrphy_cfg_param pool_ddr_phy_fsp0_cfg[];

#define MAX_DDR_PHY_MSGH_FSP0_CFG_LEN 40
extern const struct config_info_t ddr_phy_msgh_fsp0_cfg_configs[];
extern const struct ddrphy_cfg_param pool_ddr_phy_msgh_fsp0_cfg[];

#define MAX_DDR_PHY_PIE_FSP0_CFG_LEN 153
extern const struct config_info_t ddr_phy_pie_fsp0_cfg_configs[];
extern const struct ddrphy_cfg_param pool_ddr_phy_pie_fsp0_cfg[];

#define MAX_DDR_PHY_PIE_LEN 2071
extern const struct config_info_t ddr_phy_pie_configs[];
extern const struct ddrphy_cfg_param pool_ddr_phy_pie[];

#define MAX_DDR_DDRPHY_CFG_LEN 84
extern const struct config_info_t ddr_ddrphy_cfg_configs[];
extern const struct ddrphy_cfg_param pool_ddr_ddrphy_cfg[];

#define MAX_DDR_DDRPHY_TRAINED_CSR_LEN 3357
extern const struct config_info_t ddr_ddrphy_trained_csr_configs[];
extern const struct ddrphy_addrs pool_ddr_ddrphy_trained_csr[];

#endif