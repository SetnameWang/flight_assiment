/*******************************************************************************
 * 48430 Fundamentals of C Programming - Assignment 2
 * Name: Haoyu Wang
 * Student ID:12846756
 * Date of submission:
 * A brief statement on what you could achieve (less than 50 words):
 *
 *
 * A brief statement on what you could NOT achieve (less than 50 words):
 *
 *
 *******************************************************************************/

 /*******************************************************************************
  * List header files - do NOT use any other header files. Note that stdlib.h is
  * included in case you want to use any of the functions in there. However the
  * task can be achieved with stdio.h and string.h only.
  *******************************************************************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

  /*******************************************************************************
   * List preprocessing directives - you may define your own.
   *******************************************************************************/
#define MAX_FLIGHTCODE_LEN 6
#define MAX_CITYCODE_LEN 3
#define MAX_NUM_FLIGHTS 5
#define DB_NAME "database"

   /*******************************************************************************
	* List structs - you may define struct date_time and struct flight only. Each
	* struct definition should have only the fields mentioned in the assignment
	* description.
	*******************************************************************************/
typedef struct date_time
{
	int month;
	int day;
	int hour;
	int mintue;
}date_time_t;

typedef struct flight
{
	char flightcode[MAX_FLIGHTCODE_LEN + 1];
	date_time_t departure_dt;
	char arrival_city[MAX_CITYCODE_LEN + 1];
	date_time_t arrival_dt;
}flight_t;


/*******************************************************************************
 * Function prototypes - do NOT change the given prototypes. However you may
 * define your own functions if required.
 *******************************************************************************/
void print_menu(void);
/* func used to add flight info into memory */
void add_flight(flight_t* flights, int* counter);
/* func used to display data with keyword city_code */
void display_data(flight_t* flights, int* counter, char city_code[MAX_CITYCODE_LEN]);
/* func used to display all data */
void display_all_data(flight_t* flights, int* counter);
/* func used to save data into database file */
void save_data(flight_t* flights, int* counter);
/* func used to load data from database file */
void load_db(flight_t* flights, int* counter);
/* get flight code*/
int get_flight_code(char flightcode[MAX_FLIGHTCODE_LEN + 1]);

/*******************************************************************************
 * Main
 *******************************************************************************/
int main(void)
{
	/* TODO */

    /* choice is used to save what the user select which should be 0 < choice < 5. */

	int choice = 0;
    /* chounter is used to count the number of data in memory. */

	int counter = 0;
    /* array used to save the flight data. */

	flight_t flights[MAX_NUM_FLIGHTS];

    /* infinite loop to keep tracking what the user need. */

	while (1)
    {

		print_menu();
        /* get the num of user */

		scanf("%d", &choice);
		if (choice < 1 || choice >5)
        {
            /* print error info. */

			printf("Invalid choice\n");
		}
		else if (choice == 1) {
			add_flight(flights, &counter);
		}
		else if (choice == 2) {
            /* city_code is used to save user input of city code */

			char city_code[MAX_CITYCODE_LEN + 1];
            /* print head */

			printf("Enter arrival city code or enter * to show all destinations>\n");
            /* collect city_code */

			scanf("%s", city_code);
            /* if * use display_all_data function */

			if (city_code[0] == '*')
            {
				display_all_data(flights, &counter);
			}
			else
            {
				display_data(flights, &counter, city_code);
			}
		}
		else if (choice == 3)
        {
			save_data(flights, &counter);
		}
		else if (choice == 4) {
			counter = 0;
			load_db(flights, &counter);
		}
		else if (choice == 5)
        {
			break;
		}
	}

return 0;

}

/*******************************************************************************
 * This function prints the initial menu with all instructions on how to use
 * this program.
 * inputs:
 * - none
 * outputs:
 * - none
 *******************************************************************************/
