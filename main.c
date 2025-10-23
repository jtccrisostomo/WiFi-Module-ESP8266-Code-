
#include "usart.h"
#include "usart1.h"
#include <stdint.h>	// C standard header; contains uint32_t, for example
#include <stm32f4xx.h>	// Header for the specific device family
#include <stdio.h> // For printf
#include <string.h>

////////////////////////////////////////////////////////////////////////////



void Hdelay(int d){
	int i;
	while (d>0){
		for(i =0; i<2657;i++);
		d--;
	}
}



bool Wait_for(char *string)
{
	char		rxb_data[128];
	unsigned int	rxb_idx  = 0;
	memset(rxb_data,0,sizeof(rxb_data));

	while(1)
	{
		struct usart1_rx_event evt1;
			// USART1 event
		if (!usart1_rx_get_event(&evt1))
			// Nothing to do here
		{
			usart2_tx_send("empty",sizeof("empty")-1);
//			while(usart2_tx_is_busy());
			break;}
		else if (!evt1.valid)
			break;
		/*
		 * [1] If an IDLE is detected, update the size.
		 *
		 * [2] If no data is present, we're done.
		 */
		if (evt1.is_idle) {
			break;
		}
		if (!evt1.has_data) {
			break;
		}

		// Store the data
		if (rxb_idx >= sizeof(rxb_data)) {
			break;
		}
//		usart2_tx_send("way",sizeof("way")-1);
		rxb_data[rxb_idx++] = evt1.c;

	}
	rxb_data[rxb_idx]= '\0';
//	}
	if ((strstr(rxb_data,string) != NULL))
	{
		usart2_tx_send(rxb_data,sizeof(rxb_data)-1);
		while(usart2_tx_is_busy());
	}

//	if (strcmp(rxb_data,"OK")==0){
//		return true;
//	}
	return (strstr(rxb_data,string) != NULL);
}

void ESP_Init (char *SSID, char *PASSWD)
{

	char data[100];
	usart2_init();
	Hdelay(100);
	usart1_init();
	do{
		Hdelay(100);
		usart1_tx_send("AT+RESTORE\r\n",sizeof("AT+RESTORE\r\n")-1);
		Hdelay(100);
		while(usart1_tx_is_busy());
		Hdelay(30);
//		usart2_tx_send("infinite",sizeof("infinite")-1);
//		while(usart2_tx_is_busy());
	}while(!(Wait_for("OK")));

	Hdelay(40);
	usart2_tx_send("\n\r AT+REST DONE\n\n",sizeof("\n\r AT+REST DONE\n\n")-1);
	while(usart2_tx_is_busy());
	Hdelay(20);
	/********* AT **********/
	do{
		Hdelay(40);
		usart1_tx_send("AT\r\n",sizeof("AT\r\n")-1);
		while(usart1_tx_is_busy());
		Hdelay(30);
//		usart2_tx_send("infinite",sizeof("infinite")-1);
//		while(usart2_tx_is_busy());
	}while(!(Wait_for("OK")));


	Hdelay(40);
	usart2_tx_send("\n\r AT DONE\n\n",sizeof("\n\r AT DONE\n\n")-1);
	while(usart2_tx_is_busy());
	Hdelay(20);
//
	do{
		Hdelay(40);
		usart1_tx_send("AT+RST\r\n",sizeof("AT+RST\r\n")-1);
		while(usart1_tx_is_busy());
	}while(!(Wait_for("OK")));

	Hdelay(40);
	usart2_tx_send("\n AT+RST DONE\n\n",sizeof("\n AT+RST DONE\n\n")-1);
	while(usart2_tx_is_busy());
//	Hdelay(2);
//	usart2_tx_send("RESETTING.\r\n",sizeof("RESETTING.\r\n")-1);
//	while(usart2_tx_is_busy());
//	Hdelay(2);
//
	do{
		Hdelay(40);
		sprintf(data, "AT+CWJAP =\"%s\", \"%s\"\r\n", SSID, PASSWD);
		usart1_tx_send(data,sizeof(data)-1);
		while(usart1_tx_is_busy());
	}while(!(Wait_for("OK")));
//
	Hdelay(40);
	usart2_tx_send("\n AT+CWJAP DONE\n\n",sizeof("\n AT+CWJAP DONE\n\n")-1);
	while(usart2_tx_is_busy());
//
//	/********* AT+CWJAP="SSID","PASSWD" **********/
//	usart2_tx_send("\n connecting to the provided AP\r\n",sizeof("\n connecting to the provided AP\r\n")-1);
//	while(usart2_tx_is_busy());
//	Hdelay(2);
//	sprintf (data, "AT+CWJAP =\"%s\", \"%s\"\r\n", SSID, PASSWD);
//
//	usart1_tx_send(data,sizeof(data)-1);
//	while (usart1_tx_is_busy());
//	while(!(Wait_for("WIFI CONNECTED")));
//	while(!(Wait_for("WIFI GOT I{")));
//	while(!(Wait_for("OK")));
//	Hdelay(2);
//	sprintf (data, "Connected to \"%s\"\n\n", SSID);
//	usart2_tx_send(data,sizeof(data)-1);
//	while(usart2_tx_is_busy());
//	usart2_flush();
//	Hdelay(2);
}


int main (void)
{

	ESP_Init("Sandeng","Sandeng<3");
	while(1)
	{
		continue;
	}

}
