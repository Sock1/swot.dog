#ifndef SWOT_H
#define SWOT_H

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define FIELD_COUNT 5
#define TOPICS_PER_FIELD 2

typedef enum {STRENGTH = 0, WEAKNESS = 1, OPPORTUNITY = 2, THREAT = 3, TOPIC = 4} Field;

void pick_random_fields(size_t topic_count, size_t* fields);
void print_swot(FILE* file, long* topics, size_t* topic_ids);

#endif // SWOT_H

