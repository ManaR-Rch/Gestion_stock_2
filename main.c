#include <stdio.h>
#include <string.h>

#define MAX 100

typedef struct {
    char titre[50];
    char auteur[50];
    float prix;
    int quantite;
} Livre;

Livre stock[MAX];
int nombre_livres = 0;

void afficherLivres() {
    if (nombre_livres == 0) {
        printf("Aucun livre disponible dans le stock.\n");
    } else {
        printf("\n--- Livres disponibles ---\n");
        for (int i = 0; i < nombre_livres; i++) {
            printf("Titre : %s\nAuteur : %s\nPrix : %.2f\nQuantité : %d\n\n",
                   stock[i].titre, stock[i].auteur, stock[i].prix, stock[i].quantite);
        }
    }
}

void afficherStatistiques() {
    int totalQuantite = 0;
    for (int i = 0; i < nombre_livres; i++) {
        totalQuantite += stock[i].quantite;
    }
    printf("\n--- Statistiques ---\n");
    printf("Nombre total de livres en stock : %d\n", nombre_livres);
    printf("Quantité totale de livres : %d\n", totalQuantite);
}

void ajouterLivreOuPlusieurs() {
    int choix, nombre;

    printf("\n--- Ajout de Livres ---\n");
    printf("Voulez-vous ajouter :\n");
    printf("1. Un seul livre\n");
    printf("2. Plusieurs livres\n");
    printf("Entrez votre choix : ");
    scanf("%d", &choix);

    switch (choix) {
        case 1:
            if (nombre_livres < MAX) {
                printf("\n--- Ajout d'un livre ---\n");
                printf("Entrez le titre du livre : ");
                scanf(" %[^\n]", stock[nombre_livres].titre);
                printf("Entrez l'auteur du livre : ");
                scanf(" %[^\n]", stock[nombre_livres].auteur);
                printf("Entrez le prix du livre : ");
                scanf("%f", &stock[nombre_livres].prix);
                printf("Entrez la quantité en stock : ");
                scanf("%d", &stock[nombre_livres].quantite);
                nombre_livres++;
                printf("Livre ajouté avec succès !\n");
                afficherLivres();
                afficherStatistiques();
            } else {
                printf("Le stock est plein !\n");
            }
            break;

        case 2:
            printf("Combien de livres voulez-vous ajouter ? ");
            scanf("%d", &nombre);
            for (int i = 0; i < nombre; i++) {
                if (nombre_livres < MAX) {
                    printf("\n--- Ajout du livre %d ---\n", i + 1);
                    printf("Entrez le titre du livre : ");
                    scanf(" %[^\n]", stock[nombre_livres].titre);
                    printf("Entrez l'auteur du livre : ");
                    scanf(" %[^\n]", stock[nombre_livres].auteur);
                    printf("Entrez le prix du livre : ");
                    scanf("%f", &stock[nombre_livres].prix);
                    printf("Entrez la quantité en stock : ");
                    scanf("%d", &stock[nombre_livres].quantite);
                    nombre_livres++;
                    printf("Livre ajouté avec succès !\n");
                } else {
                    printf("Le stock est plein !\n");
                    break;
                }
            }
            afficherLivres();
            afficherStatistiques();
            break;

        default:
            printf("Choix invalide.\n");
            break;
    }
}

void rechercherLivre() {
    char titre[50];
    printf("Entrez le titre du livre à rechercher : ");
    scanf(" %[^\n]", titre);

    for (int i = 0; i < nombre_livres; i++) {
        if (strcmp(stock[i].titre, titre) == 0) {
            printf("\nLivre trouvé :\nTitre : %s\nAuteur : %s\nPrix : %.2f\nQuantité : %d\n",
                   stock[i].titre, stock[i].auteur, stock[i].prix, stock[i].quantite);
            afficherLivres();
            afficherStatistiques();
            return;
        }
    }
    printf("Livre non trouvé.\n");
}

