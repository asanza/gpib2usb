/*
 * hal_timer.c
 *
 * Copyright (c) 2015, Diego F. Asanza. All rights reserved.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301  USA
 *
 * Created on December 5, 2015, 9:40 AM 
 */

#include "hal_timer.h"
#include <xc.h>

static bool oneshoot = true;
static int period; 
static bool triggered = false;

void hal_timer_init(int period_us, bool _oneshoot){
    oneshoot = _oneshoot;
    period = period_us;
    TCCR1B |= (1 << WGM12) | (1<<CS11);
    TCNT1 = 0;
    TIMSK1 |= (1<<TOIE1);
    OCR1A = period_us;
}

void hal_timer_start(void){
    OCR1A = period;
    TCNT1 = 0;
    TCCR1B |= ( 1 << CS11);
}

void hal_timer_stop(void){
    TCCR1B &= ~(1 << CS11);
}

bool hal_timer_elapsed(void){
    bool t = triggered;
    triggered = false;
    return t;
}

ISR(TIMER1_COMPA_vect){
    TCNT1 = 0; //clear the counter of counter0
    if(oneshoot){
        TCCR1B &= ~(1 << CS11);
    }
    triggered = true;
}