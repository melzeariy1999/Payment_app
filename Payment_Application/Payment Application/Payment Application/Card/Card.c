#include <stdio.h>
#include <string.h>
#include "Card.h"

#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_WARNINGS

EN_cardError_t getCardHolderName(ST_cardData_t* cardData)
{

	// This function will ask for the Card Holder Name and store it into card data.
	// Card Holder Name must be  24 String Max and 20 min and can not be Null.

	printf("Please Enter Card Data:");
	printf("\nPlease Enter card Holder Name: \t ");
	gets(cardData->cardHolderName);

	if (strlen(cardData->cardHolderName) < 20 || strlen(cardData->cardHolderName) > 24 || cardData->cardHolderName == NULL)
	{

		return WRONG_NAME;

	}
	else {

		return CARD_OK;

	}

}

EN_cardError_t getCardExpiryDate(ST_cardData_t* cardData)
{

	//This function will ask for the card expiry date and store it in card data.
	//card expiry date must be in this Format (MM/YY) and have only 5 Strings.

	printf("Plese Enter Card Expiration Date: \t(MM/YY)\t");
	gets(cardData->cardExpirationDate);

	if (strlen(cardData->cardExpirationDate) != 5 || cardData->cardExpirationDate == NULL || cardData->cardExpirationDate[3] < '2' || cardData->cardExpirationDate[4] < '2') {

		return WRONG_EXP_DATE;
	}
	else if (cardData->cardExpirationDate[0] >= '2' || cardData->cardExpirationDate[3] < '2' || cardData->cardExpirationDate[2] != '/')
	{
		return WRONG_EXP_DATE;
	}
	else if (cardData->cardExpirationDate[0] = '1' & cardData->cardExpirationDate[1] > '2')
	{
		return WRONG_EXP_DATE;
	}
	else if (cardData->cardExpirationDate[3] = '2' & cardData->cardExpirationDate[1] > '2')
	{
		return WRONG_EXP_DATE;
	}
	else
	{
		return CARD_OK;
	}

}

EN_cardError_t getCardPAN(ST_cardData_t* cardData)
{

	//This Function ask for PAN.
	//PAN must be between 16 and 19 strings and can not be Null.

	printf("\nPlese Enter primary Account Number:\t");
	gets(cardData->primaryAccountNumber);

	if (strlen(cardData->primaryAccountNumber) > 19 || strlen(cardData->primaryAccountNumber) < 16)
	{
		return WRONG_PAN;
	}
	else if (cardData->primaryAccountNumber == NULL)
	{
		return WRONG_PAN;
	}
	else {
		return CARD_OK;
	}

}
