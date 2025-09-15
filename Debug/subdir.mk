################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../APP.c \
../DIO_program.c \
../GLOBINT_program.c \
../KPD_program.c \
../LCD_program.c \
../TIMER_program.c 

OBJS += \
./APP.o \
./DIO_program.o \
./GLOBINT_program.o \
./KPD_program.o \
./LCD_program.o \
./TIMER_program.o 

C_DEPS += \
./APP.d \
./DIO_program.d \
./GLOBINT_program.d \
./KPD_program.d \
./LCD_program.d \
./TIMER_program.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega16 -DF_CPU=1000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


