# Jeu2048

## Présentation
Jeu2048 est une implémentation en C++ du célèbre jeu de puzzle à blocs coulissants, 2048. Le but pour les joueurs est de fusionner des tuiles portant les mêmes nombres pour atteindre un score plus élevé, en visant la tuile ultime de 2048.

## Fonctionnalités
- Interface simple et intuitive.
- Comptabilisation des points en temps réel.
- Capacité de jouer avec des commandes clavier faciles.

## Comment ca marche?
- Les fonction de mouvement (Gauche, droite, haut et bas) foncionnent avec un algorithme. Pour bien comprendre nous prendrons l'exemple de la fonction droite(), la fonction parcours la grille g de haut en bas, puis parcours la ligne de droite a gauche et si on trouve une tuile, on la bouge le plus a droite possible, et nous verifions si il est possible de la fusionner avec la tuile a droite. Les fonctions gauche(), haut() et bas() sont analogue a cela.
- nous avons ajouter quelque fonction pour rendre le code plus lisible
    - 'ajout_tuile' : cette fonction prends une grille g en parametre par passage en reference et place une tuille aleatoirement dans la grille. Cette tuile peut etre un 2 ou un 4 suivant la proportion de la grille. Cette fonction est utiliser lors du jeu pour ajouter une tuile apres chaque movement du joueur, sauf si le tableau est remplis.
    - 'perdu' : cette fonction prends une grille et retourne true si il n'y a plus de mouvements possible, je n'ai pas utiliser les fonction de mouvement car ils change la grille directement et il sera plus complex puisqu'on devra faire 4 iteration de double boucle alors qu'ici on a 1 seul double boucle.

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

