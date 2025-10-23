#include "main.h"
#include "usart.h"
#include "usart1.h"
#include <stdint.h>	// C standard header; contains uint32_t, for example
#include <stm32f4xx.h>	// Header for the specific device family
#include <stdio.h> // For printf
#include <string.h>

////////////////////////////////////////////////////////////////////////////
uint16_t Value_Buf [1];
int num = 0;
int count = 0;
void displayDigit(int digit, int value);
void displayNumber(int number);

void bufclr (char *buf)
{
	int len = strlen (buf);
	for (int i=0; i<len; i++) buf[i] = '\0';
}




void GPIO_init(void){
	RCC->AHB1ENR |= (1 << 0); //Enables GPIOA peripheral
	RCC->AHB1ENR |= (1 << 1); //Enables GPIOB peripheral
	RCC->AHB1ENR |= (1 << 2); //Enables GPIOB peripheral

    GPIOA->MODER &= ~(3 << 0);      // Clear the two mode bits for PA0
    GPIOA->MODER |= (1 << 0);       // Set PA0 as Output (MODER = 0b01)
    GPIOA->OTYPER &= ~(1 << 0);     // Set PA0 as Push-Pull
    GPIOA->OSPEEDR |= (3 << 0);     // Set PA0 output speed to High
    GPIOA->PUPDR &= ~(3 << 0);      // No Pull-Up/Pull-Down for PA0

    GPIOA->MODER &= ~(3 << 2);      // Clear the two mode bits for PA1
    GPIOA->MODER |= (1 << 2);       // Set PA1 as Output (MODER = 0b01)
    GPIOA->OTYPER &= ~(1 << 1);     // Set PA1 as Push-Pull
    GPIOA->OSPEEDR |= (3 << 2);     // Set PA1 output speed to High
    GPIOA->PUPDR &= ~(3 << 2);      // No Pull-Up/Pull-Down for PA1

    GPIOA->MODER &= ~(3 << 4);      // Clear the two mode bits for PA2
    GPIOA->MODER |= (1 << 4);       // Set PA2 as Output (MODER = 0b01)
    GPIOA->OTYPER &= ~(1 << 2);     // Set PA2 as Push-Pull
    GPIOA->OSPEEDR |= (3 << 4);     // Set PA2 output speed to High
    GPIOA->PUPDR &= ~(3 << 4);      // No Pull-Up/Pull-Down for PA2

    GPIOA->MODER &= ~(3 << 6);      // Clear the two mode bits for PA3
    GPIOA->MODER |= (1 << 6);       // Set PA3 as Output (MODER = 0b01)
    GPIOA->OTYPER &= ~(1 << 3);     // Set PA3 as Push-Pull
    GPIOA->OSPEEDR |= (3 << 6);     // Set PA3 output speed to High
    GPIOA->PUPDR &= ~(3 << 6);      // No Pull-Up/Pull-Down for PA3

    GPIOB->MODER &= ~(3 << 6);      // Clear the two mode bits for PB3
    GPIOB->MODER |= (1 << 6);       // Set PB3 as Output (MODER = 0b01)
    GPIOB->OTYPER &= ~(1 << 3);     // Set PB3 as Push-Pull
    GPIOB->OSPEEDR |= (3 << 6);     // Set PB3 output speed to High
    GPIOB->PUPDR &= ~(3 << 6);      // No Pull-Up/Pull-Down for PB3

    GPIOB->MODER &= ~(3 << 8);      // Clear the two mode bits for PB4
    GPIOB->MODER |= (1 << 8);       // Set PB4 as Output (MODER = 0b01)
    GPIOB->OTYPER &= ~(1 << 4);     // Set PB4 as Push-Pull
    GPIOB->OSPEEDR |= (3 << 8);     // Set PB4 output speed to High
    GPIOB->PUPDR &= ~(3 << 8);      // No Pull-Up/Pull-Down for PB4

    GPIOB->MODER &= ~(3 << 10);     // Clear the two mode bits for PB5
    GPIOB->MODER |= (1 << 10);      // Set PB5 as Output (MODER = 0b01)
    GPIOB->OTYPER &= ~(1 << 5);     // Set PB5 as Push-Pull
    GPIOB->OSPEEDR |= (3 << 10);    // Set PB5 output speed to High
    GPIOB->PUPDR &= ~(3 << 10);     // No Pull-Up/Pull-Down for PB5

    GPIOB->MODER &= ~(3 << 12);     // Clear the two mode bits for PB6
    GPIOB->MODER |= (1 << 12);      // Set PB6 as Output (MODER = 0b01)
    GPIOB->OTYPER &= ~(1 << 6);     // Set PB6 as Push-Pull
    GPIOB->OSPEEDR |= (3 << 12);    // Set PB6 output speed to High
    GPIOB->PUPDR &= ~(3 << 12);     // No Pull-Up/Pull-Down for PB6

    GPIOB->MODER &= ~(3 << 14);     // Clear the two mode bits for PB7
    GPIOB->MODER |= (1 << 14);      // Set PB7 as Output (MODER = 0b01)
    GPIOB->OTYPER &= ~(1 << 7);     // Set PB7 as Push-Pull
    GPIOB->OSPEEDR |= (3 << 14);    // Set PB7 output speed to High
    GPIOB->PUPDR &= ~(3 << 14);     // No Pull-Up/Pull-Down for PB7

    GPIOB->MODER &= ~(3 << 16);     // Clear the two mode bits for PB8
    GPIOB->MODER |= (1 << 16);      // Set PB8 as Output (MODER = 0b01)
    GPIOB->OTYPER &= ~(1 << 8);     // Set PB8 as Push-Pull
    GPIOB->OSPEEDR |= (3 << 16);    // Set PB8 output speed to High
    GPIOB->PUPDR &= ~(3 << 16);     // No Pull-Up/Pull-Down for PB8

    GPIOB->MODER &= ~(3 << 18);     // Clear the two mode bits for PB9
    GPIOB->MODER |= (1 << 18);      // Set PB9 as Output (MODER = 0b01)
    GPIOB->OTYPER &= ~(1 << 9);     // Set PB9 as Push-Pull
    GPIOB->OSPEEDR |= (3 << 18);    // Set PB9 output speed to High
    GPIOB->PUPDR &= ~(3 << 18);     // No Pull-Up/Pull-Down for PB9

    GPIOB->MODER &= ~(3 << 20);     // Clear the two mode bits for PB10
    GPIOB->MODER |= (1 << 20);      // Set PB10 as Output (MODER = 0b01)
    GPIOB->OTYPER &= ~(1 << 10);    // Set PB10 as Push-Pull
    GPIOB->OSPEEDR |= (3 << 20);    // Set PB10 output speed to High
    GPIOB->PUPDR &= ~(3 << 20);     // No Pull-Up/Pull-Down for PB10

	GPIOA->MODER &= ~(3 << 26);     // Clear the two mode bits for PA13
	GPIOA->PUPDR &= ~(1 << 26);     // No Pull-Up/Pull-Down for PA13
	GPIOA->PUPDR &= ~(1 << 27);     // No Pull-Up/Pull-Down for PA13

	GPIOA->PUPDR &= ~(3 << 28);     // No Pull-Up/Pull-Down for PA14
	GPIOA->MODER &= ~(1 << 28);     // Clear the two mode bits for PA14
	GPIOA->PUPDR &= ~(1 << 29);     // No Pull-Up/Pull-Down for PA13

}

