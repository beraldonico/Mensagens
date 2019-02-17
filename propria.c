/*
* propria.c
*
* Created: 17/02/2019 12:20:00
* Author: nicol
*/

#include "propria.h"

void send(bool sending)
{
	sending = !sending;
}

char convert_int_to_string(int direcao, int raio, int ID, int horas, int minutos, int segundos)
{
	char final_msg_char1[6], final_msg_char2[6];
	int final_msg_int1, final_msg_int2;
	char final_msg_char[12];

	final_msg_int1 = direcao*100000 + raio*1000 + ID;
	final_msg_int2 = horas*10000 + minutos*100 + segundos;

	itoa(final_msg_int1, final_msg_char1, 10);
	itoa(final_msg_int2, final_msg_char2, 10);

	strcpy(final_msg_char, final_msg_char1);
	strcat(final_msg_char, final_msg_char2);

	return final_msg_char[12];
}

 void send_message(char msg_to_send)
 {
	uint32_t relogio1,  relogio2;
	while(!fnRADIO_Send_Message( (uint8_t*)&msg_to_send, 12, false ))
	{
		relogio1 = fnRTC_Get_Count();
		while(1){
			relogio2 = fnRTC_Get_Count();
			if(relogio2 > relogio1 + 10)
			{
				break;
			}
		}
	}
}