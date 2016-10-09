#ifndef hal_timer_H
#define hal_timer_H

typedef void (*timer_handler)(void);

void hal_timer_init(int period, timer_handler fn);
void hal_timer_service(void);
#endif // hal_timer_H