void Hdelay(int d){
	int i;
	while (d>0){
		for(i =0; i<2657;i++);
		d--;
	}
}

void delay(int d){
	while (d>0){
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
			Hdelay(1000);
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
        displayNumber(num);
        loop();

	}
	rxb_data[rxb_idx]= '\0';

//	}
//	usart2_tx_send(rxb_data,strlen(rxb_data));
    displayNumber(num);
    loop();
//	while(usart2_tx_is_busy());
	if ((strstr(rxb_data,string) != NULL))
	{
		usart2_tx_send(rxb_data,strlen(rxb_data));
		while(usart2_tx_is_busy());
		return true;
	}

	if ((strstr(rxb_data,"WIFI") != NULL))
	{
		usart2_tx_send("OK",strlen("OK"));
		while(usart2_tx_is_busy());
		return true;
	}

	if ((strstr(rxb_data,"GOT") != NULL))
	{
		usart2_tx_send("OK",strlen("OK"));
		while(usart2_tx_is_busy());
		return true;
	}

	if ((strstr(rxb_data,"IP") != NULL))
	{
		usart2_tx_send("OK",strlen("OK"));
		while(usart2_tx_is_busy());
		return true;
	}
    displayNumber(num);
    loop();
	return false;
}

void loop(void) {
	int count = 0;
	int ready = 1;
	int state_A ;
	int state_B ;
	int TIMEOUT = 0; // Timeout period in milliseconds

	if (ready ==1){
		displayNumber(num);
		state_A = (GPIOA->IDR &  (1 << 13)) ? GPIO_PIN_SET : GPIO_PIN_RESET;
		state_B = (GPIOA->IDR &  (1 << 14)) ? GPIO_PIN_SET : GPIO_PIN_RESET;
		while (state_A == GPIO_PIN_RESET && ready ==1){
			state_B = (GPIOA->IDR &  (1 << 14)) ? GPIO_PIN_SET : GPIO_PIN_RESET;
			displayNumber(num);
			count ++;
			if (count >1000){
				count = 0;
				ready = 0;
			}
			if (state_B == GPIO_PIN_RESET){
				ready = 0;
				count = 0;
				num++;
				Hdelay(1);
			}
			TIMEOUT++;
			if (TIMEOUT >= 2000){
				TIMEOUT = 0;
				return;
			}
		}
		state_A = (GPIOA->IDR &  (1 << 13)) ? GPIO_PIN_SET : GPIO_PIN_RESET;
		state_B = (GPIOA->IDR &  (1 << 14)) ? GPIO_PIN_SET : GPIO_PIN_RESET;
		while (state_B == GPIO_PIN_RESET && ready==1){
			state_A = (GPIOA->IDR &  (1 << 13)) ? GPIO_PIN_SET : GPIO_PIN_RESET;
			displayNumber(num);
			count ++;
			if (count >1000){
				count = 0;
				ready = 0;
			}
			if (state_A == GPIO_PIN_RESET){
				count = 0;
				ready = 0;
				if (num>0){
					num--;
				}
				delay(5000);
			}
			TIMEOUT++;
			if (TIMEOUT >= 2000){
				TIMEOUT = 0;
				return;
			}
		}
		while (ready==0){
			while (state_A == GPIO_PIN_RESET || state_B == GPIO_PIN_RESET){
				displayNumber(num);
				state_A = (GPIOA->IDR &  (1 << 13)) ? GPIO_PIN_SET : GPIO_PIN_RESET;
				state_B = (GPIOA->IDR &  (1 << 14)) ? GPIO_PIN_SET : GPIO_PIN_RESET;
				TIMEOUT++;
				if (TIMEOUT >= 2000){
					TIMEOUT = 0;
					ready = 1;
					return;
				}
			ready = 1;
			Hdelay(1);
			}
		}
	}

}

