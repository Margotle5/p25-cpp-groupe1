Déclaration et définition:

Définition de variable à l'ext du main--> variable globale
Mécanisme de pile d'exécution: il "empile" les variables et le pointeur se balade de couche en couche

|  i=17 | Dans boucle if
|  i=12 | Dans main
|___N___| Dans global

int N; //globale, initialisation de variable global à vide pour int = 0, pour char = '0'
int main(){
    int i = 12; //locale
    if (i<3)
    {
        int i = 17; //Dans ce bloc le i d'avant est caché
    }
    //Sortie du bloc if, le i d'avant est de retour
    i= i + 1; //i=13
}

Pointeurs:
