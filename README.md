In https://github.com/cristina2689/iio_evgen_local/blob/master/iio_dummy_evgen.c :

* am adaugat un irq_work in loc de hardcodarea intreruperilor
* registrele se asigneaza pe principiul primul venit, primul servit, in iio_dummy_evgen_get_regs(void)

In https://github.com/cristina2689/iio_evgen_local/blob/master/iio_simple_dummy_events.c :

* in iio_simple_dummy_events_register(struct iio_dev *indio_dev) (#225) atasez o structura regs si inregistrez handlerul cu functii exportate din iio_dummy_evgen.c

Problema:
* handlerul din iio_simple_dummy_events.c trebuie sa aiba forma:

static void iio_simple_dummy_event_handler(struct irq_work *work) {}

si nu poate sa acceseze struct iio_dev-ul pentru care trebuie sa faca push in userspace, e.g. iio_push_event(indio_dev,...)
* ca sa rezolv, am adaugat un camp struct iio_dev *src_dev  in regs, dar tot nu merge, pentru ca nu retin maparea intre dispozitive si regs => nu am cum sa accesez regs (#168)
