#include <stdio.h>
#include <string.h>

#define MAX_PRODUCTS 100
#define MAX_NAME_LENGTH 20

// Arrays to represent product information
int productCodes[MAX_PRODUCTS];
char productNames[MAX_PRODUCTS][MAX_NAME_LENGTH];
int productQuantities[MAX_PRODUCTS];

// Function prototypes
void displayMenu();
void displayStock(int numProducts);
void addProduct(int *numProducts);
void removeProduct(int *numProducts);
void removeQuantity(int numProducts);
void exitProgram();

int main() {


    int numProducts = 0;
    int choice;
    do {
        displayMenu();

        printf("Choisissez l'operation desiree : ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                displayStock(numProducts);
                break;
            case 2:
                addProduct(&numProducts);
                break;
            case 3:
                removeProduct(&numProducts);
                break;
            case 4:
                removeQuantity(numProducts);
                break;
            case 5:
                exitProgram();
                break;
            default:
                printf("Choix invalide. Veuillez ressayer.\n");
        }

    } while (choice != 5);

    return 0;
}

void displayMenu() {
    printf("\n        Menu\n");
    printf("\n");
    printf("1. Afficher le stock\n");
    printf("2. Ajouter un produit\n");
    printf("3. Retirer un produit\n");
    printf("4. Retirer une quantite\n");
    printf("5. Sortir\n");
    printf("\n");
}

void displayStock(int numProducts) {
	
	if (numProducts==0)
    	printf("Attention le stock est vide, veuillez le remplir!\n");
    	else {
    printf("\nProduit du stock\n");
    printf("%-15s%-25s%-10s\n", "Code", "Noms", "Quantite");

    for (int i = 0; i < numProducts; i++) {
    	
        printf("%-15d%-25s%-10d\n", productCodes[i], productNames[i], productQuantities[i]);
    }
  } 
}


void addProduct(int *numProducts) {
    if (*numProducts == MAX_PRODUCTS) {
        printf("Le stock est plein. Impossible d'ajouter plus de produits.\n");
        return;
    }

    int newCode;
    printf("Entrez le code du produit (00-99) : ");
    scanf("%d", &newCode);

    if (newCode < 0 || newCode > 99) {
        printf("Code de produit invalide. Veuillez ressayer.\n");
        return;
    }

    // Check if the code already exists in the stock
    for (int i = 0; i < *numProducts; i++) {
        if (productCodes[i] == newCode) {
            printf("Produit existant avec le meme code. Nom du produit : %s\n", productNames[i]);

            // Ask for the quantity to be added to the existing quantity
            int quantity;
            printf("Entrez la quantite a ajouter : ");
            scanf("%d", &quantity);

            productQuantities[i] += quantity;
            printf("Quantite ajoutee avec succes.\n");
            return;
        }
    }

    // If the code is not found, proceed to add a new product
    productCodes[*numProducts] = newCode;

    printf("Entrez le nom du produit : ");
    scanf("%s", productNames[*numProducts]);

    printf("Entrez la quantite du produit : ");
    scanf("%d", &productQuantities[*numProducts]);

    (*numProducts)++;
    printf("Produit ajoute avec succes.\n");
}

void removeProduct(int *numProducts) {
    if (*numProducts == 0) {
        printf("Le stock est vide. Impossible de retirer des produits.\n");
        return;
    }

    int productCode;
    printf("Entrez le code du produit a retirer (00-99) : ");
    scanf("%d", &productCode);

    if (productCode < 0 || productCode > 99) {
        printf("Code de produit invalide. Veuillez ressayer.\n");
        return;
    }

    int foundIndex = -1;
    for (int i = 0; i < *numProducts; i++) {
        if (productCodes[i] == productCode) {
            foundIndex = i;
            break;
        }
    }

    if (foundIndex != -1) {
        // Remove the product by shifting elements to fill the gap
        for (int i = foundIndex; i < *numProducts - 1; i++) {
            productCodes[i] = productCodes[i + 1];
            strncpy(productNames[i], productNames[i + 1], MAX_NAME_LENGTH);
            productQuantities[i] = productQuantities[i + 1];
        }

        (*numProducts)--;
        printf("Produit retire avec succes.\n");
    } else {
        printf("Produit non trouve. Veuillez ressayer.\n");
    }
}

void removeQuantity(int numProducts) {
    if (numProducts == 0) {
        printf("Le stock est vide. Impossible de retirer des quantites.\n");
        return;
    }

    int productCode;
    printf("Entrez le code du produit (00-99) : ");
    scanf("%d", &productCode);

    if (productCode < 0 || productCode > 99) {
        printf("Code de produit invalide. Veuillez ressayer.\n");
        return;
    }

    int quantity;
    printf("Entrez la quantite a retirer : ");
    scanf("%d", &quantity);

    int foundIndex = -1;
    for (int i = 0; i < numProducts; i++) {
        if (productCodes[i] == productCode) {
            foundIndex = i;
            break;
        }
    }

    if (foundIndex != -1) {
        // Check if there's enough quantity to remove
        if (productQuantities[foundIndex] >= quantity) {
            productQuantities[foundIndex] -= quantity;
            printf("Quantite retiree avec succes.\n");
        } else {
            printf("Quantite insuffisante. Veuillez ressayer.\n");
        }
    } else {
        printf("Produit non trouve. Veuillez ressayer.\n");
    }
}

void exitProgram() {
    printf("Sortir du programme. Au revoir !\n");
}