void print_menu(void)
{
	printf("\n"
		"1. add a flight\n"
		"2. display all flights to a destination\n"
		"3. save the flights to the database file\n"
		"4. load the flights from the database file\n"
		"5. exit the program\n"
		"Enter choice (number between 1-5)>\n");
}
void add_flight(flight_t* flights, int* counter)
{
	/* return if number of flights is arrival to max. */

	if (*counter >= MAX_NUM_FLIGHTS) {
		printf("Invalid input\n");
		return;
	}
	/* tempory save the data */

	flight_t tempory;
	/* get flight code */

	printf("Enter flight code>\n");
	while (get_flight_code(tempory.flightcode) == 0) {
		printf("Invalid input\n");
	}

	printf("Enter departure info for the flight leaving SYD.\n");
	printf("Enter month, date, hour and minute separated by spaces>\n");
	scanf("%d %d %d %d", &tempory.departure_dt.month, &tempory.departure_dt.day, &tempory.departure_dt.hour, &tempory.departure_dt.mintue);
	/* when month is incorrect, loop to get correct infomation */

	while (tempory.departure_dt.month < 0 || tempory.departure_dt.month > 12
		|| tempory.departure_dt.day < 0 || tempory.departure_dt.day > 31
		|| tempory.departure_dt.hour < 0 || tempory.departure_dt.hour > 24
		|| tempory.departure_dt.mintue < 0 || tempory.departure_dt.mintue > 59
		)
	{
		printf("Invalid input\n");
		printf("Enter month, date, hour and minute separated by spaces>\n");
		scanf("%d %d %d %d", &tempory.departure_dt.month, &tempory.departure_dt.day, &tempory.departure_dt.hour, &tempory.departure_dt.mintue);
	}
	/* when data is incorrect, loop to get correct infomation */

	printf("Enter arrival city code>\n");
	scanf("%s", tempory.arrival_city);

	tempory.arrival_city[3] = '\0';
	/* get arrival info */

	printf("Enter arrival info.\n");
	printf("Enter month, date, hour and minute separated by spaces>\n");
	scanf("%d %d %d %d", &tempory.arrival_dt.month, &tempory.arrival_dt.day, &tempory.arrival_dt.hour, &tempory.arrival_dt.mintue);
	/* when month is incorrect, loop to get correct infomation */

	while (tempory.arrival_dt.month < 0 || tempory.arrival_dt.month > 12
		|| tempory.arrival_dt.day < 0 || tempory.arrival_dt.day > 31
		|| tempory.arrival_dt.hour < 0 || tempory.arrival_dt.hour > 24
		|| tempory.arrival_dt.mintue < 0 || tempory.arrival_dt.mintue > 59
		)
	{
		printf("Invalid input\n");
		printf("Enter month, date, hour and minute separated by spaces>\n");
		scanf("%d %d %d %d", &tempory.arrival_dt.month, &tempory.arrival_dt.day, &tempory.arrival_dt.hour, &tempory.arrival_dt.mintue);
	}
	/* when data is incorrect, loop to get correct infomation */

	/* make counter to the tail of array */

	flights = flights + *counter;
	/* save tempory to flights */

	(*flights) = tempory;
	/* increase counter */

	(*counter)++;
}

int get_flight_code(char flightcode[MAX_FLIGHTCODE_LEN + 1]) {
	char ch;
	int counter;
	counter = 0;
	int switcher;
	switcher = 0;
	/* infinate loop to get chars untial \n */
	while (1) {
		ch = getchar();
		/* if first char is \n skip */
		if (counter == 0 && ch == '\n') {
			continue;
		}
		/* if meet \n and have more than 3 chars(2 A-Z + 1 0-9), return true */
		if (counter > 2 && counter <= MAX_FLIGHTCODE_LEN && ch == '\n') {
			flightcode[counter] = '\0';
			if (switcher == 0) {
				return 1;
			}
		}
		/* if first char is not A-Z, switch switcher to 1 */
		if (counter < 2) {
			if (ch >= 'A' && ch <= 'Z'){
				flightcode[counter] = ch;
			}
			else {
				switcher = 1;
			}
		}
		/* if first char is not 0-9, switch switcher to 1 */
		if (counter > 1 && counter < MAX_FLIGHTCODE_LEN) {
			if (ch >= '0' && ch <= '9') {
				flightcode[counter] = ch;
			}
			else {
				switcher = 1;
			}
		}
		/* if number of chars out of range, switch switcher to 1 */
		if (counter > MAX_FLIGHTCODE_LEN) {
			switcher = 1;
		}
		/* read all chars inside the cache */
		if (counter > 0 && ch == '\n' && switcher == 1) {
			return 0;
		}
		counter++;
		/* add a end for next char */
		if (counter <= MAX_FLIGHTCODE_LEN) {
			flightcode[counter] = '\0';
		}
	}
}