void displayDigit(int digit, int value)
{
    switch (digit)
    {
    case 1:
    	GPIOA->ODR |= (1 << 0);
        break;
    case 2:
    	GPIOA->ODR |= (1 << 1);
        break;
    }
    switch (value)
    {
    case 0:
    	GPIOB->ODR |= (1 << 3);
    	GPIOB->ODR |= (1 << 4);
    	GPIOB->ODR |= (1 << 5);
    	GPIOB->ODR |= (1 << 6);
    	GPIOB->ODR |= (1 << 7);
    	GPIOB->ODR |= (1 << 8);

    	GPIOB->ODR &= ~(1 << 9);
    	GPIOB->ODR &= ~(1 << 10);
        break;
    case 1:
    	GPIOB->ODR |= (1 << 4);
    	GPIOB->ODR |= (1 << 5);

    	GPIOB->ODR &= ~(1 << 3);
    	GPIOB->ODR &= ~(1 << 6);
    	GPIOB->ODR &= ~(1 << 7);
    	GPIOB->ODR &= ~(1 << 8);
    	GPIOB->ODR &= ~(1 << 9);
    	GPIOB->ODR &= ~(1 << 10);
        break;
    case 2:
    	GPIOB->ODR |= (1 << 3);
    	GPIOB->ODR |= (1 << 4);
    	GPIOB->ODR |= (1 << 6);
    	GPIOB->ODR |= (1 << 7);
    	GPIOB->ODR |= (1 << 9);

    	GPIOB->ODR &= ~(1 << 5);
    	GPIOB->ODR &= ~(1 << 8);
    	GPIOB->ODR &= ~(1 << 10);
        break;
    case 3:
    	GPIOB->ODR |= (1 << 3);
    	GPIOB->ODR |= (1 << 4);
    	GPIOB->ODR |= (1 << 5);
    	GPIOB->ODR |= (1 << 6);
    	GPIOB->ODR |= (1 << 9);

    	GPIOB->ODR &= ~(1 << 7);
    	GPIOB->ODR &= ~(1 << 8);
    	GPIOB->ODR &= ~(1 << 10);
        break;
    case 4:
    	GPIOB->ODR |= (1 << 4);
    	GPIOB->ODR |= (1 << 5);
    	GPIOB->ODR |= (1 << 8);
    	GPIOB->ODR |= (1 << 9);

    	GPIOB->ODR &= ~(1 << 3);
    	GPIOB->ODR &= ~(1 << 6);
    	GPIOB->ODR &= ~(1 << 7);
    	GPIOB->ODR &= ~(1 << 10);
        break;
    case 5:
    	GPIOB->ODR |= (1 << 3);
    	GPIOB->ODR |= (1 << 5);
    	GPIOB->ODR |= (1 << 6);
    	GPIOB->ODR |= (1 << 8);
    	GPIOB->ODR |= (1 << 9);

    	GPIOB->ODR &= ~(1 << 4);
    	GPIOB->ODR &= ~(1 << 7);
    	GPIOB->ODR &= ~(1 << 10);
        break;
    case 6:
    	GPIOB->ODR |= (1 << 5);
    	GPIOB->ODR |= (1 << 6);
    	GPIOB->ODR |= (1 << 7);
    	GPIOB->ODR |= (1 << 8);
    	GPIOB->ODR |= (1 << 9);
    	GPIOB->ODR |= (1 << 3);

    	GPIOB->ODR &= ~(1 << 4);
    	GPIOB->ODR &= ~(1 << 10);
        break;
    case 7:
    	GPIOB->ODR |= (1 << 3);
    	GPIOB->ODR |= (1 << 4);
    	GPIOB->ODR |= (1 << 5);
    	GPIOB->ODR |= (1 << 8);

    	GPIOB->ODR &= ~(1 << 6);
    	GPIOB->ODR &= ~(1 << 7);
    	GPIOB->ODR &= ~(1 << 9);
    	GPIOB->ODR &= ~(1 << 10);
        break;
    case 8:
    	GPIOB->ODR |= (1 << 3);
    	GPIOB->ODR |= (1 << 4);
    	GPIOB->ODR |= (1 << 5);
    	GPIOB->ODR |= (1 << 6);
    	GPIOB->ODR |= (1 << 7);
    	GPIOB->ODR |= (1 << 8);
    	GPIOB->ODR |= (1 << 9);

    	GPIOB->ODR &= ~(1 << 10);
        break;
    case 9:
    	GPIOB->ODR |= (1 << 3);
    	GPIOB->ODR |= (1 << 4);
    	GPIOB->ODR |= (1 << 5);
    	GPIOB->ODR |= (1 << 6);
    	GPIOB->ODR |= (1 << 8);
    	GPIOB->ODR |= (1 << 9);

    	GPIOB->ODR &= ~(1 << 7);
    	GPIOB->ODR &= ~(1 << 10);
        break;
    }
}
void displayNumber(int number)
{
    int digit3 = (number / 10) % 10;
    int digit4 = number % 10;
	GPIOA->ODR &= ~(1 << 0);
	GPIOA->ODR &= ~(1 << 1);
	GPIOA->ODR &= ~(1 << 2);
	GPIOA->ODR &= ~(1 << 3);
    displayDigit(2, digit3);
    Hdelay(1);

	GPIOA->ODR &= ~(1 << 0);
	GPIOA->ODR &= ~(1 << 1);
	GPIOA->ODR &= ~(1 << 2);
	GPIOA->ODR &= ~(1 << 3);
    displayDigit(1, digit4);
    Hdelay(1);
}


