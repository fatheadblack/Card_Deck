#include<iostream>
#include<vector>
#include<string>
#include<random>
#include<ctime>
#include<algorithm>


class Card
{
	enum suit 
	{
		CLUBS,
		DIAMONDS,
		HEARTS,
		SPADES
	};

	int val;
	suit sut;
	
public:

	Card() = default;

	Card(int v, int s) : val(v), sut(static_cast<suit>(s)) {}

	Card(const Card& c) { val = c.val, sut = c.sut; } //copy constructor

	int getval()
	{
		return val;
	}

	suit getsuit()
	{
		return sut;
	}
};


class Deck
{
public:

	std::vector<Card> theDeck;
	
	std::vector<Card>::iterator it;

	void init()
	{
		for (int j = 0; j <= 3; j++)
			for (int i = 1; i <= 13; i++)
			
			{
				theDeck.push_back(Card(i, j));
			}
	}

	void shuffle()
	{
		//std::vector<Card>::iterator tempit;
		typedef std::mt19937 rng_type;
		std::uniform_int_distribution<rng_type::result_type> udist(0, 10000);

		rng_type rng;

		rng_type::result_type const seedval = time(0); // get this from somewhere
		rng.seed(seedval);

		rng_type::result_type random_number = udist(rng);

		for (int i = 0; i < random_number; i++)						////TODO: Sort this abortion of a random shuffle out!!!!!!!
		{	
			std::random_shuffle(theDeck.begin(), theDeck.end());   
		}


	}

	friend void show(const std::vector<Card>&);
	

	Card get_top_card()
	{
		it = theDeck.end() -1;
		Card temp(it->getval(), it->getsuit());
		theDeck.pop_back();

		return temp;
	}
	

};

class Player

{
public:

	std::vector<Card> hand;

	std::vector<Card>::iterator iter = hand.begin();
	
	void deal( Deck& td)
	{
		hand.clear();
		for (int i = 0; i < 2; i++)
		{
			hand.push_back(td.get_top_card());
		}
	}

	friend void show(const std::vector<Card>&);

	
};


class River
{

public:
	std::vector<Card> rhand;

	std::vector<Card>::iterator iter = rhand.begin();

	void deal(Deck& tr)
	{

		rhand.clear();
		for (int i = 0; i < 5; i++)
		{
			rhand.push_back(tr.get_top_card());

		}


	}

	friend void show(const std::vector<Card>&);

};




void show(std::vector<Card>& i)

	{
	std::vector<Card>::iterator it;
		std::string face;
		char suit;
		for (it = i.begin(); it != i.end(); it++)
		{
			if (it->getval() == 1) face = 'A';
			if (it->getval() == 2) face = '2';
			if (it->getval() == 3) face = '3';
			if (it->getval() == 4) face = '4';
			if (it->getval() == 5) face = '5';
			if (it->getval() == 6) face = '6';
			if (it->getval() == 7) face = '7';
			if (it->getval() == 8) face = '8';
			if (it->getval() == 9) face = '9';
			if (it->getval() == 10) face = "10";
			if (it->getval() == 11) face = 'J';
			if (it->getval() == 12) face = 'Q';
			if (it->getval() == 13) face = 'K';

			if (it->getsuit() == 0) suit = 05;
			if (it->getsuit() == 1)	suit = 04;
			if (it->getsuit() == 2) suit = 03;
			if (it->getsuit() == 3) suit = 06;

			std::cout << face << suit << " ";

		}
		std::cout << std::endl;
		std::cout << std::endl;
	}




int main()
{
	
	Deck d = Deck();
	Player player;
	River river;
	
	d.init();

	std::cout << "The unshuffled Deck : " << std::endl;
	show(d.theDeck);
	
	d.shuffle();
	std::cout << "The Shuffled Deck : " << std::endl;
	show(d.theDeck);
		
	player.deal(d);
	std::cout << "The first dealt two card hand : " << std::endl;
	show(player.hand);

	std::cout << "The remaining cards in the deck minus the dealt hand : " << std::endl;
	show(d.theDeck);

	player.deal(d);
	std::cout << "The second dealt two card hand : " << std::endl;
	show(player.hand);
	std::cout << "The remaining cards in the deck minus the dealt hand : " << std::endl;
	show(d.theDeck);

	river.deal(d);

	std::cout << "The all important river : " << std::endl;
	show(river.rhand);

	std::cout << "The remaining cards in the deck after the river : " << std::endl;
	show(d.theDeck);

	std::cin.get();

	return 0;
}