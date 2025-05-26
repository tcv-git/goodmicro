/* stm32h743xi.ld */
/* PUBLIC DOMAIN */
/* https://www.purposeful.co.uk/goodmicro/ */

/*
  I, Tom Vajzovic, am the author of this software and its documentation.
  I permanently abandon all copyright and other intellectual property rights
  in them.

  I am fairly certain that the software does what the documentation says it
  does, but I do not guarantee that it does, or that it does what you think it
  should.  I do not guarantee that it will not have undesirable side effects.

  If you use, modify or distribute this software then you do so at your own
  risk.  If you do not pass on this warning then you may be responsible for any
  problems encountered by those who obtain the software through you.
*/


/******************************************************************************/
/*******        MEMORY LAYOUT                                             *****/
/******************************************************************************/

MEMORY
{
  ITCMRAM (rx) : ORIGIN = 0x00000000, LENGTH =  64K
  FLASH   (rx) : ORIGIN = 0x08000000, LENGTH =   2M
  DTCMRAM (rw) : ORIGIN = 0x20000000, LENGTH = 128K
  D1SRAM  (rw) : ORIGIN = 0x24000000, LENGTH = 512K
  D2SRAM  (rw) : ORIGIN = 0x30000000, LENGTH = 288K
  D3SRAM  (rw) : ORIGIN = 0x38000000, LENGTH =  64K
  BKPSRAM (rw) : ORIGIN = 0x38800000, LENGTH =   4K
}

_Min_Stack_Size = 16K;
_Min_Heap_Size  = 16K;

