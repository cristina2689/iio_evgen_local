Version1:
In iio_dummy_evgen.c :
* modulul se ocupa de poke si asignarea registrelor
* registrele se asigneaza pe principiul primul venit, primul servit, in iio_dummy_evgen_get_regs(void)
* pentru a declansa tratarea unui eveniment, se apeleaza irq_work_queue() in handlerul de poke

In iio_simple_dummy_events.c :
* am adaugat irq_work in struct iio_dummy_state
* functia iio_simple_dummy_events_register() inregistreaza handlerul pe irq_work si cere un registru disponibil de la iio_dummy_evgen.c
* handlerul pentru tratarea evenimentului corespunzator driverului, iio_simple_dummy_event_handler face push in userspace pe baza 
pointerului de la regs, care va retine si sursa evenimentului, src_dev



