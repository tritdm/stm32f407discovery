################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../spl/stm32f4xx_gpio.c \
../spl/stm32f4xx_rcc.c \
../spl/stm32f4xx_tim.c 

C_DEPS += \
./spl/stm32f4xx_gpio.d \
./spl/stm32f4xx_rcc.d \
./spl/stm32f4xx_tim.d 

OBJS += \
./spl/stm32f4xx_gpio.o \
./spl/stm32f4xx_rcc.o \
./spl/stm32f4xx_tim.o 


# Each subdirectory must supply rules for building sources it contributes
spl/%.o spl/%.su spl/%.cyclo: ../spl/%.c spl/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F407VGTx -DSTM32F40_41xxx -DUSE_STDPERIPH_DRIVER -c -I../Inc -I/home/mike/Documents/stm32/STM32F4xx_DSP_StdPeriph_Lib_V1.8.0/Libraries/CMSIS/Device/ST/STM32F4xx/Include -I/home/mike/Documents/stm32/STM32F4xx_DSP_StdPeriph_Lib_V1.8.0/Libraries/CMSIS/Include -I/home/mike/Documents/stm32/STM32F4xx_DSP_StdPeriph_Lib_V1.8.0/Libraries/STM32F4xx_StdPeriph_Driver/inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-spl

clean-spl:
	-$(RM) ./spl/stm32f4xx_gpio.cyclo ./spl/stm32f4xx_gpio.d ./spl/stm32f4xx_gpio.o ./spl/stm32f4xx_gpio.su ./spl/stm32f4xx_rcc.cyclo ./spl/stm32f4xx_rcc.d ./spl/stm32f4xx_rcc.o ./spl/stm32f4xx_rcc.su ./spl/stm32f4xx_tim.cyclo ./spl/stm32f4xx_tim.d ./spl/stm32f4xx_tim.o ./spl/stm32f4xx_tim.su

.PHONY: clean-spl

