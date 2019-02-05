################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
MSP_EXP430F5529LP.obj: ../MSP_EXP430F5529LP.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: MSP430 Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-msp430_16.9.6.LTS/bin/cl430" -vmspx --data_model=restricted --use_hw_mpy=F5 --include_path="C:/ti/ccsv7/ccs_base/msp430/include" --include_path="C:/Users/Abdullah/Desktop/Current_works/CCworkspaces/ti-rtos" --include_path="C:/Users/Abdullah/Desktop/Current_works/CCworkspaces/ti-rtos" --include_path="C:/ti/tirtos_msp43x_2_20_00_06/products/msp430_driverlib_2_70_01_01a/driverlib/MSP430F5xx_6xx" --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-msp430_16.9.6.LTS/include" --advice:power=all --advice:power_severity=suppress --define=__MSP430F5529__ --define=ccs --define=MSP430WARE -g --printf_support=minimal --diag_warning=225 --diag_warning=255 --diag_wrap=off --display_error_number --abi=eabi --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU23 --silicon_errata=CPU40 --preproc_with_compile --preproc_dependency="MSP_EXP430F5529LP.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

empty_min.obj: ../empty_min.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: MSP430 Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-msp430_16.9.6.LTS/bin/cl430" -vmspx --data_model=restricted --use_hw_mpy=F5 --include_path="C:/ti/ccsv7/ccs_base/msp430/include" --include_path="C:/Users/Abdullah/Desktop/Current_works/CCworkspaces/ti-rtos" --include_path="C:/Users/Abdullah/Desktop/Current_works/CCworkspaces/ti-rtos" --include_path="C:/ti/tirtos_msp43x_2_20_00_06/products/msp430_driverlib_2_70_01_01a/driverlib/MSP430F5xx_6xx" --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-msp430_16.9.6.LTS/include" --advice:power=all --advice:power_severity=suppress --define=__MSP430F5529__ --define=ccs --define=MSP430WARE -g --printf_support=minimal --diag_warning=225 --diag_warning=255 --diag_wrap=off --display_error_number --abi=eabi --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU23 --silicon_errata=CPU40 --preproc_with_compile --preproc_dependency="empty_min.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

build-743999313:
	@$(MAKE) --no-print-directory -Onone -f subdir_rules.mk build-743999313-inproc

build-743999313-inproc: ../empty_min.cfg
	@echo 'Building file: "$<"'
	@echo 'Invoking: XDCtools'
	"C:/ti/xdctools_3_32_00_06_core/xs" --xdcpath="C:/ti/tirtos_msp43x_2_20_00_06/packages;C:/ti/tirtos_msp43x_2_20_00_06/products/bios_6_46_00_23/packages;C:/ti/tirtos_msp43x_2_20_00_06/products/tidrivers_msp43x_2_20_00_08/packages;C:/ti/tirtos_msp43x_2_20_00_06/products/uia_2_00_06_52/packages;C:/ti/ccsv7/ccs_base;" xdc.tools.configuro -o configPkg -t ti.targets.msp430.elf.MSP430X -p ti.platforms.msp430:MSP430F5529 -r release -c "C:/ti/ccsv7/tools/compiler/ti-cgt-msp430_16.9.6.LTS" --compileOptions "-vmspx --data_model=restricted --use_hw_mpy=F5 --include_path=\"C:/ti/ccsv7/ccs_base/msp430/include\" --include_path=\"C:/Users/Abdullah/Desktop/Current_works/CCworkspaces/ti-rtos\" --include_path=\"C:/Users/Abdullah/Desktop/Current_works/CCworkspaces/ti-rtos\" --include_path=\"C:/ti/tirtos_msp43x_2_20_00_06/products/msp430_driverlib_2_70_01_01a/driverlib/MSP430F5xx_6xx\" --include_path=\"C:/ti/ccsv7/tools/compiler/ti-cgt-msp430_16.9.6.LTS/include\" --advice:power=all --advice:power_severity=suppress --define=__MSP430F5529__ --define=ccs --define=MSP430WARE -g --printf_support=minimal --diag_warning=225 --diag_warning=255 --diag_wrap=off --display_error_number --abi=eabi --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU23 --silicon_errata=CPU40  " "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

configPkg/linker.cmd: build-743999313 ../empty_min.cfg
configPkg/compiler.opt: build-743999313
configPkg/: build-743999313

tasks.obj: ../tasks.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: MSP430 Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-msp430_16.9.6.LTS/bin/cl430" -vmspx --data_model=restricted --use_hw_mpy=F5 --include_path="C:/ti/ccsv7/ccs_base/msp430/include" --include_path="C:/Users/Abdullah/Desktop/Current_works/CCworkspaces/ti-rtos" --include_path="C:/Users/Abdullah/Desktop/Current_works/CCworkspaces/ti-rtos" --include_path="C:/ti/tirtos_msp43x_2_20_00_06/products/msp430_driverlib_2_70_01_01a/driverlib/MSP430F5xx_6xx" --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-msp430_16.9.6.LTS/include" --advice:power=all --advice:power_severity=suppress --define=__MSP430F5529__ --define=ccs --define=MSP430WARE -g --printf_support=minimal --diag_warning=225 --diag_warning=255 --diag_wrap=off --display_error_number --abi=eabi --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU23 --silicon_errata=CPU40 --preproc_with_compile --preproc_dependency="tasks.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


