cmd_/home/cocacola/working/proj/easy_version/driver/led_driver.mod := printf '%s\n'   led_driver.o | awk '!x[$$0]++ { print("/home/cocacola/working/proj/easy_version/driver/"$$0) }' > /home/cocacola/working/proj/easy_version/driver/led_driver.mod
