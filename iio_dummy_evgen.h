#ifndef _IIO_DUMMY_EVGEN_H_
#define _IIO_DUMMY_EVGEN_H_
#include<linux/irq_work.h>

struct iio_dummy_regs {
	u32 reg_id;
	u32 reg_data;
	struct iio_dev *src_dev;
	bool in_use;
};

struct iio_dummy_regs *iio_dummy_evgen_get_regs(void);
void iio_evgen_register_work_handler(void (*f)(struct irq_work *));


#endif /* _IIO_DUMMY_EVGEN_H_ */
