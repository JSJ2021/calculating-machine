#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

typedef enum {
    num,
    add,
    multiplication,
    parenthesis_open,
    parenthesis_close
} cal_type;

typedef struct s_token
{
    cal_type type;
    char num;
    struct s_token *left;
    struct s_token *right;    
} t_token;

t_token *parser(char *s, int i)
{
    
    if (isdigit(s[i]))
    {
        t_token *token = (t_token *)malloc(sizeof(t_token));
        token->type = num;
        token->num = s[i] - 48;
    }
    else
    {
        t_token *token = (t_token *)malloc(sizeof(t_token));
        if(s[i] == '+')
        {
            token->type = add;
        }
        else if(s[i] == '*')
        {
            token->type = multiplication;
        }
    }
}
int main(int argc, char **argv)
{
    t_token *token;

}