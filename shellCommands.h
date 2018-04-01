//
//  shellCommands.h
//
//  Created by Nagarjuna Pamidi on 3/31/18.
//  Copyright © 2018 Nagarjuna Pamidi. All rights reserved.
//

#ifndef _SHELLCOMMANDS_H
#define _SHELLCOMMANDS_H

#include <string.h>
#include <stdint.h>
#include <stdlib.h> //atoi
#include <stdio.h> //snprintf
#include "kmpSearch.h"

#define MAX_PHONE_NUM_LENGTH   12
#define MAX_SUBSCRIBERS         5
#define MAX_FULLNAME_LENGTH         25

#define US_CANADA_COUNTRY_CODE      "+1"

#define ADD_SUBSCRIBER              "add "
#define REMOVE_SUBSCRIBER           "remove "
#define DISPLAY_SUBSCRIBER_LIST     "show"
#define ADD_SUBSCRIBER_STRLEN       strlen(ADD_SUBSCRIBER)
#define REMOVE_SUBSCRIBER_STRLEN    strlen(REMOVE_SUBSCRIBER)

#define SHELL_HELP                  "help"
#define SHELL_HELP_RESPONSE         "\n\"add +1xxxxxxxxxx\" - adds a new subscriber phone number\
                                    \n\"remove n\" - removes subscriber \'n\' from the list\
                                    \n\"show\" - displays subscriber list\
                                    \n\"help\" - help menu\
                                    \n\nNote: Commands are case sensitive"

struct subscribersInfo
{
    char mobileNum[MAX_SUBSCRIBERS][MAX_PHONE_NUM_LENGTH+1];
    char fullName[MAX_SUBSCRIBERS][MAX_FULLNAME_LENGTH+1];
    uint8_t subscriberIdx;
};

static uint8_t shellMenuStatus =0;

static void addNewSubscriberNum(const char *subscriberMobileNumb);
static void addNewSubscriberName(const char *subscriberFullName);
static void removeSubscriberInfo(uint8_t subscriberIdx);
static void displayAllSubscribers(void);
static void sendShellResponse(const char *strr);
void parseShellCommands(const char *buffer);
static uint8_t validatePhoneNum(const char *buffer);

#endif /* shellCommands.h */
