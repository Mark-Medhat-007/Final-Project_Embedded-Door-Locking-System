################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../First_MicroController.c \
../Timer0.c \
../delay.c \
../gpio.c \
../keypad.c \
../lcd.c \
../main1.c \
../uart.c 

OBJS += \
./First_MicroController.o \
./Timer0.o \
./delay.o \
./gpio.o \
./keypad.o \
./lcd.o \
./main1.o \
./uart.o 

C_DEPS += \
./First_MicroController.d \
./Timer0.d \
./delay.d \
./gpio.d \
./keypad.d \
./lcd.d \
./main1.d \
./uart.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega16 -DF_CPU=1000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