SECTIONS
{
  /****************************************************************************/
  /*****        ROM                                                       *****/
  /****************************************************************************/

  .startup_vectors :
  {
    KEEP(*(.startup_vectors))
  }
  >FLASH

  .startup :
  {
    *(.startup*)
  }
  >FLASH

  .init :
  {
    KEEP (*(SORT_NONE(.init)))
  }
  >FLASH

  .fini :
  {
    KEEP (*(SORT_NONE(.fini)))
  }
  >FLASH

  .tm_clone_table :
  {
    *(.tm_clone_table)
  }
  >FLASH

  .preinit_array :
  {
    PROVIDE_HIDDEN (__preinit_array_start = .);
    KEEP (*(.preinit_array))
    PROVIDE_HIDDEN (__preinit_array_end = .);
  }
  >FLASH

  .init_array :
  {
    PROVIDE_HIDDEN (__init_array_start = .);
    KEEP (*(SORT_BY_INIT_PRIORITY(.init_array.*) SORT_BY_INIT_PRIORITY(.ctors.*)))
    KEEP (*(.init_array EXCLUDE_FILE (*crtbegin.o *crtbegin?.o *crtend.o *crtend?.o ) .ctors))
    PROVIDE_HIDDEN (__init_array_end = .);
  }
  >FLASH

  .fini_array :
  {
    PROVIDE_HIDDEN (__fini_array_start = .);
    KEEP (*(SORT_BY_INIT_PRIORITY(.fini_array.*) SORT_BY_INIT_PRIORITY(.dtors.*)))
    KEEP (*(.fini_array EXCLUDE_FILE (*crtbegin.o *crtbegin?.o *crtend.o *crtend?.o ) .dtors))
    PROVIDE_HIDDEN (__fini_array_end = .);
  }
  >FLASH

  .ctors :
  {
    KEEP (*crtbegin.o(.ctors))
    KEEP (*crtbegin?.o(.ctors))
    KEEP (*(EXCLUDE_FILE (*crtend.o *crtend?.o ) .ctors))
    KEEP (*(SORT(.ctors.*)))
    KEEP (*(.ctors))
  }
  >FLASH

  .dtors :
  {
    KEEP (*crtbegin.o(.dtors))
    KEEP (*crtbegin?.o(.dtors))
    KEEP (*(EXCLUDE_FILE (*crtend.o *crtend?.o ) .dtors))
    KEEP (*(SORT(.dtors.*)))
    KEEP (*(.dtors))
  }
  >FLASH

  .ARM.extab :
  {
    *(.ARM.extab* .gnu.linkonce.armextab.*)
  }
  >FLASH

  .ARM.exidx :
  {
    PROVIDE_HIDDEN (__exidx_start = .);
    *(.ARM.exidx* .gnu.linkonce.armexidx.*)
    PROVIDE_HIDDEN (__exidx_end = .);
  }
  >FLASH

  .eh_frame_hdr :
  {
    *(.eh_frame_hdr)
    *(.eh_frame_entry .eh_frame_entry.*)
  }
  >FLASH

  .eh_frame :
  {
    KEEP (*(.eh_frame))
    *(.eh_frame.*)
  }
  >FLASH

  .gcc_except_table :
  {
    *(.gcc_except_table .gcc_except_table.*)
  }
  >FLASH

  .gnu_extab :
  {
    *(.gnu_extab*)
  }
  >FLASH

  /* vector needs to be 1024 byte(!) aligned, but don't specify that here */
  /* because it forces the load address to be aligned by the same amount  */
  .vectors : ALIGN(4)
  {
    KEEP(*(.vectors))
    KEEP(*(.isr_vector))
    . = .; /* assignment forces output section to exist even if empty */
  }
  >ITCMRAM AT>FLASH

  .text0 : ALIGN(4)
  {
    *(.text0 .text0.*)
    *(.text .text.* .stub .gnu.linkonce.t.*)
    . = .;
  }
  >ITCMRAM AT>FLASH

  .rodata0 : ALIGN(4)
  {
    *(.rodata0 .rodata0.*)
    *(.rodata .rodata.* .gnu.linkonce.r.*)
    . = .;
  }
  >ITCMRAM AT>FLASH

  .text1 :
  {
    *(.text1 .text1.*)
    . = .;
  }
  >FLASH

  .rodata1 :
  {
    *(.rodata1 .rodata1.*)
    . = .;
  }
  >FLASH


  /****************************************************************************/
  /*****        RAM                                                       *****/
  /****************************************************************************/

  .data0 : ALIGN(4)
  {
    *(.data0 .data0.*)
    *(.data .data.* .gnu.linkonce.d.*)
    *(.sdata .sdata.* .gnu.linkonce.s.*)
    . = .;
  }
  >DTCMRAM AT>FLASH

  .bss0 (NOLOAD) : ALIGN(4)
  {
    *(.bss0 .bss0.*)
    *(.bss .bss.* .gnu.linkonce.b.*)
    *(.sbss .sbss.* .scommon)
    *(COMMON)
    . = .;
  }
  >DTCMRAM

  .noinit0 (NOLOAD) :
  {
    *(.noinit0 .noinit0.*)
    . = .;
  }
  >DTCMRAM

  .stack (NOLOAD) : ALIGN(8)
  {
    *(.stack .stack.*)
    . = (. < _Min_Stack_Size ? _Min_Stack_Size : .);
    . = ALIGN(8);
  }
  >DTCMRAM

  .dma (NOLOAD) : ALIGN(32)
  {
    *(.dma .dma.*)
    . = .;
  }
  >D1SRAM

  .data1 : ALIGN(4)
  {
    *(.data1 .data1.*)
    . = .;
  }
  >D1SRAM AT>FLASH

  .bss1 (NOLOAD) : ALIGN(4)
  {
    *(.bss1 .bss1.*)
    . = .;
  }
  >D1SRAM

  .noinit1 (NOLOAD) :
  {
    *(.noinit1 .noinit1.*)
    . = .;
  }
  >D1SRAM

  .heap (NOLOAD) : ALIGN(8)
  {
    *(.heap .heap.*)
    . = (. < _Min_Heap_Size ? _Min_Heap_Size : .);
  }
  >D1SRAM


  /****************************************************************************/
  /*****        OTHER SECTIONS (debugging etc)                            *****/
  /****************************************************************************/

  .stab               0 : { *(.stab) }
  .stabstr            0 : { *(.stabstr) }
  .stab.excl          0 : { *(.stab.excl) }
  .stab.exclstr       0 : { *(.stab.exclstr) }
  .stab.index         0 : { *(.stab.index) }
  .stab.indexstr      0 : { *(.stab.indexstr) }
  .comment            0 : { *(.comment) }
  .debug              0 : { *(.debug) }
  .debug_abbrev       0 : { *(.debug_abbrev) }
  .debug_addr         0 : { *(.debug_addr) }
  .debug_aranges      0 : { *(.debug_aranges) }
  .debug_frame        0 : { *(.debug_frame) }
  .debug_funcnames    0 : { *(.debug_funcnames) }
  .debug_info         0 : { *(.debug_info .gnu.linkonce.wi.*) }
  .debug_line         0 : { *(.debug_line .debug_line.* .debug_line_end ) }
  .debug_line_str     0 : { *(.debug_line_str) }
  .debug_loc          0 : { *(.debug_loc) }
  .debug_loclists     0 : { *(.debug_loclists) }
  .debug_macinfo      0 : { *(.debug_macinfo) }
  .debug_macro        0 : { *(.debug_macro) }
  .debug_pubnames     0 : { *(.debug_pubnames) }
  .debug_pubtypes     0 : { *(.debug_pubtypes) }
  .debug_ranges       0 : { *(.debug_ranges) }
  .debug_rnglists     0 : { *(.debug_rnglists) }
  .debug_sfnames      0 : { *(.debug_sfnames) }
  .debug_srcinfo      0 : { *(.debug_srcinfo) }
  .debug_str          0 : { *(.debug_str) }
  .debug_typenames    0 : { *(.debug_typenames) }
  .debug_varnames     0 : { *(.debug_varnames) }
  .debug_weaknames    0 : { *(.debug_weaknames) }
  .line               0 : { *(.line) }
  .ARM.attributes     0 : { KEEP (*(.ARM.attributes)) KEEP (*(.gnu.attributes)) }
  .note.gnu.arm.ident 0 : { KEEP (*(.note.gnu.arm.ident)) }
  .note.gnu.build-id  0 : { KEEP (*(.note.gnu.build-id)) }

  /DISCARD/ :
  {
    *(.note.GNU-stack)
    *(.gnu_debuglink)
    *(.gnu.lto_*)
  }

  .should_be_empty :
  {
    __should_be_empty_start = .;
    *(*)
    __should_be_empty_end = .;
  }
  >D1SRAM
}


