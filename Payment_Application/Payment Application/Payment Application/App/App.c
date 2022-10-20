#include"../Server/Server.h"
#include<stdio.h>

#define appStart main


void appStart(void)
{
	//Card Part

	//Card Data Structure
	ST_cardData_t card;
	ST_cardData_t* cardData = &card;


	//Calling Card Function
	if (getCardHolderName(&card) == WRONG_NAME) //this Function to get Name
	{
		printf("Name is Wrong");
		return 0;
	}
	else if (getCardExpiryDate(&card) == WRONG_EXP_DATE) //this Function to get ExpiryDate
	{
		printf("Expiry Date is Wrong");
		return 0;
	}
	else if (getCardPAN(&card) == WRONG_PAN) //this Function to get PAN
	{
		printf("primary Account Number is Wrong");
		return 0;
	}

	//Terminal Part

	//Terminal Data Structure
	ST_terminalData_t term;
	ST_terminalData_t* termData = &term;

	//Calling Terminal Function
	if (getTransactionDate(&term) == WRONG_DATE) //this Function to get Transaction Date
	{
		printf("Transaction Date is Wrong");
		return 0;
	}
	else if (IsCardExpired(&card, &termData) == EXPIRED_CARD) //this Function to check if the card is expired or not
	{
		printf("Card is Expired");
		return 0;
	}
	if (IsValidPAN(&card) == INVALID_CARD) //this Function to check if the card PAN is valid or not
	{
		printf("Card PAN is Invalid");
		return 0;
	}
	if (getTransactionAmount(&term) == INVALID_AMOUNT) //this Function to get Transaction Amount
	{
		printf("TransactionAmount is Invalid");
		return 0;
	}
	else if (setMaxAmount(&term) == INVALID_MAX_AMOUNT) //this Function to get Max Transaction Amount
	{
		printf("Max TransactionAmount is Invalid");
		return 0;
	}
	else if (IsBelowMaxAmount(&term) == EXCEED_MAX_AMOUNT) //this Function to check if Transaction Amount less than Max Transaction Amount or not
	{
		printf("Transaction Declined because of EXCEED_MAX_AMOUNT");
		return 0;
	}

	//Server Part
	ST_transaction_t trans;
	ST_transaction_t* transData = &trans;
	ST_accountsDB_t Ref;
	ST_accountsDB_t* accountRefrence = &Ref;

	//Calling Server Function
	if (isValidAccount(&card) == ACCOUNT_NOT_FOUND) //this Function to check if the acount exists in DB or not
	{
		printf("Card is Fraud");
		return 0;
	}
	else if (isBlockedAccount(&Ref)) //this Function to check if the account is blocked or not 
	{
		printf("\nDECLINED_STOLEN_CARD");
		return 0;
	}
	else if (isAmountAvailable(&term, &card) == SERVER_OK) //this Function to check the value of balance 
	{
		printf("\nSuccessful Transaction ");
		return 0;
	}
	else if (isAmountAvailable(&term, &card) == LOW_BALANCE)
	{
		printf("DECLINED_INSUFFECIENT_FUND");
		return 0;
	}
	else if (saveTransaction(&trans) == SAVING_FAILED) //this Function to validate the saving of  transaction 
	{
		printf("INTERNAL_SERVER_ERROR");
		return 0;
	}
}