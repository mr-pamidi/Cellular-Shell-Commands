//
//  kmpSearch.h
//
//  Created by Nagarjuna Pamidi on 3/31/18.
//  Open Source:/* https://en.wikipedia.org/wiki/Knuth–Morris–Pratt_algorithm */
//

#ifndef _KMPSEARCH_H
#define _KMPSEARCH_H

#include <string.h>
#include <stdint.h>

#ifndef true
#define true 1
#endif

#ifndef false
#define false 0
#endif

uint8_t KMPsearch(const char *haystack, const char *needle);
static void generateKMPtable(const char *needle, int32_t *table);

#endif /* End of kmpSearch */
