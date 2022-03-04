# minishell

Explication des fonctions présentes :

`int  search_fct(char *str)`

Cherche dans le parametre str si on a une fonction que l'on doit coder et renvoie son numéro (ou 0 si rien ne correspond).
fonction avec son numéro correspondant:
echo = 1;
echo -n = 2;
cd = 3;
pwd = 4;
export = 5;
unset = 6;
env = 7;
exit = 8;



`void do_fct(int cmd, char *current)`

Vient après le search_fct. Prends le numéro de fonction obtenu et l'exécute avec les paramètres de current.



`int  ft_strstr(char *str, char *tofind)`

Un peu différent de la vraie strstr. Cherche si "tofind" apparait dans "str", renvoie 1 si c'est le cas et 0 si aucune occurence n'est trouvée.
(utile pour search_fct)



`void ft_echo(int mode, char *str)`

mode 1 = echo;
mode 2 = echo -n;
Ecrit dans STD_OUT la str avec ou sans \n selon le mode.
