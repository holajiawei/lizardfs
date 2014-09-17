/*
   Copyright 2005-2010 Jakub Kruszona-Zawadzki, Gemius SA, 2013 Skytechnology sp. z o.o..

   This file was part of MooseFS and is part of LizardFS.

   LizardFS is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, version 3.

   LizardFS is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with LizardFS  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include "common/platform.h"

#include <inttypes.h>

uint32_t mycrc32(uint32_t crc,const uint8_t *block,uint32_t leng);
uint32_t mycrc32_combine(uint32_t crc1, uint32_t crc2, uint32_t leng2);
#define mycrc32_zeroblock(crc,zeros) mycrc32_combine((crc)^0xFFFFFFFF,0xFFFFFFFF,(zeros))
#define mycrc32_zeroexpanded(crc,block,leng,zeros) mycrc32_zeroblock(mycrc32((crc),(block),(leng)),(zeros))
#define mycrc32_xorblocks(crc,crcblock1,crcblock2,leng) ((crcblock1)^(crcblock2)^mycrc32_zeroblock(crc,leng))

void mycrc32_init(void);
/**
 * In the special case when the block consists only of zeros and passed crc is equal to 0 update
 * crc to be equal to mycrc32_zeroblock(0, MFSBLOCKSIZE)
 */
void recompute_crc_if_block_empty(uint8_t* block, uint32_t& crc);
