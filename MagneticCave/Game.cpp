#include "Game.h"
#include "AIPlayer.h"

using namespace std;

Game::~Game(void)
{
	for (unsigned int i = 0 ; i < p.size(); ++i)
	{
		delete p[i];
	}
	p.clear();
}

void Game::newGame()
{

	cout<< "Player 1, please choose your type,  AI = AIPlayer, MP = Manual Player " << endl;
	string choice;
	cin >> choice;

	if(choice == "AI" || choice == "ai" || choice == "aI" || choice == "Ai")
	{
		p.push_back(new AIPlayer());
		p.push_back(new Player());
	}
	else
	{
		p.push_back(new Player());
		p.push_back(new AIPlayer());
	}

	p[0]->setColor(Brick_Black);
	p[1]->setColor(Brick_White);


	//Test.
	//p.push_back(new AIPlayer());
	//p[0]->setColor(Brick_Black);
	//p.push_back(new Player());
	//p[1]->setColor(Brick_White);

	grid.reset();
}

void Game::play()
{
	bool gameOn = true;
	while (gameOn)
	{
		Winner winner = Winner_None;

		do
		{

			GridError res = GridError_Unknown;

			do
			{
				grid.printBoard();
				std::string color = p[playerTurn]->getColor() == Brick_Black ? "Black" : "White";
				cout << "Player"<< (playerTurn+1) << " turn (Player color is " <<  color << ")" << endl;

				p[playerTurn]->getMove(grid);

				Point position = p[playerTurn]->getPlayPosition();

				res = grid.move(position.x, position.y, p[playerTurn]->getColor());
				if (res == GridError_InvalidPos)
				{
					cout << "**** Invalid Play:\ninvalid position(" << position.x << "," << position.y  << "), try again! ***\n " << endl;
				}
				else if (res == GridError_Occupied)
				{
					cout << "**** Invalid Play:\nposition already occupied! (" << position.x << "," << position.y  << "), try again! ***\n" << endl;
				}
			}
			while (res != GridError_Success);

			if (playerTurn == 1)
			{
				playerTurn = 0;
			}	
			else if (playerTurn == 0)
			{
				playerTurn = 1;
			}

			winner = grid.getWinner();

		}
		while(winner == Winner_None);

		cout << "\n\n################# Congratulations !!! ################\n" ;
		if (winner == Winner_Black)
		{
			cout<< "\nBlack is the winner!!!!\n";
		}
		else if (winner == Winner_White)
		{
			cout << "\nWhite is the winner!!!\n";
		}	
		grid.printBoard();
		grid.reset();

		cout <<"\n\nDo you want to play again? Y/N \n";
		std::string str;
		cin >> str;
		gameOn = (str == "Y") || (str == "y"); 
	}
	cout << "\n--------------------------------------\n" ;
	cout << "Press any key to quit the game " << endl;
}
