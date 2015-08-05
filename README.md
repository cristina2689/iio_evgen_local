In https://github.com/cristina2689/iio_evgen_local/blob/master/iio_dummy_evgen.c

* am adaugat un irq_work in loc de hardcodarea intreruperilor
* registrele se asigneaza pe principiul primul venit, primul servit, in iio_dummy_evgen_get_regs(void)


In https://github.com/cristina2689/iio_evgen_local/blob/master/iio_simple_dummy_events.c

