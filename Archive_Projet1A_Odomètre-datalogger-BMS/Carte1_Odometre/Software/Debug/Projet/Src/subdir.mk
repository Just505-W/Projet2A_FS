################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Projet/Src/utils.c 

OBJS += \
./Projet/Src/utils.o 

C_DEPS += \
./Projet/Src/utils.d 


# Each subdirectory must supply rules for building sources it contributes
Projet/Src/%.o Projet/Src/%.su Projet/Src/%.cyclo: ../Projet/Src/%.c Projet/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32C092xx -c -I../Core/Inc -I../Drivers/STM32C0xx_HAL_Driver/Inc -I../Drivers/STM32C0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32C0xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/justi/OneDrive/Belgeler/Dossier_GIT/Projet2A_FS/Archive_Projet1A_Odomètre-datalogger-BMS/Carte1_Odometre/Software/Projet/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Projet-2f-Src

clean-Projet-2f-Src:
	-$(RM) ./Projet/Src/utils.cyclo ./Projet/Src/utils.d ./Projet/Src/utils.o ./Projet/Src/utils.su

.PHONY: clean-Projet-2f-Src

