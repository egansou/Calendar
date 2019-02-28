/*
  Enock Gansou                   
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "event.h"
#include "calendar.h"
#include "my_memory_checker_216.h"

/*****************************************************/
/* In this file you will provide tests for your      */
/* calendar application.  Each test should be named  */
/* test1(), test2(), etc. Each test must have a      */
/* brief description of what it is testing (this     */
/* description is important).                        */
/*                                                   */
/* You can tell whether any test failed if after     */
/* executing the students tests, you executed        */
/* "echo $?" on the command line and you get a value */
/* other than 0.  "echo $?" prints the status of     */
/* the last command executed by the shell.           */ 
/*                                                   */
/* Notice that main just calls test1(), test2(), etc.*/
/* and once one fails, the program eventually        */
/* return EXIT_FAILURE; otherwise EXIT_SUCCESS will  */
/* be returned.                                      */
/*****************************************************/

static int comp_minutes(const void *ptr1, const void *ptr2) {
  return ((Event *)ptr1)->duration_minutes - ((Event *)ptr2)->duration_minutes;
}

static int comp_time(const void *ptr1, const void *ptr2) {
  return ((Event *)ptr1)->start_time - ((Event *)ptr2)->start_time;
}

static void free_info(void *ptr) {
  char *info = (char *)ptr;
  free(info);
}
/* 
   This test checks whether the calendar is initialized and destroyed correctly  
*/
static int test1() {
  int days = 7;
  Calendar *calendar;

  printf("*****Test 1*****\n");
  if (init_calendar("Spr", days, comp_minutes, NULL, &calendar) == SUCCESS) {
    if (print_calendar(calendar, stdout, 1) == SUCCESS) {
      return destroy_calendar(calendar);
    }
  }
    
  return FAILURE;
}

/* test2 tests whether event(s) are added and removed properly */
static int test2() {
  int days = 7, start_time_mil = 900, duration_minutes = 120;
  int activity_day = 6;
  Calendar *calendar;
  void *info = NULL;

  printf("\n*****Test 2*****\n"); 
  if(init_calendar("Week Calendar", days, comp_time, NULL, &calendar) == SUCCESS){
    /* Adding events */
    add_event(calendar, "study", start_time_mil, duration_minutes, 
	      info, activity_day);
    add_event(calendar, "beach", 1200, 80, NULL, 7);
    add_event(calendar, "group study", 1700, 900, NULL, 5); 
    add_event(calendar, "Math exam", 1000, 50, NULL, 1);
    add_event(calendar, "Project due", 1200, 45, NULL, 3);
    print_calendar(calendar, stdout, 1);

    /* Removing beach on sunday and everything on friday */
    if(remove_event(calendar, "beach") == SUCCESS){
      if(clear_day(calendar, 5) == SUCCESS){
	/* Notice no header will be printed */
	print_calendar(calendar, stdout, 0);

	/* Clearing the whole calendar */
	if(clear_calendar(calendar) == SUCCESS){
	  /* Notice no header will be printed */
	  print_calendar(calendar, stdout, 0);
	  return destroy_calendar(calendar);
	}
      }
    }
  }

  return FAILURE;
}

/* 
   test 3 verify whether an information about an event is
   well defined and if an event can be found in the calendar
*/
static int test3() {
  int days = 2, start_time_mil = 800, duration_minutes = 300;
  int activity_day = 1;
  Calendar *calendar;
  Event* event;

  /*Creating my information*/
  char *info = malloc(100);
  if (info== NULL) {
    return FAILURE;
  }
  strcpy(info,"Learning Python for the job interview");
   
  printf("\n*****Test 3*****\n");

  if(init_calendar("Internship", days, comp_time, free_info, &calendar)
     == SUCCESS){

    /* Adding events */
    add_event(calendar, "python", start_time_mil, duration_minutes, 
	      info, activity_day);
   
    add_event(calendar, "java", 900, 200, NULL, 2);

    print_calendar(calendar, stdout, 1);

    /* Notice adding C will fail the num of days is only 2 */
    if(add_event(calendar, "C", start_time_mil, duration_minutes, 
		 info, 3)== FAILURE){
      printf("C cannot be added (day 3)\n");
    }

    /* Notice adding Java  will fail since it already exists */
    if(add_event(calendar, "java", 800, 200, NULL, 2)== FAILURE){
      printf("Java cannot be added again\n");
    }
   

    if (find_event(calendar, "C++", &event) == SUCCESS) {
      printf("Event found: %s, %d, %d\n", event->name, event->start_time,
	     event->duration_minutes);
    } else {
      printf("Event \"C++\" not found\n");
    }

    if (find_event_in_day(calendar, "java", 2, &event) == SUCCESS) {
      printf("Event found: %s, %d, %d\n", event->name, event->start_time,
	     event->duration_minutes);
    } else {
      printf("event \"java\" not found\n");
    }

    info = get_event_info(calendar, "python"); 
    printf("Python info\n");
    printf("%s\n", info);

    return destroy_calendar(calendar);
  }
  return FAILURE;
}

int main() {
  int result = SUCCESS;

  /***** Starting memory checking *****/
  start_memory_check();
  /***** Starting memory checking *****/

  if (test1() == FAILURE) result = FAILURE;
  if (test2() == FAILURE) result = FAILURE;
  if (test3() == FAILURE) result = FAILURE;

  /****** Gathering memory checking info *****/
  stop_memory_check();
  /****** Gathering memory checking info *****/
   
  if (result == FAILURE) {
    exit(EXIT_FAILURE);
  }

  return EXIT_SUCCESS;
}
