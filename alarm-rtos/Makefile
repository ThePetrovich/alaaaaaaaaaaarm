# Project settings
TARG = alarm
MCU = atmega2560

# Libraries & includes
INCLUDES = -I"./include" -I "./cubesat-rtos/include"

# Project directories
SRCDIR = alarm
BUILDDIR = build
TARGDIR = bin

# Compiler & linker settings
CC = "C:\Program Files (x86)\Atmel\Studio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-gcc.exe"
ASM = "C:\Program Files (x86)\Atmel\Studio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-gcc.exe"
AR = "C:\Program Files (x86)\Atmel\Studio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-ar.exe"

# AVR-specific tool settings
OBJCOPY_CMD = "C:\Program Files (x86)\Atmel\Studio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-objcopy.exe"
OBJDUMP_CMD = "C:\Program Files (x86)\Atmel\Studio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-objdump.exe"
AVR_SIZE_CMD = "C:\Program Files (x86)\Atmel\Studio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-size.exe"

# Host platform settings
RM_CMD = C:/Tools/Coreutils/bin/rm -rf
MKDIR_CMD = C:/Tools/Coreutils/bin/mkdir.exe -p
COPY_CMD = C:/Tools/Coreutils/bin/cp.exe

VERSION_SEMANTIC = 0.0.1
VERSION_GIT_HASH = `git rev-parse HEAD | cut -c1-8`
VERSION_GIT_BRANCH = `git rev-parse --abbrev-ref HEAD`
VERSION_STRING = $(VERSION_SEMANTIC)-git-$(VERSION_GIT_BRANCH)-$(VERSION_GIT_HASH)
 
# Compiler & linker flags
CFLAGS = -x c -DDEBUG -DVERSION_STRING="\"$(VERSION_STRING)\"" $(INCLUDES) -Os -g2 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -mrelax -mmcu=$(MCU) -c -std=gnu99 -Wall -Wextra -Wpedantic
ASMFLAGS = -Wa,-gdwarf2 -x assembler-with-cpp -c -B -DDEBUG $(INCLUDES) -Os -g2 -mrelax -mmcu=$(MCU) -Wall -Wextra -Wpedantic 
LDFLAGS = -Wl,-static -Wl,-Map="$(TARGDIR)/$(TARG).map" -Wl,--gc-sections -mrelax -Wl,-section-start=.bootloader=0x3c000 -mmcu=$(MCU) -lm -L./cubesat-rtos -lrtos -Wall -Wextra -Wpedantic 

# AVR-specific tool flags
OBJCOPY_HEX_FLAGS = -O ihex -R .eeprom -R .fuse -R .lock -R .signature -R .user_signatures
OBJCOPY_EEP_FLAGS = -j .eeprom  --set-section-flags=.eeprom=alloc,load --change-section-lma .eeprom=0  --no-change-warnings -O ihex
OBJCOPY_SIGN_FLAGS = -j .user_signatures --set-section-flags=.user_signatures=alloc,load --change-section-lma .user_signatures=0 --no-change-warnings -O ihex
OBJCOPY_SREC_FLAGS = -O srec -R .eeprom -R .fuse -R .lock -R .signature -R .user_signatures
OBJDUMP_LSS_FLAGS = -h -S

#-------------------------------------------------------------------------------
# DO NOT EDIT BELOW THIS LINE
#-------------------------------------------------------------------------------

# Recursive makefile wildcard
# https://stackoverflow.com/a/12959764
rwildcard=$(wildcard $(addsuffix $2, $1)) $(foreach d,$(wildcard $(addsuffix *, $1)),$(call rwildcard,$d/,$2))

# Automatically find all source files
SRCS = $(call rwildcard, $(SRCDIR)/,*.c)
ASM_SRCS = $(call rwildcard, $(SRCDIR)/,*.S)

# Generate build directory structure
DIRS = $(addprefix $(BUILDDIR)/,$(dir $(SRCS)))

# Generate list of objects
OBJS = $(addprefix $(BUILDDIR)/,$(SRCS:.c=.o)) $(addprefix $(BUILDDIR)/,$(ASM_SRCS:.S=.o))
 
all: dirs $(SUBDIRS) $(TARG)

# Create build directories
dirs:
	$(MKDIR_CMD) $(BUILDDIR)
	$(MKDIR_CMD) $(TARGDIR)

ifneq ($(strip $(DIRS)),)
	$(MKDIR_CMD) $(DIRS)
endif

rtos:
	make -C cubesat-rtos arch=avr mcu=atmega2560

# Compile target
$(TARG):  rtos $(OBJS)
	$(CC) -o $(TARGDIR)/$@.elf $(OBJS) $(OBJS) $(LDFLAGS)
	$(OBJCOPY_CMD)  $(OBJCOPY_HEX_FLAGS) "$(TARGDIR)/$(TARG).elf" "$(TARGDIR)/$(TARG).hex"
	$(OBJCOPY_CMD)  $(OBJCOPY_EEP_FLAGS) "$(TARGDIR)/$(TARG).elf" "$(TARGDIR)/$(TARG).eep" || exit 0
	$(OBJDUMP_CMD)  $(OBJDUMP_LSS_FLAGS) "$(TARGDIR)/$(TARG).elf" > "$(TARGDIR)/$(TARG).lss"
	$(OBJCOPY_CMD)  $(OBJCOPY_SREC_FLAGS) "$(TARGDIR)/$(TARG).elf" "$(TARGDIR)/$(TARG).srec"
	$(OBJCOPY_CMD)  $(OBJCOPY_SIGN_FLAGS) "$(TARGDIR)/$(TARG).elf" "$(TARGDIR)/$(TARG).usersignatures" || exit 0
	$(AVR_SIZE_CMD) "$(TARGDIR)/$(TARG).elf"
	$(COPY_CMD) "$(TARGDIR)/$(TARG).elf" "./$(TARG).elf"

# Compile objects
$(BUILDDIR)/%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

$(BUILDDIR)/%.o: %.S
	$(ASM) $(ASMFLAGS) -c -o $@ $<

# Clean
cleandirs:
	$(RM_CMD) $(TARGDIR) $(BUILDDIR)

cleanobjs:
	$(RM_CMD) $(OBJS)

cleanmisc:
	$(RM_CMD) $(TARGDIR)/$(TARG).map $(TARGDIR)/$(TARG).usersignatures $(TARGDIR)/$(TARG).srec $(TARGDIR)/$(TARG).lss $(TARGDIR)/$(TARG).eep

clean: cleanobjs cleanmisc cleandirs
	$(RM_CMD) $(TARGDIR)/$(TARG).elf $(TARG).elf $(TARGDIR)/$(TARG).bin $(TARGDIR)/$(TARG).hex
	make -C cubesat-rtos clean