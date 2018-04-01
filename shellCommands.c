//
//  shellCommands.c
//  practice
//
//  Created by Nagarjuna Pamidi on 3/31/18.
//  Copyright © 2018 Nagarjuna Pamidi. All rights reserved.
//

#include "shellCommands.h"

struct subscribersInfo mySubscribersList;

void parseShellCommands(const char *buffer)
{
    
    //main menu
    //TBD//Implement sub-menu
    if(shellMenuStatus==0)
    {
        //"add" command
        if(KMPsearch(buffer, ADD_SUBSCRIBER))
        {
            //only +1 country code is allowed!
            if(KMPsearch(buffer, US_CANADA_COUNTRY_CODE))
            {
                //remove "add +" form the rx buffer and validate the phone number
                if (!validatePhoneNum(&buffer[ADD_SUBSCRIBER_STRLEN+1]))
                {
                    sendShellResponse("\nInvalid Phone Number!");
                }
                else
                {
                    addNewSubscriberNum(&buffer[ADD_SUBSCRIBER_STRLEN]);
                }
            }
            //other country codes are not allowed
            else if (KMPsearch(buffer, "+"))
            {
                sendShellResponse("Note: Only USA/Canada phones allowed!");
            }
            //Country code required
            else
            {
                sendShellResponse("Enter countery code!");
            }
        }
        
        //"remove" command
        else if (KMPsearch(buffer, REMOVE_SUBSCRIBER))
        {
            removeSubscriberInfo(atoi(&buffer[REMOVE_SUBSCRIBER_STRLEN])-1);
        }
        
        else if (KMPsearch(buffer, DISPLAY_SUBSCRIBER_LIST))
        {
            displayAllSubscribers();
        }
        else if (KMPsearch(buffer, SHELL_HELP))
        {
            sendShellResponse(SHELL_HELP_RESPONSE);
        }
        else if(buffer[0]=='\n')
        {
            //do nothing
        }
        else
        {
            sendShellResponse("\nCommand not found! Enter \"help\" to show available commands");
        }
    }
    else if(shellMenuStatus==1)
    {
        //TBD//implement sub-menu
        
        shellMenuStatus = 0;
        addNewSubscriberName(buffer);
    }
}


static void addNewSubscriberNum(const char *subscriberMobileNumb)
{
    if(mySubscribersList.subscriberIdx < MAX_SUBSCRIBERS)
    {
        
        strncpy (mySubscribersList.mobileNum[mySubscribersList.subscriberIdx], subscriberMobileNumb, MAX_PHONE_NUM_LENGTH); //copy mobile number
        mySubscribersList.mobileNum[mySubscribersList.subscriberIdx][MAX_PHONE_NUM_LENGTH] = '\0'; //Null Terminate string

        sendShellResponse("\nEnter subscriber full name: ");
        //addNewSubscriberName(ReceivedSTring); //TBD//more accurate sub-menu
        shellMenuStatus = 1;
    }
    else
    {
        sendShellResponse("List is full!");
    }
}

static void addNewSubscriberName(const char *subscriberFullName)
{
    if(mySubscribersList.subscriberIdx < MAX_SUBSCRIBERS)
    {
        
        strncpy (mySubscribersList.fullName[mySubscribersList.subscriberIdx], subscriberFullName, strlen(subscriberFullName)-1); //copy name
        mySubscribersList.fullName[mySubscribersList.subscriberIdx][MAX_FULLNAME_LENGTH] = '\0'; //Null Terminate string
        ++mySubscribersList.subscriberIdx;
        displayAllSubscribers();
    }
    else
    {
        sendShellResponse("List is full!");
    }
}


static void removeSubscriberInfo(uint8_t subscriberIdx)
{
    uint8_t bufferIdx=0;
    
    --mySubscribersList.subscriberIdx;
    
    while(subscriberIdx<MAX_SUBSCRIBERS)
    {
        if(*mySubscribersList.mobileNum[subscriberIdx] == '\0')
        {
            displayAllSubscribers();
            return;
        }

        for(bufferIdx=0; bufferIdx <MAX_PHONE_NUM_LENGTH; ++bufferIdx)
        {
            mySubscribersList.mobileNum[subscriberIdx][bufferIdx] = '\0';
            mySubscribersList.mobileNum[subscriberIdx][bufferIdx] = mySubscribersList.mobileNum[subscriberIdx+1][bufferIdx];
        }
        for(bufferIdx=0; bufferIdx <MAX_FULLNAME_LENGTH; ++bufferIdx)
        {
            mySubscribersList.fullName[subscriberIdx][bufferIdx] = '\0';
            mySubscribersList.fullName[subscriberIdx][bufferIdx] = mySubscribersList.fullName[subscriberIdx+1][bufferIdx];
            if(!mySubscribersList.fullName[subscriberIdx+1][bufferIdx])
            {
                break;
            }
        }

        ++subscriberIdx;
    }
    
    displayAllSubscribers();
}


static void displayAllSubscribers(void)
{
    uint8_t displayIdx=0;
    char tempStr[100]="";
    
    sendShellResponse("\nSubscriber Info:");
    sendShellResponse("\n----------------");
    while(displayIdx<MAX_SUBSCRIBERS)
    {
        snprintf(tempStr, 4, "\n%d)", displayIdx+1);
        strncat(tempStr, "Name:  ", 6);
        strncat(tempStr, mySubscribersList.fullName[displayIdx], MAX_FULLNAME_LENGTH);
        strncat(tempStr, "\tPhone:  ", 8);
        strncat(tempStr, mySubscribersList.mobileNum[displayIdx], MAX_PHONE_NUM_LENGTH);
        
        sendShellResponse(tempStr);
        tempStr[0] = '\0';
        
        ++displayIdx;
        
        if(*mySubscribersList.mobileNum[displayIdx] == '\0')
        {
            return;
        }
    }
}

static uint8_t validatePhoneNum(const char *buffer)
{
    uint8_t bufferIdx=0;
    
    //Phone number must be atleast 11 digits (including country code (+1))
    while(bufferIdx < MAX_PHONE_NUM_LENGTH-1)
    {
        //ASCII value for 0 => 48
        //ASCII value for 9 => 57
        if(buffer[bufferIdx] < 48 || buffer[bufferIdx] > 57)
        {
            return false;
        }
        
        ++bufferIdx;
    }
    
    return true;
}

static void sendShellResponse(const char *strr)
{
    printf("%s", strr); //TBD//replace with UART/USART TX commands
}
