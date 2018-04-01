//
//  kmpSearch.h
//
//  Created by Nagarjuna Pamidi on 3/31/18.
//  Open Source:/* https://en.wikipedia.org/wiki/Knuth–Morris–Pratt_algorithm */
//

#ifndef kmpSearch_h
#define kmpSearch

#include <string.h>

static void generateKMPtable(const char *needle, int *table);
int KMPsearch(const char *haystack, const char *needle);

#endif /* End of kmpSearch */
