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
	{ 0x3df5362e, __VMLINUX_SYMBOL_STR(module_layout) },
	{ 0x7485e15e, __VMLINUX_SYMBOL_STR(unregister_chrdev_region) },
	{ 0x4847f84c, __VMLINUX_SYMBOL_STR(remove_proc_entry) },
	{ 0x5f13b39a, __VMLINUX_SYMBOL_STR(class_destroy) },
	{ 0xdf13aa80, __VMLINUX_SYMBOL_STR(class_unregister) },
	{ 0xfe123f2e, __VMLINUX_SYMBOL_STR(pci_unregister_driver) },
	{ 0xcec1f225, __VMLINUX_SYMBOL_STR(__pci_register_driver) },
	{ 0x298e95f2, __VMLINUX_SYMBOL_STR(proc_create_data) },
	{ 0xeb751375, __VMLINUX_SYMBOL_STR(__class_create) },
	{ 0x29537c9e, __VMLINUX_SYMBOL_STR(alloc_chrdev_region) },
	{ 0x449ad0a7, __VMLINUX_SYMBOL_STR(memcmp) },
	{ 0xb8e7ce2c, __VMLINUX_SYMBOL_STR(__put_user_8) },
	{ 0x4f6b400b, __VMLINUX_SYMBOL_STR(_copy_from_user) },
	{ 0xc171d4f5, __VMLINUX_SYMBOL_STR(pci_set_master) },
	{ 0x37329223, __VMLINUX_SYMBOL_STR(pci_enable_msi_range) },
	{ 0xde5c79ca, __VMLINUX_SYMBOL_STR(device_create) },
	{ 0xf1629318, __VMLINUX_SYMBOL_STR(cdev_add) },
	{ 0xc4b11a73, __VMLINUX_SYMBOL_STR(cdev_init) },
	{ 0x2072ee9b, __VMLINUX_SYMBOL_STR(request_threaded_irq) },
	{ 0x42c8de35, __VMLINUX_SYMBOL_STR(ioremap_nocache) },
	{ 0x1fedf0f4, __VMLINUX_SYMBOL_STR(__request_region) },
	{ 0x1a3ec6d7, __VMLINUX_SYMBOL_STR(pci_bus_write_config_dword) },
	{ 0xfb578fc5, __VMLINUX_SYMBOL_STR(memset) },
	{ 0xc98cb0e0, __VMLINUX_SYMBOL_STR(arch_dma_alloc_attrs) },
	{ 0xf49fee23, __VMLINUX_SYMBOL_STR(pci_enable_device) },
	{ 0x9e88526, __VMLINUX_SYMBOL_STR(__init_waitqueue_head) },
	{ 0xd6aa1fed, __VMLINUX_SYMBOL_STR(kmem_cache_alloc_trace) },
	{ 0xf8a96516, __VMLINUX_SYMBOL_STR(kmalloc_caches) },
	{ 0x4f8b5ddb, __VMLINUX_SYMBOL_STR(_copy_to_user) },
	{ 0x28318305, __VMLINUX_SYMBOL_STR(snprintf) },
	{ 0xd2b09ce5, __VMLINUX_SYMBOL_STR(__kmalloc) },
	{ 0x16305289, __VMLINUX_SYMBOL_STR(warn_slowpath_null) },
	{ 0x6e3acf00, __VMLINUX_SYMBOL_STR(dma_ops) },
	{ 0xe61fb6d8, __VMLINUX_SYMBOL_STR(pci_disable_msi) },
	{ 0xdd391222, __VMLINUX_SYMBOL_STR(pci_disable_device) },
	{ 0x7c61340c, __VMLINUX_SYMBOL_STR(__release_region) },
	{ 0x69a358a6, __VMLINUX_SYMBOL_STR(iomem_resource) },
	{ 0xedc03953, __VMLINUX_SYMBOL_STR(iounmap) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0x78764f4e, __VMLINUX_SYMBOL_STR(pv_irq_ops) },
	{ 0xf20dabd8, __VMLINUX_SYMBOL_STR(free_irq) },
	{ 0x80321fcd, __VMLINUX_SYMBOL_STR(cdev_del) },
	{ 0xe62b1e32, __VMLINUX_SYMBOL_STR(device_destroy) },
	{ 0xa6bbd805, __VMLINUX_SYMBOL_STR(__wake_up) },
	{ 0x4c9d28b0, __VMLINUX_SYMBOL_STR(phys_base) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0xffa6756f, __VMLINUX_SYMBOL_STR(remap_pfn_range) },
	{ 0x5944d015, __VMLINUX_SYMBOL_STR(__cachemode2pte_tbl) },
	{ 0xa50a80c2, __VMLINUX_SYMBOL_STR(boot_cpu_data) },
	{ 0x436c2179, __VMLINUX_SYMBOL_STR(iowrite32) },
	{ 0x727c4f3, __VMLINUX_SYMBOL_STR(iowrite8) },
	{ 0xe484e35f, __VMLINUX_SYMBOL_STR(ioread32) },
	{ 0xf10de535, __VMLINUX_SYMBOL_STR(ioread8) },
	{ 0x9b6340b6, __VMLINUX_SYMBOL_STR(current_task) },
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
MODULE_ALIAS("pci:v00001BEEd00000013sv00001BEEsd00000013bc*sc*i*");
MODULE_ALIAS("pci:v00001BEEd00000010sv00001BEEsd00000010bc*sc*i*");
MODULE_ALIAS("pci:v00001BEEd00000015sv00001BEEsd00000015bc*sc*i*");
MODULE_ALIAS("pci:v00001BEEd00000004sv00001BEEsd00000004bc*sc*i*");
MODULE_ALIAS("pci:v00001BEEd00000005sv00001BEEsd00000005bc*sc*i*");
MODULE_ALIAS("pci:v00001BEEd0000000Esv00001BEEsd0000000Ebc*sc*i*");
MODULE_ALIAS("pci:v00001BEEd00000017sv00001BEEsd00000017bc*sc*i*");
MODULE_ALIAS("pci:v00001BEEd00000019sv00001BEEsd00000019bc*sc*i*");
MODULE_ALIAS("pci:v00001BEEd0000001Asv00001BEEsd0000001Abc*sc*i*");
MODULE_ALIAS("pci:v00001BEEd00000012sv00001BEEsd00000012bc*sc*i*");
MODULE_ALIAS("pci:v00001BEEd0000002Csv00001BEEsd0000002Cbc*sc*i*");
MODULE_ALIAS("pci:v00001BEEd00000003sv00001BEEsd00000003bc*sc*i*");
MODULE_ALIAS("pci:v00001BEEd00000014sv00001BEEsd00000014bc*sc*i*");
MODULE_ALIAS("pci:v00001BEEd00000011sv00001BEEsd00000011bc*sc*i*");
MODULE_ALIAS("pci:v00001BEEd00000016sv00001BEEsd00000016bc*sc*i*");
MODULE_ALIAS("pci:v00001BEEd00000006sv00001BEEsd00000006bc*sc*i*");
MODULE_ALIAS("pci:v00001BEEd0000000Fsv00001BEEsd0000000Fbc*sc*i*");
MODULE_ALIAS("pci:v00001BEEd00000018sv00001BEEsd00000018bc*sc*i*");
MODULE_ALIAS("pci:v00001BEEd0000001Bsv00001BEEsd0000001Bbc*sc*i*");
MODULE_ALIAS("pci:v00001BEEd0000001Csv00001BEEsd0000001Cbc*sc*i*");
MODULE_ALIAS("pci:v00001BEEd0000002Dsv00001BEEsd0000002Dbc*sc*i*");

MODULE_INFO(srcversion, "4870CB91AC90B7FFA365FA0");
