USE_MBOOT ?= 0

MCU_SERIES = h7
CMSIS_MCU = STM32H743xx
MICROPY_FLOAT_IMPL = double
AF_FILE = boards/stm32h743_af.csv

ifeq ($(USE_MBOOT),1)
####    # When using Mboot all the text goes together after the filesystem
LD_FILES = boards/stm32h743.ld boards/common_blifs.ld
CMSIS_MCU = STM32H750xx
AF_FILE = boards/stm32h750_af.csv 
else
# When not using Mboot the ISR text goes first, then the rest after the filesystem
LD_FILES = boards/stm32h743.ld boards/common_ifs.ld
TEXT0_ADDR = 0x08000000
TEXT1_ADDR = 0x08040000
endif

# MicroPython settings
MICROPY_PY_LWIP = 1
MICROPY_PY_USSL = 1
MICROPY_SSL_MBEDTLS = 1
MICROPY_VFS_LFS2 = 1



####    ### This is NUCLEO H7
####    
####    USE_MBOOT ?= 0
####    
####    # MCU settings
####    MCU_SERIES = h7
####    CMSIS_MCU = STM32H743xx
####    MICROPY_FLOAT_IMPL = double
####    AF_FILE = boards/stm32h743_af.csv
####    
####    ifeq ($(USE_MBOOT),1)
####    # When using Mboot all the text goes together after the filesystem
####    LD_FILES = boards/stm32h743.ld boards/common_blifs.ld
####    TEXT0_ADDR = 0x08040000
####    else
####    # When not using Mboot the ISR text goes first, then the rest after the filesystem
####    LD_FILES = boards/stm32h743.ld boards/common_ifs.ld
####    LD_FILES = boards/PYBD_SF2/f722_qspi.ld
####    TEXT0_ADDR = 0x08000000
####    TEXT1_ADDR = 0x08040000
####    endif
####    
####    # MicroPython settings
####    MICROPY_PY_LWIP = 1
####    MICROPY_PY_USSL = 1
####    MICROPY_SSL_MBEDTLS = 1
####    
####    
####    
####    ### This is PYBD_SF2
####    
####    # MCU settings
####    MCU_SERIES = f7
####    CMSIS_MCU = STM32F722xx
####    MICROPY_FLOAT_IMPL = single
####    AF_FILE = boards/stm32f722_af.csv
####    LD_FILES = boards/PYBD_SF2/f722_qspi.ld
####    TEXT0_ADDR = 0x08008000
####    TEXT1_ADDR = 0x90000000
####    TEXT0_SECTIONS = .isr_vector .text .data .ARM
####    TEXT1_SECTIONS = .text_ext
####    
####    # MicroPython settings
####    MICROPY_PY_BLUETOOTH ?= 1
####    MICROPY_BLUETOOTH_NIMBLE ?= 1
####    MICROPY_BLUETOOTH_BTSTACK ?= 0
####    MICROPY_PY_LWIP = 1
####    MICROPY_PY_NETWORK_CYW43 = 1
####    MICROPY_PY_USSL = 1
####    MICROPY_SSL_MBEDTLS = 1
####    MICROPY_VFS_LFS2 = 1
####    
####    # PYBD-specific frozen modules
####    FROZEN_MANIFEST = $(BOARD_DIR)/manifest.py
