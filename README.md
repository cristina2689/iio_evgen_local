In iio_dummy_evgen.c :

* am adaugat un irq_work in loc de hardcodarea intreruperilor
* registrele se asigneaza pe principiul primul venit, primul servit, in iio_dummy_evgen_get_regs(void)

In iio_simple_dummy_events.c :

* in iio_simple_dummy_events_register(struct iio_dev *indio_dev) (#225) atasez o structura regs si inregistrez handlerul cu functii exportate din iio_dummy_evgen.c



