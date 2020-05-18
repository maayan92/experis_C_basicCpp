
typedef enum
{
	HEART,
	LEAF,
	DIAMOND,
	CLOVER,
	NUM_OF_SUITES
}Suite;

typedef enum
{
	TWO,
	THREE,
	FOUR,
	FIVE,
	SIX,
	SEVEN,
	EIGHT,
	NINE,
	TEN,
	PRINCE,
	QUEEN,
	KING,
	AS,
	NUM_OF_RANKS
}Rank;

typedef struct Card
{
	Suite m_suite;
	Rank m_rank;
}Card;



