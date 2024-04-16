#include "jeu.h"
#include <cassert>

/* A faire dans un second temps: petit menu pour exécuter les commandes de
 * l'utilisateur
 */
int interactif(int dim, int cible, int proportion);
void testFV();

void menu(){
  int dim = 4, cible = 2048, proportion = 9, quit = 0;
  unsigned int choix;
  do{
    cout << "\033[2J";// efface l'ecran
    cout << "1. Lancer le jeu \n2. Choisir parametres \n3. Lancer Teste \n4. Quitter" << endl;
    do{
        cout << "choisir une des options: ";
        cin >> choix;
      }while(choix >  4 or choix == 0);
  switch (choix){
    case 1:
      cout << "\033[2J";// efface l'ecra
      resetRand(true);
      interactif(dim, cible, proportion);
      break;
    case 2:
      choix = 0;
      cout << "\033[2J";// efface l'ecra
      cout << "1. dimension (default = 4): " << dim << endl;
      cout << "2. cible (default = 2048): " << cible << endl;
      cout << "3. proportion (default = 9): " << proportion << endl;
      cout << "4. Retour au menu principal. ";
      do{
        cout << "\nChoissisez  une option a changer: " ;
        cin >> choix;
      }while(choix > 4 or choix == 0);
      switch (choix){
        case 1:
          cout << "veuillez choisir une nouvelle dimension du tableau: ";
          cin >> dim;
          break;
        case 2:
          cout << "veuillez entrer une nouvelle cible: ";
          cin >> cible;
          break;
        case 3:
          cout << "Veuillez entrez une nouvelle valeur de la proportion: ";
          cin >> proportion;
        case 4:
          break;
        
      }
      break;
    case 3:
      testFV();
      cout << "appuyez sur Entrée pour continuer";
      cin.ignore(); //ignorer tout input avant cette ligne
      cin.get(); //detecter un appuie de clavier pour continuer
      break;
    case 4:
      quit = 1;
      break;
    }
  }while(quit == 0);
}
int interactif(int dim, int cible, int proportion) {
  // a faire ulterieurement
  Grille g;
  assert(init(g, dim, cible, proportion)); // exemple d'initialisation d'une grille.
  char choix;
  int m;
  affiche(g);
  cout << "choisir movement (w,a,s,d) ou q pour quitter : ";
  cin >> choix;
  while (choix != 'q'){
    cout << "\033[2J";// efface l'ecran
    switch (choix){
      case 'w':
      m = haut(g);
      break;
      case 's':
      m = bas(g);
      break;
      case 'a':
      m = gauche(g);
      break;
      case 'd':
      m = droite(g);
    }
    if  (m == -1){
      
      if (perdu(g)){
        affiche(g);
        cout << "Vous avez perdu! " <<endl;
        break;
      }else{
        cout << "ce mouvement est impossible veuillez reessayer! " << endl;
        affiche(g);
      }
    }else if (succes(g)){
      affiche(g);
      cout << "Partie gagner! " << endl;
      break;
    }
    else{
      ajout_tuile(g);
      affiche(g);
    }

    do{
      cout << "choisir movement (w,a,s,d) ou q pour quitter : ";
      cin >> choix;
    }while(choix != 'a' and choix != 'w' and choix != 's' and choix != 'd' and choix != 'q');
  }
  return 0;
}


/* Quelques fonctions de test mises à disposition.
 * Elles sont lancées par la fonction testFV qui est elle-même lançable
 * dans la fonction main()à située en fin de fichier.
 * Pour l'instant l'appel à cette fonction est mis en commentaire.
 */


void teste3() {
  Grille g;
  vector<vector<int>> v =
    { { 8, 4, 4, 4 }, { 4, 0, 4, 4 }, { 4, 4, 4, 4 }, { 4, 0, 0, 4} };
  cout << "Debut du test3\n";
  assert(charge(g, v, 32, 7)); // charge et teste le resultat
  affiche(g);

  gauche(g); affiche(g);
  droite(g); affiche(g);
  haut(g);   affiche(g);
  gauche(g); affiche(g);
  haut(g);   affiche(g);
  bas(g);    affiche(g);
  assert(score(g) == 128 and succes(g));
  cout << "Teste3 OK" << endl;
}

void teste3bis() {
  Grille g;
  vector<vector<int>> v =
    { { 2, 4, 0, 0, 4 }, { 4, 0, 4, 8, 8 }, { 0, 0, 4, 0, 4 }, { 2, 4, 0, 0, 4},
      { 2, 4, 0, 4, 2 }
    };
  cout << "Debut du teste3bis" << endl;
  assert(charge(g, v, 64, 10)); // avec que des tuiles de valeur 2
  affiche(g);
  
  gauche(g); affiche(g);
  assert(score(g) == 56 and gauche(g) == -1);
  cout << "teste3bis-I: OK" << endl;
  // On repart de la meme configuration initiale mais on essaye
  // un autre deplacement
  Grille g2;
  assert(charge(g2, v, 8, 0));
  affiche(g2);
  
  haut(g2);   affiche(g2);
  bas(g2);    affiche(g2);
  droite(g2); affiche(g2);
  assert(score(g2) == 68 and vides(g2) == 16);
  cout << "teste3bis-II: OK" << endl;
  cout << "Fin de teste3bis" << endl;
}

void teste4() {
  Grille g;
  vector<vector<int>> v =
  // une grille bloquée.
    { { 128, 8, 2, 4 }, { 4, 16, 4, 8 }, { 8, 2, 8, 4}, { 2, 4, 16, 32} };
  cout << "Debut du test4" << endl;
  assert(charge(g, v, 2048, 7));
  affiche(g);
  
  assert(gauche(g) == -1 and droite(g) == -1 and
	 haut(g)   == -1 and droite(g) == -1);
  affiche(g);
  cout << "Teste4 OK" << endl;
}

void teste5() {
  Grille g;
  cout << "Debut du test5" << endl;
  assert(init(g, 5, 8, 0)); // on ne cree que des tuiles de valeur 4
  affiche(g);
  
  haut(g);   affiche(g);
  droite(g); affiche(g);
  assert(score(g) == 8 and succes(g));
  cout << "Teste5 OK" << endl;
}

void testFV() {
  teste3();
  teste3bis();
  teste4();
  teste5();
}

int main() {
  resetRand(true);
  testFV();
  menu();
  return 0;
}
