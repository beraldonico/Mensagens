/*
 * Teste 1
 * Enviar msg ao iniciar o dispositivo
 */

#include "main.h"
#include "propria.h"	//header proprio do programador

#define DIRECAO		5	//N 1, S 2, L 3, O 4, Inicio 5
#define RAIO		1
#define ID			11
#define HORAS		12
#define MINUTOS		34
#define SEGUNDOS	56

#define DEBUGAR			//Define quando o sistema vai debugar
//#undef DEBUGAR  		//Comentar para desativar low power

//ativacao do low power(necessario desativar low power para debugar)
#ifdef DEBUGAR
	bool __b_system_low_power_enabled__ = false;
#else
	bool __b_system_low_power_enabled__ = true;
#endif

//Iniciar variaveis
int direcao		= DIRECAO;
int raio		= RAIO;
int id			= ID;
int horas		= HORAS;
int minutos		= MINUTOS;
int segundos	= SEGUNDOS;

char msg[12];			//variavel para armazenar a mensagem

uint32_t relogio1;		//variaveis para amazenar o RTC
uint32_t relogio2;		//utilizado para criar o delay

// This function will execute once, use it to initialize components and set initial values.
void fnUSER_Setup( void )
{
	#ifdef DEBUGAR
		//iniciar debug do dispositivo
		fnCONSOLE_USB_Init( );
		//print inicial no terminal
		fnDEBUG_Const_String( "\rDispositivo iniciado\n\r");
	#endif
	//delay no loop para dar tempo
	fnDELAY_LOOP_ms (500);
	//Inicia o radio
	fnRADIO_Init();
}

// Anything within the USER_Loop context will execute continuously.
void fnUSER_Loop( void )
{
	if ( id <= ID + 9 )
	{
		//inversao do estado do LED
		fnGPIO_LED_Toggle();

		#ifndef DEBUGAR
			//print afim de indicar a entrada na funcao
			fnDEBUG_Const_String ( "\rentrando em convert_int_to_string\n\r");
		#endif

		//Conversao dos dados de inteiro para string
		//com a finalidade de mandar a mensagem
		convert_int_to_string(direcao, raio, id, horas, minutos, segundos);

		#ifndef DEBUGAR
			//print afim de indicar a entrada na funcao
			fnDEBUG_Const_String ( "\rentrando em send_message\n\r");
		#endif

		//envio da mensagem
		send_message(msg);

		//inversao do estado do LED
		fnGPIO_LED_Toggle();

		#ifdef DEBUGAR
			//printf no terminal das variaveis
			fnDEBUG_Uint8_Value ( "\rdirecao  : ", direcao , "\n\r");
			fnDEBUG_Uint8_Value ( "\rraio     : ", raio , "\n\r");
			fnDEBUG_Uint8_Value ( "\rID       : ", id , "\n\r");
			fnDEBUG_Uint8_Value ( "\rhoras    : ", horas, "\n\r");
			fnDEBUG_Uint8_Value ( "\rminutos  : ", minutos, "\n\r");
			fnDEBUG_Uint8_Value ( "\rsegundos : ", segundos , "\n\r");
			fnDEBUG_Const_String ( "\rmsg : ");
			fnDEBUG_String_Size ( msg, 12 );
			fnDEBUG_Const_String ( "\n\n\r");

			//print no terminal entre as mensagens
			if(id < ID + 9)
			{
				fnDEBUG_Const_String ( "\rmandando proxima msg\n\n\r");
				fnDEBUG_Const_String ( "\rentrando no delay\n\n\r");
			}
			else if(id == ID + 9)
			{
				fnDEBUG_Const_String ( "\rultima msg enviada\n\n\r");
			}
			else
			{
				fnDEBUG_Const_String ( "\rterminou de mandar\n\n\r");
			}
		#endif

		//delay entre as diferente mensagens
		relogio1 = fnRTC_Get_Count();
		while(1){
			relogio2 = fnRTC_Get_Count();
			if(relogio2 > relogio1 + 10)
			{
				break;
			}
		}

		//incremento do ID
		id++;
	}
}