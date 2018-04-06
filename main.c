#include "parse.h"
#include "swot.h"
#include "parse_args.h"

void fail(char* msg)
{
    fprintf(stderr, "ERROR: %s\n", msg);
    exit(EXIT_FAILURE);
}

size_t topics_per_field = TOPICS_PER_FIELD;

int main(int argc, char** argv)
{
    const char* file_path = parse_args(argc, argv);
    
    FILE* file = fopen(file_path, "r");
    if (file == NULL)
	fail("fopen failed");
    
    long* topics = NULL;
    size_t topic_count = 0;
    topics = get_topics(file, topics, &topic_count);

    // size_t swot_fields[4 * topics_per_field] = { 0 };
    size_t* swot_fields = calloc(4 * topics_per_field, sizeof(size_t));
    pick_random_fields(topic_count, swot_fields);

    print_swot(file, topics, swot_fields);

    free(swot_fields);
    free(topics);
    fclose(file);

    return EXIT_SUCCESS;
}

