################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/pcap_api.c \
../src/shell_cmd_executor.c \
../src/shell_cmd_parser.c \
../src/sniffer-demo-main.c 

OBJS += \
./src/pcap_api.o \
./src/shell_cmd_executor.o \
./src/shell_cmd_parser.o \
./src/sniffer-demo-main.o 

C_DEPS += \
./src/pcap_api.d \
./src/shell_cmd_executor.d \
./src/shell_cmd_parser.d \
./src/sniffer-demo-main.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -I/home/soierr/eclipse-workspace/libpcap-1.8.1 -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


