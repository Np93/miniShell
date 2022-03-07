//Contenu des fichiers//


main.c : search_fct, do_fct, cpy_env, init_para, main

echo.c : ft_echo

ft_strstr.c : ft_strlen, ft_strstr

ft_calloc.c : ft_bzero, ft_calloc

ft_strdup.c : ft_strdup

ft_env.c : ft_env, ft_export

ft_pwd.c : ft_pwd




//Explications de la struct//


`char *prompt`

C'est la ptite ligne qui apparait quand on attend une commande, je pensais la pimper un peu avec genre un utilisateur perso donne en arg quand on lance minishell... a voir.



`char *current`

la ligne de commande tapee qui contient du coup tous ce qui a a faire... Faudra voir pour la modifier selon les quotes, pipes,...


`int cmd`

int que search_fct a renvoye apres avoir cherche dans current.



`int quote`

je pensais utiliser un int pour verifier que dans current il n'y ait pas de quote non ferme et sera aussi surement utile pour supprimer les quotes de la char * sur un echo par exemple.



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



`ft_pwd(t_para *para)`

meme que bash : ecrit le chemin ou on se trouve
