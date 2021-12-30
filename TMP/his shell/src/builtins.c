#include "../include/builtins.h"

int same_file(int fd1, int fd2)
{
    struct stat stat1, stat2;
    if (fstat(fd1, &stat1) < 0)
        return -1;
    if (fstat(fd2, &stat2) < 0)
        return -1;
    return (stat1.st_dev == stat2.st_dev) && (stat1.st_ino == stat2.st_ino);
}

// ----------------------------------------

int cd(int argc, char **argv)      // cd is real built-in
{
	char *s;
	if (argc == 1)
    {
		s = getenv("HOME");
		if (s == NULL)
        {
            fprintf(stderr, "where is your home, stranger?\n");
            return 1;
        }
		else
            chdir(s);
	}
	else if (argc > 2)
    {
        fprintf(stderr, "cd command accepts only 1 argument\n");
        return 2;
    }
    else if (chdir(argv[1]))
    {
        perror(argv[1]);
        return 3;
    }
    return 0;
}

// ----------------------------------------

void mv(int argc, char **argv)
{
    if (argc != 3)
    {
        fprintf(stderr, "shell_mv: exactly 2 arguments are needed\n");
        exit(1);
    }
    FILE *from = fopen(argv[1], "r");
    FILE *to = fopen(argv[2], "w");
    if (from == NULL)
    {
        fprintf(stderr, "shell_mv: %s: No such file or directory or read protected\n", argv[1]);
        exit(1);
    }
    if (to == NULL)
    {
        fprintf(stderr, "shell_mv: %s: No such file or directory or write protected\n", argv[2]);
        exit(1);
    }
    int test1 = open(argv[1], O_RDONLY), test2 = open(argv[2], O_RDONLY);
    int same = same_file(test1, test2);
    close(test1);
    close(test2);
    if (same == 1)
    {
        fprintf(stderr, "shell_mv: '%s' and '%s' are the same file\n", argv[1], argv[2]);
        exit(0);
    }
    if (same == -1)
    {
        fprintf(stderr, "shell_mv: error while checking files\n");
        exit(1);
    }
    char c = fgetc(from);
    while (!feof(from))
    {
        putc(c, to);
        c = fgetc(from);
    }
    fclose(from);
    fclose(to);
    remove(argv[1]);
    exit(0);
}

void cat(int argc, char **argv)
{
    if (argc == 1)      // 'cat' and 'cat -' are the same
    {
        argv[argc] = malloc(2 * sizeof(char));
        strcpy(argv[argc], "-");
    }
    bool number_lines = false;
    int i, lines_cnt = 1;
    for (i = 1; i < argc; ++i)
        if (!strcmp(argv[i], "-n"))
            number_lines = true;
    for (i = 1; i <= argc; ++i)
    {
        if (argv[i] == NULL)
            break;
        if (argv[i][0] == '-' && strcmp(argv[i], "-"))
            continue;
        FILE *f;
        if (argv[i][0] == '-')
            f = stdin;
        else
        {
            int test = open(argv[i], O_RDONLY);
            if (test == -1)
            {
                fprintf(stderr, "shell_cat: %s: No such file or directory\n", argv[i]);
                continue;
            }
            int same = same_file(STDOUT_FILENO, test);
            if (same == -1)
                printf("shell_cat: %s: error while checking file\n", argv[i]);
            if (same == 1)     // same_file can return -1 but who knows what we should do then
            {
                fprintf(stderr, "shell_cat: %s: input file is output file\n", argv[i]);
                close(test);
                continue;
            }
            close(test);
            f = fopen(argv[i], "r");
        }
        float mult = 1.5;
        size_t sz = 256, it = 0;
        char *buf = malloc(sz);
        int c;
        do
        {
            while ((c = fgetc(f)) != EOF)
            {
                buf[it++] = (char)c;
                if (it == sz)
                {
                    sz *= mult;
                    buf = realloc(buf, sz);
                }
                if ((char)c == '\n')
                    break;
            }
            if (it == 0)
                break;
            if (number_lines)
                printf("%d\t", lines_cnt++);
            size_t j;
            for (j = 0; j < it; ++j)
                putc(buf[j], stdout);
            it = 0;
        } while (c != EOF);
        fclose(f);
        free(buf);
    }
    exit(0);
}

void cmp(int argc, char **argv)
{
    if (argc == 1)
    {
        fprintf(stderr, "shell_cmp: missing operand after 'cmp'\n");
        exit(1);
    }
    if (argc == 2)          //  compare with stdin
    {
        argv[argc] = malloc(2 * sizeof(char));
        strcpy(argv[argc], "-");
        ++argc;
    }
    if (argc > 3)
        fprintf(stderr, "shell_cmp: only two first operands are used\n");
    if (!strcmp(argv[1], argv[2]))      // just in case (useful when 'cmp - -')
        exit(0);
    FILE *f1, *f2;
    if (!strcmp(argv[1], "-"))
        f1 = stdin;
    else
        f1 = fopen(argv[1], "r");
    if (f1 == NULL)
    {
        fprintf(stderr, "shell_cmp: %s: error opening file\n", argv[1]);
        exit(1);
    }
    if (!strcmp(argv[2], "-"))
        f2 = stdin;
    else
        f2 = fopen(argv[2], "r");
    if (f2 == NULL)
    {
        fprintf(stderr, "shell_cmp: %s: error opening file\n", argv[2]);
        exit(1);
    }
    char c1 = fgetc(f1), c2 = fgetc(f2);
    size_t lines_cnt = 1, bytes_cnt = 1;
    while (!feof(f1) && !feof(f2))
    {
        if (c1 != c2)
        {
            printf("%s %s differ: byte %zd, line %zd\n", argv[1], argv[2], bytes_cnt, lines_cnt);
            exit(0);
        }
        if (c1 == '\n')
        {
            ++lines_cnt;
            bytes_cnt = 0;
        }
        ++bytes_cnt;
        c1 = fgetc(f1);
        c2 = fgetc(f2);
    }
    if (feof(f1) && feof(f2))
        exit(0);
    printf("%s %s differ: byte %zd, line %zd\n", argv[1], argv[2], ++bytes_cnt, lines_cnt);
    exit(0);
}

// ---------- built-ins registration fuctions ---------

void add_builtin(void (*fptr)(int, char**), const char *name)
{
    if (builtins.begin == NULL)
        builtins.begin = builtins.end = malloc(sizeof(builtin_list_node_t));
    else
    {
        builtins.end->next = malloc(sizeof(builtin_list_node_t));
        builtins.end = builtins.end->next;
    }
    builtins.end->fptr = fptr;
    builtins.end->name = malloc((strlen(name) + 1) * sizeof(char));
    builtins.end->next = NULL;
    strcpy(builtins.end->name, name);
    builtins.size++;
}

void init_builtins(void)
{

    builtins.begin = NULL;
    builtins.size = 0;
    add_builtin(cat, "cat");
    add_builtin(cmp, "cmp");
    add_builtin(mv, "mv");
}
