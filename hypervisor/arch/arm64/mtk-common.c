/*
 * Jailhouse, a Linux-based partitioning hypervisor
 *
 * Copyright (c) 2026 MediaTek
 *
 * Common part for sharing EINT between root and other inmate cells and
 * control concurrent access to shared registers.
 *
 * Authors:
 *   Felix Freimann <felix.freimann@mediatek.com>
 *
 * This work is licensed under the terms of the GNU GPL, version 2.  See
 * the COPYING file in the top-level directory.
 */

#include <asm/mtk-common.h>


access_descr_t get_access_descr (struct mmio_access*        mmio,
                                 const access_descr_map_t*  access_descr_map,
                                 size_t                     access_descr_map_size)
{                                
    if ((mmio->address & 0x00000003) != 0)
    {
        return (ACCESS_DESCR_EMPTY);
    }

    while (access_descr_map_size > 0)
    {
        if ((mmio->address >= access_descr_map->reg_start) &&
            (mmio->address <  access_descr_map->reg_end))
        {
            return (access_descr_map->access_descr [(mmio->address - access_descr_map->reg_start) >> 2]);
        }

        access_descr_map++;
        access_descr_map_size--;
    }

    return (ACCESS_DESCR_EMPTY);
}
