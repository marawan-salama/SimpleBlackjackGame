/*Marawan Salama**/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

typedef struct {
		char rank;
		char suit;
} Card;

typedef struct {
		Card cards[5];
		int card_count;
		int value;
} Hand;

void shuffle(Card *deck, int size) {
		for (int i = size - 1; i > 0; i--) {
				int j = rand() % (i + 1);
				Card temp = deck[i];
				deck[i] = deck[j];
				deck[j] = temp;
		}
}

int cardValue(Card card) {
		if (card.rank >= '2' && card.rank <= '9') {
				return card.rank - '0';
		} else if (card.rank == 'A') {
				return 11;
		} else {
				return 10;
		}
}

void updateHandValue(Hand *hand) {
		hand->value = 0;
		int aces = 0;
		for (int i = 0; i < hand->card_count; i++) {
				int card_val = cardValue(hand->cards[i]);  // Corrected line
				hand->value += card_val;
				if (card_val == 11) aces++;
		}
		while (hand->value > 21 && aces > 0) {
				hand->value -= 10;
				aces--;
		}
}

void addCardToHand(Hand *hand, Card card) {
		if (hand->card_count < 5) {
				hand->cards[hand->card_count] = card;
				hand->card_count++;
				updateHandValue(hand);
		}
}

void printCard(Card card) {
		printf("%c%c ", card.rank, card.suit);
}

void printHand(Hand hand, int hideFirstCard) {
		if (hideFirstCard) {
				printf("?? ");
				for (int i = 1; i < hand.card_count; i++) {
						printCard(hand.cards[i]);
				}
		} else {
				for (int i = 0; i < hand.card_count; i++) {
						printCard(hand.cards[i]);
				}
		}
}

int playerTurn(Card *deck, int *deckIndex, Hand *playerHand) {
		char choice[10];
		while (1) {
				printf("\n> ");
				scanf("%s", choice);
				if (strcmp(choice, "hit") == 0) {
						addCardToHand(playerHand, deck[(*deckIndex)++]);
						printf("Dealer: ");
						printHand(*playerHand, 1);
						printf("\nPlayer: ");
						printHand(*playerHand, 0);
						if (playerHand->value > 21) {
								printf("\nPlayer busts!\n");
								return 0;
						}
						if (playerHand->card_count == 5) {
								return 1;
						}
				} else if (strcmp(choice, "stay") == 0) {
						return 1;
				} else if (strcmp(choice, "quit") == 0) {
						exit(0);
				}
		}
}

int dealerTurn(Card *deck, int *deckIndex, Hand *dealerHand) {
		while (dealerHand->value < 16 && dealerHand->card_count < 5) {
				addCardToHand(dealerHand, deck[(*deckIndex)++]);
				printf("Dealer hits: ");
				printHand(*dealerHand, 0);
				if (dealerHand->value > 21) {
						printf("\nDealer busts!\n");
						return 0;
				}
		}
		return 1;
}

void playBlackjack() {
		Card deck[52];
		char suits[] = {'C', 'D', 'H', 'S'};
		char ranks[] = "23456789TJQKA";
		int index = 0;
		for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 13; j++) {
						deck[index].suit = suits[i];
						deck[index].rank = ranks[j];
						index++;
				}
		}

		int playerScore = 100;
		int deckIndex = 0;
		shuffle(deck, 52);

		while (playerScore > 0 && deckIndex < 52 - 20) {
				printf("*******Blackjack game********\n");
				printf("Total :%d\n", playerScore);
				printf("Deck: %d\n", 52 - deckIndex);

				Hand playerHand = {0};
				Hand dealerHand = {0};

				addCardToHand(&playerHand, deck[deckIndex++]);
				addCardToHand(&dealerHand, deck[deckIndex++]);
				addCardToHand(&playerHand, deck[deckIndex++]);
				addCardToHand(&dealerHand, deck[deckIndex++]);

				printf("Dealer: ");
				printHand(dealerHand, 1);
				printf("\nPlayer: ");
				printHand(playerHand, 0);

				if (playerTurn(deck, &deckIndex, &playerHand)) {
						printf("\nDealer: ");
						printHand(dealerHand, 0);
						if (dealerTurn(deck, &deckIndex, &dealerHand)) {
								if (playerHand.value > dealerHand.value) {
										printf("Player wins!\n");
										playerScore += 10;
								} else if (playerHand.value < dealerHand.value) {
										printf("Dealer wins!\n");
										playerScore -= 10;
								} else {
										printf("It's a push!\n");
								}
						} else {
								playerScore += 10;
						}
				} else {
						playerScore -= 10;
				}

				printf("\nTotal :%d\n", playerScore);
				printf("Deck: %d\n", 52 - deckIndex);
		}

		printf("Good game!\n");
}

int main() {
		srand(time(NULL));
		playBlackjack();
		return 0;
}
