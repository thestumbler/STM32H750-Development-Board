#define MICROPY_HW_BOARD_NAME       "ALIMAN_STM32H750VBTX"
#define MICROPY_HW_MCU_NAME         "STM32H7XX"
#define MICROPY_HW_FLASH_FS_LABEL   "ALIMAN_H7XX_M"
#define MICROPY_PY_SYS_PLATFORM     "aliman"

#define MICROPY_HW_HAS_SWITCH       (0)		// no user switches except RESET
#define MICROPY_HW_HAS_FLASH        (1)
#define MICROPY_HW_ENABLE_RNG       (1)
#define MICROPY_HW_ENABLE_RTC       (1)
#define MICROPY_HW_ENABLE_DAC       (1)
#define MICROPY_HW_ENABLE_USB       (1)
#define MICROPY_HW_ENABLE_SDCARD    (1)		// it has a sd scard, but no detect pin

// The board has an 8MHz HSE, the following gives 480MHz CPU speed
// VCOClock = HSE * PLLN / PLLM = 8 MHz * 480 / 4 = 960 MHz
// SYSCLK = VCOClock / PLLP = 960 MHz / 2 = 480 MHz
#define MICROPY_HW_CLK_PLLM (4) 
#define MICROPY_HW_CLK_PLLN (480) // PLL clock in MHz
#define MICROPY_HW_CLK_PLLP (2) // divide PLL clock by this to get core clock
#define MICROPY_HW_CLK_PLLQ (4)
#define MICROPY_HW_CLK_PLLR (2)

// USB clock uses PLL3
#define MICROPY_HW_CLK_PLL3M (4)
#define MICROPY_HW_CLK_PLL3N (120)
#define MICROPY_HW_CLK_PLL3P (2)
#define MICROPY_HW_CLK_PLL3Q (5)
#define MICROPY_HW_CLK_PLL3R (2)

// 4 wait states
#define MICROPY_HW_FLASH_LATENCY    FLASH_LATENCY_4

// The board has a 32kHz crystal for the RTC
// #define MICROPY_HW_RTC_USE_LSE      (1)
// #define MICROPY_HW_RTC_USE_US       (0)
// #define MICROPY_HW_RTC_USE_CALOUT   (1)  // turn on/off PC13 512Hz output

// SPI 128Mb flash for filesystem storage
//#define MICROPY_HW_SOFTQSPI_SCK_LOW(self) (GPIOE->BSRR = (0x10000 << 11))
//#define MICROPY_HW_SOFTQSPI_SCK_HIGH(self) (GPIOE->BSRR = (1 << 11))
//#define MICROPY_HW_SOFTQSPI_NIBBLE_READ(self) ((GPIOE->IDR >> 7) & 0xf)
#define MICROPY_HW_QSPIFLASH_SIZE_BITS_LOG2 (27)
#define MICROPY_HW_QSPIFLASH_CS     (pin_B10)
#define MICROPY_HW_QSPIFLASH_SCK    (pin_B2)
#define MICROPY_HW_QSPIFLASH_IO0    (pin_D11)
#define MICROPY_HW_QSPIFLASH_IO1    (pin_D12)
#define MICROPY_HW_QSPIFLASH_IO2    (pin_E2)
#define MICROPY_HW_QSPIFLASH_IO3    (pin_A1)

extern const struct _mp_spiflash_config_t spiflash_config;
extern struct _spi_bdev_t spi_bdev;

#define MICROPY_HW_SPIFLASH_SIZE_BITS (128*1024*1024)
#define MICROPY_HW_ENABLE_INTERNAL_FLASH_STORAGE (0)
#define MICROPY_HW_SPIFLASH_ENABLE_CACHE (1)
#define MICROPY_HW_BDEV_IOCTL(op, arg) ( \
    (op) == BDEV_IOCTL_NUM_BLOCKS ? (MICROPY_HW_SPIFLASH_SIZE_BITS / 8 / FLASH_BLOCK_SIZE) : \
    (op) == BDEV_IOCTL_INIT ? spi_bdev_ioctl(&spi_bdev, (op), (uint32_t)&spiflash_config) : \
    spi_bdev_ioctl(&spi_bdev, (op), (arg)) \
)
#define MICROPY_HW_BDEV_READBLOCKS(dest, bl, n) spi_bdev_readblocks(&spi_bdev, (dest), (bl), (n))
#define MICROPY_HW_BDEV_WRITEBLOCKS(src, bl, n) spi_bdev_writeblocks(&spi_bdev, (src), (bl), (n))
#define MICROPY_HW_BDEV_SPIFLASH_EXTENDED (&spi_bdev) // for extended block protocol


// USART1
#define MICROPY_HW_UART1_TX     (pin_B14)  // A9,B6,B14
#define MICROPY_HW_UART1_RX     (pin_B15) // A10,B7,B15
// USART1_CK   A8
// USART1_CTS  A11
// USART1_NSS  A11
// USART1_RTS  A12

// USART2
// #define MICROPY_HW_UART2_TX     (pin_A2) // A2,D5
// #define MICROPY_HW_UART2_RX     (pin_A3) // A3,D6
// USART2_CTS  A0,D3
// USART2_NSS  A0,D3
// USART2_RTS  A1,D4
// USART2_CK   A4,D7

// USART3
// #define MICROPY_HW_UART3_TX     (pin_D8) // B10,C10,D8
// #define MICROPY_HW_UART3_RX     (pin_D9) // B11,C11,D9
// USART3_NSS  B13,D11
// USART3_CTS  B13,D11
// USART3_RTS  B14,D12
// USART3_CK   B12,C12,D10