void mettreAJourQuantite() {
    char titre[50];
    int nouvelle_quantite;
    printf("Entrez le titre du livre à mettre à jour : ");
    scanf(" %[^\n]", titre);

    for (int i = 0; i < nombre_livres; i++) {
        if (strcmp(stock[i].titre, titre) == 0) {
            printf("Entrez la nouvelle quantité : ");
            scanf("%d", &nouvelle_quantite);
            stock[i].quantite = nouvelle_quantite;
            printf("Quantité mise à jour avec succès !\n");
            afficherLivres();
            afficherStatistiques();
            return;
        }
    }
    printf("Livre non trouvé.\n");
}

void trierLivres() {
    int choix;
    Livre temp;

    printf("\n--- Choisissez une option de tri ---\n");
    printf("1. Trier de A à Z\n");
    printf("2. Trier de Z à A\n");
    printf("Entrez votre choix : ");
    scanf("%d", &choix);

    switch (choix) {
        case 1:
            for (int i = 0; i < nombre_livres - 1; i++) {
                for (int j = i + 1; j < nombre_livres; j++) {
                    if (strcmp(stock[i].titre, stock[j].titre) > 0) {
                        temp = stock[i];
                        stock[i] = stock[j];
                        stock[j] = temp;
                    }
                }
            }
            printf("Livres triés de A à Z.\n");
            break;

        case 2:
            for (int i = 0; i < nombre_livres - 1; i++) {
                for (int j = i + 1; j < nombre_livres; j++) {
                    if (strcmp(stock[i].titre, stock[j].titre) < 0) {
                        temp = stock[i];
                        stock[i] = stock[j];
                        stock[j] = temp;
                    }
                }
            }
            printf("Livres triés de Z à A.\n");
            break;

        default:
            printf("Choix invalide.\n");
            return;
    }

    afficherLivres();
    afficherStatistiques();
}

void supprimerLivre() {
    char titre[50];
    char confirmation;
    printf("Entrez le titre du livre à supprimer : ");
    scanf(" %[^\n]", titre);

    for (int i = 0; i < nombre_livres; i++) {
        if (strcmp(stock[i].titre, titre) == 0) {
            printf("Voulez-vous vraiment supprimer ce livre (O/N) ? ");
            scanf(" %c", &confirmation);
            if (confirmation == 'O' || confirmation == 'o') {
                for (int j = i; j < nombre_livres - 1; j++) {
                    stock[j] = stock[j + 1];
                }
                nombre_livres--;
                printf("Livre supprimé avec succès !\n");
                afficherLivres();
                afficherStatistiques();
            } else {
                printf("Suppression annulée.\n");
            }
            return;
        }
    }
    printf("Livre non trouvé.\n");
}

int main() {
    int choix;
    do {
        printf("\n--- Gestion de Stock de Livres ---\n");
        printf("1. Ajouter un ou plusieurs livres\n");
        printf("2. Afficher tous les livres\n");
        printf("3. Rechercher un livre par son titre\n");
        printf("4. Mettre à jour la quantité d'un livre\n");
        printf("5. Supprimer un livre\n");
        printf("6. Trier les livres\n");
        printf("7. Afficher les statistiques (quantité totale et nombre total de livres)\n");
        printf("0. Quitter\n");
        printf("Entrez votre choix : ");
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                ajouterLivreOuPlusieurs();
                break;
            case 2:
                afficherLivres();
                afficherStatistiques();
                break;
            case 3:
                rechercherLivre();
                break;
            case 4:
                mettreAJourQuantite();
                break;
            case 5:
                supprimerLivre();
                break;
            case 6:
                trierLivres();
                break;
            case 7:
                afficherStatistiques();
                break;
            case 0:
                printf("Au revoir !\n");
                break;
            default:
                printf("Choix invalide. Veuillez réessayer.\n");
        }
    } while (choix != 0);

    return 0;
}
