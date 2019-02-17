/*
 * propria.h
 *
 * Created: 03/02/2019 22:57:58
 *  Author: nicol
 */

 #ifndef PROPRIA_H_
 #define PROPRIA_H_

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdio.h>
#include "debug.h"
#include "console_usb.h"
#include "event.h"
#include "gpio.h"
#include "radio.h"
#include "delay_loop.h"
#include "rtc.h"

void send(bool sanding);
void send_message(char msg_to_send);
char convert_int_to_string(int direcao, int raio, int ID, int horas, int minutos, int segundos);

#endif /* PROPRIA_H_ */