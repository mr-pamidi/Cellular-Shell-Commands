//
//  kmpSearch.c
//
//  Created by Nagarjuna Pamidi on 3/31/18.
//  Open Source:/* https://en.wikipedia.org/wiki/Knuth–Morris–Pratt_algorithm */
//

#include "kmpSearch.h"

/*===========================================================
 Function Name: KMPsearch
 
 Inputs:
    haystack - String to be searched
    needle - word sought
 
 Output: String match starting position
 ============================================================*/
int KMPsearch(const char *haystack, const char *needle)
{
    int haystackIdx=0, needleIdx=0;
    unsigned long haystackLen = strlen(haystack);
    unsigned long needleLen = strlen(needle);
    int tableT[needleLen];
    
    generateKMPtable(needle, tableT);
    
    while(haystackIdx < haystackLen)
    {
        if(needle[needleIdx] == haystack[haystackIdx])
        {
            ++haystackIdx;
            ++needleIdx;
            if (needleIdx == needleLen)
            {
                return (haystackIdx-needleIdx); //match found
            }
        }
        else
        {
            needleIdx = tableT[needleIdx];
            if (needleIdx < 0)
            {
                ++haystackIdx;
                ++needleIdx;
            }
        }
    }
    
    return -1; //match not found
}

/*===========================================================
 Function Name: generateKMPtable
 
 Inputs:
    needle - word sought
    table - KMP error Table
 
 Output: None
 ============================================================*/
static void generateKMPtable(const char *needle, int *table)
{
    int currentPos = 1;
    int needleZeroIdx = 0;
    unsigned long needleLen = strlen(needle);
    table[0] = -1; //initialize
    
    while(currentPos < needleLen)
    {
        if(needle[currentPos] == needle[needleZeroIdx])
        {
            table[currentPos] = table[needleZeroIdx];
            ++currentPos;
            ++needleZeroIdx;
        }
        else
        {
            table[currentPos] = needleZeroIdx;
            needleZeroIdx = table[needleZeroIdx];
            
            while(needleZeroIdx >= 0 && needle[currentPos] != needle[needleZeroIdx])
            {
                needleZeroIdx = table[needleZeroIdx];
            }
            
            ++currentPos;
            ++needleZeroIdx;
        }
    }
    
    table[currentPos] = needleZeroIdx;
}
