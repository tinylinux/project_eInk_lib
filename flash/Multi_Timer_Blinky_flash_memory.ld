/*
 * GENERATED FILE - DO NOT EDIT
 * Copyright (c) 2008-2013 Code Red Technologies Ltd,
 * Copyright 2015, 2018-2019 NXP
 * (c) NXP Semiconductors 2013-2021
 * Generated linker script file for LPC804
 * Created from memory.ldt by FMCreateLinkMemory
 * Using Freemarker v2.3.30
 * MCUXpresso IDE v11.4.1 [Build 6260] [2021-09-15] on 7 déc. 2021 à 15:24:55
 */

MEMORY
{
  /* Define each memory region */
  MFlash32 (rx) : ORIGIN = 0x0, LENGTH = 0x7f80 /* 32640 bytes (alias Flash) */  
  RamLoc4 (rwx) : ORIGIN = 0x10000000, LENGTH = 0x1000 /* 4K bytes (alias RAM) */  
}

  /* Define a symbol for the top of each memory region */
  __base_MFlash32 = 0x0  ; /* MFlash32 */  
  __base_Flash = 0x0 ; /* Flash */  
  __top_MFlash32 = 0x0 + 0x7f80 ; /* 32640 bytes */  
  __top_Flash = 0x0 + 0x7f80 ; /* 32640 bytes */  
  __base_RamLoc4 = 0x10000000  ; /* RamLoc4 */  
  __base_RAM = 0x10000000 ; /* RAM */  
  __top_RamLoc4 = 0x10000000 + 0x1000 ; /* 4K bytes */  
  __top_RAM = 0x10000000 + 0x1000 ; /* 4K bytes */  
