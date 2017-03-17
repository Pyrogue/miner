#include <iostream>
#include <cstdlib>
#include <ncurses.h>

using namespace std;

int main()
{
	//ncurses init
	initscr();
	//nobuffer
	cbreak();
	//do not write keys to sdout
	noecho();
	//all keys
	keypad(stdscr, TRUE);

	printw("Hello World !!!");	/* Print Hello World		  */
	refresh();			/* Print it on to the real screen */
	getch();			/* Wait for user input */
	endwin();			/* End curses mode		  */


	const int H=1;
	const int W=64;
	char map[H][W];

	for(int n=0; n<10; ++n)
	{
		//seed array;
		for(int a=0; a<H; ++a)
			for(int b=0; b<W; ++b)
				map[a][b]=(rand()%('Z'-'A'))+'A';
		//write array
		for(int a=0; a<H; ++a)
		{
			for(int b=0; b<W; ++b)
			{
				cout << map[a][b];
			}
			cout << '\n';
		}
		//erase?
		for(int a=0; a<H; ++a)
			for(int b=0; b<W; ++b)
				cout << '\b';
		cout << flush;
	}
	return 0;
}
