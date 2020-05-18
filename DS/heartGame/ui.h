#ifndef __UI_H_
#define __UI_H_

#include "card.h"
#include "ADTErrors.h"

void PrintCardsArr(Card *_card, int _size);

void PrintCard(Card _card);

void PrintPlayerDetails(size_t _id, char *_name, size_t _points);

void PlayAnotherHand(int *_anotherHand);

void GetReallPlayerName(char *_name);

void GetRealPlayerCard(int *_index);

void NotValidCard();

#endif
