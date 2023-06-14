/* CS 232 Project - The Vaccine Clinic
 * 
 * This program uses semaphores to coordinate resources in a simple vaccine clinic.
 * 
 * Student Name: ZeAi Sun
 * Date: Mar 10, 2023
 */

#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#define NUM_VIALS 30
#define SHOTS_PER_VIAL 6
#define NUM_CLIENTS (NUM_VIALS * SHOTS_PER_VIAL)
#define NUM_NURSES 10
#define NUM_STATIONS NUM_NURSES
#define NUM_REGISTRATIONS_SIMULTANEOUSLY 4

/* global variables */
int num_vials_left = NUM_VIALS;

int r_desk[NUM_STATIONS] = {};
int count = 0;
int in = 0;
int out = 0;

/* semaphores */
sem_t nurse_r;      // indicate if a nurse has completed with vaccination or not.
sem_t client_r;     // indicate if a client is ready for vaccination or not.
sem_t regi_desk;    // indicate if the registeration desk has an opening or not.

/* global functions */

int get_rand_in_range(int lower, int upper) {
    return (rand() % (upper - lower + 1)) + lower;
}

char *time_str;
char *curr_time_s() {
    time_t t;
    time(&t);
    time_str = ctime(&t);
    // replace ending newline with end-of-string.
    time_str[strlen(time_str) - 1] = '\0';
    return time_str;
}

// lower and upper are in seconds.
void walk(int lower, int upper) {
    sleep(get_rand_in_range(lower, upper));
}

// arg is the nurses station number.
void *nurse(void *arg) {
    long int id = (long int)arg;

    // the nurse starts her shift.
    fprintf(stderr, "%s: nurse %ld started\n", curr_time_s(), id);

    while (1) {

        fprintf(stderr, "%s: nurse %ld walking to get a vial\n", curr_time_s(), id);
        walk(1, 3);

        // if there is no vials left, the nurse leaves the clinic.
        if (num_vials_left == 0) {
            fprintf(stderr, "%s: nurse %ld found all vials are gone: exiting\n", curr_time_s(), id);
            break;
        } else {
            num_vials_left -= 1;
            fprintf(stderr, "%s: nurse %ld got vial. Num vials left = %d\n", curr_time_s(), id, num_vials_left);
            walk(1, 3);
            fprintf(stderr, "%s: nurse %ld back at station\n", curr_time_s(), id);

            // each vial can serve 6 clients before the nurse needs to get another vial.
            for (int i = 0; i < SHOTS_PER_VIAL; i++) {

                fprintf(stderr, "%s: nurse %ld tells the waiting queue that she/he is avaliable\n", curr_time_s(), id);
                // nurse tells the waiting queue that she/he is aavaliable and waits for a client to come.
                while (count == NUM_STATIONS) { ; }
                r_desk[in] = id;
                in = (in + 1) % NUM_STATIONS;
                count++;

                fprintf(stderr, "%s: nurse %ld waiting for a client to arrive.\n", curr_time_s(), id);
                sem_wait(&client_r);    // waiting for a client to be ready.
                fprintf(stderr, "%s: nurse %ld sees client is ready. Giving shot now.\n", curr_time_s(), id);
                sleep(5);               // the vaccination takes 5 seconds to complete.
                fprintf(stderr, "%s: nurse %ld gave client the shot\n", curr_time_s(), id);
                sem_post(&nurse_r);     // indicating that the vaccination is done.
            }
        }
    }
    
    fprintf(stderr, "%s: nurse %ld is done\n", curr_time_s(), id);

    pthread_exit(NULL);
}

void *client(void *arg) {
    long int id = (long int)arg;

    fprintf(stderr, "%s: client %ld has arrived and is walking to register\n", curr_time_s(), id);
    walk(3, 10);

    fprintf(stderr, "%s: client %ld waiting to register\n", curr_time_s(), id);
    sem_wait(&regi_desk);       // waiting for the registeration desk to have an opening.

    fprintf(stderr, "%s: client %ld is registering\n", curr_time_s(), id);
    walk(3, 10);                // the registeration takes 3-10 seconds.
    sem_post(&regi_desk);       // indicating that the client has left and there is an opening.

    fprintf(stderr, "%s: client %ld done registering. Now walking to the next queue.\n", curr_time_s(), id);
    walk(3, 10);

    // client waiting for station assignment.
    while(count == 0) { ; }
    int n_id = r_desk[out];
    out = (out + 1) % NUM_STATIONS;
    count--;

    fprintf(stderr, "%s: client %ld got assigned to station %d: walking there now\n", curr_time_s(), id, n_id);
    walk(1, 2);
    fprintf(stderr, "%s: client %ld is at station %d\n", curr_time_s(), id, n_id);

    fprintf(stderr, "%s: client %ld is ready for the shot from nurse %d\n", curr_time_s(), id, n_id);
    sem_post(&client_r);        // indicating that the client is ready for vaccination.

    sem_wait(&nurse_r);         // waiting for the nurse to finish vaccination.
    fprintf(stderr, "%s: client %ld got the shot! It hurt, but it is a sacrifice I'm willing to make!\n", curr_time_s(), id);
    fprintf(stderr, "%s: client %ld leaves the clinic!\n", curr_time_s(), id);

    pthread_exit(NULL);
}

int main() {

    // initialize the semaphores.
    sem_init(&nurse_r, 0, 0);
    sem_init(&client_r, 0, 0);
    sem_init(&regi_desk, 0, NUM_REGISTRATIONS_SIMULTANEOUSLY);

    // define two kinds of threads: nurse and client.
    pthread_t tn[NUM_NURSES], tc[NUM_CLIENTS];

    srand(time(0));

    // create the nurse threads.
    for (int i = 0; i < NUM_NURSES; i++) {
        pthread_create(&tn[i], NULL, nurse, i);
    }

    // create the client threads, with a 0-1 second break in between.
    for (int i = 0; i < NUM_CLIENTS; i++) {
        pthread_create(&tc[i], NULL, client, i);
        walk(0, 1); 
    } 

    pthread_exit(0);
}