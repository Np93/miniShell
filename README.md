//Contenu des fichiers//


main.c : cpy_env, init_para, main

search_fct.c : search_fct, do_fct

echo.c : ft_echo

ft_strstr.c : ft_strlen, ft_strstr

ft_calloc.c : ft_bzero, ft_calloc

ft_strdup.c : ft_strdup

ft_env.c : ft_env, ft_export, ft_unset(et ft_unset2), ft_getenv

ft_pwd.c : ft_pwd

ft_cd.c : ft_cd, get_env, ft_memcmp

ft_split.c : ft_split

ft_strjoin.c : ft_strjoin

init.c : prompt_init

current_parser.c : get_dollar, current_parser(+ 2, 3 et 4)

current_parser2.c : current_parser5 (=+ 6)

error_handler : error_handler

ft_cd.c : ft_memcmp, ft_getenv, ft_cd

cmd_not_found.c : cmd_cmp, verif_fquote, cmd_not_found, cmd_not_found2

sig_handler.c : sig_handler

execve_default.c : ft_execve, free_exec, all_path_exec, exec_and_return




//Explications de la struct// (j'ai add une struct t_parse pour une fonction qui me les brisait t'en soucie pas)


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



`void cmd_not_found(char *str)`

ecrit qu'aucune fonction ne correspond a la string passee en argument



`void cmd_not_found2(char *str)`

la meme mais c'est pour le cas ou ya eu le debut de la current qui etait quote ce qui change un peu la sortie



`int verif_fquote(t_para *para)`

verifie si le debut de para->current etait quoté car ca modifie un peu la recherche et la sortie. revoie 0 si on peut continuer sans soucis et 1 si l'argument pose soucis auquel cas on stock ledit argument dans para->bait.



`int	cmd_cmp(char *str)`

en gros c'est un peu commme search_fct mais modifiee pour pouvoir etre utilisee par verif_fquote.


`void	ft_signal(void)`

initialise le captage des signaux dans le main.



`void	sig_handler(int sig)`

il gere les signaux envoyé ("CTRL+C" et "CTRL+\") pour le CTRL+D c'est directement dans le main c'est plus tricky car CTRL+D fait quit le programme si le stdin a atteint EOF donc est NULL.



`int	ft_execve(t_para *para)`

si la commande passee dans para->current ne correspond a rien qu'on a du construire, il va tenter de lancer la commande avec le vrai shell. Si elle existe pas non plus dans le vrai shell, c'est comme meme minishell qui dit commande not found.



`char	**all_path_exec(t_para *para, char *end`

ça va chercher tous les chemins pssoible pour executer les cmd avec execve et renvoier le tableaux de str pour les tests.



`int	exec_and_return(char **all_path, char **argv, t_para *para)`

split de fonction a cause de la norminette c'est l'executeur du process ft_execve.
