#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//global variables for board, size, counts in for-loops
int i, j, size;
int **scoreboard;
char **board;
char comp, human;

//function to print board
void printBoard () {

for (i = 0; i < size; i ++) {
	for (j = 0; j < size; j ++)
		printf("%c", board[i][j]);
			printf("\n"); }

}

void printScoreboard () {

for (i = 0; i < size; i ++) {
	for (j = 0; j < size; j ++)
		printf("%d", scoreboard[i][j]);
			printf("\n"); }

}

//function to check full board

bool checkBoard () {

for (i = 0; i < size; i ++)
	for (j = 0; j < size; j ++)
		if (board[i][j] == 'U') return true;

return false;

}

//function to check for winner

bool winCheck1 () {

int row3, col3;

for (row3 = 0; row3 < size; row3 ++)
	for (col3 = 0; col3 < size; col3 ++)
		if ((board[row3][col3] == 'W') && (findLongest (row3, col3) == 6)) return true;

return false; }

bool winCheck2 () {

int row3, col3;

for (row3 = 0; row3 < size; row3 ++)
	for (col3 = 0; col3 < size; col3 ++)
		if ((board[row3][col3] == 'B') && (findLongest (row3, col3) == 6)) return true;

return false; }



//contiguous stones - 8 checks in total (2 for vertical, 2 for horizontal, 2 for diagonal 1, 2 for diagonal 2
int findLongest (int row, int col) {

int count[8] = {1,1,1,1,1,1,1,1};
int max = 0;

//North Count
for (i = row, j = col; i - 1 >= 0 && board[i - 1][j] == board[i][j]; i --)
	if (board[i][j] == board[i - 1][j])
		count[0] ++;

//South Count
for (i = row, j  = col; i + 1 < size && board[i + 1][j] == board[i][j]; i ++)
	if (board[i][j] == board[i + 1][j])
		count[1] ++; 

count[0] = count[0] + count[1] - 1;

//West Count
for (i = row, j = col; j - 1 >= 0 && board[i][j - 1] == board[i][j]; j --)
	if (board[i][j] == board[i][j - 1])
		count[2] ++;

//East Count
for (i = row, j = col; j + 1 < size && board[i][j + 1] == board[i][j]; j ++)
	if (board[i][j] == board[i][j + 1])
		count [3] ++;

count[1] = count[2] + count[3] - 1;

//North West Count

for (i = row, j = col; i + 1 < size && j + 1 < size && board[i + 1][j + 1] == board[i][j]; i ++, j ++)
	if (board[i][j] == board [i + 1][j + 1])
		count[4] ++;

for (i = row, j = col; i - 1 >= 0 && j - 1 >= 0 && board[i][j] == board [i - 1][j - 1]; i --, j --)
	if (board[i][j] == board [i - 1][j - 1])
		count[5] ++;

count[2] = count[4] + count[5] - 1;
//two diagnoal 2 counts
for (i = row, j = col; i - 1 >= 0 && j + 1 < size && board[i][j] == board[i - 1][j + 1]; i --, j ++)
	if (board[i][j] == board [i - 1][j + 1])
		count[6] ++;

for (i = row, j = col; i + 1 < size && j - 1 >= 0 && board[i][j] != 'U' && board[i][j] == board[i + 1][j -1]; i ++, j --)
	if (board[i][j] == board [i + 1][j - 1])
		count[7] ++;

count[3] = count[6] + count[7] - 1;
//find longest count

for (i = 0; i < 4; i ++) {

	if (count[i] >= max)
		max = count[i];
	else max = max; }


return max; 

}