/******************************************************************************/
/*******         CHECKS                                                   *****/
/******************************************************************************/

/* The smallest Cortex-M interrupt vector is 16 words:
 */
ASSERT((SIZEOF(.vectors) >= 0x040), "Section .vectors is unexpectedly small");

/* The interrupt vector must be aligned to a multiple of its size:
 */
ASSERT(((ADDR(.vectors) & ((1<<LOG2CEIL(SIZEOF(.vectors)))-1)) == 0), "Section .vectors is not naturally aligned");

/* The following sections should either be not present in the input or else empty:
 *
 * .interp .hash .gnu.hash .dynsym .dynstr .gnu.version* .gnu.warning .exception_ranges
 * .rel.* .rela.* .plt .got .got.plt .dynamic .dynbss .dynsbss .data.rel.ro* .gnu.linkonce.d.rel.ro*
 * .iplt .igot .igot.plt .glue_7t .glue_7 .vfp11_veneer .v4_bx .jcr .svc_table
 * .tdata .tdata.* .gnu.linkonce.td.* .tbss .tbss.* .gnu.linkonce.tb.* .tcommon .shdata .shbss
 *
 * If one of these (or any other unexpected section) is non-empty, it is an error:
 */
ASSERT((__should_be_empty_start == __should_be_empty_end), "Non-empty unexpected input section");


/******************************************************************************/
/*******         SYMBOLS                                                  *****/
/******************************************************************************/

/* Execution start address:
 */
ENTRY(Reset_Handler)

/* Symbols for multi-bank startup
 *
 */
_vectors_addr = ADDR(.vectors);
_vectors_load = LOADADDR(.vectors);
_vectors_size = SIZEOF(.vectors);

_text0_addr = ADDR(.text0);
_text0_load = LOADADDR(.text0);
_text0_size = SIZEOF(.text0);

_rodata0_addr = ADDR(.rodata0);
_rodata0_load = LOADADDR(.rodata0);
_rodata0_size = SIZEOF(.rodata0);

_data0_addr = ADDR(.data0);
_data0_load = LOADADDR(.data0);
_data0_size = SIZEOF(.data0);

_data1_addr = ADDR(.data1);
_data1_load = LOADADDR(.data1);
_data1_size = SIZEOF(.data1);

_bss0_addr = ADDR(.bss0);
_bss0_size = SIZEOF(.bss0);

_bss1_addr = ADDR(.bss1);
_bss1_size = SIZEOF(.bss1);

/* CMSIS symbols for stack:
 */
__StackLimit = ADDR(.stack);
__StackTop   = (ORIGIN(DTCMRAM) + LENGTH(DTCMRAM));
__STACK_SIZE = (__StackTop - __StackLimit);

/* ST symbols for stack:
 */
_stack  = __StackLimit;
_estack = __StackTop;

/* CMSIS symbols for heap:
 */
__HeapBase  = ADDR(.heap);
__HeapLimit = (ORIGIN(D1SRAM) + LENGTH(D1SRAM));
__HEAP_SIZE = (__HeapLimit - __HeapBase);

/* Traditional symbols for heap:
 */
_end = __HeapBase;
PROVIDE(end = _end);
