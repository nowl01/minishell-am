# minishell42

![Image of minishell](https://github.com/nowl01/minishell-am/blob/master/.tools/minishell.png)
## Authors :

 - Abdennacer ama &nbsp;&nbsp;@nowl01 &nbsp;	:   42login => `abdait-m`
 - Mohammed ajermoune &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;@majermou&nbsp;&nbsp;: 	42login => `majermou`

## Subject

[minishell_subject](https://github.com/nowl01/minishell-am/blob/master/subject/en.subject.pdf)

## How to use?

 1.  `make`  
 2.  `./minishell`
 3.  Run your commands

## Simple shell that behaves like bash and contains these commands built-in :

 1.  `echo` with option `-n`.   
 2.  `cd` with only a relative or absolute path.
 3.  `pwd` without any options.
 4.  `export` without any options.
 5.  `unset` without any options.
 6.  `env` without any options and any arguments.
 7.  `exit` without any options.

## and works with these delimiters :

 - Semicolon `;` in the command separates commands like in bash.
 -  Single quotes `'` and double quotes `"` work like in bash except for multiline commands.
 - Redirections `<` `>` `>>` work like in bash except for file descriptor aggregation.
 - Pipes `|` work like in bash.
 - Backslash `\` works like in bash.
 - Environment variables (`$` followed by characters) work like in bash.
 - `$?` works like in bash.
 - `ctrl-C`, `ctrl-D` and `ctrl-\` have the same result as in bash.

## Some Sources :

 - [Unix Processes in C](https://www.youtube.com/watch?v=cex9XrZCU14&list=PLfqABt5AS4FkW5mOn2Tn9ZZLLDwA3kZUY)
 - [Writing your own shell fundamentals](https://www.cs.purdue.edu/homes/grr/SystemsProgrammingBook/Book/Chapter5-WritingYourOwnShell.pdf)
 - [Shell System Calls Signals](https://cdn.discordapp.com/attachments/769898609562746880/776363294013128734/Shells_SystemCalls_Signals.ppt)
 - [How does copy-on-write work in fork?](https://stackoverflow.com/questions/27161412/how-does-copy-on-write-work-in-fork?rq=1)
 - [ Building a Bash-like application](https://medium.com/@ssreehari/building-a-bash-like-application-e17122609be4)
 - [ execve() linux man](https://linux.die.net/man/2/execve)
 - [exit command status](https://www.cyberciti.biz/faq/linux-bash-exit-status-set-exit-statusin-bash/)
