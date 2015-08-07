#ifndef _IIO_DUMMY_EVGEN_H_
#define _IIO_DUMMY_EVGEN_H_

struct iio_dummy_regs {
	u32 reg_id;
	u32 reg_data;
	struct iio_dev *src_dev;
	bool in_use;
};

struct iio_dummy_regs *iio_dummy_evgen_get_regs(void);
struct irq_work *get_work(struct iio_dev *indio_dev);

#endif /* _IIO_DUMMY_EVGEN_H_ */
