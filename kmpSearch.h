//
//  kmpSearch.h
//
//  Created by Nagarjuna Pamidi on 3/31/18.
//  Open Source:/* https://en.wikipedia.org/wiki/Knuth–Morris–Pratt_algorithm */
//

#ifndef _KMPSEARCH_H
#define _KMPSEARCH_H

#include <string.h>

int KMPsearch(const char *haystack, const char *needle);
static void generateKMPtable(const char *needle, int *table);

#endif /* End of kmpSearch */
