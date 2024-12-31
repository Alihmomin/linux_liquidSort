#include <stdio.h>
#include <memory.h>
#include <stdlib.h>
#include <stdbool.h>

#define VIAL_SIZE 4

enum color
 {
 	empty = (int)' ',
 	red = (int)'r',
 	blue = (int)'b',
 	yellow = (int)'y',
 	white = (int)'w',
 	gray = (int)'g',
 	brown = (int)'n',
 	black = (int)'l',
 	orange = (int)'o',
 	green = (int)'e',
 	purple = (int)'p'
 };


struct vial_struct
{
	int content[VIAL_SIZE];
	bool done;
	int top;
};

typedef struct vial_struct vial_t;

int getTopColorIndex(vial_t* v)
{

	return (v->top+1 >= 4) ? 3 : (v->top+1);
}

void incrementTop(vial_t* v)
{
	v->top = (v->top+1 >= 4) ? 3 : (v->top+1);
}

void decrementTop(vial_t* v)
{
	v->top = ((v->top-1) < -1) ? -1 : (v->top-1);
}

int getVialEmptyLen(vial_t* v)
{
	int emptySpace = 0;
	for(int i = 0; i < VIAL_SIZE; i++)
	{
		if((v->content[i]) == empty)
		{
			emptySpace++;
		}
	}

	return emptySpace;
}

enum color getTopColor(vial_t* v)
{  
	int index = getTopColorIndex(v);
	return v->content[index];
}

int removeTopColor(vial_t* v)
{
	if(getTopColor(v) == empty)
	{
		return -1;
	}

	v->content[getTopColorIndex(v)] = empty;
	incrementTop(v);

	return 0;
}

int addTopColor(vial_t* v, enum color c)
{
	if(getVialEmptyLen(v) <= 0)
	{
		return -1;
	}

	v->content[v->top] = c;
	decrementTop(v);

	return 0;
}

bool checkAndSetDone(vial_t* v)
{
	bool done = true;
	enum color toTopColor = getTopColor(v);
	for(int i = 0; i < VIAL_SIZE; i++)
	{
		done = done && (toTopColor == v->content[i]);
		if(!done)
		{
			break;
		}
	}

	v->done = done;

	return done;
}

typedef struct
{
	vial_t* state;
	int num_vials;
} gameState_t;



 

 int level[] = {4, yellow,yellow,red,red, yellow,yellow,red,red, empty,empty,empty,empty, empty,empty,empty,empty};
 //int level[] = {4, empty,empty,red,red, yellow,yellow,red,red, empty,empty,yellow,yellow, empty,empty,empty,empty};

int load_level(gameState_t* gs, int* level, int level_len)
{
	printf("loading level\n");

	if(!gs){return -3;}
	
	//TODO: check if level is valid
	
	int num_vials = level[0];
	gs->num_vials = num_vials;
	
	printf("num_vials: %d\n", num_vials);

	vial_t* state = calloc(num_vials, sizeof(vial_t));
	int level_index = 1;
	for(int i = 0; i < num_vials; i++)
	{
		printf("filling vial %d\n", i);
		state[i].done = true;
		state[i].top = -1;
		int vial_color = level[level_index];
		for(int j = 0; j<VIAL_SIZE; j++)
		{
			state[i].content[j] = level[level_index++];
			if(state[i].content[j] == empty)
			{
				state[i].top +=1;
			}
			if(state[i].content[j] != vial_color)
			{
				state[i].done = false;
			}
		}
		

	}
	gs->state = state;
	return 0;

}

int init_game(gameState_t* gs)
{
	printf("init game\n");
	if(!gs){return -1;}
	return load_level(gs, level, 17);
}


void print_game_state(gameState_t* gs)
{
	if(!gs)
	{
		printf("ERROR: game_state is null");
		return;
	}
	printf("Game State\n");
	for(int i = 0; i < VIAL_SIZE; i++)
	{
		for(int j = 0; j < gs->num_vials; j++)
		{
			char c = (char)gs->state[j].content[i];
			if(c == 0)
			{
				c = '0';
			}
			printf("|%c| ", c);
		}
		printf("\n");
	}
	for(int i = 0; i < gs->num_vials; i++)
	{
		printf("--- ");
	}
	printf("\n");

	for(int i = 0; i < gs->num_vials; i++)
	{
		printf(" %d  ", i);
	}
	
	printf("\n");
}

void print_game_state_metadata(gameState_t* gs)
{
	int num_vials = gs->num_vials;

	printf("Vial: ");
	for(int i = 0; i < num_vials; i++)
	{
		printf("%d ", i);
	}
	printf("\n");

	printf("Done: ");
	for(int i = 0; i < num_vials; i++)
	{
		printf("%c ", gs->state[i].done ? 'Y' : 'N');
	}
	printf("\n");

	printf("Top: ");
	for(int i = 0; i < num_vials; i++)
	{
		printf("%i ", gs->state[i].top);
	}
	printf("\n");

}


int pour(int from, int to, gameState_t* gs)
{

	//TODO: add input validity check

	vial_t* from_v = &gs->state[from];
	vial_t* to_v = &gs->state[to];

	//Check to see if to vial is full
	if(getVialEmptyLen(to_v) == 0)
	{
		return -1;
	}


	enum color toTopColor = getTopColor(to_v); //to_v->content[to_v->top+1];
	enum color fromTopColor = getTopColor(from_v); //from_v->content[from_v->top+1];

	if((toTopColor != fromTopColor) && (getVialEmptyLen(to_v) != 0))
	{
		return -2;
	}

	
	while(to_v->top != -1)
	{
		addTopColor(to_v, getTopColor(from_v));
		removeTopColor(from_v);
		if(getTopColor(from_v) != fromTopColor)
		{
			break;
		}
	}


	//update done status
	checkAndSetDone(from_v);
	checkAndSetDone(to_v);

	return 0;

}

bool isGameWon(gameState_t* gs)
{
	bool result = true;

	for(int i = 0; i < gs->num_vials; i++)
	{
		result = result && (gs->state[i].done);
		if(!result)
		{
			return result;
		}
	}

	return result;
}




int debug_main(void)
{
	printf("hello world\n");
	gameState_t gs;
	if(init_game(&gs))
	{
		printf("error init game exiting\n");
		return -100;
	}
	
	print_game_state(&gs);
	print_game_state_metadata(&gs);
	//int result = pour(0, 2, &gs);
	int result = pour(1, 2, &gs);
	if(result != 0)
	{
		printf("Error with pour: %i\n", result);
	}
	print_game_state(&gs);
	print_game_state_metadata(&gs);

	result = pour(0, 1, &gs);
	if(result != 0)
	{
		printf("Error with pour: %i\n", result);
	}
	print_game_state(&gs);
	print_game_state_metadata(&gs);
}


int gameplay_main(void)
{
	printf("welcome to liquid sort\n");
	gameState_t gs;
	if(init_game(&gs))
	{
		printf("error init game exiting\n");
		return -100;
	}

	print_game_state(&gs);
	print_game_state_metadata(&gs);

	//TODO: add user input

	// while(!isGameWon(&gs))
	// {
	// 	print_game_state(&gs);
	// }
	

}


//TODO: need to add destructors and free memory used to prevent memory leaks

int main(void)
{
	//return debug_main();
	return gameplay_main();
}


// gs.num_vials = 2;
// vial_t v[2];
// for(int i = 0; i < VIAL_SIZE; i++)
// {
// 	v[0].content[i] = red;
// }
// for(int i = 0; i < VIAL_SIZE; i++)
// {
// 	v[1].content[i] = blue;
// }
// gs.state = v;