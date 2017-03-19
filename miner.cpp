// thanks to: http://hughm.cs.ukzn.ac.za/~murrellh/os/notes/ncurses.html

#include <iostream>		//for cout
#include <cstdlib>		//for rand()
#include <ncurses.h>	//for all graphics
#include <chrono>		//for time
//#include <signal.h> for window resizes

using namespace std;	//for cout

int main()
{
	//------variables------------
	const unsigned int mapDim[2]={256,256};	//map dimensions (h,w)
	char map[mapDim[0]][mapDim[1]];	//map of characters
	unsigned int pos[2]={64,0};		//character position
	unsigned int cam[2]={0,0};	//camera position
	unsigned int dim[2]={0,0};		//window dimensions (h,w)
	char key;	//user input
	bool run=1;	//run loop
	//-------make map-----------
	for(int a=0; a<mapDim[0]; ++a)
		for(int b=0; b<mapDim[1]; ++b)
		{
			if(a>64)	map[a][b]='O';
			else		map[a][b]=' ';
		}
	//---------init---------
	initscr();				//ncurses init
	cbreak();				//nobuffer
	noecho();				//do not write keys to sdout
	keypad(stdscr, TRUE);	//all keys
	//------get screen size------------
	getmaxyx(stdscr, dim[0],dim[1]);			//get h,w
	if( (dim[0]>mapDim[0]) || (dim[1]>mapDim[1]) )	//if window is larger than map
	{	
		endwin();
		cout << "The window is too big for the map!\n";
		cout << "Window:\t" << dim[0] << ", " << dim[1] << '\n';
		cout << "Map:\t" << mapDim[0] << ", " << mapDim[1] << endl;
		return 1;
	}
	//---------draw map---------
	while(run)
	{
		//----set camera position----------
		for(int a=0; a<2; ++a)
		{
			if(pos[a]+dim[a]/2 > mapDim[a])
				cam[a] = mapDim[a]-dim[a];
			else if(pos[a] < dim[a]/2)
				cam[a] = 0;
			else
				cam[a]=pos[a]-dim[a]/2;
		}
		//draw map
		for(int a=0; a<dim[0]; ++a)
			for(int b=0; b<dim[1]; ++b)
				mvaddch(a, b, map[a+cam[0]][b+cam[1]] | A_BLINK);
		//draw charcter
		mvaddch(pos[0]-cam[0],pos[1]-cam[1],'@');
		move(0,0);	//move cursor to top left
		refresh();	//draw screen
		//get input
		key=getch();	//blocking input for now
		//move based on input
		switch(key)
		{
			case 'w':	//move up
				if(map[pos[0]][pos[1]]=='#')
					pos[0] -= (pos[0]>0);
				break;
			case 'a':	//move left
				pos[1] -= (pos[1]>0);
				break;
			case 's':	//move down
				pos[0] += (pos[0]<mapDim[0]-1);
				break;
			case 'd':	//move right
				pos[1] += (pos[1]<mapDim[0]-1);
				break;
			case 'l':	//place ladder
				map[pos[0]][pos[1]] = '#';
				break;
			case 'j':	//use left
				break;
			case 'k':	//use down
				break;
			case 'i':	//use up
				break;
			case 27:	//[ESCAPE] exit (strange, it takes longer than if it were a standard key)
				run=0;
				break;
			default:	//else
				break;
		}
	}
	//getch();	//block for user input
	endwin();	//close window
	return 0;	//exit
}
