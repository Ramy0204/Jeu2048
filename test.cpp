#include "jeu.h"
#include <cassert>

/* A faire dans un second temps: petit menu pour exécuter les commandes de
 * l'utilisateur
 */
bind binds = {'w', 's', 'a', 'd'};

int interactif(Grille &g);
void testFV();
void Parametres(Grille &g){
  bool s = true;
  int choix = 0;
  
  do{
    cout << "\033[2J";// efface l'ecran
    cout << "1. dimension (default = 4): " << g.dimension << endl;
    cout << "2. cible (default = 2048): " << g.cible << endl;
    cout << "3. proportion (default = 9): " << g.proportion << endl;
    cout << "4. Changer les cle de mouvements (Default : w (haut), a (gauche), s (bas), d (droite)) \n";
    cout << "5. Retour au menu principal.\n";
    cout << "Choissisez une option a changer: ";
    cin >> choix;
  
  switch (choix){
    case 1:
      cout << "veuillez choisir une nouvelle dimension du tableau: ";
      cin >> g.dimension;
      break;
    case 2:
      cout << "veuillez entrer une nouvelle cible: ";
      cin >> g.cible;
      break;
    case 3:
      cout << "Veuillez entrez une nouvelle valeur de la proportion: ";
      cin >> g.proportion;
      break;
    case 4:
      cout << "\033[2J";// efface l'ecran
      cout << "Cles de mouvements actuelles: " << binds.haut << " (haut), " << binds.gauche << " (gauche), " << binds.bas << " (bas), " << binds.droite << " (droite)" << endl;
      cout << "veuillez entrer les nouvelles cle de mouvements (q pour annuler): \n";
      cout << "haut: ";
      cin >> binds.haut;
      if (binds.haut == 'q'){
        break;
      }
      cout << "gauche: ";
      cin >> binds.gauche;
      if (binds.gauche == 'q'){
        break;
      }
      cout << "bas: ";
      cin >> binds.bas;
      if (binds.bas == 'q'){
        break;
      }
      cout << "droite: ";
      cin >> binds.droite;
      if (binds.droite == 'q'){
        break;
      }
      break;
    case 5:
      s=false;
      break;
    default:
      break;
    
  }
  }while(s);
}

int load(Grille &g){
  restaure(g, "save");
  return 0;
}

void menu(){
  Grille g;
  int dim = 4, cible = 2048, proportion = 9, quit = 0;
  unsigned int choix;
  init(g, dim, cible, proportion);
  do{
    dim = g.dimension;
    cible = g.cible;
    proportion = g.proportion;
    
    cout << "\033[2J";// efface l'ecran
    cout << "1. Lancer une nouvelle partie \n2. Continuer la derniere partie sauveguarder \n3. Choisir parametres \n4. Lancer Teste \n5. Quitter" << endl;
    do{
        cout << "choisir une des options: ";
        cin >> choix;
      }while(choix >  5 or choix == 0);
  switch (choix){
    case 1:
      init(g, dim, cible, proportion);
      cout << "\033[2J";// efface l'ecran
      interactif(g);
      break;
    case 2:
      load(g);
      cout << "\033[2J";// efface l'ecran
      interactif(g);
      break;
    case 3:
      Parametres(g);
      break;
    case 4:
      testFV();
      cout << "appuyez sur Entrée pour continuer";
      cin.ignore(); //ignorer tout input avant cette ligne
      cin.get(); //detecter un appuie de clavier pour continuer
      break;
    case 5:
      quit = 1;
      break;
    }
  }while(quit == 0);
}
int interactif(Grille &g) {
  // a verifier si double fusion possible (verifier???)
  resetRand(true);
  char choix;
  int m;
  affiche(g);
  cout << "choisir movement (w,a,s,d) ou q pour quitter : ";
  cin >> choix;
  while (choix != 'q'){
    cout << "\033[2J";// efface l'ecran
    if (choix == binds.haut) {
      m = haut(g);
    } else if (choix == binds.bas) {
      m = bas(g);
    } else if (choix == binds.gauche) {
      m = gauche(g);
    } else if (choix == binds.droite) {
      m = droite(g);
    }
    if  (m == -1){
      
      if (perdu(g)){
        affiche(g);
        char question;
        cout << "Vous avez perdu !" << endl;
        do{
          cout << "Veut tu recomencer une partie(y/n)? ";
          cin >> question;
        }while(question != 'y' and question != 'n');
        switch (question)
        {
          case 'y':
          init(g, g.dimension, g.cible, g.proportion);
          cout << "\033[2J";

          interactif(g);
          return 0;
        
          default:
            return 0;
        }
      }else{
        cout << "ce mouvement est impossible veuillez reessayer! " << endl;
        affiche(g);
      }
    }else if (succes(g)){
      affiche(g);
      cout << "Partie gagner! " << endl;
      char question;
      do{
          cout << "Veut tu recomencer une partie(y/n)? ";
          cin >> question;
        }while(question != 'y' and question != 'n');
        switch (question)
        {
          case 'y':
            init(g, g.dimension, g.cible, g.proportion);
            cout << "\033[2J";
            interactif(g);
            return 0;
        
          default:
            return 0;
      }
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
  char question;
  
  do{
      cout << "Veut tu sauveguarder ta partie (y/n)? ";
      cin >> question;
  }while (question != 'y' and question != 'n');
  switch  (question){
    case 'y':
      sauve(g, "save");
    case 'n':
      break;
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


void teste6(){
  Grille g;
  cout << "Debut du teste6" << endl;

  vector<vector<int>> v =
  {{0,0,4,0},
   {0,0,0,0},
   {0,0,4,0},
   {0,0,8,0}};
   assert(charge(g, v, 16, 9));
   affiche(g);
   bas(g);
   affiche(g);
   assert(not(succes(g)));
   cout<<"Teste6 OK" << endl;
}


void testFV() {
  teste3();
  teste3bis();
  teste4();
  teste5();
  teste6();
}

int main() {
  resetRand(true); 
  //testFV();
  menu();
  return 0;
}
