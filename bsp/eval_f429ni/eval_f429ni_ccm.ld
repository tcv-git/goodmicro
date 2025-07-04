/* eval_f429ni_ccm.ld */
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
  ROM    (rx)  : ORIGIN = 0x08000000, LENGTH =   2M
  CCMRAM (rw)  : ORIGIN = 0x10000000, LENGTH =  64K
  SRAM   (rwx) : ORIGIN = 0x20000000, LENGTH = 192K
  EXTRAM (rwx) : ORIGIN = 0xC0000000, LENGTH =  32M
}

_Min_Stack_Size = 8K;
_Min_Heap_Size  = 8K;

SECTIONS
{
  /****************************************************************************/
  /*****        INTERNAL FLASH ROM                                        *****/
  /****************************************************************************/

  .vectors :
  {
    KEEP(*(.vectors))
    KEEP(*(.isr_vector))
    . = .; /* assignment forces output section to exist even if empty */
  }
  >ROM

  .init :
  {
    KEEP (*(SORT_NONE(.init)))
  }
  >ROM

  .text :
  {
    *(.text .text.* .stub .gnu.linkonce.t.*)
  }
  >ROM

  .fini :
  {
    KEEP (*(SORT_NONE(.fini)))
  }
  >ROM

  .tm_clone_table :
  {
    *(.tm_clone_table)
  }
  >ROM

  .preinit_array :
  {
    PROVIDE_HIDDEN (__preinit_array_start = .);
    KEEP (*(.preinit_array))
    PROVIDE_HIDDEN (__preinit_array_end = .);
  }
  >ROM

  .init_array :
  {
    PROVIDE_HIDDEN (__init_array_start = .);
    KEEP (*(SORT_BY_INIT_PRIORITY(.init_array.*) SORT_BY_INIT_PRIORITY(.ctors.*)))
    KEEP (*(.init_array EXCLUDE_FILE (*crtbegin.o *crtbegin?.o *crtend.o *crtend?.o ) .ctors))
    PROVIDE_HIDDEN (__init_array_end = .);
  }
  >ROM

  .fini_array :
  {
    PROVIDE_HIDDEN (__fini_array_start = .);
    KEEP (*(SORT_BY_INIT_PRIORITY(.fini_array.*) SORT_BY_INIT_PRIORITY(.dtors.*)))
    KEEP (*(.fini_array EXCLUDE_FILE (*crtbegin.o *crtbegin?.o *crtend.o *crtend?.o ) .dtors))
    PROVIDE_HIDDEN (__fini_array_end = .);
  }
  >ROM

  .ctors :
  {
    KEEP (*crtbegin.o(.ctors))
    KEEP (*crtbegin?.o(.ctors))
    KEEP (*(EXCLUDE_FILE (*crtend.o *crtend?.o ) .ctors))
    KEEP (*(SORT(.ctors.*)))
    KEEP (*(.ctors))
  }
  >ROM

  .dtors :
  {
    KEEP (*crtbegin.o(.dtors))
    KEEP (*crtbegin?.o(.dtors))
    KEEP (*(EXCLUDE_FILE (*crtend.o *crtend?.o ) .dtors))
    KEEP (*(SORT(.dtors.*)))
    KEEP (*(.dtors))
  }
  >ROM

  .ARM.extab :
  {
    *(.ARM.extab* .gnu.linkonce.armextab.*)
  }
  >ROM

  .ARM.exidx :
  {
    PROVIDE_HIDDEN (__exidx_start = .);
    *(.ARM.exidx* .gnu.linkonce.armexidx.*)
    PROVIDE_HIDDEN (__exidx_end = .);
  }
  >ROM

  .eh_frame_hdr :
  {
    *(.eh_frame_hdr)
    *(.eh_frame_entry .eh_frame_entry.*)
  }
  >ROM

  .eh_frame :
  {
    KEEP (*(.eh_frame))
    *(.eh_frame.*)
  }
  >ROM

  .gcc_except_table :
  {
    *(.gcc_except_table .gcc_except_table.*)
  }
  >ROM

  .gnu_extab :
  {
    *(.gnu_extab*)
  }
  >ROM

  .rodata :
  {
    *(.rodata .rodata.* .gnu.linkonce.r.*)
    *(.rodata1)
  }
  >ROM


  /****************************************************************************/
  /*****        MAIN INTERNAL SRAM (dma-accessible)                       *****/
  /****************************************************************************/

  .sram_data :
  {
    *(.sram_data .sram_data.*)
    . = .;
  }
  >SRAM AT>ROM

  .sram_bss (NOLOAD) :
  {
    *(.sram_bss .sram_bss.*)
    . = .;
  }
  >SRAM

  .sram_uninit (NOLOAD) :
  {
    *(.sram_uninit .sram_uninit.*)
  }
  >SRAM


  /****************************************************************************/
  /*****        INTERNAL CORE-COUPLED SRAM (not dma-accessible)           *****/
  /****************************************************************************/

  .stack (NOLOAD) : ALIGN(8)
  {
    *(.stack .stack.*)
    . = (. < _Min_Stack_Size ? _Min_Stack_Size : .);
    . = ALIGN(8);
  }
  >CCMRAM

  .data :
  {
    *(.ccm_data .ccm_data.*)
    *(.data .data.* .gnu.linkonce.d.*)
    *(.sdata .sdata.* .gnu.linkonce.s.*)
    *(.data1)
    . = .;
  }
  >CCMRAM AT>ROM

  .bss (NOLOAD) :
  {
    *(.ccm_bss .ccm_bss.*)
    *(.bss .bss.* .gnu.linkonce.b.*)
    *(COMMON)
    *(.sbss .sbss.* .scommon)
    . = .;
  }
  >CCMRAM

  .ccm_uninit (NOLOAD) :
  {
    *(.ccm_uninit .ccm_uninit.*)
  }
  >CCMRAM

  .heap (NOLOAD) : ALIGN(8)
  {
    *(.heap .heap.*)
    . = (. < _Min_Heap_Size ? _Min_Heap_Size : .);
  }
  >CCMRAM


  /****************************************************************************/
  /*****        EXTERNAL RAM (dma-accessible)                             *****/
  /****************************************************************************/

  .ext_data :
  {
    *(.ext_data .ext_data.*)
    . = .;
  }
  >EXTRAM AT>ROM

  .ext_bss (NOLOAD) :
  {
    *(.ext_bss .ext_bss.*)
    . = .;
  }
  >EXTRAM

  .ext_uninit (NOLOAD) :
  {
    *(.ext_uninit .ext_uninit.*)
  }
  >EXTRAM


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
  >CCMRAM
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

/* CMSIS symbols for interrupt vector must be correct if defined in input:
 */
ASSERT((!DEFINED(__Vectors      )) || (__Vectors      == ADDR(.vectors)), "Symbol __Vectors is not at the start of section .vectors");
ASSERT((!DEFINED(__Vectors_Size )) || (__Vectors_Size == SIZEOF(.vectors)), "Symbol __Vectors_Size is not the size of section .vectors");
ASSERT((!DEFINED(__Vectors_End  )) || (__Vectors_End  == (__Vectors + __Vectors_Size)), "Symbol __Vectors_End is not equal to (__Vectors + __Vectors_Size)");

/* ST symbol for interrupt vector must be correct if defined in input:
 */
ASSERT((!DEFINED(g_pfnVectors)) || (g_pfnVectors == ADDR(.vectors)), "Symbol g_pfnVectors is not at the start of section .vectors");

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

/* CMSIS symbols for memory regions:
 */
__ROM_BASE = ORIGIN(ROM);
__ROM_SIZE = LENGTH(ROM);
__RAM_BASE = ORIGIN(CCMRAM);
__RAM_SIZE = LENGTH(CCMRAM);

/* Execution start address:
 */
ENTRY(Reset_Handler)

/* CMSIS symbols for interrupt vector are provided if not defined in input:
 */
PROVIDE(__Vectors      = ADDR(.vectors));
PROVIDE(__Vectors_Size = SIZEOF(.vectors));
PROVIDE(__Vectors_End  = (__Vectors + __Vectors_Size));

/* Symbols for multi-bank startup:
 */
_ccm_data_addr = ADDR(.data);
_ccm_data_size = SIZEOF(.data);
_ccm_data_load = LOADADDR(.data);

_sram_data_addr = ADDR(.sram_data);
_sram_data_size = SIZEOF(.sram_data);
_sram_data_load = LOADADDR(.sram_data);

_ext_data_addr = ADDR(.ext_data);
_ext_data_size = SIZEOF(.ext_data);
_ext_data_load = LOADADDR(.ext_data);

_ccm_bss_addr = ADDR(.bss);
_ccm_bss_size = SIZEOF(.bss);

_sram_bss_addr = ADDR(.sram_bss);
_sram_bss_size = SIZEOF(.sram_bss);

_ext_bss_addr = ADDR(.ext_bss);
_ext_bss_size = SIZEOF(.ext_bss);

/* CMSIS symbols for start and end of data and bss:
 */
__data_start__ = ADDR(.data);
__data_end__   = (ADDR(.data) + SIZEOF(.data));
__bss_start__  = ADDR(.bss);
__bss_end__    = (ADDR(.bss) + SIZEOF(.bss));

/* Traditional symbols for start and end of data and bss:
 */
_sdata = __data_start__;
_edata = __data_end__;
_sbss  = __bss_start__;
_ebss  = __bss_end__;

/* Traditional symbol for load address of the contents of initialized data:
 */
_etext = LOADADDR(.data);

/* ST symbol for load address of the contents of initialized data:
 */
_sidata = LOADADDR(.data);

/* CMSIS symbols for stack:
 */
__StackLimit = ADDR(.stack);
__StackTop   = (ADDR(.stack) + SIZEOF(.stack));
__STACK_SIZE = (__StackTop - __StackLimit);

/* ST symbols for stack:
 */
_stack  = __StackLimit;
_estack = __StackTop;

/* CMSIS symbols for heap:
 */
__HeapBase  = ADDR(.heap);
__HeapLimit = (ORIGIN(CCMRAM) + LENGTH(CCMRAM));
__HEAP_SIZE = (__HeapLimit - __HeapBase);

/* Traditional symbols for heap:
 */
_end = __HeapBase;
PROVIDE(end = _end);
