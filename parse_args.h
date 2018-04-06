#ifndef PARSE_ARGS_H
#define PARSE_ARGS_H

#define DIGITS "0123456789"

// ANSI color escape sequences
#define BOLD	"\e[1m"
#define NORMAL	"\e[0m"
#define UNDERLINE   "\e[4m"
#define RED	"\e[31m"
#define GREEN	"\e[32m"

extern void fail(char* msg); // Defined in main
extern size_t topics_per_field;

static const char* default_file_path = "swot_db.txt";

static void prog2_error()
{
    printf("%sERROR: Prog2 is actually not an option %s:-)%s\n", RED, BOLD, NORMAL);
}

static void print_usage()
{
    printf("Usage: %sswotdog%s [%sOPTION%s] [%sINPUT_FILE%s]\n\n", BOLD, NORMAL, UNDERLINE, NORMAL, UNDERLINE, NORMAL);
    
    printf("Options:\n");

    printf("%s--help, -h%s\n\tDisplay this help and exit\n\n", BOLD, NORMAL);

    printf("%s-n%s%sNUM%s\n\tGenerate %sNUM%s items for each field\n\n", BOLD, NORMAL, UNDERLINE, NORMAL, UNDERLINE, NORMAL);

    printf("%s--prog2, -prog2, prog2%s\n\n\n", GREEN, NORMAL);

    printf("If %sINPUT_FILE%s is omitted, then the SWOT entries are read from the default input file %s%s%s.\n\n",
	    UNDERLINE, NORMAL, GREEN, default_file_path, NORMAL);
}

const char* parse_args(int argc, char** argv)
{
    char* custom_file_path = NULL;
    bool help = false;
    bool prog2 = false;

    for (int i = 1; i < argc; i++)
    {
	if (strcmp(argv[i], "--help") == 0 || strcmp(argv[i], "-h") == 0)
	    help = true;

	else if (strcmp(argv[i], "--prog2") == 0
		|| strcmp(argv[i], "-prog2") == 0 || strcmp(argv[i], "prog2") == 0)
	    prog2 = true;

	else if (strncmp(argv[i], "-c", strlen("-c")) == 0)
	{
	    char* rest = strpbrk(argv[i], DIGITS);
	    if (rest == NULL)
	    {
		print_usage();
		exit(EXIT_FAILURE);
	    }

	    topics_per_field = strtoul(rest, NULL, 10);
	}

	else
	    custom_file_path = argv[i];
    }

    if (help)
    {
	print_usage();
	exit(EXIT_SUCCESS);
    }

    if (prog2)
    {
	prog2_error();
	exit(EXIT_SUCCESS);
    }

    if (custom_file_path == NULL)
	return default_file_path;

    else
	return custom_file_path;
}

#endif // PARSE_ARGS_H

