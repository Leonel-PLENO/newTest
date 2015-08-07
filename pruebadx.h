/**
 * \file
 *
 * \brief Empty user application template
 *
 */

/**
 * \mainpage User Application template doxygen documentation
 *
 * \par Empty user application template
 *
 * Bare minimum empty user application template
 *
 * \par Content
 *
 * -# Include the ASF header files (through asf.h)
 * -# Minimal main function that starts with a call to board_init()
 * -# "Insert application code here" comment
 *
 */
 
 Cambios desde una cuenta distina


//Cambios ecternos a la aplicación de GitHub

//Cambios para observar la prueba de actualización desde el navegador en GitHub


/*
 * Include header files for all drivers that have been imported from
 * Atmel Software Framework (ASF).
 */
#include <asf.h>

#include <Main.h>
#include <./System.h>
#include <./Com_1.h>
#include <./Com_0.h>

 
#include <./Twi.h>
//#include <./Bitmap.h>
#include <./ks0108.h>
#include <./fonts.h>
//--- Local Variables
	//--- For cluster's Tests
		unsigned int t_Vline[48]=	{0,  1,  2,  3,     32, 33, 34, 35,    64, 65, 66, 67,
									 96, 97, 98, 99,   128,129,130,131,   160,161,162,163,
									192,193,194,195,   224,225,226,227,   256,257,258,259,
									288,289,290,291,   320,321,322,323,   352,353,354,355
									};
//--- Main Function 

int main (void){
	



//Rutinas lineales de inicio		
		Systemini();
	
//		while(1)wdt_reset();
		
//------------------ Pruebas  ------------------ 	
	/*
		clear_mix_scr_buffer();
		printLCD("pleno",Arial_Bold_14,45 ,8,BLACK,2);
		//printLCD("www.pleno.mx",Arial_Bold_14,12 ,8,BLACK,2);
		copy_mix_to_img_buffer();			
		Trans_ram_matrix_dyn_0108();
		
		while(1)wdt_reset();
	*/
	/*
	pr_screen_flags|=0x10;
	pr_flash_line=1;
	pr_flash_pos=3;
	//*/
	
	/*
	pr_clear_wscreen();
	pr_write_digit(0, 0, D_b);
	pr_write_digit(0, 1, D_i);
	pr_write_digit(0, 2, D_E);
	pr_write_digit(0, 3, D_n);
//	*/
//---------------------------------------------- 	
//*
//	static uint8_t fmt=10;		//Mt pointer 
//	static uint8_t fstate=0;	//Holds current MT sub function pointer 
		
	while (1){		
		ADC_capture_handler();			
		mo_wiz_trama();			//Screen communications 
		Boton ();				//Push button handler
		bright_transition();	//Screen intensity Handler	
		Ir_response ();	
		xbee_ready_indicator();	
			
		led_screen_handler();	//Screen Image sequences handler		
		pr_flash_digit();		
		pr_rf_handler();
		buzz_handler();
		pr_mode_handler();
		
		
		
		//main_test_mt();
		
		/*			
		switch (fmt){																							
			case 0:	
			
			
							
				break;
		}
		*/	
		if(!(mainflags&0x10))wdt_reset();else; //Watch dog timer service
   }
//*/   
return 0;	
}

/*
 *	
 */
void led_screen_handler(void){
	//if (main_mode==1)Prueba_pant();		//General test
	if (main_mode==1){main_test_mt();pr_scr_refresh();}
	//else if (main_mode==2)Prueba_lvert(); 	
	else if (main_mode==2)Prueba_pant(); 	
	else if (main_mode==3)Prueba_lhz();		
	else if (main_mode==4) pr_scr_refresh();
	else pr_scr_refresh();
	//else if (main_mode==4) mo_scr_banner();
	//else mo_scr_banner();
}


/*------------------------------------------------------------
						xbee_ready_indicator()
--------------------------------------------------------------*/
void main_test_mt (void){
	static uint8_t fmt=0;
	static uint8_t t_counter=0;
	static uint8_t t_pos=0;
	static uint8_t t_line=0;
	
	switch(fmt){
		case 0:
			pr_write_digit(t_line,t_pos,t_counter);	
			
			fprfl=0;	
			ppant_timer1=0;
			ppant_timer1_max=SYSTEM_TIMER_500MS;
			ppant_timer_flags|=0x80;	
			fmt=1;			
			break;
		case 1:
			if(!(ppant_timer_flags&0x80)){
				if(t_counter<9)t_counter++;
				else {
					t_counter=0;
					//for(uint16_t i=0; i<PR_WSCR_BUFFSIZE; i++) pr_screen_buffer [i] = 0;
					pr_clear_digit(t_line, t_pos);
					
					if(t_pos<3)t_pos++;
					else{
					 t_pos=0;
					 if(t_line==0)t_line=1;else t_line=0;						 			
					}
				}
				fmt=0;
			}else;
			break;	
	}
}

