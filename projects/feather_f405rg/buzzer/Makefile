#
#  Goodmicro embedded project Makefile
#  PUBLIC DOMAIN
#  https://www.purposeful.co.uk/goodmicro/
#

MAKEFLAGS := --no-builtin-rules --no-builtin-variables


#################### INPUT DEFINITIONS #########################################

# NB: there cannot be two input files with the same basename
# (eg: foo1/bar.c and foo2/bar.S is not supported)

# input for assembler
ASFILES :=
ASFILES += ../../../lib/goodmicro_armv7m/_exit.s
ASFILES += ../../../lib/goodmicro_armv7m/delay_cyccnt_168MHz.s
ASFILES += ../../../lib/goodmicro_armv7m/udiv64.s
ASFILES += ../../../lib/goodmicro_stm32f4/startup/startup_stm32f405-439.s
ASFILES += ../../../lib/goodmicro_stm32f4/vectors/vectors_stm32f405xx.s

# input for C compiler
CFILES :=
CFILES += ../../../bsp/feather_f405rg/buzzer.c
CFILES += ../../../lib/goodmicro_stm32f4/system_stm32f405-439.c
CFILES += main.c

# input for C++ compiler
CXXFILES :=

# header incude path (gets added to CPPFLAGS)
INCLUDE_PATH :=
INCLUDE_PATH += ../../../bsp/feather_f405rg
INCLUDE_PATH += ../../../lib/goodmicro_stm32f4
INCLUDE_PATH += ../../../lib/goodmicro_armv7m
INCLUDE_PATH += ../../../lib/goodmicro_cortexm
INCLUDE_PATH += ../../../lib/Device_STM32F4xx/Include
INCLUDE_PATH += ../../../lib/CMSIS/Include

# binary library search path (gets added to LDFLAGS)
LIBRARY_PATH :=

# library names for linker (for libfoo.o just write foo)
LDLIBS :=
LDLIBS += m

# linker control script
LINK_SCRIPT := ../../../lib/goodmicro_stm32f4/linker/stm32f405xGxx_ccm.ld


#################### OUTPUT DEFINITIONS ########################################

OBJDIR := objects
OUTDIR := output
BINARY := program


#################### TOOL DEFINITIONS ##########################################

CROSS_COMPILE := arm-none-eabi-

AS  := $(CROSS_COMPILE)gcc
CC  := $(CROSS_COMPILE)gcc
CXX := $(CROSS_COMPILE)g++
LD  := $(CROSS_COMPILE)$(if $(CXXFILES),g++,gcc)

# flags for assembler, compiler and linker
COMMON_FLAGS :=
COMMON_FLAGS += -mthumb
COMMON_FLAGS += -mcpu=cortex-m4
COMMON_FLAGS += -mfloat-abi=hard
COMMON_FLAGS += -mfpu=fpv4-sp-d16
COMMON_FLAGS += -fmessage-length=0
COMMON_FLAGS += -fno-diagnostics-show-option
COMMON_FLAGS += -fno-diagnostics-show-caret

# C pre-processor flags (for both .c and .S files)
# NB: inlude path goes under INPUT DEFINITIONS above
CPPFLAGS :=
CPPFLAGS += -DSTM32F405xx
CPPFLAGS += -D__PROGRAM_START=Reset_Handler
CPPFLAGS += $(foreach IDIR, $(INCLUDE_PATH), -I $(IDIR))

# flags for assembler
# NB: invoked as "gcc -x assembler-with-cpp" not as "as" directly
ASFLAGS :=
ASFLAGS += $(COMMON_FLAGS)
ASFLAGS += $(CPPFLAGS)
ASFLAGS += -x assembler-with-cpp
ASFLAGS += -MMD

# flags for C compiler
CFLAGS :=
CFLAGS += $(COMMON_FLAGS)
CFLAGS += $(CPPFLAGS)
CFLAGS += -MMD
CFLAGS += -x c
CFLAGS += -std=gnu99
CFLAGS += -O3
CFLAGS += -g
CFLAGS += -fwrapv
CFLAGS += -fno-exceptions
CFLAGS += -fno-strict-aliasing
CFLAGS += -fno-common
CFLAGS += -ffunction-sections
CFLAGS += -fdata-sections
CFLAGS += -Wall
CFLAGS += -Wunknown-pragmas
CFLAGS += -Wsign-compare
CFLAGS += -Wimplicit-fallthrough=2
CFLAGS += -Wmissing-prototypes
CFLAGS += -Wignored-qualifiers
CFLAGS += -Waggregate-return
CFLAGS += -Wrestrict
CFLAGS += -Wnested-externs
CFLAGS += -Wshadow
CFLAGS += -Werror=pointer-arith
CFLAGS += -Werror=init-self
CFLAGS += -Werror=implicit
CFLAGS += -Werror=strict-prototypes

