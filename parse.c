#include "parse.h"

extern void fail(char* msg); // Defined in main
extern size_t topics_per_field;

size_t offset(size_t topic, Field field, bool end)
{
    return (size_t)((topic * 4 + field) * 2 + end);
}

static bool is_delimiter(Field field_id, char* str)
{
    static const char* const expected_str[FIELD_COUNT] =
	{"STRENGTH", "WEAKNESS", "OPPORTUNITY", "THREAT", "TOPIC"};

    return (strncmp(str, expected_str[field_id],
		strlen(expected_str[field_id])) == 0);
}

long* get_topics(FILE* file, long* topics, size_t* count)
{
    char* line = NULL;
    size_t len = 0;
    
    *count = 0;

    Field next_field = TOPIC;
    rewind(file);

    while (getline(&line, &len, file) != -1)
    {
	Field prev_field = (next_field - 1) % FIELD_COUNT;

	if (is_delimiter(next_field, line))
	{
	    if (next_field == TOPIC)
	    {
		(*count)++;
		topics = realloc(topics,
			(*count) * 4 * 2 * sizeof(long));
	    }

	    else
	    {
		long pos = ftell(file);
		assert (pos != -1);

		topics[offset(*count - 1, next_field, 0)] = pos;
	    }

	    next_field++; next_field %= FIELD_COUNT;
	}

	else if (prev_field != TOPIC)
        {
	    long pos = ftell(file);
	    assert (pos != -1);

	    topics[offset(*count - 1, prev_field, 1)] = pos;
	}

    }

    free(line); // getline allocates line but doesn't free it

    return topics;
}

// Read from offset "from" included to "to" excluded
char* read_range (FILE* file, long from, long to, char* buffer)
{
    assert(fseek(file, from, SEEK_SET) == 0);

    buffer = realloc(buffer, (to - from + 1) * sizeof(char));
    buffer[to - from] = '\0';

    fread(buffer, sizeof(char), to - from, file);
//    printf("Read from %ld to %ld:\n", from, to);
//    printf("%s\n", buffer);

    return buffer;
}

