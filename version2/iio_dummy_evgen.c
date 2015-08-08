/**
 * Copyright (c) 2011 Jonathan Cameron
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 2 as published by
 * the Free Software Foundation.
 *
 * Companion module to the iio simple dummy example driver.
 * The purpose of this is to generate 'fake' event interrupts thus
 * allowing that driver's code to be as close as possible to that of
 * a normal driver talking to hardware.  The approach used here
 * is not intended to be general and just happens to work for this
 * particular use case.
 */

#include <linux/kernel.h>
#include <linux/slab.h>
#include <linux/interrupt.h>
#include <linux/irq.h>
#include <linux/mutex.h>
#include <linux/module.h>
#include <linux/sysfs.h>

#include "iio_dummy_evgen.h"
#include <linux/iio/iio.h>
#include <linux/iio/sysfs.h>

static LIST_HEAD(iio_dummy_event_list);
static DEFINE_MUTEX(iio_dummy_event_list_mutex);

struct iio_dummy_event *get_event(int index)
{
	struct list_head *ptr, *tmp;
	struct iio_dummy_event *iio_event;

	list_for_each_safe(ptr, tmp, &iio_dummy_event_list) {
		iio_event = list_entry(ptr, struct iio_dummy_event, l);
		if (iio_event->regs.reg_id == index) {
			return iio_event;
		}
	}
	return NULL;
}

int iio_dummy_evgen_create(struct iio_dev *indio_dev, int index)
{
	struct iio_dummy_event *iio_event;

	mutex_lock(&iio_dummy_event_list_mutex);
	iio_event = kzalloc(sizeof(struct iio_dummy_event), GFP_KERNEL);
	if (!iio_event)
		return -ENOMEM;

	iio_event->dev = indio_dev;
	iio_event->regs.reg_id = index;
	list_add(&iio_event->l, &iio_dummy_event_list);
	mutex_unlock(&iio_dummy_event_list_mutex);

	return 0;
}
EXPORT_SYMBOL_GPL(iio_dummy_evgen_create);

void iio_dummy_init_work_handler(int index, void (*f)(struct irq_work *))
{
	struct iio_dummy_event *iio_event;

	if (get_event(index)){
		init_irq_work(&iio_event->work, f);
	}
}
EXPORT_SYMBOL_GPL(iio_dummy_init_work_handler);

struct iio_dummy_regs *iio_dummy_evgen_get_regs(int index)
{
	struct iio_dummy_event *iio_event;

	if (iio_event = get_event(index))
		return &iio_event->regs;

	return NULL;
}
EXPORT_SYMBOL_GPL(iio_dummy_evgen_get_regs);


static void iio_dummy_evgen_free(int index)
{
	struct list_head *ptr, *tmp;
	struct iio_dummy_event *iio_event;

	// add mutex
	list_for_each_safe(ptr, tmp, &iio_dummy_event_list) {
		iio_event =  list_entry(ptr, struct iio_dummy_event, l);
		if (iio_event->regs.reg_id == index) {
			list_del(ptr);
			kfree(iio_event);
		}
	}
}

static void iio_evgen_release(struct device *dev)
{
}

static ssize_t iio_evgen_poke(struct device *dev,
			      struct device_attribute *attr,
			      const char *buf,
			      size_t len)
{
	struct iio_dev_attr *this_attr = to_iio_dev_attr(attr);
	unsigned long event;
	struct iio_dummy_event *iio_event;
	int ret;

	ret = kstrtoul(buf, 10, &event);
	if (ret)
		return ret;

	if ((iio_event = get_event(this_attr->address))) {
		iio_event->regs.reg_data = event;
		// maybe check if previous interrupt has not been handled yet
		// to avoid overwritting
		irq_work_queue(&iio_event->work);
	}
	return len;
}

static IIO_DEVICE_ATTR(poke_ev0, S_IWUSR, NULL, &iio_evgen_poke, 0);
static IIO_DEVICE_ATTR(poke_ev1, S_IWUSR, NULL, &iio_evgen_poke, 1);
static IIO_DEVICE_ATTR(poke_ev2, S_IWUSR, NULL, &iio_evgen_poke, 2);
static IIO_DEVICE_ATTR(poke_ev3, S_IWUSR, NULL, &iio_evgen_poke, 3);
static IIO_DEVICE_ATTR(poke_ev4, S_IWUSR, NULL, &iio_evgen_poke, 4);
static IIO_DEVICE_ATTR(poke_ev5, S_IWUSR, NULL, &iio_evgen_poke, 5);
static IIO_DEVICE_ATTR(poke_ev6, S_IWUSR, NULL, &iio_evgen_poke, 6);
static IIO_DEVICE_ATTR(poke_ev7, S_IWUSR, NULL, &iio_evgen_poke, 7);
static IIO_DEVICE_ATTR(poke_ev8, S_IWUSR, NULL, &iio_evgen_poke, 8);
static IIO_DEVICE_ATTR(poke_ev9, S_IWUSR, NULL, &iio_evgen_poke, 9);

static struct attribute *iio_evgen_attrs[] = {
	&iio_dev_attr_poke_ev0.dev_attr.attr,
	&iio_dev_attr_poke_ev1.dev_attr.attr,
	&iio_dev_attr_poke_ev2.dev_attr.attr,
	&iio_dev_attr_poke_ev3.dev_attr.attr,
	&iio_dev_attr_poke_ev4.dev_attr.attr,
	&iio_dev_attr_poke_ev5.dev_attr.attr,
	&iio_dev_attr_poke_ev6.dev_attr.attr,
	&iio_dev_attr_poke_ev7.dev_attr.attr,
	&iio_dev_attr_poke_ev8.dev_attr.attr,
	&iio_dev_attr_poke_ev9.dev_attr.attr,
	NULL,
};

static const struct attribute_group iio_evgen_group = {
	.attrs = iio_evgen_attrs,
};

static const struct attribute_group *iio_evgen_groups[] = {
	&iio_evgen_group,
	NULL
};

static struct device iio_evgen_dev = {
	.bus = &iio_bus_type,
	.groups = iio_evgen_groups,
	.release = &iio_evgen_release,
};

static __init int iio_dummy_evgen_init(void)
{
	device_initialize(&iio_evgen_dev);
	dev_set_name(&iio_evgen_dev, "iio_evgen");
	return device_add(&iio_evgen_dev);
}
module_init(iio_dummy_evgen_init);

static __exit void iio_dummy_evgen_exit(void)
{
	device_unregister(&iio_evgen_dev);
}
module_exit(iio_dummy_evgen_exit);

MODULE_AUTHOR("Jonathan Cameron <jic23@kernel.org>");
MODULE_DESCRIPTION("IIO dummy driver");
MODULE_LICENSE("GPL v2");
