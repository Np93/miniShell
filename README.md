A faire :
- < : 
- > : Reno
- << :
- >> : Reno
- | : Done
-$? : Done


//Contenu des fichiers//


main.c : welcome, cpy_env, init_para, main

search_fct.c : search_fct, do_fct

echo.c : ft_echo

ft_strstr.c : ft_strlen, ft_strstr

ft_calloc.c : ft_bzero, ft_calloc

ft_strdup.c : ft_strdup

ft_env.c : ft_env, ft_export, ft_unset(et ft_unset2), ft_getenv

ft_pwd.c : ft_pwd

ft_cd.c : ft_cd, magic, update_pwd, update_oldpwd

ft_split.c : ft_split

ft_strjoin.c : ft_strjoin

init.c : prompt_init

current_parser.c : get_dollar, current_parser(+ 2, 3 et 4)

current_parser2.c : current_parser5 (+ 6 et 7)

error_handler : error_handler

ft_cd.c : ft_memcmp, ft_getenv, ft_cd

cmd_not_found.c : cmd_cmp, verif_fquote, cmd_not_found, cmd_not_found2

sig_handler.c : sig_handler

execve_default.c : ft_execve, free_exec, all_path_exec, exec_and_return(+2)

execve_default2.c : last_path, ft_check_path

welcome1.c : les welcome 1 a 5

welcome2.c : les welcome 6 a 10

ft_termios.c : ft_termios

ft_readline.c : ft_readline(+2), int_to_str_redi, cpy_bf_redi

search_redirect.c : search_redirect(+2 & 3), grep_spec(+1)

search_redirect2.c : grep_spec(2, 3, 4, 5)

search_redirect3.c : grepr, grepxec, split_grep

launch_redirect.c : unquoter, unquoter6, launch_redi(+1, 2);

init_redirect.c : int_to_str_redi, cpy_bf_redi

ft_cd_tool.c : ft_memcmp, ft_strncmp, get_env (fichier norminette)

unquoter : unquoter(2, 3, 4, 5, 7)

redirect_utils.c : ft_freeee_split_redi, choose_redi, ft_exec_red(+2)

redirecter1.c : redi1(+1_2)




//Explications de la struct globale//

`int exit_status`

utilisé pour catch l'exit status de des commandes lancées (lu avec la var $?)



`int main`

utilisé pour reconnaitre le process principal notamment pour le CTRL+C qui, si non innhibé, va print un nouveau prompt sur tous les minishell ouverts.




//Explications de la struct//


`char *prompt`

C'est la ptite ligne qui apparait quand on attend une commande, je pensais la pimper un peu avec genre un utilisateur perso donne en arg quand on lance minishell... a voir.



`char *current`

la ligne de commande tapee qui contient du coup tous ce qui a a faire... Faudra voir pour la modifier selon les quotes, pipes,...



`char *out`

C'est en gros la string une fois qu'on a remove les quotes et add les variables d'environnement car la string current doit rester sans modif pour matcher avec l'historique



`char *bait`

string qui me sert quand le debut de current est quoté car la verif est un peu differente et c'est chiant



`int cmd`

int que search_fct a renvoye apres avoir cherche dans current.



`char **env`

stocke les variable d'environnement (pour les fonctions env et export)



`struct termios term`

utile pour ft_termios en gros on peut toucher aux parametre du terminal



`char *split_redi`

pointeur sur string pour stocker les differentes operations en cas de redirection, les args impaires sont systematiquement une string qui contient la redirection (par ex. {"echo judas", ">", "outfile"})




//Explication des fonctions//


`int	search_fct(char *str)`

cherche si une des commandes que l'on doit coder est présente dans str et renvoie son numéro.
Fonctions et leurs numéros :
echo -n = 1;
echo = 2;
cd = 3;
pwd = 4;
export = 5;
unset = 6;
env = 7;
exit = 8;
cd .. = 9;



`void	do_fct(int cmd, t_para *para)`

Reçoit en arg l'int revoyé par search_fct et exécute la commande correspondante.



`void ft_echo(int mode, char *str)`

Ecrit la str avec ou sans \n selon le mode :
echo -n = mode 1;
echo = mode 2;



`int	ft_strstr(char *str, char *tofind)`

Un peu différente de la version originale. Cherche la premiere occurence de tofind dans str et renvoie l'index du caractere qui suit cette apparition ou 0 si aucune occurence n'apparait. (sera utile pour search_fct)



`void	ft_env(char **env)`

meme que bash : ecrit toutes les variables d'environnement



`int	ft_export(t_para *para)`

meme que bash : ajoute une variable d'environnement a la char `**env`



`int	ft_unset(t_para *para)`

meme que bash : supprime les variable d'environnement designees si elles existent



`void ft_pwd(t_para *para)`

meme que bash : ecrit le chemin ou on se trouve



`prompt_init(int argc, char **argv, t_para *para)`

