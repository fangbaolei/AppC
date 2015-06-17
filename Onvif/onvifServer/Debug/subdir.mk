################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../duration.c \
../main.c \
../pubFun.c \
../serverFun.c \
../soapC.c \
../soapServer.c \
../stdsoap2.c 

OBJS += \
./duration.o \
./main.o \
./pubFun.o \
./serverFun.o \
./soapC.o \
./soapServer.o \
./stdsoap2.o 

C_DEPS += \
./duration.d \
./main.d \
./pubFun.d \
./serverFun.d \
./soapC.d \
./soapServer.d \
./stdsoap2.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


