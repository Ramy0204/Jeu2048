# Jeu2048

## Présentation
Jeu2048 est une implémentation en C++ du célèbre jeu de puzzle à blocs coulissants, 2048. Le but pour les joueurs est de fusionner des tuiles portant les mêmes nombres pour atteindre un score plus élevé, en visant la tuile ultime de 2048.

## Fonctionnalités
- Interface simple et intuitive.
- Comptabilisation des points en temps réel.
- Capacité de jouer avec des commandes clavier faciles.

## Comment ca marche?
- Les fonctions de mouvement (Gauche, droite, haut et bas) fonctionnent avec un algorithme. Pour bien comprendre, nous prendrons l'exemple de la fonction droite(), la fonction parcourt la grille g de haut en bas, puis parcourt la ligne de droite à gauche et si on trouve une tuile, on la bouge le plus à droite possible, et nous vérifions s'il est possible de la fusionner avec la tuile à droite. Les fonctions gauche(), haut() et bas() sont analogues à cela.
- nous avons ajouté quelques fonctions pour rendre le code plus lisible
    - 'ajout_tuile' : cette fonction prend une grille g en paramètre par passage en référence et place une tuile aléatoirement dans la grille. Cette tuile peut être un 2 ou un 4 suivant la proportion de la grille. Cette fonction est utilisée lors du jeu pour ajouter une tuile après chaque mouvement du joueur, sauf si le tableau est rempli.
    - 'perdu' : cette fonction prend une grille et retourne true s'il n'y a plus de mouvements possibles, je n'ai pas utilisé les fonctions de mouvement car elles changent la grille directement et il serait plus complexe puisqu'on devrait faire 4 itérations de double boucle alors qu'ici on a 1 seule double boucle.

## Comment commencer ?
Pour commencer à utiliser Jeu2048, suivez ces étapes simples :
1. Clonez le dépôt : `git clone https://github.com/Ramy0204/Jeu2048.git`
2. Naviguez dans le dossier du projet.
3. Compilez le code source et l'executer avec la commande "make jeu"
4. Profitez de jouer à votre jeu préféré!

## Contributions
Les contributions sont toujours les bienvenues ! Si vous souhaitez améliorer le Jeu2048, veuillez forker le dépôt, créer une nouvelle branche pour vos modifications, et soumettre une pull request après vos commits.

## Auteurs
- Ramy (Créateur et Développeur principal)
- Majid (Contributeur spirituel et inspirateur involontaire)