Met a jour le promt selon le pwd et le user(optionnel) donne en arg de ./minishell (="default_user" si pas d'argument)



`int *current_parser(t_para *para)`

Parse la string current et remove les quotes (singles et double) selon les regles, ajoute les variable d'environnement (genre $PWD), check si ya des ";" et remove les "\" au besoin puis renvoie 0 si tout s'est bien passe ou un int d'erreur. La string para->out est finalement modifiee par pointeur.

`char *get_dollar(char *current, int i, t_para *para)`

il va chercher la variable d'environnement qui est a l'index [i] de la string current et renvoier la string correspondante ou NULL si aucune var_env ne correspond a la recherche.


`void	ft_cd(t_para *para, int cmd)`

il effectue la commande cd le cd .. fonctinne aussi mais quand on l'effectue il ne met pas 
encore les parametre (env) du terminal a jour, j'ai aussi utiliser les numeros 3 et 9 de la 
variable cmd dans le main.


`void	error_handler(int error, t_ara *para)`

il fait des actions selon le numero d'erreur envoie

0 = erreur de malloc : ecrit qu'un prob est arrive et quitte tout avec exit(0)

1 = quotes non fermees dans la current : ecrit que t'as pas fermee tes quotes

2 = presence d'une ; dans la current : ecrit qu'on handle pas ce cas

3 = ya eu une tentative de bait dans la para->current : utilise une version alternative de cmd_not_found

4 = erreur dans l'appel de minishell : Usage : ./minishell ([username])

5 = le fd utilise est pas TTY (man isatty) et c'est chiant pour l'utilisation de ft_termios

6 = une erreur est arrivee quand on a voulu toucher aux parametres de la struct termios



`void cmd_not_found(char *str)`

ecrit qu'aucune fonction ne correspond a la string passee en argument, elle set aussi le g_glob.exit_status à 127



`void cmd_not_found2(char *str)`

la meme mais c'est pour le cas ou ya eu le debut de la current qui etait quote ce qui change un peu la sortie



`int verif_fquote(t_para *para, char *str)`

verifie si le debut de str etait quoté car ca modifie un peu la recherche et la sortie. revoie 0 si on peut continuer sans soucis et 1 si l'argument pose soucis auquel cas on stock ledit argument dans para->bait.



`int	cmd_cmp(char *str)`

utilisee pour verif_fquote : regarde dans str si ya un bait de fonction quotée avec un esape genre "echo ", renvoie 0 si RaS et 1 si probleme.


`void	ft_signal(void)`

initialise le captage des signaux dans le main.



`void	sig_handler(int sig)`

il gere les signaux envoyé ("CTRL+C" et "CTRL+\") pour le CTRL+D c'est directement dans le main c'est plus tricky car CTRL+D fait quit le programme si le stdin a atteint EOF donc est NULL. il va aussi prendre le SIGUSR1 en compte qui est envoyé par un éventuel child issu d'un fork() pour signifier qu'un process enfant s'est mal terminé et set donc la g_glob.exit_status a 1 pour le $?.



`int	ft_execve(t_para *para)`

si la commande passee dans para->current ne correspond a rien qu'on a du construire, il va tenter de lancer la commande avec le vrai shell. Si elle existe pas non plus dans le vrai shell, c'est comme meme minishell qui dit commande not found.



`void	ft_check_path(char **argv)`

il va check les str de argv qu'on donne a execve() car si ya genre "/bin/ls" on doit que garder le ls de fin du coup on modifie les strings en fonctions



`char	*last_path(char *arg)`

c'est lui qui fait la modif des str de argv dans ft_check_path juste plus haut.



`char	**all_path_exec(t_para *para, char *end`

ça va chercher tous les chemins pssoible pour executer les cmd avec execve et renvoier le tableaux de str pour les tests.



`int	exec_and_return(char **all_path, char **argv, t_para *para)`

split de fonction a cause de la norminette c'est l'executeur du process ft_execve.



`void	welcome(void)`

print un ptit accueil sympa quand on lance le shell



`void	ft_termios(t_para *para)`

Est utilisé pour inhiber le print du "^c" quand on faisait CTRL+C, la ligne importante c'est `para->term.c_lflag &= ~ECHCTL` qui met le bit de ECHOCTL (donc "echo" la touche CTRL) a 0



`void ft_readline(t_para *para`

il coupé du main pour des raisons de norminette, il va lancer le current parser sur la str lue par readline et lancer search_fct et do_fct.



`int	search_redirect(char *str)`

cherche dans la str passee en parametre si il y a une redirection et renvoie 1 si elle trouve qqchose (et si elle n'est pas inhibée par du quotage). Renvoie 0 si rien n'a ete trouve

code des redirections :

0 = >
1 = >>
2 = <
3 = <<
4 = |



`char	*cpy_bf_redi(char *str, int i)`

va copier la la partie de l'arg qui se trouve avant une redirection dans current parser et le mettre dans split_redi.



`char *int_to_str_redi(int code)`

mets dans split_redi la string qui correspond au code de redirection de search_redirect



`char *unquoter(char *str, t_para *para)`

unquote chaque element de split_redi selon les regles mandatory.



`char *grep_spec(char *str, t_para *para, int mod)`

parser special pour le cas grep dont on a parlé. renvoie une str ou le premier argument de grep sera double quoté pour etre surs de lancer la bonne recherche



`void	launch_redi(t_para *para) (+1, 2)`

une fois la redirection set par search_redirect, elle va lancer le dequotage special pour les redirections et les process de redirection en soit.



`int	choose_redi(t_para *para, int i)`

c'est elle qui selon l'int i qui sert d'index pour la `char **split_redi` va determiner quelle type de redirection on va lancer. retourne 0 si succes et l'int qui correspond a la cmd de split_redi qui fait a fail en cas d'echec



`void ft_freeee_split_redi(t_para *para)`

il vide le split_redi en settant tous ses args a NULL pour eviter des baits



`int	ft_exec_red(t_para *para, char *str)`

il execute les commande que lui envoie les differents redirecteurs selon la `char *str`. Si la commande s'est lancée sans  probleme, retourne 0 sinon retourne 1.



`int	redi1(t_para para) (+2)`

la redirection qui correspond au pipe "|". elle renvoie 0 si ok, et l'index de split_redi qui foire en cas d'echec.
