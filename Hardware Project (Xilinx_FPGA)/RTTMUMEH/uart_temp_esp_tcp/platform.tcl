# 
# Usage: To re-create this platform project launch xsct with below options.
# xsct C:\Users\nniro\uart_temp_esp_tcp\platform.tcl
# 
# OR launch xsct and run below command.
# source C:\Users\nniro\uart_temp_esp_tcp\platform.tcl
# 
# To create the platform in a different location, modify the -out option of "platform create" command.
# -out option specifies the output directory of the platform project.

platform create -name {uart_temp_esp_tcp}\
-hw {C:\Users\nniro\MSI Vivado\Vivado\project_1\design_1_wrapper.xsa}\
-proc {microblaze_0} -os {standalone} -out {C:/Users/nniro}

platform write
platform generate -domains 
platform active {uart_temp_esp_tcp}
platform generate
catch {platform remove uart_temp_accel_esp}
platform clean
platform generate
