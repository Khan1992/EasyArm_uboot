/*
 * Copyright 2008 SigmaTel, Inc
 * Copyright 2008 Embedded Alley Solutions, Inc
 * Copyright 2009 Freescale Semiconductor, Inc. All Rights Reserved.
 *
 * Based on linux/include/asm/arm/setup.h:
 * Copyright (C) 1997-1999 Russell King
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */
#ifndef __SETUP_H
#define __SETUP_H
#include <types.h>

/*
 * ARM tags definitions
 */

/* The list ends with an ATAG_NONE node. */
#define ATAG_NONE 0x00000000

struct tag_header {
    u32 size;
    u32 tag;
};

/* The list must start with an ATAG_CORE node */
#define ATAG_CORE 0x54410001

struct tag_core {
    u32 flags; /* bit 0 = read-only */
    u32 pagesize;
    u32 rootdev;
};

/* it is allowed to have multiple ATAG_MEM nodes */
#define ATAG_MEM 0x54410002

struct tag_mem32 {
    u32 size;
    u32 start; /* physical start address */
};

/* VGA text type displays */
#define ATAG_VIDEOTEXT 0x54410003

struct tag_videotext {
    u8 x;
    u8 y;
    u16 video_page;
    u8 video_mode;
    u8 video_cols;
    u16 video_ega_bx;
    u8 video_lines;
    u8 video_isvga;
    u16 video_points;
};

/* describes how the ramdisk will be used in kernel */
#define ATAG_RAMDISK 0x54410004

struct tag_ramdisk {
    u32 flags; /* bit 0 = load, bit 1 = prompt */
    u32 size;  /* decompressed ramdisk size in _kilo_ bytes */
    u32 start; /* starting block of floppy-based RAM disk image */
};

/* describes where the compressed ramdisk image lives (virtual address) */
/*
 * this one accidentally used virtual addresses - as such,
 * its depreciated.
 */
#define ATAG_INITRD 0x54410005

/* describes where the compressed ramdisk image lives (physical address) */
#define ATAG_INITRD2 0x54420005

struct tag_initrd {
    u32 start; /* physical start address */
    u32 size;  /* size of compressed ramdisk image in bytes */
};

/* board serial number. "64 bits should be enough for everybody" */
#define ATAG_SERIAL 0x54410006

struct tag_serialnr {
    u32 low;
    u32 high;
};

/* board revision */
#define ATAG_REVISION 0x54410007

struct tag_revision {
    u32 rev;
};

/* initial values for vesafb-type framebuffers. see struct screen_info
 * in include/linux/tty.h
 */
#define ATAG_VIDEOLFB 0x54410008

struct tag_videolfb {
    u16 lfb_width;
    u16 lfb_height;
    u16 lfb_depth;
    u16 lfb_linelength;
    u32 lfb_base;
    u32 lfb_size;
    u8 red_size;
    u8 red_pos;
    u8 green_size;
    u8 green_pos;
    u8 blue_size;
    u8 blue_pos;
    u8 rsvd_size;
    u8 rsvd_pos;
};

/* command line: \0 terminated string */
#define ATAG_CMDLINE 0x54410009

struct tag_cmdline {
    char cmdline[1]; /* this is the minimum size */
};

/* acorn RiscPC specific information */
#define ATAG_ACORN 0x41000101

struct tag_acorn {
    u32 memc_control_reg;
    u32 vram_pages;
    u8 sounddefault;
    u8 adfsdrives;
};

/* footbridge memory clock, see arch/arm/mach-footbridge/arch.c */
#define ATAG_MEMCLK 0x41000402

struct tag_memclk {
    u32 fmemclk;
};

struct tag {
    struct tag_header hdr;
    union {
        struct tag_core core;
        struct tag_mem32 mem;
        struct tag_videotext videotext;
        struct tag_ramdisk ramdisk;
        struct tag_initrd initrd;
        struct tag_serialnr serialnr;
        struct tag_revision revision;
        struct tag_videolfb videolfb;
        struct tag_cmdline cmdline;

        /*
         * Acorn specific
         */
        struct tag_acorn acorn;

        /*
         * DC21285 specific
         */
        struct tag_memclk memclk;
    } u;
};

#define tag_member_present(tag, member)                                        \
    ((unsigned long)(&((struct tag *)0L)->member + 1) <= (tag)->hdr.size * 4)

#define tag_next(t) ((struct tag *)((u32 *)(t) + (t)->hdr.size))
#define tag_size(type) ((sizeof(struct tag_header) + sizeof(struct type)) >> 2)

#define for_each_tag(t, base) for (t = base; t->hdr.size; t = tag_next(t))

/*
 * Magic keys definitions
 */
enum magic_key {
    NO_MAGIC_KEY = 0,
    MAGIC_KEY1,
    MAGIC_KEY2,
    MAGIC_KEY3,
    MAGIC_KEY_NR,
};

/*
 * Platform specific magic key combinations and command
 * lines corresponding to each magic key including default
 * command line used if no magic keys detected
 */
extern u32 magic_keys[MAGIC_KEY_NR];

/* Pointers to .commandlines section within linux_prep */
extern char cmdlines_start[], cmdlines_end[];

/* Platform specific default command line */
extern char cmdline_def[];
#endif /* __SETUP_H */
