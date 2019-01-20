################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Game.cpp \
../src/Letter.cpp \
../src/Turn.cpp 

OBJS += \
./src/Game.o \
./src/Letter.o \
./src/Turn.o 

CPP_DEPS += \
./src/Game.d \
./src/Letter.d \
./src/Turn.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cygwin C++ Compiler'
	g++ -I"C:\Users\Brad Saylor\Documents\programming\cpp\alphabet_game_cpp\include" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


