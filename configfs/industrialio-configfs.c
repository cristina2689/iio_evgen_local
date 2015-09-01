/*
 * Industrial I/O configfs bits
 *
 * Copyright (c) 2015 Intel Corporation
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 2 as published by
 * the Free Software Foundation.
 */

#include <linux/configfs.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/kmod.h>
#include <linux/slab.h>

#include <linux/iio/iio.h>
#include <linux/iio/sw_trigger.h>
#include <linux/iio/iio_simple_dummy.h>

static struct config_group *trigger_make_group(struct config_group *group,
					       const char *name)
{
	struct iio_sw_trigger *t;

	t = iio_sw_trigger_create(group->cg_item.ci_name, name);
	if (IS_ERR(t))
		return ERR_CAST(t);
	printk(KERN_ALERT "Called make_group: %s\n", name);
	config_item_set_name(&t->group.cg_item, name);

	return &t->group;
}

static void trigger_drop_group(struct config_group *group,
			       struct config_item *item)
{
	struct iio_sw_trigger *t = to_iio_sw_trigger(item);

	printk(KERN_ALERT "Called drop_group");
	iio_sw_trigger_destroy(t);
	config_item_put(item);
}

static struct configfs_group_operations trigger_ops = {
	.make_group	= &trigger_make_group,
	.drop_item	= &trigger_drop_group,
};

static struct config_item_type iio_trigger_type_group_type = {
	.ct_group_ops = &trigger_ops,
	.ct_owner       = THIS_MODULE,
};

static struct config_item_type iio_triggers_group_type = {
	.ct_owner = THIS_MODULE,
};

static struct config_group iio_triggers_group = {
	.cg_item = {
		.ci_namebuf = "triggers",
		.ci_type = &iio_triggers_group_type,
	},
};
//-----------------------------------------------------------------

static struct config_group *device_make_group(struct config_group *group,
					       const char *name)
{
	struct iio_dummy_instance *dummy = kzalloc(sizeof(struct iio_dummy_instance), GFP_KERNEL);

	config_item_set_name(&dummy->group.cg_item, name);
	config_group_init_type_name(&dummy->group, name, &iio_dummy_type);

	iio_dummy_probe(name);
	printk(KERN_ALERT  "device make group called with name %s\n", name);
	return &dummy->group;
}

static void device_drop_group(struct config_group *group,
			       struct config_item *item)
{
 	iio_dummy_remove(item->ci_name);
	printk(KERN_ALERT "device drop group called\n");
	config_item_put(item);	
}


static struct configfs_group_operations device_ops = {
	.make_group	= &device_make_group,
	.drop_item	= &device_drop_group,
};

static struct config_item_type iio_device_type_group_type = {
	.ct_group_ops = &device_ops,
	.ct_owner = THIS_MODULE,
};

static struct config_item_type iio_devices_group_type = {
	.ct_owner = THIS_MODULE,
};


static struct config_group iio_devices_group = {
	.cg_item = {
		.ci_namebuf = "devices",
		.ci_type = &iio_devices_group_type,
	},
};

//-----------------------------------------------------------------

static struct config_group *iio_root_default_groups[] = {
	&iio_triggers_group,
	&iio_devices_group,
	NULL
};
//-----------------------------------------------------------------
static struct config_item_type iio_root_group_type = {
	.ct_owner       = THIS_MODULE,
};

static struct configfs_subsystem iio_configfs_subsys = {
	.su_group = {
		.cg_item = {
			.ci_namebuf = "iio",
			.ci_type = &iio_root_group_type,
		},
		.default_groups = iio_root_default_groups,
	},
	.su_mutex = __MUTEX_INITIALIZER(iio_configfs_subsys.su_mutex),
};

int iio_sw_trigger_type_configfs_register(struct iio_sw_trigger_type *tt)
{
	config_group_init_type_name(&tt->group, tt->name,
		&iio_trigger_type_group_type);

	return configfs_register_group(&iio_triggers_group, &tt->group);
}
EXPORT_SYMBOL_GPL(iio_sw_trigger_type_configfs_register);

void iio_sw_trigger_type_configfs_unregister(struct iio_sw_trigger_type *tt)
{
	configfs_unregister_group(&tt->group);
}
EXPORT_SYMBOL_GPL(iio_sw_trigger_type_configfs_unregister);

//-----------------------------------------------------------

int iio_device_type_configfs_register(struct config_group *dummy, const char *name)
{
	config_group_init_type_name(dummy, name, &iio_device_type_group_type);

	return configfs_register_group(&iio_devices_group, dummy);
}
EXPORT_SYMBOL_GPL(iio_device_type_configfs_register);

void iio_device_type_configfs_unregister(struct config_group *dummy)
{
	configfs_unregister_group(dummy);
}
EXPORT_SYMBOL_GPL(iio_device_type_configfs_unregister);

//----------------------------------------------------------
static int __init iio_configfs_init(void)
{
	config_group_init(&iio_triggers_group);
	config_group_init(&iio_devices_group);
	config_group_init(&iio_configfs_subsys.su_group);

	return configfs_register_subsystem(&iio_configfs_subsys);
}
module_init(iio_configfs_init);

static void __exit iio_configfs_exit(void)
{
	configfs_unregister_subsystem(&iio_configfs_subsys);
}
module_exit(iio_configfs_exit);

MODULE_AUTHOR("Daniel Baluta <daniel.baluta@intel.com>");
MODULE_DESCRIPTION("Industrial I/O configfs support");
MODULE_LICENSE("GPL v2");
