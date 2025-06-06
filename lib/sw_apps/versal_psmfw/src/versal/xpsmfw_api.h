/******************************************************************************
* Copyright (c) 2019 - 2021 Xilinx, Inc.  All rights reserved.
* Copyright (c) 2022 - 2024 Advanced Micro Devices, Inc. All Rights Reserved.
* SPDX-License-Identifier: MIT
 ******************************************************************************/


#ifndef XPSMFW_API_H_
#define XPSMFW_API_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "xparameters.h"
#include "xpsmfw_default.h"

#define NODE_CLASS_SHIFT	26U
#define NODE_SUBCLASS_SHIFT	20U
#define NODE_TYPE_SHIFT		14U
#define NODE_INDEX_SHIFT	0U
#define NODE_CLASS_MASK_BITS    0x3FU
#define NODE_SUBCLASS_MASK_BITS 0x3FU
#define NODE_TYPE_MASK_BITS     0x3FU
#define NODE_INDEX_MASK_BITS    0x3FFFU
#define NODE_CLASS_MASK         (NODE_CLASS_MASK_BITS << NODE_CLASS_SHIFT)
#define NODE_SUBCLASS_MASK      (NODE_SUBCLASS_MASK_BITS << NODE_SUBCLASS_SHIFT)
#define NODE_TYPE_MASK          (NODE_TYPE_MASK_BITS << NODE_TYPE_SHIFT)
#define NODE_INDEX_MASK         (NODE_INDEX_MASK_BITS << NODE_INDEX_SHIFT)

#define NODEID(CLASS, SUBCLASS, TYPE, INDEX)	\
	((((u32)(CLASS) & NODE_CLASS_MASK_BITS) << NODE_CLASS_SHIFT) | \
	(((u32)(SUBCLASS) & NODE_SUBCLASS_MASK_BITS) << NODE_SUBCLASS_SHIFT) | \
	(((u32)(TYPE) & NODE_TYPE_MASK_BITS) << NODE_TYPE_SHIFT) | \
	(((u32)(INDEX) & NODE_INDEX_MASK_BITS) << NODE_INDEX_SHIFT))

#define XPSMFW_NODECLASS_DEVICE		(6U)
#define XPSMFW_NODECLASS_POWER		(1U)

#define XPSMFW_NODESUBCL_DEV_CORE	(1U)
#define XPSMFW_NODESUBCL_POWER_DOMAIN	(2U)

#define XPSMFW_NODETYPE_DEV_CORE_APU		(3U)
#define XPSMFW_NODETYPE_DEV_CORE_RPU		(4U)
#define XPSMFW_NODETYPE_POWER_DOMAIN_CPM	(6U)

#define XPSMFW_NODEIDX_DEV_ACPU_0	(3U)
#define XPSMFW_NODEIDX_DEV_ACPU_1	(4U)
#define XPSMFW_NODEIDX_DEV_RPU0_0	(5U)
#define XPSMFW_NODEIDX_DEV_RPU0_1	(6U)
#define XPSMFW_NODEIDX_POWER_CPM	(7U)
#define XPSMFW_NODEIDX_POWER_CPM5	(39U)
#define XPSMFW_NODEIDX_ISO_CPM5_LPD	(34U)
#define XPSMFW_NODEIDX_ISO_CPM5_LPD_DFX	(35U)
#define XPSMFW_NODEIDX_ISO_CPM5_PL	(26U)
#define XPSMFW_NODEIDX_ISO_CPM5_PL_DFX	(41U)
#define XPSMFW_NODEIDX_ISO_CPM5_GT	(42U)
#define XPSMFW_NODEIDX_ISO_CPM5_GT_DFX	(43U)

#define XPSMFW_DEV_ACPU_0	NODEID(XPSMFW_NODECLASS_DEVICE,		\
				       XPSMFW_NODESUBCL_DEV_CORE,	\
				       XPSMFW_NODETYPE_DEV_CORE_APU,	\
				       XPSMFW_NODEIDX_DEV_ACPU_0)

#define XPSMFW_DEV_ACPU_1	NODEID(XPSMFW_NODECLASS_DEVICE,		\
				       XPSMFW_NODESUBCL_DEV_CORE,	\
				       XPSMFW_NODETYPE_DEV_CORE_APU,	\
				       XPSMFW_NODEIDX_DEV_ACPU_1)

#define XPSMFW_DEV_RPU0_0	NODEID(XPSMFW_NODECLASS_DEVICE,		\
				       XPSMFW_NODESUBCL_DEV_CORE,	\
				       XPSMFW_NODETYPE_DEV_CORE_RPU,	\
				       XPSMFW_NODEIDX_DEV_RPU0_0)

#define XPSMFW_DEV_RPU0_1	NODEID(XPSMFW_NODECLASS_DEVICE,		\
				       XPSMFW_NODESUBCL_DEV_CORE,	\
				       XPSMFW_NODETYPE_DEV_CORE_RPU,	\
				       XPSMFW_NODEIDX_DEV_RPU0_1)

#define XPSMFW_POWER_CPM	NODEID(XPSMFW_NODECLASS_POWER,		\
				       XPSMFW_NODESUBCL_POWER_DOMAIN,	\
				       XPSMFW_NODETYPE_POWER_DOMAIN_CPM,\
				       XPSMFW_NODEIDX_POWER_CPM)

#define XPSMFW_POWER_CPM5	NODEID(XPSMFW_NODECLASS_POWER,		\
				       XPSMFW_NODESUBCL_POWER_DOMAIN,	\
				       XPSMFW_NODETYPE_POWER_DOMAIN_CPM,\
				       XPSMFW_NODEIDX_POWER_CPM5)

#define PSM_KEEP_ALIVE_COUNTER_ADDR	(0xF20140C8U)
#define IPI_PSM_ISR_ADDR		(0xFF310010U)
#define PMC_IPI_BIT			(0x2U)

#define PM_PSM_TO_PLM_EVENT	(1U)

#define PSM_API_DIRECT_PWR_DWN	(1U)
#define PSM_API_DIRECT_PWR_UP	(2U)
#define PSM_API_FPD_HOUSECLEAN	(3U)
#define PSM_API_CCIX_EN		(4U)
#define PSM_API_KEEP_ALIVE	(5U)
#define PSM_API_DOMAIN_ISO	(6U)
#define PSM_API_GET_PSM_TO_PLM_EVENT_ADDR	(7U)

/**
 *  PM init node functions
 */
enum XPmInitFunctions {
	FUNC_INIT_START,
	FUNC_INIT_FINISH,
	FUNC_SCAN_CLEAR,
	FUNC_BISR,
	FUNC_MBIST_LBIST,
	FUNC_ME_INITREG,
	FUNC_MBIST_CLEAR,
	FUNC_SECLOCKDOWN = 11U
};

XStatus XPsmFw_NotifyPlmEvent(void);
void XPsmFw_ProcessIpi(const u32 *Payload, u32 *Response);

#ifdef __cplusplus
}
#endif

#endif /* XPSMFW_API_H_ */
