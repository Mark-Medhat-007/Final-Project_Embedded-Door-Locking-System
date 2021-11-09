################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Buzzer.c \
../Motor_driver.c \
../Second_MicroController.c \
../Timer0.c \
../delay.c \
../external_eeprom.c \
../gpio.c \
../lcd.c \
../main2.c \
../twi.c \
../uart.c 

OBJS += \
./Buzzer.o \
./Motor_driver.o \
./Second_MicroController.o \
./Timer0.o \
./delay.o \
./external_eeprom.o \
./gpio.o \
./lcd.o \
./main2.o \
./twi.o \
./uart.o 

C_DEPS += \
./Buzzer.d \
./Motor_driver.d \
./Second_MicroController.d \
./Timer0.d \
./delay.d \
./external_eeprom.d \
./gpio.d \
./lcd.d \
./main2.d \
./twi.d \
./uart.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega16 -DF_CPU=1000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


