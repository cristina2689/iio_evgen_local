#ifndef _IIO_DUMMY_EVGEN_H_
#define _IIO_DUMMY_EVGEN_H_
#include <linux/irq_work.h>

struct iio_dummy_regs {
	u32 reg_id;
	u32 reg_data;
};

struct iio_dummy_event {
	struct iio_dev *dev;
	struct iio_dummy_regs regs;
	struct irq_work work;
	struct list_head l;
};

int iio_dummy_evgen_create(struct iio_dev *indio_dev, int index);
void iio_dummy_init_work_handler(int index, void (*f)(struct irq_work *));
struct iio_dummy_regs *iio_dummy_evgen_get_regs(int index);

#endif /* _IIO_DUMMY_EVGEN_H_ */
