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
	{ 0x50bcee77, __VMLINUX_SYMBOL_STR(kmalloc_caches) },
	{ 0x6bc138f3, __VMLINUX_SYMBOL_STR(mutex_unlock) },
	{ 0x3c80c06c, __VMLINUX_SYMBOL_STR(kstrtoull) },
	{ 0xa83693d8, __VMLINUX_SYMBOL_STR(mutex_lock) },
	{ 0xe3d0c418, __VMLINUX_SYMBOL_STR(device_add) },
	{ 0xbdfb6dbb, __VMLINUX_SYMBOL_STR(__fentry__) },
	{ 0x9c4f4383, __VMLINUX_SYMBOL_STR(kmem_cache_alloc_trace) },
	{ 0xcfb5871c, __VMLINUX_SYMBOL_STR(irq_work_queue) },
	{ 0x6bbcd043, __VMLINUX_SYMBOL_STR(device_initialize) },
	{ 0x10cf47b5, __VMLINUX_SYMBOL_STR(device_unregister) },
	{ 0x13b81937, __VMLINUX_SYMBOL_STR(dev_set_name) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";


MODULE_INFO(srcversion, "8506F5B0EFE1D0C3945AA0E");
