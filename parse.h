#ifndef PARSE_H
#define PARSE_H

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>
#include "swot.h"

char* read_range(FILE* file, long from, long to, char* buffer);
long* get_topics(FILE* file, long* topics, size_t* count);

size_t offset(size_t topic, Field field, bool end);

#endif // PARSE_H