void ESP_Send_Multi (char *APIkey, int numberoffields, uint16_t value[])
{
	char local_buf[500] = {0};
	char local_buf2[30] = {0};
	char field_buf[200] = {0};

    //Connect to Thingspeak IP 184.106.153.149
	usart1_tx_send("AT+CIPSTART=\"TCP\",\"184.106.153.149\",80\r\n", sizeof("AT+CIPSTART=\"TCP\",\"184.106.153.149\",80\r\n")-1);
	while(usart1_tx_is_busy());

	//
    displayNumber(num);
    loop();
    //

	sprintf (local_buf, "GET /update?api_key=%s", APIkey);

    displayNumber(num);
    loop();


	sprintf(field_buf, "&field%d=%u",3, value[0]);
	strcat (local_buf, field_buf);

    displayNumber(num);
    loop();

	strcat(local_buf, "\r\n");
	int len = strlen (local_buf);
	sprintf (local_buf2, "AT+CIPSEND=%d\r\n", len);

	//
    displayNumber(num);
    loop();
    //

	usart1_tx_send(local_buf2,sizeof(local_buf2)-1); //Send length of data to send
	while(usart1_tx_is_busy());
	Hdelay(100);

    displayNumber(num);
    loop();
	//while (!(Wait_for(">")));
	usart1_flush();
	usart2_flush();

    displayNumber(num);
    loop();

	usart1_tx_send(local_buf,sizeof(local_buf)-1); //Send actual data to Thingspeak
	while(usart1_tx_is_busy());
	//while (!(Wait_for("SEND OK\r\n")));
	//while (!(Wait_for("CLOSED")));

    displayNumber(num);
    loop();

	usart2_tx_send("DATA SENT.\r\n",sizeof("DATA SENT.\r\n")-1); //If printed, data sent is successful
	while(usart2_tx_is_busy());
	//
    displayNumber(num);
    loop();
    displayNumber(num);
    //
	bufclr(local_buf); //Clear buffers
	bufclr(local_buf2);
	displayNumber(num);

    displayNumber(num);
    loop();
}

