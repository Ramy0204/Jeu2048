#include "jeu.h"
#include <iomanip> // pour setw dans affichage.


/* Les definitions actuelles des fonctions servent uniquement à ce que le
 * compilateur ne râle pas. Il faut bien sur écrire le code de ces fonctions
 */

int vides(const Grille &g) { 
  int vide = 0;
  for (size_t i = 0; i < g.dimension; i+=1){
    for (size_t j = 0; j < g.dimension; j +=1) {
      if (g.table[i][j] == 0) {vide += 1;};
  } 
  }
  return vide;

}

int proportion(const Grille &g) { int res = -1; res = g.proportion; return res; }

int cible(const Grille &g)  {int res = -1;  res = g.cible; return res; }

int dimension(const Grille &g)  {int res = -1;  res = g.dimension; return res; }

int score(const Grille &g)  { int res = -1; res =g.score; return res; }

bool succes(const Grille &g) { 
  for (size_t i = 0; i < g.dimension; i+=1){
    for (size_t j = 0; j < g.dimension; j+=1){
      if  (g.table.at(i).at(j)==g.cible){
        return true;
      }
    }
  }
  return false; 
}

bool perdu(Grille &g) {
  if (vides(g) != 0){return false;}
  for (size_t i = 0; i < g.dimension-1 ; i+=1){
    for  (size_t j=0; j < g.dimension-1; j+=1){
      if (g.table.at(i).at(j) == g.table.at(i+1).at(j)){return false;}
      if (g.table.at(i).at(j+1) == g.table.at(i).at(j)) {return false;}
    }
  }
  return true;  
  
}

bool ajout_tuile(Grille& g) {
  bool res=false; 
  int val= nouvelle(g); // valeur de la tuile a ajouter
  int pos= place(g); // pos est le nombre de vides avant cette tuile
  int vide=0;
  while (vides(g) < pos){ 
    pos = place(g);
  }
  int i = 0,j = 0;
  while (vide <= pos){ // parcourir les vides jusqu'arriver a la bonne case
    if (g.table.at(i).at(j) == 0) {vide+=1;}
    if (vide == pos) {g.table.at(i).at(j) = val; res = true;  break;}
    if  (j==g.dimension-1) {i+=1; j=0;}
    else {j+=1;}
}
return res;
}

bool init(Grille &g, int dimension, int cible, int proportion) {
  bool res = false;
  g.dimension = dimension;
  g.cible = cible;
  g.proportion = proportion;
  g.score = 0;
  if (dimension >= 4){
    g.table = vector<vector <int>> (dimension, vector<int> (dimension, 0)); // initialisation du vecteur
    for (int k = 0; k < 2; k+=1){ // ajouter deux tuiles
      res = ajout_tuile(g);
      if (res == false){return false;} // retourner 0 si l'ajout de tuile echout
    }
  
  }else{
    cout << "La dimension doit être supérieure ou égale à 4." << endl;
  }
  return res;
}

// Ne pas oublier de vérifier la validité des paramètres !
bool charge(Grille &g, vector<vector<int>> &v, int cible, int proportion) {
  size_t dim = v.size(); bool res = false;
  if (dim < 4) { 
    cerr << "Nombre de lignes insuffisant: " << v.size() << endl;
    return res;
  }else{
    g.score = 0;
    g.dimension = v.size();
    g.cible = cible;
    g.proportion = proportion;
    g.table = vector<vector <int>> (g.dimension, vector<int> (g.dimension, 0)); // initialisation du vecteur de la grille avec g.dimension lignes et g.dimension colonnes avec des 0
    for (size_t i = 0; i < g.dimension; i++){ // parcourir les lignes 
      for (size_t j = 0; j < g.dimension; j++){ // parcourir les colonnes
        if (v.at(i).at(j) != 0) {g.table.at(i).at(j) = v.at(i).at(j);} // mettres les tuiles dans leur bonne place
      }
    }
    
    res = true;
  }
  return res;
}