/***********************************************************************
							Main_ini()
***********************************************************************/
void Main_ini(void){
	//--- main		
		mainflags=0b10000100;  //Banderas de main ---Public
		mainflags&=0xFD;	//Borra bandera Online Modo stand alone
//		if (!(EEPROM_read(add_RSLGPLN_Ena)))mainflags|=0x08;else; // Habilita Logo pleno on RESET 
		//else mainflags&=0xF7; //Inhabilita Logo pleno on RESET
		main_mode=4; //Modo de operación --Exhibición de LOGO
	//--- Prueba_pant	
		fp_pant=0;	//Registro MT		
		ipant=0;	//Acumulador para alimentación de trama
	    tpant=0;	//Acumulador para conteo de tramas
		ppant_timer_flags=0;//Banderas timer prueba pantalla ---Public
		ppant_timer1_max=0;	//Puntero tope timer1 pantalla ---Public
		ppant_timer1=0;		//Acumulador timer1 pantalla ---Public
	//	bdbnc_max; (No necesario iniciar)	//Puntero tope acumulador button debouncer timer --- Public
		bdbnc=0;			//Acumulador button debouncer timer --- Public
		tto=0;				//Acumulador Test timeout --- Public
	//--- Prueba_lvert
		fplv=0;		//Registro MT
		s_line=0;	//Posición de línea para prueba
	//--- Prueba_lhz
		flhz=0;		//Registro MT
		h_line=23;	//Posición de línea para prueba
		/*
			h_lb1;(No necesario iniciar)	//Línea a encender en bloque 1 (top)
			h_lb2;(No necesario iniciar)	//Línea a encender en bloque 2 (Middle)
			h_lb3;(No necesario iniciar)	//Línea a encender en bloque 3 (Bottom)	
			mblock;(No necesario iniciar)	//No. Minibloque
			char mbline;(No necesario iniciar)	//No. línea en minibloque
			mblpix;(No necesario iniciar)	//No. pixel en línea de minibloque
		*/		
	//--- Pleno_logo
		fpll=0;		//Registro MT
		//scroll;(No necesario iniciar)	//temporal para exhibición
	//--- Boton
		fboton=0;		//Registro MT
	
	//---- xbee_ready_indicator
	    mt_init_flags=0;
		mt_init_timer1=0;
		mt_init_timer1_max=0;
		
	//--- Other functions
		mo_scr_load_scr_prm();		//Load Banner screen parameters
		
}
/***********************************************************************
						Prueba_pant()
***********************************************************************/
void Prueba_pant(void){
	switch (fp_pant){
		case 0:
			for (ipant=0;ipant<1024;ipant++){			
				if (ipant&0x01){DT1_H;}else {DT1_L;}	//Lineas verticales
				if (ipant&0x04){DT2_H;}else {DT2_L;}	//Lineas horizontales
				if (((ipant&0x10)&&!(ipant&0x20))||(!(ipant&0x10)&&(ipant&0x20))){DT3_H;}else {DT3_L;} //Moños
				if (tpant&0x02){if(ipant&0x40){DT3_L;}else;}else{if(!(ipant&0x40)){DT3_L;}else;}	//Apaga moño alternado
				//if (ipant&0x01){DT4_H;DT8_H;}else {DT4_L;DT8_L;}	//Lineas verticales	
				//CK1_H;CK2_H;CK3_H;CK_delay;	CK1_L;CK2_L;CK3_L;CK_delay;	//Pulso CK
				PCK_H;CK_delay;PCK_L;CK_delay;	//Pulso CK
			}
			//LT1_H;LT2_H;LT3_H;DT_delay;LT1_L;LT2_L;LT3_L;DT_delay;  	//Pulso LATCH
			PLT_H;DT_delay;PLT_L;DT_delay;  	//Pulso LATCH
			ppant_timer1_max=1953;		//Establece 500 ms
			ppant_timer_flags|=0x80;	//Activa timer
			fp_pant=1;		
			break;
		case 1:
			if(!(ppant_timer_flags&0x80)){	//Retardo		
				if (!(mainflags&0x01))fp_pant=2;else;	//Si pausa no hace cambios				
			}
			else;	
			break;
		case 2:
			for (ipant=0;ipant<1024;ipant++){		
				if (ipant&0x01){DT1_L;}else {DT1_H;}							
				if (ipant&0x04){DT2_L;}else {DT2_H;}
				if (((ipant&0x10)&&!(ipant&0x20))||(!(ipant&0x10)&&(ipant&0x20))){DT3_L;}else {DT3_H;}				
				if (tpant&0x02){if(ipant&0x40)DT3_L;else;}else{if(!(ipant&0x40)){DT3_L;}else;}
				//if (ipant&0x01){DT4_L;DT8_L;}else {DT4_H;DT8_H;}	
				//CK1_H;CK2_H;CK3_H;CK_delay;CK1_L;CK2_L;CK3_L;CK_delay;
				PCK_H;CK_delay;PCK_L;CK_delay;	//Pulso CK
			}		
			//LT1_H;LT2_H;LT3_H;DT_delay;LT1_L;LT2_L;LT3_L;DT_delay;
			PLT_H;DT_delay;PLT_L;DT_delay;  	//Pulso LATCH
			tpant++;
			ppant_timer1_max=1953;		//Establece 500 ms
			ppant_timer_flags|=0x80;	//Activa timer
			fp_pant=3;			
			break;
		case 3:
			if(!(ppant_timer_flags&0x80)){
				if (!(mainflags&0x01))fp_pant=0;else; //Si pausa no hace cambios
			}else;	//Retardo		
			break;
	}
}

