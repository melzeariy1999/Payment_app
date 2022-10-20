#include "Server.h"
#include <string.h>
#include <stdio.h>



ST_accountsDB_t Data_Base[255] =
{
   {50000.00,BLOCKED,"624315266243948142"},
   {10000.00,BLOCKED,"716342849262543141"},
   {5000.00,RUNNING,"319071516046306422"},
   {2000.00,RUNNING,"519102506142340316"},
   {500.00,RUNNING,"403151216758021302"} };

ST_transaction_t Transaction_DB[255] = { 0 };
uint32_t Trans_Num = 0;
int i;
ST_terminalData_t term;
ST_cardData_t card;
ST_transaction_t trans;
ST_accountsDB_t Ref;


EN_serverError_t isValidAccount(ST_cardData_t* cardData)
{
    //this function takes PAN and checks if it in date base or not

    for (i = 0; i < 255; i++)
    {
        if (strcmp(cardData->primaryAccountNumber, Data_Base[i].primaryAccountNumber) == 0)
        {
            return SERVER_OK;
        }
    }
    return ACCOUNT_NOT_FOUND;
}

EN_serverError_t isAmountAvailable(ST_terminalData_t* termData, ST_cardData_t* cardData)
{
    //This Function is take terminal date and validate it 
    // if PAN is exist then check if TransAmount is less the Balance or not 

    if (termData->transAmount < Data_Base[i].balance)
    {
        printf("\nBalance befor Transaction:%f", Data_Base[i].balance);
        Data_Base[i].balance = (Data_Base[i].balance - termData->transAmount);
        printf("\nBalance After Transaction:%f", Data_Base[i].balance);
        return SERVER_OK;
    }
    else if (termData->transAmount > Data_Base[i].balance)
        return LOW_BALANCE;
}

EN_transState_t recieveTransactionData(ST_transaction_t* transData)
{
    transData->cardHolderData = card;

    if (isValidAccount(&card) == ACCOUNT_NOT_FOUND)
    {
        printf("FRAUD_CARD");
        return FRAUD_CARD;
    }
    else if (isBlockedAccount(&Ref) == BLOCKED_ACCOUNT)
    {
        printf("DECLINED_STOLEN_CARD");
        return DECLINED_STOLEN_CARD;
    }

    else if (isAmountAvailable(&term, &card) == LOW_BALANCE)
    {
        printf("DECLINED_INSUFFECIENT_FUND");
        return DECLINED_INSUFFECIENT_FUND;
    }
    else if (isAmountAvailable(&term, &card) == SERVER_OK)
    {
        return APPROVED;
    }
    else if (saveTransaction(transData) == SAVING_FAILED)
    {
        printf("INTERNAL_SERVER_ERROR");
        return INTERNAL_SERVER_ERROR;
    }

}

EN_serverError_t saveTransaction(ST_transaction_t* transData)
{
    if (Trans_Num <= 255)
    {


        Transaction_DB[Trans_Num].transactionSequenceNumber = transData->transactionSequenceNumber;
        Transaction_DB[Trans_Num].cardHolderData = transData->cardHolderData;
        Transaction_DB[Trans_Num].terminalData = transData->terminalData;
        Transaction_DB[Trans_Num].transState = transData->transState;
        if (getTransaction(Trans_Num, transData) == SERVER_OK)
        {
            // printf("Tran_Sec_Num=%d", transData->transactionSequenceNumber);
             //printf("\nSAVING");
            return SERVER_OK;
        }

    }
    printf("\nSAVING_FAILED");
    return SAVING_FAILED;
}

EN_serverError_t getTransaction(uint32_t transactionSequenceNumber, ST_transaction_t* transData)
{
    Trans_Num = 0;
    for (Trans_Num; Trans_Num < 255; Trans_Num++)
    {
        transData->transactionSequenceNumber = Trans_Num;
        return SERVER_OK;
    }
    return SAVING_FAILED;
}

EN_serverError_t isBlockedAccount(ST_accountsDB_t* accountRefrence)
{
    if (Data_Base[i].state == BLOCKED)
    {
        return BLOCKED_ACCOUNT;
    }
    else if (Data_Base[i].state == RUNNING)
    {
        return SERVER_OK;
    }


}