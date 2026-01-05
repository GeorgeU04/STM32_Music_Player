#######################################################################
# STM32H7 + LVGL Makefile
#######################################################################

TARGET = Music_Player_CM7
BUILD_DIR = build
DEBUG = 1
OPT = -Og

PREFIX = arm-none-eabi-
CC = $(PREFIX)gcc
AS = $(PREFIX)gcc -x assembler-with-cpp
CP = $(PREFIX)objcopy
SZ = $(PREFIX)size
HEX = $(CP) -O ihex
BIN = $(CP) -O binary -S

CPU = -mcpu=cortex-m7
FPU = -mfpu=fpv5-d16
FLOAT_ABI = -mfloat-abi=hard
MCU = $(CPU) -mthumb $(FPU) $(FLOAT_ABI)

C_DEFS = -DCORE_CM7 -DUSE_HAL_DRIVER -DSTM32H755xx -DUSE_PWR_DIRECT_SMPS_SUPPLY -DUSE_NUCLEO_144
C_INCLUDES = \
-I../../CM7/Core/Inc \
-I../../Drivers/STM32H7xx_HAL_Driver/Inc \
-I../../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy \
-I../../Drivers/BSP/STM32H7xx_Nucleo \
-I../../Drivers/CMSIS/Device/ST/STM32H7xx/Include \
-I../../Drivers/CMSIS/Include

CFLAGS = $(MCU) $(C_DEFS) $(C_INCLUDES) $(OPT) -Wall -fdata-sections -ffunction-sections
ASFLAGS = $(MCU) $(OPT) -Wall -fdata-sections -ffunction-sections

ifeq ($(DEBUG),1)
CFLAGS += -g -gdwarf-2
endif

CFLAGS += -MMD -MP

LDSCRIPT = stm32h755xx_flash_CM7.ld
LIBS = -lc -lm -lnosys
LDFLAGS = $(MCU) -specs=nano.specs -T$(LDSCRIPT) -Wl,-Map=$(BUILD_DIR)/$(TARGET).map,--cref -Wl,--gc-sections $(LIBS)

##########################################################
# LVGL
##########################################################
LVGL_PATH := ../../Drivers/lvgl
include $(LVGL_PATH)/lvgl.mk

# Add LVGL include path
CFLAGS += -I$(LVGL_PATH)
ASFLAGS += -I$(LVGL_PATH)

##########################################################
# Sources
##########################################################
# Project C sources
C_SOURCES := \
../../CM7/Core/Src/main.c \
../../CM7/Core/Src/stm32h7xx_it.c \
../../CM7/Core/Src/stm32h7xx_hal_msp.c \
../../Drivers/BSP/STM32H7xx_Nucleo/stm32h7xx_nucleo.c \
../../Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_cortex.c \
../../Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_rcc.c \
../../Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_rcc_ex.c \
../../Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_flash.c \
../../Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_flash_ex.c \
../../Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_gpio.c \
../../Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_hsem.c \
../../Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_dma.c \
../../Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_dma_ex.c \
../../Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_mdma.c \
../../Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_pwr.c \
../../Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_pwr_ex.c \
../../Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal.c \
../../Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_i2c.c \
../../Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_i2c_ex.c \
../../Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_exti.c \
../../Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_spi.c \
../../Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_spi_ex.c \
../../Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_tim.c \
../../Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_tim_ex.c \
../../Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_usart.c \
../../Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_usart_ex.c \
../../Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_uart_ex.c \
../../Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_uart.c \
../../Common/Src/system_stm32h7xx_dualcore_boot_cm4_cm7.c \
../../CM7/Core/Src/sysmem.c \
../../CM7/Core/Src/syscalls.c \
../../CM7/Core/Src/ILI9341.c \
../../CM7/Core/Src/lv_port_disp.c

# Combine project + LVGL sources
C_SOURCES += $(CSRCS)
AS_SOURCES  = $(ASRCS)
CXX_SOURCES = $(CXXSRCS)

##########################################################
# Objects
##########################################################
OBJECTS := $(C_SOURCES)
OBJECTS := $(patsubst %,$(BUILD_DIR)/%,$(OBJECTS))
OBJECTS := $(OBJECTS:.c=.o)

OBJECTS += $(patsubst %,$(BUILD_DIR)/%,$(AS_SOURCES:.S=.o))
OBJECTS += $(BUILD_DIR)/startup_stm32h755xx_CM7.o

vpath %.c $(sort $(dir $(C_SOURCES)))
vpath %.S $(sort $(dir $(AS_SOURCES)))
vpath %.cpp $(sort $(dir $(CXX_SOURCES)))

##########################################################
# Build rules
##########################################################
all: $(BUILD_DIR)/$(TARGET).elf $(BUILD_DIR)/$(TARGET).hex $(BUILD_DIR)/$(TARGET).bin

# C compile
$(BUILD_DIR)/%.o: %.c | $(BUILD_DIR)
	@mkdir -p $(dir $@)
	$(CC) -c $(CFLAGS) $< -o $@

# C++ compile
$(BUILD_DIR)/%.o: %.cpp | $(BUILD_DIR)
	@mkdir -p $(dir $@)
	$(CC) -c $(CXXFLAGS) $< -o $@

# ASM compile
$(BUILD_DIR)/%.o: %.S | $(BUILD_DIR)
	@mkdir -p $(dir $@)
	$(AS) -c $(ASFLAGS) $< -o $@

# Startup ASM
$(BUILD_DIR)/startup_stm32h755xx_CM7.o: startup_stm32h755xx_CM7.s | $(BUILD_DIR)
	$(AS) -c $(ASFLAGS) $< -o $@

# Link
$(BUILD_DIR)/$(TARGET).elf: $(OBJECTS)
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@
	$(SZ) $@

# HEX / BIN
$(BUILD_DIR)/%.hex: $(BUILD_DIR)/%.elf
	$(HEX) $< $@

$(BUILD_DIR)/%.bin: $(BUILD_DIR)/%.elf
	$(BIN) $< $@

# Build dir
$(BUILD_DIR):
	mkdir -p $@

flash: $(BUILD_DIR)/$(TARGET).bin
	st-flash write $< 0x8000000

clean:
	rm -rf $(BUILD_DIR)

# Dependencies
-include $(wildcard $(BUILD_DIR)/**/*.d)

