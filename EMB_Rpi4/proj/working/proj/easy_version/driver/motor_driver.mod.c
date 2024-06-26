#include <linux/module.h>
#define INCLUDE_VERMAGIC
#include <linux/build-salt.h>
#include <linux/elfnote-lto.h>
#include <linux/export-internal.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

BUILD_SALT;
BUILD_LTO_INFO;

MODULE_INFO(vermagic, VERMAGIC_STRING);
MODULE_INFO(name, KBUILD_MODNAME);

__visible struct module __this_module
__section(".gnu.linkonce.this_module") = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

#ifdef CONFIG_RETPOLINE
MODULE_INFO(retpoline, "Y");
#endif


static const struct modversion_info ____versions[]
__used __section("__versions") = {
	{ 0x1171558e, "gpio_to_desc" },
	{ 0x7419044a, "gpiod_set_raw_value" },
	{ 0x7fffffff, "__aeabi_unwind_cpp_pr0" },
	{ 0x7fffffff, "__gnu_mcount_nc" },
	{ 0x7fffffff, "_printk" },
	{ 0x7fffffff, "gpiod_direction_output_raw" },
	{ 0x7fffffff, "arm_copy_from_user" },
	{ 0x7fffffff, "msleep" },
	{ 0x5f754e5a, "memset" },
	{ 0x3ea1b6e4, "__stack_chk_fail" },
	{ 0x7fffffff, "__stack_chk_guard" },
	{ 0x7fffffff, "alloc_chrdev_region" },
	{ 0x7fffffff, "__class_create" },
	{ 0x65e8d5d2, "device_create" },
	{ 0x7fffffff, "cdev_init" },
	{ 0x4b8165c6, "cdev_add" },
	{ 0x47229b5c, "gpio_request" },
	{ 0x7fffffff, "gpio_free" },
	{ 0x6f5d2137, "device_destroy" },
	{ 0x11d1d8fb, "class_destroy" },
	{ 0x6091b333, "unregister_chrdev_region" },
	{ 0x7fffffff, "cdev_del" },
	{ 0x3557a220, "module_layout" },
};

MODULE_INFO(depends, "");


MODULE_INFO(srcversion, "9674329F4F788A858A32755");
