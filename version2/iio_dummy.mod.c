#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

MODULE_INFO(vermagic, VERMAGIC_STRING);

__visible struct module __this_module
__attribute__((section(".gnu.linkonce.this_module"))) = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

MODULE_INFO(staging, "Y");

static const struct modversion_info ____versions[]
__used
__attribute__((section("__versions"))) = {
	{ 0x4b77f6d3, __VMLINUX_SYMBOL_STR(module_layout) },
	{ 0xd2b09ce5, __VMLINUX_SYMBOL_STR(__kmalloc) },
	{ 0xe4689576, __VMLINUX_SYMBOL_STR(ktime_get_with_offset) },
	{ 0xc0a3d105, __VMLINUX_SYMBOL_STR(find_next_bit) },
	{ 0x17144568, __VMLINUX_SYMBOL_STR(iio_dummy_evgen_get_regs) },
	{ 0x6bc138f3, __VMLINUX_SYMBOL_STR(mutex_unlock) },
	{ 0x87cf31b8, __VMLINUX_SYMBOL_STR(__mutex_init) },
	{ 0xa83693d8, __VMLINUX_SYMBOL_STR(mutex_lock) },
	{ 0xbdfb6dbb, __VMLINUX_SYMBOL_STR(__fentry__) },
	{ 0x766d67cd, __VMLINUX_SYMBOL_STR(__dynamic_dev_dbg) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0xb352177e, __VMLINUX_SYMBOL_STR(find_first_bit) },
	{ 0x63c4d61f, __VMLINUX_SYMBOL_STR(__bitmap_weight) },
	{ 0x383c7c9d, __VMLINUX_SYMBOL_STR(param_ops_uint) },
	{ 0x1cd7225e, __VMLINUX_SYMBOL_STR(iio_evgen_register_work_handler) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=iio_dummy_evgen";


MODULE_INFO(srcversion, "518143D87956B958C028AE4");
