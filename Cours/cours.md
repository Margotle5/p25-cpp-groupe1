Déclaration et définition:

Définition de variable à l'ext du main--> variable globale
Mécanisme de pile d'exécution: il "empile" les variables et le pointeur se balade de couche en couche, dernier arrivé, premier sortie

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

Dangling error:
Lorsqu'on référence un emplacement mémoire qui n'est pas attribuer
Exemple:
    int* create_stack(int size){
        int tab[size];
        return tab;
    }   
    int main(){

        // on définit les 3 variables constituant la pile
        int size = 5;
        create_stack(size);
        int nb = 0;
        push(tab, size, &nb, -17)
        return 0
        }

Pour éviter ce problème, on utilise le 'heap' ie la mémoire dynamique
int* pi=new int(12) // stock dans la mémoire l'adresse de la case dans mémoire dynamique
delete pi; // désaloue l'adresse dans la mémoire dynamique, la zone a été libéré mais pi existe toujours, il référence juste rien

new int [nb] crée un tableau dans le heap
Il faut toujours delete l'objet à la fin de son utilisation! Pour des class avec des tableau dans le heap utiliser le bloc suivant dans le corps de la classe
~NomClass(){
    del tab;
}

Exemple:
Stack *ps = new Stack(200);
ps->push(-17);
delete ps; //delete appel d'abord le destructeur de ps puis delete le truc à l'adresse ps de la mémoire heap

