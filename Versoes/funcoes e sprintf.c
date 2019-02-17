/*
 * Teste 1
 * Enviar msg ao clicar no "user botton"
 */

#include "main.h"
#include "propria.h"
#include "debug.h"
#include "console_usb.h"
#include "event.h"
#include "gpio.h"
#include "radio.h"
#include "delay_loop.h"
#include "rtc.h"

#define DEBUGAR			//Define quando o sistema vai debugar
//#undef DEBUGAR  		//Comentar para ativar low power

//ativar baixo consumo de energia(necessario desativar para debugar)
#ifdef DEBUGAR
	bool __b_system_low_power_enabled__ = false;
#else
	bool __b_system_low_power_enabled__ = true;
#endif

//Iniciar variaveis
bool sending = false;
int i;

int direcao		= 1;	//N 1, S 2, O 3, L 4
int raio		= 14;
int ID			= 101;
int horas		= 18;
int minutos		= 34;
int segundos	= 55;

char buffer_msg[12];
char final_msg_char[12];
uint8_t *msg_to_send;
uint32_t relogio1,  relogio2;

// This function will execute once, use it to initialize components and set initial values.
void fnUSER_Setup( void )
{
	#ifdef DEBUGAR
		//iniciar debug do dispositivo
		fnCONSOLE_USB_Init( );
		fnDELAY_LOOP_ms (500);
		fnDEBUG_Const_String( "\rDispositivo iniciado\n\r");
	#endif
	//Inicia o radio
	fnRADIO_Init();

	//vincula a acao de clicar o botao com a de trocar a variavel de envio
	fnEVENT_Attach_Callback(EVENT_INPUT_BUTTON_PRESS, send);
}

// Anything within the USER_Loop context will execute continuously.
void fnUSER_Loop( void )
{
	if ( sending == true )
	{
		fnGPIO_LED_Toggle();

		for( i = 1; i < 11; i++)
		{
			//relogio1 = fnRTC_Get_Count ();

			//final_msg_int1 = direcao*100000 + raio*1000 + ID;
			//final_msg_int2 = horas*10000 + minutos*100 + segundos;

			sprintf(buffer_msg,"%i%i%i%i%i%i", direcao, raio, ID, horas, minutos, segundos);
			//printf("%s\n", buffer_msg);

			//itoa(final_msg_int1, final_msg_char1, 10);
			//itoa(final_msg_int2, final_msg_char2, 10);

			//strcpy(final_msg_char, final_msg_char1);
			//strcat(final_msg_char, final_msg_char2);

			//msg_to_send = (uint8_t*)buffer_msg;
			send_message(buffer_msg);

			/*while(1)
			{
				if(fnRADIO_Send_Message(msg_to_send, 12, false ))
				{
					break;
				}
			}*/

			#ifdef DEBUGAR
				fnDEBUG_Uint8_Value ( "\rdirecao  : ", direcao , "\n\r");
				fnDEBUG_Uint8_Value ( "\rraio     : ", raio , "\n\r");
				fnDEBUG_Uint8_Value ( "\rID       : ", ID , "\n\r");
				fnDEBUG_Uint8_Value ( "\rhoras    : ", horas, "\n\r");
				fnDEBUG_Uint8_Value ( "\rminutos  : ", minutos, "\n\r");
				fnDEBUG_Uint8_Value ( "\rsegundos : ", segundos , "\n\r");
				fnDEBUG_Const_String ( "\rchar msg : ");
				fnDEBUG_String_Size ( final_msg_char, 12 );
				fnDEBUG_Const_String ( "\n\r");

				fnDEBUG_Const_String ( "\rmandando proxima msg\n\n\r");
			#endif
			ID++;
			fnGPIO_LED_Toggle();
		}
		send();
		#ifdef DEBUGAR
			fnDEBUG_Const_String ( "\rTerminou de mandar msgs\n\r");
		#endif
	}
}

void send(void){
	sending = !sending;
}

void send_message(char * buffer_msg){
	msg_to_send = (uint8_t*)buffer_msg;
	bool result = false;
	while(!result){
		result = fnRADIO_Send_Message(msg_to_send, 12, false);
		relogio1 = fnRTC_Get_Count();
		while(1){
			relogio2 = fnRTC_Get_Count();
			if(relogio2 > relogio1 + 5)
			{
				break;
			}
		}
	}
}

