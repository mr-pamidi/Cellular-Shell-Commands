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
int32_t KMPsearch(const char *haystack, const char *needle)
{
    int32_t haystackIdx=0, needleIdx=0;
    uint64_t haystackLen = strlen(haystack);
    uint64_t needleLen = strlen(needle);
    int32_t tableT[needleLen];
    
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
static void generateKMPtable(const char *needle, int32_t *table)
{
    int32_t currentPos = 1;
    int32_t needleZeroIdx = 0;
    uint64_t needleLen = strlen(needle);
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
