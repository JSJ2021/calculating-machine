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
    int num;
    struct s_token *left;
    struct s_token *right;    
} t_token;

t_token *create_num(int n)
{
    t_token *node = malloc(sizeof(t_token));
    node->type = num;
    node->num = n;
    node->left = 0;
    node->right = 0;
    return node;
}
void free_node(t_token *token)
{
    if (token)
    {
        if ((token)->left)
            free_node((token)->left);
        if ((token)->right)
            free_node((token)->right);
        free(token);
        token = 0;
    }
}

t_token *init_token(cal_type type, t_token *left, t_token *right)
{
    t_token *result = (t_token *)malloc(sizeof(t_token));
    result->left = left;
    result->right = right;
    result->type = type;
    return (result);
}

t_token *parser_num(char *s, int *i)
{
    t_token *token = 0;
    
    if(isdigit(s[*i]))
        token = create_num(s[*i] - 48);
    (*i)++;
    return (token);
}

t_token *parser_trem(char *s, int *i)
{
    t_token *left = parser_num(s, i);
    t_token *right;
    while (s[*i] == '*')
    {
        (*i)++;
        right = parser_num(s, i);
        left = init_token(multiplication, left, right);
    }
    return left;
}

t_token *parser(char *s, int *i)
{
    t_token *left = parser_trem(s, i);
    t_token *right;
    while (s[*i] == '+')
    {
        (*i)++;
        right = parser_trem(s, i);
        left = init_token(add, left, right);
    }
    if (right == 0 || left == 0)
    {
        printf("Unexpected end of input\n");
        free_node(left);
    }
    return left;
}

int operating(t_token *token)
{
    int num1 = 0;
    int num2 = 0;
    int result = 0;
    if (token->type == num)
        return (token->num);
    else if (token->left != 0 && token->right != 0)
    {
        num1 = operating(token->left);
        num2 = operating(token->right);
    }
    else
        return (-1);
    
    if (token->type == add)
        result = (num1 + num2);
    else if (token->type == multiplication)
    {
        result = (num1 * num2);
    }
    if (num1 == -1 || num2 == -1)
        return (-1);
    return (result);
}

int main()
{
    int result;
    int i = 0;
    t_token *token = parser("1+1*2*5+1*2+2", &i);
    result = operating(token);
    if(result != -1)
        printf("%d\n", result);
    return (0);
}