/**********************************************************************
							Prueba_lvert()
***********************************************************************/
void Prueba_lvert(void){
	switch (fplv){
		case 0:
			for (ipant=0;ipant<256;ipant++){			
				if (ipant==t_Vline[s_line]){DT1_H;DT2_H;DT3_H;}
				else if (ipant==(4+t_Vline[s_line])){DT1_H;DT2_H;DT3_H;}
				else if (ipant==(8+t_Vline[s_line])){DT1_H;DT2_H;DT3_H;}
				else if (ipant==(12+t_Vline[s_line])){DT1_H;DT2_H;DT3_H;}
				else if (ipant==(16+t_Vline[s_line])){DT1_H;DT2_H;DT3_H;}
				else if (ipant==(20+t_Vline[s_line])){DT1_H;DT2_H;DT3_H;}
				else if (ipant==(24+t_Vline[s_line])){DT1_H;DT2_H;DT3_H;}
				else if (ipant==(28+t_Vline[s_line])){DT1_H;DT2_H;DT3_H;}
				else {DT1_L;DT2_L;DT3_L;}			
			PCK_H;CK_delay;PCK_L;CK_delay;	//Pulso CK
			}
			PLT_H;DT_delay;PLT_L;DT_delay;  	//Pulso LATCH
			ppant_timer1_max=1250;		//Establece 500 ms
			ppant_timer_flags|=0x80;	//Activa timer
			fplv=1;
			break;
		case 1:
			if (!(mainflags&0x01)){//Si pausa no hace cambios
				if(!(ppant_timer_flags&0x80)){	//Retardo concluido			
					if (s_line<32)s_line++;else s_line=0;
					fplv=0;
				}else;	//Retardo		
			}else; 
			break;		
	
	}
}
/**********************************************************************
							Prueba_lhz()
***********************************************************************/
void Prueba_lhz(void){
	switch (flhz){
		case 0:
			h_lb2=0xFF;h_lb1=0xFF;h_lb3=0xFF;h_lb4=0xFF;
			if(h_line<8)h_lb4=h_line;			
			else if(h_line<16)h_lb3=h_line-8;							
			else if(h_line<24)h_lb2=h_line-16;
			else if(h_line<32)h_lb1=h_line-24;			
			else;		
			for (mblock=0;mblock<32;mblock++){
				for (mbline=0;mbline<8;mbline++){
					for(mblpix=0;mblpix<4;mblpix++){
						if(h_lb1==mbline){DT1_H;}else {DT1_L;}
						if(h_lb2==mbline){DT2_H;}else{DT2_L;}
						if(h_lb3==mbline){DT3_H;}else {DT3_L;}
						//if(h_lb4==mbline){DT4_H;DT8_H;}else{DT4_L;DT8_L;}
						PCK_H;CK_delay;PCK_L;CK_delay;	//Pulso CK
					}			
				}
			}			
			PLT_H;DT_delay;PLT_L;DT_delay;  	//Pulso LATCH
			ppant_timer1_max=1250;		//Establece 500 ms
			ppant_timer_flags|=0x80;	//Activa timer			
			if(h_line>0)h_line--;else h_line=31;
			flhz=1;			
			break;
		case 1:
			if (!(mainflags&0x01)){//Si pausa no hace cambios
				if(!(ppant_timer_flags&0x80)){	//Retardo concluido				
					flhz=0;
				}else;
			}else;
			break;
			
	}
}


