
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define randomize() srand(time(NULL))

#define BALL_RED 33
#define BALL_BLUE 16
#define TIC_TOTAL 90

typedef struct
{
	int tic_red[6];
	int tic_blue;
}Ticket;

Ticket Ticket_Matrix[TIC_TOTAL];
Ticket Lottery_Prize;

int B_61;
int B_60;
int B_51;
int B_50;
int B_41;
int B_40;
int B_31;
int B_x1;

int tot_money;

void init_sim()
{
	Lottery_Prize.tic_red[0] = 5;
	Lottery_Prize.tic_red[1] = 17;
	Lottery_Prize.tic_red[2] = 21;
	Lottery_Prize.tic_red[3] = 25;
	Lottery_Prize.tic_red[4] = 27;
	Lottery_Prize.tic_red[5] = 32;
	//Lottery_Prize.tic_red = {5, 17, 21, 25, 27, 32};
	Lottery_Prize.tic_blue = 14;
}

void tic_gen()
{
	int i;
	//int j;
	int k;
	int t = 0;
	int flag = 0;
	int ball = 0;
	int blue;
	int red[6] = {0};

	Ticket* ptr_tic = Ticket_Matrix;

	randomize();

	for(i=0; i<6; i++)
	{
		red[0] = Lottery_Prize.tic_red[i];

		while(1)
		{
			flag = 0;
			ball = (rand()%BALL_RED)+1;

			for(k=0; k<=t; k++)
			{
				if(red[k] == ball)
				{
					flag = 1;
					break;
				}
			}

			if(!flag)
			{
				t++;
				red[t] = ball;

				if(t==5)
				{
					t = 0;
					break;
				}
			}
		}

		for(blue=1; blue<=BALL_BLUE; blue++)
		{
			if(blue != Lottery_Prize.tic_blue)
			{
				memcpy(ptr_tic->tic_red, red, sizeof(red));
				ptr_tic->tic_blue = blue;
				ptr_tic++;
			}
		}
	}
}

void prize_gen()
{
	int k;
	int t = 0;
	int flag = 0;
	int ball = 0;
	int blue;
	int red[6] = {0};

	randomize();

	while(1)
		{
			flag = 0;
			ball = (rand()%BALL_RED)+1;

			for(k=0; k<=t; k++)
			{
				if(red[k] == ball)
				{
					flag = 1;
					break;
				}
			}

			if(!flag)
			{
				red[t] = ball;
				t++;

				if(t==6)
				{
					break;
				}
			}
		}

	blue = (rand()%BALL_BLUE)+1;

	memcpy(Lottery_Prize.tic_red, red, sizeof(red));
	Lottery_Prize.tic_blue = blue;
}

void tic_ana()
{
	int i;
	int j;
	int k;
	int r = 0;
	int b = 0;
	int result = 0;

	for(i=0; i<TIC_TOTAL; i++)
	{
		r = 0;
		b = 0;
		for(j=0; j<6; j++)
		{
			for(k=0; k<6; k++)
			{
				if(Ticket_Matrix[i].tic_red[j] == Lottery_Prize.tic_red[k])
					r++;
			}
		}
		if(Ticket_Matrix[i].tic_blue == Lottery_Prize.tic_blue)
			b++;

		result = r*10 + b;
		printf("%d-%d\n", r,b);

		switch(result)
		{
		case 61:
			B_61++;
			tot_money += 5000000;
			break;
		case 60:
			B_60++;
			tot_money += 300000;
			break;
		case 51:
			B_51++;
			tot_money += 3000;
			break;
		case 50:
			B_50++;
			tot_money += 198;
			break;
		case 41:
			B_41++;
			tot_money += 198;
			break;
		case 40:
			B_40++;
			tot_money += 8;
			break;
		case 31:
			B_31++;
			tot_money += 8;
			break;
		case 21:
		case 11:
		case 1:
			B_x1++;
			tot_money += 3;
			break;
		default:
			tot_money -= 2;
			break;
		}
	}
}

void main()
{
	int i;
	int j;

	init_sim();

	tic_gen();

	prize_gen();

	tic_ana();

	for(i=0; i<TIC_TOTAL; i++)
	{
		printf("R: ");
		for(j=0; j<6; j++)
		{
			printf("%d ", Ticket_Matrix[i].tic_red[j]);
		}

		printf("B: ");
		printf("%d \n", Ticket_Matrix[i].tic_blue);
	}

	printf("\n-PRIZE-------------------\n");
	for(j=0; j<6; j++)
		{
			printf("%d ", Lottery_Prize.tic_red[j]);
		}

		printf("B: ");
		printf("%d \n", Lottery_Prize.tic_blue);

		printf("\n-BONUS-------------------\n");
		printf("B_61: %d \n", B_61);
		printf("B_60: %d \n", B_60);
		printf("B_51: %d \n", B_51);
		printf("B_50: %d \n", B_50);
		printf("B_41: %d \n", B_41);
		printf("B_40: %d \n", B_40);
		printf("B_31: %d \n", B_31);
		printf("B_x1: %d \n", B_x1);
		printf("$: %d \n", tot_money);
}