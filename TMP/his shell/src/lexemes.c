#include "../include/lexemes.h"

char *str_begin, *lexeme;
wlist_t *lexemes_list;

void lexem_error(void)
{
    if (str_begin != NULL)
        free(str_begin);
    str_begin = NULL;
    if (lexeme != NULL)
        free(lexeme);
    lexeme = NULL;
    if (lexemes_list != NULL)
        delete_list(&lexemes_list);
    error("bad character");
}

bool is_correct(char c)
{
	if ((tolower(c) >= 'a' && tolower(c) <= 'z') ||
        (c >= '0' && c <= '9') ||
        (c == '_') ||
        (c == '/') ||
        (c == '.') ||
        (c == ')') ||
        (c == '(') ||
        (c == '<') ||
        (c == '>') ||
        (c == '&') ||
        (c == ';') ||
        (c == '|') ||
        (c == ' ') ||
        (c == '-'))
        return true;
	return false;
}

char *next_lexeme(char *str)
{
	char *lex_end, *ptr;
	while (isspace(str[0]))
        ++str;
	if (str[0] == 0)    // no more lexemes
    {
        lexeme = NULL;
        return NULL;
    }
    switch (str[0])
    {
    case ';':           // special symbols
    case '(':
    case ')':
    case '<':
        lex_end = str + 1;
        break;
    case '|':           // | or ||, & or &&, > or >>
    case '&':
    case '>':
        if (str[1] == str[0])
        {
            lex_end = str + 2;
            if (str[2] == str[0])
                lexem_error();
        }
        else
            lex_end = str + 1;
        break;
    default:
        lex_end = strpbrk(str, " \t\n;()<>|&");
        break;
    }
    lexeme = malloc((lex_end - str + 1) * sizeof(char));
    for (ptr = lexeme; str < lex_end; ++str, ++ptr)
    {
        if (is_correct(str[0]))
            ptr[0] = str[0];
        else
            lexem_error();
    }
    ptr[0] = 0;     // set the end of lexeme
    return str;
}

wlist_t *get_lexemes_list(void)
{
    static const size_t base_len = 256;
    size_t mult = 1;
    char buf[base_len + 1];
	str_begin = malloc(sizeof(char));
	str_begin[0] = 0;     // empty string
	lexemes_list = malloc(sizeof(wlist_t));
	build_empty_list(lexemes_list);
	while(fgets(buf, sizeof(buf) / sizeof(buf[0]), stdin) != NULL)
	{
        str_begin = realloc(str_begin, (mult * base_len + 1) * sizeof(char));
        strcat(str_begin, buf);
        ++mult;
		if (strpbrk(buf, "\n"))
		{
		    char *str = str_begin;
		    str = next_lexeme(str);
			while (lexeme != NULL)
            {
                add_word(lexemes_list, lexeme);
                str = next_lexeme(str);
            }
			free(str_begin);
			str_begin = str = NULL;
			return lexemes_list;
		}
	}
	return lexemes_list;
}