// UART4
// #define MICROPY_HW_UART4_TX     (pin_A0) // A0,A12,B9,C10,D1
// #define MICROPY_HW_UART4_RX     (pin_A1) // A1,A11,B8,C11,D0
// UART4_RTS  A15,B14
// UART4_CTS  B0,B15

// UART5
// #define MICROPY_HW_UART5_TX     (pin_C12) // B6,B13,C12
// #define MICROPY_HW_UART5_RX     (pin_D2)  // B5,B12,D2
// UART5_RTS  C8
// UART5_CTS  C9

// USART6
// #define MICROPY_HW_UART_TX      (pin_C6) // C6
// #define MICROPY_HW_UART_RX      (pin_C7) // C7
// USART6_CK  C8

// UART7
// #define MICROPY_HW_UART7_TX     (pin_E8) // A15,B4,E8
// #define MICROPY_HW_UART7_RX     (pin_E7) // A8,B3,E7
// UART7_RTS  E9
// UART7_CTS  E10

// UART8
// #define MICROPY_HW_UART8_TX     (pin_E1) // E1
// #define MICROPY_HW_UART8_RX     (pin_E0) // E0
// UART8_CTS  D14
// UART8_RTS  D15

// I2C busses
#define MICROPY_HW_I2C1_SCL (pin_B8) // B6,B8
#define MICROPY_HW_I2C1_SDA (pin_B9) // B7,B9

#define MICROPY_HW_I2C2_SCL (pin_B10) // B10
#define MICROPY_HW_I2C2_SDA (pin_B11) // B11

#define MICROPY_HW_I2C3_SCL (pin_A8) // A8
#define MICROPY_HW_I2C3_SDA (pin_C9) // C9

#define MICROPY_HW_I2C4_SCL (pin_B6) // B6,B8,D12
#define MICROPY_HW_I2C4_SDA (pin_B7) // B7,D13

// SPI busses
#define MICROPY_HW_SPI1_NSS  (pin_A4) // A4,A15
#define MICROPY_HW_SPI1_SCK  (pin_A5) // A5,B3
#define MICROPY_HW_SPI1_MISO (pin_A6) // A6,B4
#define MICROPY_HW_SPI1_MOSI (pin_A7) // A7,B5,D7

#define MICROPY_HW_SPI2_NSS  (pin_B12) // A11,B4,B9,B12
#define MICROPY_HW_SPI2_SCK  (pin_B13) // A9,A12,B10,B13,D3
#define MICROPY_HW_SPI2_MISO (pin_B14) // B14,C2
#define MICROPY_HW_SPI2_MOSI (pin_B15) // B15,C1,C3

#define MICROPY_HW_SPI3_NSS  (pin_A15) // A4,A15
#define MICROPY_HW_SPI3_SCK  (pin_B3)  // B3,C10
#define MICROPY_HW_SPI3_MISO (pin_B4)  // B4,C11
#define MICROPY_HW_SPI3_MOSI (pin_B2)  // B2,B5,C12,D6

#define MICROPY_HW_SPI4_NSS  (pin_E4) // E4,E11
#define MICROPY_HW_SPI4_SCK  (pin_E2) // E2,E12
#define MICROPY_HW_SPI4_MISO (pin_E5) // E5,E13
#define MICROPY_HW_SPI4_MOSI (pin_E6) // E6,E14

// no SPI5

#define MICROPY_HW_SPI6_NSS  (pin_A4) // A4,A15
#define MICROPY_HW_SPI6_SCK  (pin_A5) // A5,B3
#define MICROPY_HW_SPI6_MISO (pin_A6) // A6,B4
#define MICROPY_HW_SPI6_MOSI (pin_A7) // A7,B5

// CAN busses
#define MICROPY_HW_CAN1_TX (pin_B9) // A12,B9,D1
#define MICROPY_HW_CAN1_RX (pin_B8) // A11,B8,D0

// K0 has no pullup or pulldown; Pressing the button makes the input go low.
// #define MICROPY_HW_USRSW_PIN        (pin_E3)
// #define MICROPY_HW_USRSW_PULL       (GPIO_PULLUP)
// #define MICROPY_HW_USRSW_EXTI_MODE  (GPIO_MODE_IT_FALLING)
// #define MICROPY_HW_USRSW_PRESSED    (0)

// LEDs
// LED D2 is the power LED and always on
#define MICROPY_HW_LED1             (pin_C15)  // LED D2
#define MICROPY_HW_LED_ON(pin)      (mp_hal_pin_high(pin))
#define MICROPY_HW_LED_OFF(pin)     (mp_hal_pin_low(pin))

// SD card detect switch
#define MICROPY_HW_SDCARD_DETECT_PIN        (pin_C13)
#define MICROPY_HW_SDCARD_DETECT_PULL       (GPIO_PULLUP)
#define MICROPY_HW_SDCARD_DETECT_PRESENT    (GPIO_PIN_RESET)
// 1  PC10 - DAT2/RES
// 2  PC11 - CD/DAT3/CS
// 3  PD2  - CMD/DI
// 4  VCC  - VDD
// 5  PC12 - CLK/SCLK
// 6  GND  - VSS
// 7  PC8  - DAT0/D0
// 8  PC9  - DAT1/RES
// 9  SW2 - NC

// USB config
#define MICROPY_HW_USB_FS (1)
// #define MICROPY_HW_USB_VBUS_DETECT_PIN (pin_A9)
#define MICROPY_HW_USB_OTG_ID_PIN      (pin_A10)
