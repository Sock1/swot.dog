#include "parse.h"
#include "main.h"
#include "swot.h"

extern void fail(char* msg); // Defined in main
extern size_t topics_per_field;

static size_t topic_offset(Field f, size_t topic_num)
{
    return f * topics_per_field + topic_num;
}

// Return whether fields f1 & f2 first n-1 topics collide
static bool equivalent_fields(size_t* topic_ids, Field f1, Field f2, size_t n)
{
    if (n >= topics_per_field)
	fail("equivalent_fields: n >= topics_per_field");

    for (size_t i = 0; i <= n; i++)
    {
	for (size_t j = 0; j <= n; j++)
	{
	    size_t offset1 = topic_offset(f1, i);
	    size_t offset2 = topic_offset(f2, j);

	    if (topic_ids[offset1] == topic_ids[offset2]
		&& (i != j || f1 != f2))
		return true;
	}
    }

    return false;
}

static bool incoherent_swot(size_t* topic_ids)
{
    /* All topics within the same field must be different
     * No topic can be in two different fields,
     * except Str+Opp or Weak+Threat */

    for (Field f = STRENGTH; f <= THREAT; f++)
    {
	for (Field g = f; g <= THREAT; g++)
	{
	    if ( !((f == STRENGTH && g == OPPORTUNITY)
		|| (g == STRENGTH && f == OPPORTUNITY)
		|| (f == WEAKNESS && g == THREAT)
		|| (g == WEAKNESS && f == THREAT))
		&& equivalent_fields(topic_ids, f, g, topics_per_field - 1))
		return true;
	}
    }

    return false;
}

// topic_ids[fields][topics]
// BEWARE! The loop never ends if there are less than 2 * topics_per_field topic entries available
void pick_random_fields(size_t topic_count, size_t* topic_ids)
{
    static bool random_init = false;
    if (!random_init)
    {
	srandom(time(NULL));
	random_init = true;
    }
    
    if (topic_count == 0)
	fail("No topics");

    /* Strengths can be equivalent to opportunities,
     * and weaknesses to threats. */

    do
    {
	for (size_t i = 0; i < topics_per_field; i++)
	{
	    for (Field f = STRENGTH; f <= THREAT; f++)
	    {
		size_t offset = topic_offset(f, i);
		topic_ids[offset] = random() % topic_count;
	    }
	}
    } while (incoherent_swot(topic_ids));
}

// topic_ids[fields][topics]
void print_swot(FILE* file, long* topics, size_t* topic_ids)
{
    static const char* const item_names[] = { "Forces", "Faiblesses", "Opportunités", "Menaces" };
    char* buffer = NULL;

    printf("\\section{Auto-évaluation SWOT}\n");
    printf("\t\\begin{description}\n");

    for (Field i = STRENGTH; i <= THREAT; i++)
    {
	printf("\t\t\\item[%s]\n", item_names[i]);
	for (size_t j = 0; j < topics_per_field; j++)
	{
	    size_t top = topic_ids[topic_offset(i, j)];

	    buffer = read_range(file, topics[offset(top, i, 0)], 
		        topics[offset(top, i, 1)], buffer);

	    printf("\t\t\t%s", buffer); // buffer already contains a newline
	}
    }

    printf("\t\\end{description}\n");
    free(buffer);
}

