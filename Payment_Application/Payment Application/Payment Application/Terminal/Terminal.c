#include <stdio.h>
#include <string.h>
#include "Terminal.h"
#include "../Card/Card.h"

EN_terminalError_t getTransactionDate(ST_terminalData_t* termData) {

	//This function ask for the transaction data and store it in terminal data.
	//the transaction data must be in this Form (DD/MM/20YY)  and has 10 strings and can not be Null.

	printf("\nPlease Enter Transaction Date: \t DD/MM/20YY \t");
	gets(termData->transactionDate);

	if (termData->transactionDate == NULL || strlen(termData->transactionDate) != 10 || termData->transactionDate[0] > '2' || termData->transactionDate[2] != '/')
	{
		return WRONG_DATE;
	}
	else if (termData->transactionDate[5] != '/' || termData->transactionDate[6] < '2' || termData->transactionDate[8] < '2')
	{
		return WRONG_DATE;
	}
	else if (termData->transactionDate[8] = '2' && termData->transactionDate[9] < '2')
	{
		return WRONG_DATE;
	}
	else if (termData->transactionDate[1] = '3' && termData->transactionDate[2] > '0')
	{
		return WRONG_DATE;
	}
	else if (termData->transactionDate[3] = '1' && termData->transactionDate[4] > '2')
	{
		return WRONG_DATE;
	}
	else
	{
		return TERMINAL_OK;
	}
}

EN_terminalError_t IsCardExpired(ST_cardData_t cardData, ST_terminalData_t termData) {

	// This Function Compare Transaction Data with Expiry Data.
	// if Transaction Data > Expiry Data the Card will be expired else the Card will not be expired.

	char ED_Years = 0, ED_Months = 0, TD_Years = 0, TD_Months = 0;

	ED_Years = ((cardData.cardExpirationDate[3] * 10) + cardData.cardExpirationDate[4]);
	ED_Months = ((cardData.cardExpirationDate[0] * 10) + cardData.cardExpirationDate[1]);

	TD_Years = ((termData.transactionDate[8] * 10) + termData.transactionDate[9]);
	TD_Months = ((termData.transactionDate[3] * 10) + cardData.cardExpirationDate[4]);

	if (ED_Years > TD_Years)
	{

		return TERMINAL_OK;
	}
	else if (ED_Years == TD_Years && TD_Months < ED_Months)
	{
		return TERMINAL_OK;
	}
	else
	{
		return EXPIRED_CARD;
	}
}

EN_terminalError_t getTransactionAmount(ST_terminalData_t* termData)
{


	//This function asks for the transaction amount and saves it into terminal data.
	// If the transaction amount is less than or equal to 0 will return INVALID_AMOUNT, else return OK.

	printf("\nPlease Enter the transaction Amount: \t");
	scanf_s("%f", &termData->transAmount);

	if (termData->transAmount == 0.0 || termData->transAmount < 0.0)
	{
		return INVALID_AMOUNT;
	}
	else
	{
		return TERMINAL_OK;
	}
}

EN_terminalError_t IsBelowMaxAmount(ST_terminalData_t* termData)
{
	//Compare between transamount and maxtransamount 
	if (termData->transAmount > termData->maxTransAmount)
	{
		return EXCEED_MAX_AMOUNT;
	}
	else
	{
		return TERMINAL_OK;
	}
}

EN_terminalError_t setMaxAmount(ST_terminalData_t* termData)
{
	//This function sets the maximum  amount into terminal data.
	// transaction max amount less than or equal to 0 will return INVALID_MAX_AMOUNT error, else return OK.

	termData->maxTransAmount = 2000;
	printf("\nMax TransAmount is:%f", termData->maxTransAmount);

	if (termData->maxTransAmount == 0 || termData->maxTransAmount < 0)
	{
		return INVALID_MAX_AMOUNT;
	}
	else
	{
		//printf("Max Amount is valid");
		return TERMINAL_OK;

	}
}


EN_terminalError_t IsValidPAN(ST_cardData_t* cardData)
{
	//Start from most right digit then double the value of every second number.
	//if doubling of second numer is greater than 9 get the sum of this number ex(12-->> =1+2=3)
	//Take the Sum of all digits if the total modulo is equall 10 the numer will be Right according to Luhn Formula

	uint8_t Luhn_Size = strlen(cardData->primaryAccountNumber);
	int i;
	int Second_Digits = 0;
	int Sum = 0;

	for (i = Luhn_Size - 1; i >= 0; i--)
	{
		uint8_t Luhn_Digit = cardData->primaryAccountNumber[i] - '0';

		if (Second_Digits % 2)
		{
			Luhn_Digit *= 2;
		}
		else
		{
			Luhn_Digit *= 1;
		}

		Sum += Luhn_Digit / 10;
		Sum += Luhn_Digit % 10;
		Second_Digits++;
	}
	if (Sum % 10 == 0) {
		return  TERMINAL_OK;
	}
	else {
		return INVALID_CARD;
	}
}

