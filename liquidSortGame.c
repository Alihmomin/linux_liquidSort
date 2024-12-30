#include <stdio.h>
#include <memory.h>
#include <stdlib.h>
#include <stdbool.h>

#define VIAL_SIZE 4

struct vial_struct
{
	int content[VIAL_SIZE];
	bool done;
	int top;
};

typedef struct vial_struct vial_t;

typedef struct
{
	vial_t* state;
	int num_vials;
} gameState_t;



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

 int level[] = {4, yellow,yellow,red,red, yellow,yellow,red,red, empty,empty,empty,empty, empty,empty,empty,empty};

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
	for(int i = 0; i < num_vials; i++)
	{
		printf("vial: %d\n", i);
		printf("Done: %c\n", gs->state[i].done ? 'Y' : 'N');
		printf("Top: %i\n", gs->state[i].top);
		printf("\n");
	}

}

int vailOpenSpaces(int vial, gameState_t* gs)
{
	int openSpaces = 0;
	int i = 0;
	while((i < VIAL_SIZE))
	{
		if(gs->state[vial].content[i] != empty)
		{
			break;
		}
		i++;
		openSpaces++;	
	}
	

	return openSpaces;
}

int pour(int from, int to, gameState_t* gs)
{
	//TODO: add input validity check

	vial_t* from_v = &gs->state[from];
	vial_t* to_v = &gs->state[to];

	//Check to see if to vial is full
	if(to_v->top == -1)
	{
		return -1;
	}




}

int main(void)
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