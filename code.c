#include <stdio.h>
#include <stdlib.h>

// Define a structure for a card node
typedef struct Card {
    int value;
    int flipped;
    struct Card* next;
} Card;

// Function to create a new card node
Card* createCard(int value) {
    Card* newCard = (Card*)malloc(sizeof(Card));
    newCard->value = value;
    newCard->flipped = 0; // Initially, the card is not flipped
    newCard->next = NULL;
    return newCard;
}

// Function to add a card to the end of the linked list
void addCard(Card** head, int value) {
    Card* newCard = createCard(value);
    if (*head == NULL) {
        *head = newCard;
    } else {
        Card* current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newCard;
    }
}

// Function to flip a card
void flipCard(Card* card) {
    card->flipped = 1;
}

// Function to check if two flipped cards match
int cardsMatch(Card* card1, Card* card2) {
    return (card1->value == card2->value) && (card1->flipped == 1) && (card2->flipped == 1);
}

// Function to remove a card from the linked list
void removeCard(Card** head, Card* cardToRemove) {
    if (*head == cardToRemove) {
        *head = cardToRemove->next;
    } else {
        Card* current = *head;
        while (current->next != cardToRemove) {
            current = current->next;
        }
        current->next = cardToRemove->next;
    }
    free(cardToRemove);
}

// Function to print the current state of the game
void printGameStatus(Card* head) {
    Card* current = head;
    while (current != NULL) {
        if (current->flipped) {
            printf("%d ", current->value);
        } else {
            printf("X ");
        }
        current = current->next;
    }
    printf("\n");
}

int main() {
    Card* head = NULL;

    // Add some cards to the game
    addCard(&head, 1);
    addCard(&head, 2);
    addCard(&head, 3);
    addCard(&head, 1);
    addCard(&head, 2);
    addCard(&head, 3);

    int matchedPairs = 0;

    while (matchedPairs < 3) {
        int choice1, choice2;

        // Ask the player to choose two cards
        printf("Choose two cards to flip (0-5): ");
        scanf("%d %d", &choice1, &choice2);

        // Ensure the choices are valid
        if (choice1 < 0 || choice1 > 5 || choice2 < 0 || choice2 > 5 || choice1 == choice2) {
            printf("Invalid choices. Please try again.\n");
            continue;
        }

        Card* card1 = head;
        Card* card2 = head;

        // Find the selected cards in the linked list
        for (int i = 0; i < choice1; i++) {
            card1 = card1->next;
        }

        for (int i = 0; i < choice2; i++) {
            card2 = card2->next;
        }

        // Flip the selected cards
        flipCard(card1);
        flipCard(card2);

        // Print the current state of the game
        printGameStatus(head);

        // Check if the flipped cards match
        if (cardsMatch(card1, card2)) {
            printf("You found a pair!\n");
            matchedPairs++;
            removeCard(&head, card1);
            removeCard(&head, card2);
        }
    }

    printf("Congratulations! You've matched all pairs.\n");

    // Free memory for the remaining cards
    while (head != NULL) {
        Card* temp = head;
        head = head->next;
        free(temp);
    }

    return 0;
}
