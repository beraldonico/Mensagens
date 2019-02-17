/*
 * Teste 1
 * Enviar msg ao clicar no "user botton"
 */

#include "main.h"
#include "propria.h"

#define DEBUGAR			//Define quando o sistema vai debugar
//#undef DEBUGAR  		//Comentar para ativar low power

//ativar baixo consumo de energia(necessario desativar para debugar)
#ifdef DEBUGAR
	bool __b_system_low_power_enabled__ = false;
#else
	bool __b_system_low_power_enabled__ = true;
#endif

//Iniciar variaveis
int direcao		= 1;	//N 1, S 2, L 3, O 4
int raio		= 14;
int ID			= 001;
int horas		= 18;
int minutos		= 34;
int segundos	= 55;
char msg[12];

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
}

// Anything within the USER_Loop context will execute continuously.
void fnUSER_Loop( void )
{
	if ( ID <= 10 )
	{
		fnGPIO_LED_Toggle();

		send_message(convert_int_to_string(direcao, raio, ID, horas, minutos, segundos));

		#ifdef DEBUGAR
			fnDEBUG_Uint8_Value ( "\rdirecao  : ", direcao , "\n\r");
			fnDEBUG_Uint8_Value ( "\rraio     : ", raio , "\n\r");
			fnDEBUG_Uint8_Value ( "\rID       : ", ID , "\n\r");
			fnDEBUG_Uint8_Value ( "\rhoras    : ", horas, "\n\r");
			fnDEBUG_Uint8_Value ( "\rminutos  : ", minutos, "\n\r");
			fnDEBUG_Uint8_Value ( "\rsegundos : ", segundos , "\n\r");
			fnDEBUG_Const_String ( "\rchar msg : ");
			fnDEBUG_String_Size ( msg, 12 );
			fnDEBUG_Const_String ( "\n\r");

			fnDEBUG_Const_String ( "\rmandando proxima msg\n\n\r");
			if(ID == 10)
			{
				fnDEBUG_Const_String ( "\rterminou de mandar\n\n\r");
			}
		#endif

		relogio1 = fnRTC_Get_Count();
		while(1){
			relogio2 = fnRTC_Get_Count();
			if(relogio2 > relogio1 + 10)
			{
				break;
			}
		}

		ID++;
		fnGPIO_LED_Toggle();
	}
}