/**********************************************************************
							Boton()
***********************************************************************/
void Boton (void){		//Respuesta a botón presionado
	switch (fboton){
		case 0:
			if (_boton_on){	//Espera hasta que esté presionado el botón		
				bdbnc_max=_boton_debounce_time;
				ppant_timer_flags&=0xFC;	//Reporta Deboucing timing, BORRA Debouncing y Longpress detection flag
				ppant_timer_flags|=0x01;	//SET Button Debouncer timer flag			
				fboton=1;
				}else;
			break;		
		case 1:			
			if (!(ppant_timer_flags&0x01)){	//Retardo debouncing terminado			
				if (_boton_on){	//Si se confirma botón presionado
					if(mainflags&0x01)mainflags&=0xFE;else mainflags|=0x01; //Play-Pausa Toggle					
					bdbnc_max=_boton_function_time;		//Carga en timer periodo función push extendido
					ppant_timer_flags|=0x03;			//Activa timer para detección de función push extendido	
					tto=0;	//Reinicia timer Test timeout
					ppant_timer_flags|=0x04;
					fboton=2;
				}else fboton=0;  //Si no hay botón presionado				
			}else;	//Deboncing en proceso
			break;			
		case 2:			
			if (_boton_off){
				
					
				
				//--- Control de inicia subrutina pleno logo
					if(!(ppant_timer_flags&0x08)){	//Si exhibición logo permitida
						if(main_mode==0)main_mode=4;else;	//Conmuta a exhibición de LOGO
					}else ppant_timer_flags&=0xF7;	//salta evaluación de exhib logo, borra solicitud
				//---Reinicia timer cambio de función					
					ppant_timer_flags&=0xFC;	//Reinicia bandera timer
					bdbnc=0;	//Reinicia contador retardo	debouncer		
				fboton=0;	//reinicia subrutina Botón
			}else;	//Espera hasta que esté liberado el botón						
			break;
	}
}


/*------------------------------------------------------------
						xbee_ready_indicator()
--------------------------------------------------------------*/
unsigned char xbee_ready_indicator (void){
	static uint8_t fmt=0;
//	static uint8_t fstate=0;	//Holds command response
//---Led Blinking 
    static uint16_t led_blink_counter=0;
	#define INIT_LED_BLINK_TIMES 150	//Number of System LED
	
	switch (fmt){
		case 0:
			
		
			fmt=10;
			//fmt=40;
			break;	
//---Delay with LED flashing
		case 10:
			_TOGGLE_USER_LED;			
			mt_init_timer1=0;	//RESET Timer tick accumulator
			mt_init_timer1_max = SYSTEM_TIMER_50MS;	//Timer_l term 
			mt_init_flags|=0x80;	//Set timer running flag
			fmt = 20;			
			break;
		case 20:
			if (!(mt_init_flags&0x80)){ //Time delay elapsed
				_TOGGLE_USER_LED;
				mt_init_timer1=0;	//RESET Timer tick accumulator
				mt_init_timer1_max = SYSTEM_TIMER_50MS;	//Timer_l term
				mt_init_flags|=0x80;	//Set timer running flag
				fmt = 30;				
			}else;
			break;		
		case 30:
			if (!(mt_init_flags&0x80)){ //Time delay elapsed
				if(++led_blink_counter<INIT_LED_BLINK_TIMES)fmt=10;
				else{
					 fmt = 40;				
					 led_blink_counter=0;
				}
			}else;
			break;
//--- Broadcast Control Card ID through USART
		case 40:			
			_St_LED_off;			//Led Verde
			_St_LED_G_on;
			fmt=41;	
			break;		
	//---End of switch reached
	}
	if (fmt==255){fmt=0; return 255;}
	else return fmt;
//---End of function reached		
}
