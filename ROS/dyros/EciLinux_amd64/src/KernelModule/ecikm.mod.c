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

static const struct modversion_info ____versions[]
__used
__attribute__((section("__versions"))) = {
	{ 0xd2901226, __VMLINUX_SYMBOL_STR(module_layout) },
	{ 0x7485e15e, __VMLINUX_SYMBOL_STR(unregister_chrdev_region) },
	{ 0x2397e50a, __VMLINUX_SYMBOL_STR(remove_proc_entry) },
	{ 0x5f13b39a, __VMLINUX_SYMBOL_STR(class_destroy) },
	{ 0xdf13aa80, __VMLINUX_SYMBOL_STR(class_unregister) },
	{ 0x9fd7f8ea, __VMLINUX_SYMBOL_STR(pci_unregister_driver) },
	{ 0x5125e680, __VMLINUX_SYMBOL_STR(__pci_register_driver) },
	{ 0x55da9811, __VMLINUX_SYMBOL_STR(proc_create_data) },
	{ 0xeb751375, __VMLINUX_SYMBOL_STR(__class_create) },
	{ 0x29537c9e, __VMLINUX_SYMBOL_STR(alloc_chrdev_region) },
	{ 0x449ad0a7, __VMLINUX_SYMBOL_STR(memcmp) },
	{ 0xb8e7ce2c, __VMLINUX_SYMBOL_STR(__put_user_8) },
	{ 0x4f8b5ddb, __VMLINUX_SYMBOL_STR(_copy_to_user) },
	{ 0x4f6b400b, __VMLINUX_SYMBOL_STR(_copy_from_user) },
	{ 0x40c450dc, __VMLINUX_SYMBOL_STR(pci_set_master) },
	{ 0xd2b09ce5, __VMLINUX_SYMBOL_STR(__kmalloc) },
	{ 0x13f66d18, __VMLINUX_SYMBOL_STR(pci_bus_write_config_dword) },
	{ 0xdf9b999a, __VMLINUX_SYMBOL_STR(device_create) },
	{ 0xcab7dd67, __VMLINUX_SYMBOL_STR(cdev_add) },
	{ 0xac283b73, __VMLINUX_SYMBOL_STR(cdev_init) },
	{ 0x2072ee9b, __VMLINUX_SYMBOL_STR(request_threaded_irq) },
	{ 0x28318305, __VMLINUX_SYMBOL_STR(snprintf) },
	{ 0x42c8de35, __VMLINUX_SYMBOL_STR(ioremap_nocache) },
	{ 0x1fedf0f4, __VMLINUX_SYMBOL_STR(__request_region) },
	{ 0xfb578fc5, __VMLINUX_SYMBOL_STR(memset) },
	{ 0x92a338cf, __VMLINUX_SYMBOL_STR(arch_dma_alloc_attrs) },
	{ 0xdb7305a1, __VMLINUX_SYMBOL_STR(__stack_chk_fail) },
	{ 0x51381898, __VMLINUX_SYMBOL_STR(pci_enable_device) },
	{ 0x9e88526, __VMLINUX_SYMBOL_STR(__init_waitqueue_head) },
	{ 0x910e0dc, __VMLINUX_SYMBOL_STR(kmem_cache_alloc_trace) },
	{ 0x84f43e8d, __VMLINUX_SYMBOL_STR(kmalloc_caches) },
	{ 0x91715312, __VMLINUX_SYMBOL_STR(sprintf) },
	{ 0x16305289, __VMLINUX_SYMBOL_STR(warn_slowpath_null) },
	{ 0x6da45f2a, __VMLINUX_SYMBOL_STR(dma_ops) },
	{ 0x7356cebf, __VMLINUX_SYMBOL_STR(pci_disable_device) },
	{ 0x7c61340c, __VMLINUX_SYMBOL_STR(__release_region) },
	{ 0x69a358a6, __VMLINUX_SYMBOL_STR(iomem_resource) },
	{ 0xedc03953, __VMLINUX_SYMBOL_STR(iounmap) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0x78764f4e, __VMLINUX_SYMBOL_STR(pv_irq_ops) },
	{ 0xf20dabd8, __VMLINUX_SYMBOL_STR(free_irq) },
	{ 0x9d99c61f, __VMLINUX_SYMBOL_STR(cdev_del) },
	{ 0xb3643e6b, __VMLINUX_SYMBOL_STR(device_destroy) },
	{ 0xa6bbd805, __VMLINUX_SYMBOL_STR(__wake_up) },
	{ 0x4c9d28b0, __VMLINUX_SYMBOL_STR(phys_base) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0x7876d70, __VMLINUX_SYMBOL_STR(remap_pfn_range) },
	{ 0x5944d015, __VMLINUX_SYMBOL_STR(__cachemode2pte_tbl) },
	{ 0xa50a80c2, __VMLINUX_SYMBOL_STR(boot_cpu_data) },
	{ 0x436c2179, __VMLINUX_SYMBOL_STR(iowrite32) },
	{ 0x727c4f3, __VMLINUX_SYMBOL_STR(iowrite8) },
	{ 0xe484e35f, __VMLINUX_SYMBOL_STR(ioread32) },
	{ 0xf10de535, __VMLINUX_SYMBOL_STR(ioread8) },
	{ 0xbdfb6dbb, __VMLINUX_SYMBOL_STR(__fentry__) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";

MODULE_ALIAS("pci:v000010B5d00009050sv000010B5sd00002540bc*sc*i*");
MODULE_ALIAS("pci:v000010B5d00009050sv000010B5sd00001128bc*sc*i*");
MODULE_ALIAS("pci:v000010B5d00009030sv000010B5sd00002977bc*sc*i*");
MODULE_ALIAS("pci:v000010B5d00009056sv000010B5sd00003268bc*sc*i*");
MODULE_ALIAS("pci:v00001BEEd00000001sv00001BEEsd00000001bc*sc*i*");
MODULE_ALIAS("pci:v00001BEEd00000002sv00001BEEsd00000002bc*sc*i*");
MODULE_ALIAS("pci:v00001BEEd00000010sv00001BEEsd00000010bc*sc*i*");
MODULE_ALIAS("pci:v00001BEEd00000004sv00001BEEsd00000004bc*sc*i*");
MODULE_ALIAS("pci:v00001BEEd00000005sv00001BEEsd00000005bc*sc*i*");
MODULE_ALIAS("pci:v00001BEEd00000003sv00001BEEsd00000003bc*sc*i*");
MODULE_ALIAS("pci:v00001BEEd0000000Esv00001BEEsd0000000Ebc*sc*i*");
MODULE_ALIAS("pci:v00001BEEd00000019sv00001BEEsd00000019bc*sc*i*");
MODULE_ALIAS("pci:v00001BEEd00000012sv00001BEEsd00000012bc*sc*i*");
MODULE_ALIAS("pci:v00001BEEd00000013sv00001BEEsd00000013bc*sc*i*");
MODULE_ALIAS("pci:v00001BEEd00000003sv00001BEEsd00000003bc*sc*i*");
MODULE_ALIAS("pci:v00001BEEd00000011sv00001BEEsd00000011bc*sc*i*");
MODULE_ALIAS("pci:v00001BEEd00000006sv00001BEEsd00000006bc*sc*i*");
MODULE_ALIAS("pci:v00001BEEd0000000Fsv00001BEEsd0000000Fbc*sc*i*");
MODULE_ALIAS("pci:v00001BEEd0000001Bsv00001BEEsd0000001Bbc*sc*i*");
MODULE_ALIAS("pci:v00001BEEd00000016sv00001BEEsd00000016bc*sc*i*");

MODULE_INFO(srcversion, "0A1EACC68A80F1E02F3EC90");
