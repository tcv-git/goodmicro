# Nucleo CAD Logger

The Nucleo CAD Logger uses an ST
[NUCLEO-L452RE](https://www.st.com/en/evaluation-tools/nucleo-l452re.html) board
to log both the serial interfaces of the
[CAD](https://geo-jira.atlassian.net/wiki/spaces/SMETSCAD/overview).

The UART between the K32W041A (Zigbee processor) and ESP8285 (WiFi processor) is
logged in both directions, as well as the output of TAP test interface.

The messages are decoded and interleaved to a single built-in USB-UART.

## Pinout

The following 4 pins must be connected with jumper leads:

| Direction  | Signal          | Nucleo pin | CAD pin        | Log prefix | Log colour |
| -----------|-----------------|------------|----------------|------------|------------|
| common     | GND             | CN7 pin 8  | J2 or J4 pin 1 |            |            |
| ESP to K32 | PA1(UART4_RX)   | CN7 pin 30 | J4 pin 3       | `<`        | Yellow     |
| K32 to ESP | PB7(USART1_RX)  | CN7 pin 21 | J4 pin 2       | `>`        | Green      |
| K32 to TAP | PC11(USART3_RX) | CN7 pin 2  | J2 pin 3       | `^`        | Blue       |

The following pin is reserved for future expansion (not currently implemented):

| Direction  | Signal          | Logger pin | CAD pin        | Log prefix | Log colour |
| -----------|-----------------|------------|----------------|------------|------------|
| TAP to K32 | PC10(USART3_TX) | CN7 pin 1  | J2 pin 2       | `$`        | White      |

## USB

The USB cable provides both power and communication to the PC.  It will appear
in both Linux and Windows as a multifunction device providing both a storage
drive and a standard serial port.  The storage drive can be ignored.

The serial port can be opened with any normal serial console or logging program,
such as [putty](https://www.chiark.greenend.org.uk/~sgtatham/putty/).  With
putty, timestamps can be prefixed to each line.

The serial settings to use are 1000000 Baud (1MBaud), 1 start bit, 8 data bits,
no parity, 1 stop bit.  The device name under Linux will be something like
`/dev/ttyACM0`.

## Toggling colour output

If the blue button `B1` (labelled "USER") is pressed, the green LED `LD2` will
toggle on and off.  While the LED is on the terminal output will be in colour.
This is best suited to live display.  While the LED is off the terminal output
will be in plain ASCII.  This is best suited to logging to a file.

## Build and programming instructions

This project can be built and programmed to the Nucleo board under Linux or
Windows.

To compile, just run `make` in this directory.  This requires `make` and an
[arm-none-eabi-gcc](https://developer.arm.com/downloads/-/arm-gnu-toolchain-downloads)
toolchain.

To program, run `make flash`.  This requires either
[ST-LINK Utility](https://www.st.com/en/development-tools/stsw-link004.html) or
[STM32CubeProgrammer](https://www.st.com/en/development-tools/stm32cubeprog.html),
or a recent version of [OpenOCD](https://openocd.org/).