int droite(Grille &g)  { 
  int moved = 0;
  vector<vector<bool>> merged(g.dimension, vector<bool>(g.dimension, false));
  for (size_t i=0; i<g.dimension; i++) { // pacours les lignes de haut en bas
    
    for (int j = g.dimension-2; j >= 0; j-=1){ //parcours des cases de droite a gauche pour assurer que tout les tuiles ce fussionnes dans l'ordre si possible
      if (g.table.at(i).at(j) == 0) {continue;} // passer les case vides
      else{
        int k = j;
        while (k<g.dimension-1){ // bouger la tuile vers la droite jusqu'a trouver une case non vide, puis verifier si on peut les fusionner
          if (g.table.at(i).at(k+1) == 0){g.table.at(i).at(k+1) = g.table.at(i).at(k); g.table.at(i).at(k) =  0; moved = 1;}
          else if (g.table.at(i).at(k+1) != 0 and g.table.at(i).at(k) != 0){
            if (g.table.at(i).at(k) == g.table.at(i).at(k+1) and !merged.at(i).at(k+1)){
              g.table.at(i).at(k+1) *= 2; 
              g.table.at(i).at(k) = 0;
              g.score += g.table.at(i).at(k+1);
              moved = 1;
              merged.at(i).at(k+1) = true;
              }
            break;
            }
          k++;
        }
        
      }
    }
  }
  return moved ? vides(g) : -1; // retourne -1 si pas de movement possible sinon retourne le nombre de cases vides
  }

int gauche(Grille &g)  { 
  int moved = 0;
  vector<vector<bool>> merged(g.dimension, vector<bool>(g.dimension, false));
  for (size_t i=0; i<g.dimension; i++) {// pacours les lignes de haut en bas
    
    for (int j = 0; j <= g.dimension - 1; j +=1){//parcours des cases de gauche a droite pour assurer que tout les tuiles ce fussionnes dans l'ordre si possible
      if (g.table.at(i).at(j) == 0) {continue;}
      else{
        int k = j;
        while (k>0){ // bouger la tuile vers la gauche jusqu'a trouver une case non vide, puis verifier si on peut les fusionner
          if (g.table.at(i).at(k-1) == 0){g.table.at(i).at(k-1) = g.table.at(i).at(k); g.table.at(i).at(k) =  0; moved = 1;}
          else if (g.table.at(i).at(k-1) != 0 and !merged.at(i).at(k-1)){
            if (g.table.at(i).at(k-1) == g.table.at(i).at(k)){
              g.table.at(i).at(k-1) *= 2; 
              g.table.at(i).at(k) = 0;
              g.score += g.table.at(i).at(k-1);
              moved = 1;
              merged.at(i).at(k-1) = true;
              }
            break;
            }
          k--;
        }
        
      }
    }
  }
  return moved ? vides(g) : -1; // idem que les autres fonctions de mouvements
  }



int haut(Grille &g)  { 
  int moved = 0; // pour verifier si il a eu un movement des tuiles
  vector<vector<bool>> merged(g.dimension, vector<bool>(g.dimension, false));

  for (size_t i=0; i<g.dimension; i++) {// parcours des colonnes de gauche a droite
    
    for (int j = 0; j <= g.dimension - 1; j +=1){ //parcours des lignes de haut en bas
      if (g.table.at(j).at(i) == 0) {continue;}
      else{
        int k = j;
        while (k>0){// bouger la tuile vers le haut jusqu'a trouver une case non vide, puis verifier si on peut les fusionner
          if (g.table.at(k-1).at(i) == 0){g.table.at(k-1).at(i) = g.table.at(k).at(i); g.table.at(k).at(i) =  0; moved = 1;}
          else if (g.table.at(k-1).at(i) != 0 and !merged.at(k-1).at(i)){
            if (g.table.at(k-1).at(i) == g.table.at(k).at(i)){
              g.table.at(k-1).at(i) *= 2; 
              g.table.at(k).at(i) = 0;
              g.score += g.table.at(k-1).at(i);
              merged.at(k-1).at(i) = true;
              }
            break;
            }
          k--;
        }
        
      }
    }
  }
  return moved ? vides(g) : -1; 

}

