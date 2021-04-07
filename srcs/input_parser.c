/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdait-m <abdait-m@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 18:38:31 by abdait-m          #+#    #+#             */
/*   Updated: 2021/04/07 23:21:40 by abdait-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


int     _char_in_tab_(char c, char tab[3])
{
    if (c == tab[0] || c == tab[1] || c == tab[2])
        return 1;
    return 0;
}

int     _is_white_space(char c)
{
    if (c == ' ' || c == '\t' || c == '\v' || c == '\f' || c == '\r' || c == '\n')
        return 1;
    return 0;
}


int _check_semi_colon(char *line, ms_p *prs)
{
    prs->i++;
    if (line[0] == ';') // if the first chars is semicolon it is an ms_por
    {
        prs->er = 1;
        return prs->i;
    }
    while (prs->i)
    {
        // if the char after the semicolon is one of this | or ; then it is an ms_por
        if (line[prs->i] == '|' || line[prs->i] == ';')
        {
            prs->er = 1;
            break;
        }
        else if (_is_white_space(line[prs->i])) // skip while it's a white space
            prs->i++;
        else
            break; // break if nothing above was executed
    }
    return(--prs->i);// for knowing the char that we break at .... pardon my english hahaha
}

int _check_pipe(char *line, ms_p *prs)
{
    prs->i++;
                // if the first char is pipe or the next one is backslash zero then it is an ms_por
    if (line[0] == '|' || !line[prs->i + 1])
    {
        prs->er = 1;
        return prs->i;
    }
    while (line[prs->i])
    {
        // Skip white spaces :
        if (_is_white_space(line[prs->i]))
            prs->i++;
        else if (line[prs->i] == '|' || line[prs->i] == ';') // Raise an exception if this condtion true
        {
            prs->er = 1;
            break;
        }
        else
            break;
    }
    return (--prs->i);
}

int _check_redirection(char *line, ms_p *prs)
{
    prs->credir = 1;
    prs->i++;
    while (line[prs->i])
    {
        // Start counting the redirection > 
        if (prs->tmp == '>' && line[prs->i] == '>')
        {
            puts("hi");
            prs->tmp = '>';
            prs->credir += 1;
            prs->i++;
        }
        else if (line[prs->i + 1] && prs->tmp == '>' && _is_white_space(line[prs->i]) && line[prs->i + 1] == '>') // This condition for this case for example  > > 
        {
            prs->er = 1;
            return prs->i;
        }
        else if (_is_white_space(line[prs->i]))
            prs->i++; // this condition for ; and | after redir | this  for > after < | this for  > or < after < | this for counting the number of redirection >  
        else if (line[prs->i] == ';' || line[prs->i] == '|' || (line[prs->i] == '<' && prs->tmp == '>') || (prs->tmp == '<' && (line[prs->i] == '>' || line[prs->i] == '<')) || prs->credir >= 3)
        {
            prs->er = 1;
            return prs->i;
        }
        else
            break;
    }
    if (!line[prs->i])
        prs->er = 1;
    return (--prs->i);
}

int _check_double_quotes(char *line, ms_p *prs)
{
    prs->i++;
    while (line[prs->i] != prs->tmp && line[prs->i])
    {
        // if you find backslash skip too chars the current one and the next one :
        if (line[prs->i] == '\\' && line[prs->i + 1] != '\0')
        {
            prs->i += 2;
            continue;
        }
        prs->i++;
    }
    if (line[prs->i] != prs->tmp) // this for checking the double quotes exists : else we raise an exception
        prs->er = 1; 
    return prs->i;
}

int _check_single_quotes(char *line, ms_p *prs)
{
    prs->i++;
    while (line[prs->i] != '\'' && line[prs->i])
        prs->i++;
    if (line[prs->i] != prs->tmp) // checking that the last chars after loop is single quotes else it is an ms_por
        prs->er = 1;
    return prs->i;
}

int _handle_syntax_errors(char *line, ms_p *prs)
{

    prs->i = 0;
    // puts("im in");
    prs->er = 0;
    while (line[prs->i])
    {
        prs->tmp = line[prs->i];
        // Check ms_pors of semicolon :
        if (line[prs->i] == ';')
            prs->i = _check_semi_colon(line, prs);
        else if (line[prs->i] == '|') 
            prs->i = _check_pipe(line, prs);
        else if ((line[prs->i] == '>' || line[prs->i] == '<')) // Check errors of redirection :
            prs->i = _check_redirection(line, prs);
        else if (prs->tmp == '"') // Check errors of double quotes :
           prs->i = _check_double_quotes(line, prs);
        else if (prs->tmp == '\'') // Check errors of single quotes :
           prs->i = _check_single_quotes(line, prs);
        if (prs->er)
            return 1;
       prs->i++;
    }
    return (0);
}


void        _raise_an_exception()
{
    write(1, "mini$hell: Syntax error .\n", 26);
}

void        _initialize_vars(s_split *ps)
{
    ps->check_dq = 0;
    ps->check_sq = 0;
    ps->i = 0;
    
}


void        _free_tokens_data_(t_cmd_list **head)
{
    int i;

    i = -1;
    if ((*head)->args)
    {
        while ((*head)->args[++i])
            free((*head)->args[i]);
        free((*head)->args);   
    }
    if ((*head)->command)
        free((*head)->command);
}


void        _free_all_tokens(t_cmd_list **head)
{
    t_cmd_list *next;
    
    if ((*head))
    {
        while (*head)
        {
            next = (*head)->next;
            _free_tokens_data_(head);
            free((*head));
            (*head) = next;
        }
        (*head) = NULL;
    }
}


void    _free_all_(ms_p *prs, t_cmd_list **head)
{
    // int i;

    // i = -1;
    _free_all_tokens(head);
    prs->err.i = 0;
    // if (prs->sc_cmds)
    // {
    //     while (prs->sc_cmds[++i])
    //             free(prs->sc_cmds[i]);
    //     free(prs->sc_cmds);
    //     prs->sc_cmds = NULL;
    // }
    
}

int     _check_for_special_chars_(char *buff)
{
    while (*buff)
    {
        if (_char_in_tab_(*buff, "><|"))
            return 1;
        buff++;
    }
    return 0;
}


void _push_back_normal_tokens_(char *line, t_cmd_list **head, ms_p *prs)
{
    t_cmd_list *curr;
    t_cmd_list *new;
    s_split sp;
    
    //  use double pointer for declaring the struct ...
    prs->err.i = 0;
    new = malloc(sizeof(t_cmd_list));
    new->prev = NULL;
    new->next = NULL;
    new->beg = 1;
    new->end = 1;
    _initialize_vars(&sp);
    new->args = _split_tokens(&sp, line, ' ');
    new->command = ft_strdup(new->args[0]);
    if (!(*head))
    {
        (*head) = new;
    }
    else
    {
        curr = (*head);
        while (curr->next)
            curr =  curr->next;
        curr->next = new;
        new->prev = curr;
    }
}



void        _copy_tokens_data_(char *token, ms_p *prs, t_cmd_list **head)
{
    // prs->err.i = 0;
    // *head = NULL;
    // t_cmd_list *curr;
    if (token != NULL)
    {
        if (!_check_for_special_chars_(token))
        {
            _push_back_normal_tokens_(token, head, prs);
        }
        else
        {
            puts("special tokens");
        }
    }
    
    // else
        // Fill the data of special tokens find a way to _handle_syntax_errors this tokens that has pipes and redirs in it..
}

char _ret_special(char buffer)
{
    if (buffer == '\\')
        return ('\\');
    else if (buffer == '"')
        return '"';
    else if (buffer == '$')
        return '$';
    else if (buffer == '`') // this one is not needed
        return '`';
    else
        return 0;
}
int _is_special(char c)
{
    if (c == '\\' || c == '"' || c == '$' || c == '`')
        return 1;
    return 0;
}
void        _bs_for_double_quotes_(ms_p *prs, char *token)
{
    prs->buff[prs->j++] = token[prs->i++];
    while (token[prs->i] != '"')
    {
        if (token[prs->i] == '\\' && _is_special(token[prs->i + 1]))
        {
            puts("im in");
            prs->buff[prs->j++] = _ret_special(token[prs->i + 1]);
            prs->i += 2;
            continue;
        }
        prs->buff[prs->j++] = token[prs->i++];
    }
    prs->buff[prs->j++] = token[prs->i++];
}


void        _bs_for_single_quotes_(ms_p *prs, char *token)
{
    prs->buff[prs->j++] = token[prs->i++];
    while (token[prs->i] != '\'')
        prs->buff[prs->j++] = token[prs->i++];
    prs->buff[prs->j++] = token[prs->i++];
}


char *_handle_backslash_(ms_p *prs, char *token)
{   
    prs->i = 0;
    prs->j = 0;
    prs->buff = (char *)malloc(sizeof(char) * (ft_strlen(token) + 1));
    while (prs->i < (int)ft_strlen(token))
    {
        if (token[prs->i] == '"')
            _bs_for_double_quotes_(prs, token);
        else if (token[prs->i] == '\'')
            _bs_for_single_quotes_(prs, token);
        else
            prs->buff[prs->j++] = token[prs->i++];
    }
    prs->buff[prs->j] = '\0';
    return (prs->buff);
}

int     in(char *check, char c)
{
    while (*check)
    {
        if (*check == c)
            return 1;
        check++;
    }
    return 0;
}

void _start_parsing(char *line, ms_p *prs, t_cmd_list **head)
{
    s_split sp;
    // int j;
    int i;
    // t_cmd_list *curr;
    
    // curr = *head;
    _initialize_vars(&sp);
    if (_handle_syntax_errors(ft_strtrim(line, " \t\v\n"), prs))
        _raise_an_exception();
    else
    {
        prs->sc_cmds = _split_tokens(&sp, line, ';');
        printf("split|%s|\n", prs->sc_cmds[0]);
        // printf("|-%s-|\n", prs->sc_cmds[0]);
        i = -1;
        while (prs->sc_cmds[++i])
        {
            // i guess you need to handle the env variable before handling the backslash!!!!
            if (in(prs->sc_cmds[i], '"'))
                prs->sc_cmds[i] = _handle_backslash_(prs, prs->sc_cmds[i]);
            printf("%d --> |%s| \n", i, prs->sc_cmds[i]);
            // if (prs->sc_cmds[i] && prs->sc_cmds[i][0])
            // {
            //     _copy_tokens_data_(prs->sc_cmds[i], prs, head);
            // }
            // curr = (*head);
            // while (curr)
            // {
            //     printf("{%s}\n", curr->args[0]);
            //     curr = curr->next;
            // }
            // _free_all_(prs, head);
            // i = -1;
            // if (prs->sc_cmds)
            // {
            //     while (prs->sc_cmds[++i])
            //             free(prs->sc_cmds[i]);
            //     free(prs->sc_cmds);
            //     prs->sc_cmds = NULL;
            // }
            // while (curr)
            // {
            //     printf("dll = -> |%s| <-\n", curr->args[0]);   
            //     puts("1");
            //     curr = curr->next;
            // }
            _free_all_(prs, head);
        }
    }
}