//Explications de la struct//


`char *prompt`

C'est la ptite ligne qui apparait quand on attend une commande, je pensais la pimper un peu avec genre un utilisateur perso donne en arg quand on lance minishell... a voir.



`char *current`

la ligne de commande tapee qui contient du coup tous ce qui a a faire... Faudra voir pour la modifier selon les quotes, pipes,...


`int cmd`

int que search_fct a renvoye apres avoir cherche dans current.



`int quote`

je pensais utiliser un int pour verifier que dans current il n'y ait pas de quote non ferme et sera aussi surement utile pour supprimer les quotes de la char * sur un echo par exemple.



`char **env_var`

on va stocker les variable d'environnement la dedans (pour les fonctions env et export)




//Explication des fonctions//


`int	search_fct(char *str)`

cherche si une des commandes que l'on doit coder est pr�sente dans str et renvoie son num�ro.
Fonctions et leurs num�ros :
echo -n = 1;
echo = 2;
cd = 3;
pwd = 4;
export = 5;
unset = 6;
env = 7;
exit = 8;



`void	do_fct(int cmd, char *current)`

Re�oit en arg l'int revoy� par search_fct et ex�cute la commande correspondante.



`void ft_echo(int mode, char *str)`

Ecrit la str avec ou sans \n selon le mode :
echo -n = mode 1;
echo = mode 2;



`int	ft_strstr(char *str, char *tofind)`

Un peu diff�rente de la version originale. Cherche si tofind apparait dans str puis renvoie 1 si oui et 0 si aucune occurence n'apparait. (sera utile pour search_fct)