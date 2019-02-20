/*
 * propria.h
 *
 * Created: 03/02/2019 22:57:58
 *  Author: nicol
 */

#ifndef PROPRIA_H_
#define PROPRIA_H_

//bibliotecas C
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdio.h>

//bibliotecas sigfox
#include "debug.h"
#include "console_usb.h"
#include "gpio.h"
#include "radio.h"
#include "delay_loop.h"
#include "rtc.h"

//conecao de variavel entre os arquivos
extern char msg[12];

//declaracao de funcoes
//conversao das variaveis de int para string
void convert_int_to_string(int direcao, int raio, int id, int horas, int minutos, int segundos);
//envio da mensagem
void send_message(char *msg_to_send);

#endif /* PROPRIA_H_ */