int score (char unit) {

int temp, max = -10;
int row1, col1, row2, col2;

//recursive function for computer

if (unit == comp) {


//look for U, change to comp, calculate score, calculate human score, calculate total score

for (row1 = 0; row1 < size; row1 ++)
	for (col1 = 0; col1 < size; col1 ++) 
		if (board[row1][col1] == 'U') {
			board[row1][col1] = comp;
			scoreboard[row1][col1] = findLongest (row1, col1) - score(human);
			board[row1][col1] = 'U'; } 
			
//printScoreboard();

//return largest number in scoreboard

for (i = 0; i < size; i ++)
	for (j = 0; j < size; j ++)
		if (board[i][j] == 'U' && scoreboard[i][j] > max) max = scoreboard[i][j];

return max;


}

//recursive function for human

if (unit == human) { 

//look for U, change to human, calculate maximum score using temp and max variables, return max to function above

for (row2 = 0; row2 < size; row2 ++)
	for (col2 = 0; col2 < size; col2 ++)
		if (board[row2][col2] == 'U') {
			board[row2][col2] = human;
			temp = findLongest (row2, col2);
		if (temp > max) max = temp;
			board[row2][col2] = 'U'; }

return max;  }

}

//main function, start with variable initialization
int main(void) {

int row, col, maximum, wincount = 0;

char unit;

printf("Enter board dimensions (n): ");
scanf("%d", &size);

//dynamically allocate memory
board = (char **)malloc(size* sizeof(char *));

for (i = 0; i < size; i++)
	board[i] = (char *)malloc(size*sizeof(char));

for (i = 0; i < size; i++)
	for (j = 0; j < size; j++)
		board[i][j] = 'U';

scoreboard = (int **)malloc(size * sizeof(int *));

for (i = 0; i < size; i ++)
	scoreboard[i] = (int *)malloc(size*sizeof(int));

for (i = 0; i < size; i ++)
	for (j = 0; j < size; j ++)
		scoreboard[i][j] = 0;

printBoard ();

//determine first player
printf("Computer playing B or W?: ");
scanf(" %c", &comp);

if (comp == 'B') human = 'W';
else human = 'B';

if (comp == 'B') { 
	printf("Computer lays a stone at ROW 0 COL 0.\n");
	board[0][0] = comp; 
	printBoard ();
	printf("Lay down a stone (ROW COL): ");
	scanf("%d %d", &row, &col);
	if (board[row][col] != 'U')
		{printf("That square is occupied.\n");
		 printf("Lay down a stone (ROW COL): ");
		 scanf("%d %d", &row, &col);
		 board[row][col] = human;
		 printBoard ();}		
	
	else {  board[row][col] = human;
			printBoard (); } }

else { printf("Lay down a stone (ROW COL): ");
	 scanf("%d %d", &row, &col);
	 board[row][col] = human;
	 printBoard (); }

while (checkBoard () && wincount == 0) {

//recursive function. 

maximum = score (comp);

for (i = 0; i < size; i ++)
	for (j = 0; j < size; j ++)
		if (scoreboard [i][j] == maximum && board[i][j] == 'U') {
			printf("Computer lays a stone at ROW %d COL %d.\n", i, j);
			board[i][j] = comp;
			printBoard (); }



for (i = 0; i < size; i ++)
	for (j = 0; j < size; j ++)
		scoreboard[i][j] = 0;
	
if(winCheck1()) { printf("White player wins.\n");
				wincount ++; }
if(winCheck2()) { printf("Black player wins.\n");
				wincount ++; }

if (wincount == 0 && checkBoard()) {

printf("Lay down a stone (ROW COL): ");
scanf("%d %d", &row, &col);

if (board[row][col] == 'U') {
board[row][col] = human;
printBoard (); }

else {

printf("That square is occupied.\n");
printf("Lay down a stone (ROW COL): ");
scanf("%d %d", &row, &col);
board[row][col] = human;
printBoard (); }

if(winCheck1()) { printf("White player wins.\n");
					wincount ++; }
if(winCheck2()) { printf("Black player wins.\n");
					wincount ++; }

}

}


if (!checkBoard ())
printf("Draw!\n");

return 0;

}


