cmd_/home/cocacola/working/seg_example/modules.order := {   echo /home/cocacola/working/seg_example/seg_driver.ko; :; } | awk '!x[$$0]++' - > /home/cocacola/working/seg_example/modules.order