void display_data(flight_t* flights, int* counter, char city_code[MAX_CITYCODE_LEN])
{
	int match[MAX_NUM_FLIGHTS + 1] = {0};
	int num_flight = 0;

    /* print head */
	/*
	printf("%-6s %-15s %-15s\n", "Flight", "Origin", "Destination");
	printf("------ --------------- ---------------\n");
	*/
    /* counter used to compare charaters between city_code and flights->arriva_city */

	int char_counter;
    int i;
	for (i = 0; i < *counter; i++) {
        /* initial counter each loop */

		char_counter = 0;
        int j;
        
		for (j = 0; j < MAX_CITYCODE_LEN; j++)
        {
            /* if reach end of string, break */

			if (city_code[j] == flights->arrival_city[j] && city_code[j] == '\0')
            {
				break;
			}
            /* compare each charaters between city_code and flights->arriva_city, if one charater doesn't same, change counter to 1 */

			if (city_code[j] != flights->arrival_city[j])
            {
				char_counter = 1;
			}
		}
        /* if counter is 0(each charater of two variable is same, print this line) */

		if (char_counter == 0) {
			num_flight++;
			match[i] = 1;
			/*
			printf("%-6s SYD %02d-%02d %02d:%02d ", flights->flightcode, flights->departure_dt.month, flights->departure_dt.day, flights->departure_dt.hour, flights->departure_dt.mintue);
			printf("%-3s %02d-%02d %02d:%02d\n", flights->arrival_city, flights->arrival_dt.month, flights->arrival_dt.day, flights->arrival_dt.hour, flights->arrival_dt.mintue);
			*/
		}
        /* next line */

		flights++;
	}
	if (num_flight == 0){
		printf("No flights\n");
		return;
	} else {
		/* print head */
		printf("%-6s %-15s %-15s\n", "Flight", "Origin", "Destination");
		printf("------ --------------- ---------------\n");
		for(i = 0; i < MAX_NUM_FLIGHTS; i++){
			if (match[i] == 1){
			printf("%-6s SYD %02d-%02d %02d:%02d ", flights->flightcode, flights->departure_dt.month, flights->departure_dt.day, flights->departure_dt.hour, flights->departure_dt.mintue);
			printf("%-3s %02d-%02d %02d:%02d\n", flights->arrival_city, flights->arrival_dt.month, flights->arrival_dt.day, flights->arrival_dt.hour, flights->arrival_dt.mintue);
			}
		}
	}
}
void display_all_data(flight_t* flights, int* counter)
{
	if(*counter == 0){
		printf("No flights\n");
		return;
	}

    /* print head */
	printf("%-6s %-15s %s\n", "Flight", "Origin", "Destination");
	printf("------ --------------- ---------------\n");
    
    int i;
	for (i = 0; i < *counter; i++)
    {
		/* print each line of data */
		printf("%-6s SYD %02d-%02d %02d:%02d ", flights->flightcode, flights->departure_dt.month, flights->departure_dt.day, flights->departure_dt.hour, flights->departure_dt.mintue);
		printf("%-3s %02d-%02d %02d:%02d\n", flights->arrival_city, flights->arrival_dt.month, flights->arrival_dt.day, flights->arrival_dt.hour, flights->arrival_dt.mintue);
		flights++;
	}
}

void save_data(flight_t* flights, int* counter)
{
    /* create file pointer */

	FILE* file_pointer;
	file_pointer = fopen(DB_NAME, "w");
    
    int i;
	for (i = 0; i < *counter; i++)
    {
        /* save data from array. */

		fprintf(file_pointer, "%s SYD ", flights->flightcode);
		fprintf(file_pointer, "%d %d %d %d ", flights->departure_dt.month, flights->departure_dt.day, flights->departure_dt.hour, flights->departure_dt.mintue);
		fprintf(file_pointer, "%s ", flights->arrival_city);
		fprintf(file_pointer, "%d %d %d %d\n", flights->arrival_dt.month, flights->arrival_dt.day, flights->arrival_dt.hour, flights->arrival_dt.mintue);
        /* next element in array */

		flights++;
	}
    /* close file */

	fclose(file_pointer);
}

void load_db(flight_t* flights, int* counter)
{
    /* create file pointer */

	FILE* file_pointer;
    /* read-only */

	file_pointer = fopen(DB_NAME, "r");
    /* structers used to save data tempory */

	if (file_pointer == NULL) {
		printf("null files on read file\n");
		return;
	}
	flight_t single_data;
	date_time_t date;
    /* loop untial MAX_NUM_FLIGHTS */
    int i;
	for (i = 0; i < MAX_NUM_FLIGHTS; i++)
    {
		/* veriable used to skip SYT */
		char SYT[MAX_CITYCODE_LEN + 1];
		/*
		data structure:
			flightcode SYD month day hour mintue arrival_city month day hour mintue\n
			...
		*/
        /* stop if fscanf return EOF(file pointer reach to the botton of file.*/

		if (fscanf(file_pointer, "%s %s", single_data.flightcode, SYT) == EOF)
        {
			break;
		}
        /* scan data */

		fscanf(file_pointer, "%d %d %d %d", &date.month, &date.day, &date.hour, &date.mintue);
        /* save date for next use. */

		single_data.departure_dt = date;
		fscanf(file_pointer, "%s", single_data.arrival_city);
		fscanf(file_pointer, "%d %d %d %d", &date.month, &date.day, &date.hour, &date.mintue);
		single_data.arrival_dt = date;
        /* save infomations into flight pointer */

		(*flights) = single_data;
        /* shift pointer to next element */

		flights++;
        /* update the counter */

		(*counter)++;
	}
	fclose(file_pointer);
	return;
}
