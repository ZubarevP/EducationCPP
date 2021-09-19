################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/coursera/4week/1.\ вывод\ с\ точностью/main.cpp 

OBJS += \
./src/coursera/4week/1.\ вывод\ с\ точностью/main.o 

CPP_DEPS += \
./src/coursera/4week/1.\ вывод\ с\ точностью/main.d 


# Each subdirectory must supply rules for building sources it contributes
src/coursera/4week/1.\ вывод\ с\ точностью/main.o: ../src/coursera/4week/1.\ вывод\ с\ точностью/main.cpp src/coursera/4week/1.\ вывод\ с\ точностью/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/coursera/4week/1. вывод с точностью/main.d" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