# flags for C++ compiler
CXXFLAGS :=
CXXFLAGS += $(COMMON_FLAGS)
CXXFLAGS += $(CPPFLAGS)
CXXFLAGS += -MMD
CXXFLAGS += -x c++
CXXFLAGS += -std=gnu++14
CXXFLAGS += -O0
CXXFLAGS += -g
CXXFLAGS += -fwrapv
CXXFLAGS += -fno-exceptions
CXXFLAGS += -fno-rtti
CXXFLAGS += -fno-use-cxa-atexit
CXXFLAGS += -fno-threadsafe-statics
CXXFLAGS += -fno-strict-aliasing
CXXFLAGS += -fno-strict-enums
CXXFLAGS += -fno-common
CXXFLAGS += -ffunction-sections
CXXFLAGS += -fdata-sections
CXXFLAGS += -Wall
CXXFLAGS += -Wunknown-pragmas
CXXFLAGS += -Wsign-compare
CXXFLAGS += -Wimplicit-fallthrough=2
CXXFLAGS += -Wmissing-declarations
CXXFLAGS += -Wignored-qualifiers
CXXFLAGS += -Waggregate-return
CXXFLAGS += -Wrestrict
CXXFLAGS += -Wshadow
CXXFLAGS += -Werror=pointer-arith
CXXFLAGS += -Werror=init-self

# flags for linker
# NB: invoked as "gcc" or "g++" not "ld" directly
# NB: library names and library path go under INPUT DEFINITIONS above
LDFLAGS :=
LDFLAGS += $(COMMON_FLAGS)
LDFLAGS += --specs=nosys.specs
LDFLAGS += -T $(LINK_SCRIPT)
LDFLAGS += -Wl,-Map=$(OUTDIR)/$(BINARY).map
LDFLAGS += -Wl,--cref
LDFLAGS += -Wl,--gc-sections
LDFLAGS += $(foreach LDIR, $(LIBRARY_PATH), -L $(LDIR))


#################### DERIVED VARIABLES #########################################

OBJECTS := $(foreach FILE, $(ASFILES) $(CFILES) $(CXXFILES), $(OBJDIR)/$(basename $(notdir $(FILE))).o)


#################### MAKE TARGETS ##############################################

.PHONY : all size clean

all: $(OUTDIR)/$(BINARY).elf $(OUTDIR)/$(BINARY).hex $(OUTDIR)/$(BINARY).lss $(OUTDIR)/$(BINARY).sym

$(OBJECTS) : | $(OBJDIR)
$(OUTDIR)/$(BINARY).elf $(OUTDIR)/$(BINARY).hex $(OUTDIR)/$(BINARY).lss $(OUTDIR)/$(BINARY).sym : | $(OUTDIR)

$(OBJDIR) $(OUTDIR) :
	@mkdir -p $@

define ASFILE_TEMPLATE =
$$(OBJDIR)/$(basename $(notdir $(1))).o : $(1)
	@echo `basename "$$(AS)"` `basename "$$<"`
	@echo $$(AS) $$(ASFLAGS) -Wa,-adlns=$$(basename $$@).lst -c $$< -o $$@ >$$@.cmd
	@$$(AS) $$(ASFLAGS) -Wa,-adlns=$$(basename $$@).lst -c $$< -o $$@
endef

define CFILE_TEMPLATE =
$$(OBJDIR)/$(basename $(notdir $(1))).o : $(1)
	@echo `basename "$$(CC)"` `basename "$$<"`
	@echo $$(CC) $$(CFLAGS) -Wa,-adlns=$$(basename $$@).lst -c $$< -o $$@ >$$@.cmd
	@$$(CC) $$(CFLAGS) -Wa,-adlns=$$(basename $$@).lst -c $$< -o $$@
endef

define CXXFILE_TEMPLATE =
$$(OBJDIR)/$(basename $(notdir $(1))).o : $(1)
	@echo `basename "$$(CXX)"` `basename "$$<"`
	@echo $$(CXX) $$(CXXFLAGS) -Wa,-adlns=$$(basename $$@).lst -c $$< -o $$@ >$$@.cmd
	@$$(CXX) $$(CXXFLAGS) -Wa,-adlns=$$(basename $$@).lst -c $$< -o $$@
endef

$(foreach FILE, $(ASFILES),  $(eval $(call ASFILE_TEMPLATE,  $(FILE))))
$(foreach FILE, $(CFILES),   $(eval $(call CFILE_TEMPLATE,   $(FILE))))
$(foreach FILE, $(CXXFILES), $(eval $(call CXXFILE_TEMPLATE, $(FILE))))

-include $(OBJDIR)/*.d

$(OUTDIR)/$(BINARY).elf : $(OBJECTS)
	@echo `basename "$(LD)"` -o $@
	@echo $(LD) $(LDFLAGS) $(OBJECTS) $(foreach LIB, $(LDLIBS), -l$(LIB)) -o $@ >$@.cmd
	@$(LD) $(LDFLAGS) $(OBJECTS) $(foreach LIB, $(LDLIBS), -l$(LIB)) -o $@

size : $(OUTDIR)/$(BINARY).elf
	@$(CROSS_COMPILE)size -A $<

$(OUTDIR)/$(BINARY).hex : $(OUTDIR)/$(BINARY).elf
	@$(CROSS_COMPILE)objcopy -O ihex $< $@

$(OUTDIR)/$(BINARY).lss : $(OUTDIR)/$(BINARY).elf
	@$(CROSS_COMPILE)objdump -C -d -h -M reg-names-std -w -x $< >$@

$(OUTDIR)/$(BINARY).sym : $(OUTDIR)/$(BINARY).elf
	@$(CROSS_COMPILE)nm -C -S -n -t x $< >$@

clean :
	rm -rf $(OBJDIR) $(OUTDIR) 2>/dev/null


#################### HARDWARE TARGETS ##########################################

.PHONY : erase flash

erase :
	../../../scripts/erase_stm32f4_swd_srst

flash : $(OUTDIR)/$(BINARY).elf
	../../../scripts/program_stm32f4_swd_srst $<