int bas(Grille &g){
  int moved = 0;
  vector<vector<bool>> merged(g.dimension, vector<bool>(g.dimension, false));
  for (size_t i=0; i<g.dimension; i++) {
    for (int j = g.dimension-2; j >= 0; j-=1){
      if (g.table.at(j).at(i) == 0) {continue;}
      else{
        int k = j;
        while (k<g.dimension-1){ //bouger la tuile vers le bas jusqu'a trouver une case non vide puis verifier si on peut les fusionner
          if (g.table.at(k+1).at(i) == 0){g.table.at(k+1).at(i) = g.table.at(k).at(i); g.table.at(k).at(i) =  0; moved = 1;}
          else if (g.table.at(k+1).at(i) != 0 ){
            if (g.table.at(k).at(i) == g.table.at(k+1).at(i) and !merged.at(k+1).at(i)){
              g.table.at(k+1).at(i) *= 2; 
              g.table.at(k).at(i) = 0;
              g.score += g.table.at(k+1).at(i);
              moved = 1;
              merged.at(k+1).at(i) = true;
              }
            break;
            }
          k++;
        }
        
      }
    }
  }
  return moved ? vides(g) : -1; 
  }




/*		 Pour les extensions éventuelles */
void sauve(const Grille &g, string filename) {
  /*
  On sauvegarde la grille et ses parametres dans un fichier texte sur ce format:\
  score
  dimension
  cible
  proportion
  grille
  */
  ofstream fichier("./saves/" + filename + ".txt");
  fichier << g.score << endl; // sauvegarder le score
  fichier << g.dimension << endl; // sauvegarder la dimension de la grille 
  fichier << g.cible << endl; // sauvegarder la cible
  fichier << g.proportion << endl; // sauvegarder la proportion
  for (int i = 0; i < g.dimension; i+=1){
    for (int j = 0; j < g.dimension; j+= 1){
      fichier << g.table.at(i).at(j) << " ";
    }
    fichier << endl;
  }
  fichier.close();
}



void restaure(Grille &g, string filename) {
  /*
  Restaure l'état d'une grille à partir d'un fichier avec le format du fichier sauver de la fonction sauve.
 */
  ifstream  fichier("./saves/" + filename + ".txt");
  int score;
  fichier >> score;
  fichier >> g.dimension;
  int cible; 
  fichier >> cible;
  int proportion;
  fichier >> proportion;
  vector<vector <int>> v (g.dimension , vector<int> (g.dimension, 0));
  for (size_t i = 0; i < g.dimension; i+=1){ // parcourir les lignes
    for (size_t j = 0; j < g.dimension; j += 1){ // parcourir les colonnes
      fichier >> v.at(i).at(j); // recuperer les valeurs des tuiles
    }
  }
  charge(g, v, cible, proportion); // charger la grille
  g.score = score; // mettre le score sauvegarder`
}


/*
 * 		Fonctions mise à disposition. Pas de raison d'y toucher !
 *	Rappel: la fonction main() est dans le fichier test.cpp
 */	



void affiche (const Grille &g) {
  int i, j, k;
  int max = dimension(g);
  cout << endl << " \t ";
  for(k = 0; k < (6+1)*max-1; k = k+1) { cout << "-"; }
  cout << endl;
  /* Verifier si on veut que la ligne du haut soit 0 ou max-1 */
  for(i = 0; i < max; i = i+1) {
    cout << "\t|";
    for(j=0; j < max; j=j+1) {
      if(g.table.at(i).at(j) == 0) {
	cout << "      |";
      } else { cout << " " << setw(4) << g.table.at(i).at(j) << " |" ; }
    }
    if (i != max-1) {
      cout << endl << "\t|";
      for(k = 0; k < (6+1)*max-1; k = k+1) { cout << "-"; }
      cout << "|" << endl;
    } else {
      cout << endl << "\t ";
      for(k = 0; k < (6+1)*max-1; k = k+1) { cout << "-"; }
      cout << endl;
    }
  }
  cout << endl << "Score: " << score(g) << ", Vides: " << vides(g) << endl;
}
