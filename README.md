# ADC-Peripheral-in-STM32F446RE

A comprehensive, register-level C program for the Analog-to-Digital Converter (ADC) on the STM32F446RE (ARM Cortex-M4). This project demonstrates high-performance peripheral interfacing without the overhead of HAL or LL libraries.

## 🚀 Key Features
**Bare-Metal Implementation:** Direct manipulation of RCC, ADC, and GPIO registers for maximum efficiency.

**Multiple Operating Modes:**

**Single Conversion:** Standard polling-based conversion.

**Scan Mode:** Sequential conversion of multiple channels (PA0 and PA1).

**Multi-Mode (Dual ADC):** Simultaneous conversion using ADC1 and ADC2 in Dual Regular Simultaneous mode.

**Continuous Conversion:** Automated re-triggering for real-time monitoring.

**Hardware Safety:** Implementation of the Analog Watchdog with higher and lower thresholds  to trigger interrupts.

**System Monitoring:**

Internal Temperature Sensor: Includes formula-based calculation ($V_{SENSE}$ to $°C$).

$V_{BAT}$ Monitoring: Internal bridge monitoring for backup battery voltage.

**Interrupt Driven:** Full configuration for NVIC and ADC interrupts (EOCIE, OVRIE).

**UART Integration:** Includes a custom UART driver for serial debugging and data logging.


## 🔧 Technical Specifications (Bare-Metal)

**Bus:** ADC connected via APB2 (enabled via RCC_APB2ENR).

**Resolution:** 12-bit (0-4095).

**Sample Time:** Configurable via SMPR1/SMPR2 (set to 480 cycles in code).

**Interrupts:** Managed via NVIC_ISER0 (Interrupt ID 18).


## 📝 Temperature Calculation Logic

The temperature is calculated from the sensor voltage using the following equation:

Temperature (°C) = (V_SENSE − 0.76) / 0.0025 + 25

where:

**V_SENSE** : (data * VREF) / 4095

**data** is the ADC value

**0.76 V** corresponds to V25 (voltage at 25 °C)  

**0.0025 V/°C** is the average slope of the temperature sensor 

## 🛠 How to Run

**Hardware:** Connect your STM32F446RE Nucleo board.

**Clock Setup:** Ensure your system clock matches the APB1_CLK defined in UART header for accurate UART baud rates.

**Compilation:** Use STM32CubeIDE or a GCC-based toolchain.

**Monitoring:** Open a Serial Terminal (115200 baud) to view the converted values
