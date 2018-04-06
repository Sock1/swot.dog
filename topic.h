#ifndef SWOT_H
#define SWOT_H

#define FIELDS 4
#define MAX_ID 5

enum {STRENGTH = 0, WEAKNESS = 1, OPPORTUNITY = 2, THREAT = 3, TOPIC = 4};

typedef struct {long begin; long end;} Field;
typedef Field[FIELDS] Topic;

#endif // SWOT_H