void ESP_Init (char *SSID, char *PASSWD)
{
	char data[100];
	usart2_init();
	usart1_init();

	usart2_tx_send("AT+RST\r\n",strlen("AT+RST\r\n"));
	while(usart2_tx_is_busy());
	usart1_tx_send("AT+RST\r\n",sizeof("AT+RST\r\n")-1); //AT+RST to WIFI
	while(usart1_tx_is_busy());
	Hdelay(1000);


	usart2_tx_send("AT\r\n",strlen("AT\r\n"));
	while(usart2_tx_is_busy());
	do{
	usart1_tx_send("AT\r\n",sizeof("AT\r\n")-1); //AT to WIFI
	while(usart1_tx_is_busy());
	Hdelay(1000);
	}while(!(Wait_for("OK")));

	usart2_tx_send("AT+CWMODE\r\n",strlen("AT+CWMODE\r\n"));
	while(usart2_tx_is_busy());
	do{
	usart1_tx_send("AT+CWMODE=1\r\n",sizeof("AT+CWMODE=1\r\n")-1); //AT+CWMODE to WIFI
	while(usart1_tx_is_busy());
	Hdelay(1000);
	}while(!(Wait_for("OK")));

	usart2_tx_send("AT+CJWAP\r\n",strlen("AT+CJWAP\r\n"));
	while(usart2_tx_is_busy());

	sprintf(data, "AT+CWJAP=\"%s\",\"%s\"\r\n", SSID, PASSWD);
	usart1_tx_send(data,sizeof(data)-1); //AT+CWJAP to WIFI
	while(usart1_tx_is_busy());
	Hdelay(1000);
	data[0] = '\0';

	sprintf(data, "Connected to,\"%s\"\n\n", SSID);
	usart2_tx_send(data,sizeof(data)-1);
	while(usart2_tx_is_busy());
}


int main (void)
{
	int counter = 0;
	GPIO_init();
	ESP_Init("EEE192-429","EEE192_Room429");
	do{
	while(1)
	{
    	if (num <=0){
    		num =0;
    	}

        displayNumber(num);
        loop();
        displayNumber(num);
        Value_Buf[0] = num; //Make buffer with 2 Values
        displayNumber(num);
        if (counter == 500){
        	ESP_Send_Multi("MSSMYZGGBZHZ3NNO", 1, Value_Buf); //Send to Thingspeak with API Key MSSMYZGGBZHZ3NNO
        	counter = 0;
        }
        displayNumber(num);
        loop();
        counter += 1;
	}
	}while(0);
}
