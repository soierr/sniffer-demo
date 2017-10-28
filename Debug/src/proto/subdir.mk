################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/proto/node.pb-c.c 

OBJS += \
./src/proto/node.pb-c.o 

C_DEPS += \
./src/proto/node.pb-c.d 


# Each subdirectory must supply rules for building sources it contributes
src/proto/%.o: ../src/proto/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -I/home/soierr/eclipse-workspace/libpcap-1.8.1 -I/usr/include -I"/home/soierr/eclipse-workspace/sniffer-demo/src" -I/usr/local/include -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


