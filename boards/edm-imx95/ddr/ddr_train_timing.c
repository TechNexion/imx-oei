#include <stdio.h>
#include <oei.h>
#include <board.h>
#include "ddr_segmented_data.h"
#include "ddr_train_timing.h"

static struct ddrphy_cfg_param ddr_phy_msgh_fsp0_cfg[MAX_DDR_PHY_MSGH_FSP0_CFG_LEN] = { 0 };
static struct dram_fsp_msg ddr_dram_fsp_msg[1] = {
    {
        /* P0 6400mts */
        .drate = 6400,
        .ssc = false,
        .fw_type = FW_1D_IMAGE,
        .fsp_phy_msgh_cfg = ddr_phy_msgh_fsp0_cfg,
        .fsp_phy_msgh_cfg_num = 0,
    },
};

static struct ddrc_cfg_param ddr_dram_fsp0_ddrc_cfg[MAX_DDR_DRAM_FSP0_DDRC_CFG_LEN] = { 0 };
/* dram fsp cfg */
static struct dram_fsp_cfg ddr_dram_fsp_cfg[1] = {
    {
        .ddrc_cfg = ddr_dram_fsp0_ddrc_cfg,
        .ddrc_cfg_num = 0,
        .bypass = 0,
    },
};

struct ddrc_cfg_param ddr_ddrc_cfg[MAX_DDR_DDRC_CFG_LEN] = { 0 };

/* ddr timing config params */
struct dram_timing_info dram_timing = {
    .ddrc_cfg = ddr_ddrc_cfg,
    .ddrc_cfg_num = 0,
    .fsp_msg = ddr_dram_fsp_msg,
    .fsp_msg_num = ARRAY_SIZE(ddr_dram_fsp_msg),
    .fsp_table = { 6400, },
    .fsp_cfg = ddr_dram_fsp_cfg,
    .fsp_cfg_num = ARRAY_SIZE(ddr_dram_fsp_cfg),
};

static unsigned int _init_cfg_param(int version_id, const struct config_info_t *configs, const struct ddrc_cfg_param *pool, struct ddrc_cfg_param *output) {
    unsigned int current_idx = 0;
    const struct config_info_t *ver = &configs[version_id];
    uint16_t start;
    uint16_t count;
    uint16_t src_idx;

    for (uint16_t s = 0; s < ver->seg_count; s++) {
        start = ver->segments[s].start;
        count = ver->segments[s].count;

        for (uint16_t i = 0; i < count; i++) {
            src_idx = start + i;

            output[current_idx].reg = pool[src_idx].reg;
            output[current_idx].val = pool[src_idx].val;
            current_idx++;
        }
    }
    return current_idx;
}

static unsigned int _init_phy_cfg_param(int ddr_idx, const struct config_info_t *configs, const struct ddrphy_cfg_param *pool, struct ddrphy_cfg_param *output) {
    const struct config_info_t *ver = &configs[ddr_idx];
    unsigned int current_idx = 0;
    uint16_t start;
    uint16_t count;
    uint16_t src_idx;

    for (uint16_t s = 0; s < ver->seg_count; s++) {
        start = ver->segments[s].start;
        count = ver->segments[s].count;

        for (uint16_t i = 0; i < count; i++) {
            src_idx = start + i;

            output[current_idx].reg = pool[src_idx].reg;
            output[current_idx].val = pool[src_idx].val;
            current_idx++;
        }
    }
    return current_idx;
}

static int _get_ddr_idx(void) {
    int ddrcode = Read32(OCRAM_NON_SECURE_BASE_ADDR);
    switch (ddrcode) {
        case LPDDR5_4GB:  return 0; break;
        case LPDDR5_8GB:  return 1; break;
        case LPDDR5_16GB: return 2; break;
        default:          return 0; break;
    }
}

void ddr_conf_init(void) {
    const int ddr_idx = _get_ddr_idx();

    dram_timing.ddrc_cfg_num =                 _init_cfg_param     ( ddr_idx, ddr_ddrc_cfg_configs,           pool_ddr_ddrc_cfg, ddr_ddrc_cfg                     );
    ddr_dram_fsp_msg[0].fsp_phy_msgh_cfg_num = _init_phy_cfg_param ( ddr_idx, ddr_phy_msgh_fsp0_cfg_configs,  pool_ddr_phy_msgh_fsp0_cfg, ddr_phy_msgh_fsp0_cfg   );
    ddr_dram_fsp_cfg[0].ddrc_cfg_num =         _init_cfg_param     ( ddr_idx, ddr_dram_fsp0_ddrc_cfg_configs, pool_ddr_dram_fsp0_ddrc_cfg, ddr_dram_fsp0_ddrc_cfg );

}

unsigned int TN_Ddr_Phy_Cfg_Set(const struct config_info_t *cfg, const struct ddrphy_cfg_param *pool) {
    unsigned int current_idx = 0;

    const int ddr_idx = _get_ddr_idx();
    const struct config_info_t *ver = &cfg[ddr_idx];

    for (uint16_t s = 0; s < ver->seg_count; s++) {
        uint16_t start = ver->segments[s].start;
        uint16_t count = ver->segments[s].count;

        for (uint16_t i = 0; i < count; i++) {
            uint16_t src_idx = start + i;

            Dwc_Ddrphy_Apb_Wr(pool[src_idx].reg, pool[src_idx].val);
            current_idx++;
        }
    }
    return current_idx;
}


unsigned int TN_To_Ddr_Phy_Reg(struct ddrphy *ddrphy) {
    unsigned int current_idx = 0;

    const int ddr_idx = _get_ddr_idx();
    const struct ddrphy_addrs* pool = pool_ddr_ddrphy_trained_csr;
    const struct config_info_t *ver = &ddr_ddrphy_trained_csr_configs[ddr_idx];
    uint16_t start;
    uint16_t count;
    uint16_t src_idx;

    for (uint16_t s = 0; s < ver->seg_count; s++) {
        start = ver->segments[s].start;
        count = ver->segments[s].count;

        for (uint16_t i = 0; i < count; i++) {
            src_idx = start + i;
            ddrphy[current_idx].reg = pool[src_idx].reg;
            current_idx++;
        }
    }
    return current_idx;
}
