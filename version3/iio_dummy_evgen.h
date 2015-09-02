#ifndef _IIO_DUMMY_EVGEN_H_
#define _IIO_DUMMY_EVGEN_H_

#include <linux/irq_work.h>
#define IIO_EVENTGEN_NO 10

struct iio_dummy_regs {
	u32 reg_id;
	u32 reg_data;
};

/**
 * struct iio_dummy_evgen - evgen state
 * @chip: irq chip we are faking
 * @base: base of irq range
 * @enabled: mask of which irqs are enabled
 * @inuse: mask of which irqs are connected
 * @regs: irq regs we are faking
 * @lock: protect the evgen state
 */
struct iio_dummy_eventgen {
	struct irq_chip chip;
	int base;
	bool enabled[IIO_EVENTGEN_NO];
	bool inuse[IIO_EVENTGEN_NO];
	struct iio_dummy_regs regs[IIO_EVENTGEN_NO];
	struct mutex lock;
	struct irq_work *work;
};

struct iio_dummy_regs *iio_dummy_evgen_get_regs(int irq);
int iio_dummy_evgen_get_irq(void);
void iio_dummy_evgen_release_irq(int irq);
void iio_dummy_init_work(struct irq_work *work);
#endif /* _IIO_DUMMY_EVGEN_H_ */
