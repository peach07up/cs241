/**
 * Overworked Interns Lab
 * CS 241 - Spring 2016
 */
#include "company.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// Whoa! A global mutex .. I wonder what this can be used for :)
//pthread_mutex_t arbitrate = PTHREAD_MUTEX_INITIALIZER;


void *work_interns(void *p) {
    Company *company = (Company *)p;
    pthread_mutex_t *left_intern, *right_intern;
    while (running) {
        left_intern = Company_get_left_intern(company);
        right_intern = Company_get_right_intern(company);
        
        if(left_intern == right_intern) { break; }
        
        if(Company_get_company_number(company) % 2 == 1)
        {
            pthread_mutex_lock(right_intern);
            pthread_mutex_lock(left_intern);
        }
        else
        {
            pthread_mutex_lock(left_intern);
            pthread_mutex_lock(right_intern);
        }
        
        //do
        //{
        //if(left_intern->__data.__owner != 0 || right_intern->__data.__owner != 0)
        //{
        //    continue;
        //}
        //pthread_mutex_lock(&arbitrate);
        //printf("Company %d Trying for Interns ", Company_get_company_number(company));
        //int result = 0;
        //lock = 0;
        
        
        //if(left_intern->__data.__owner == 0 && right_intern->__data.__owner == 0)
        //{
        //    pthread_mutex_lock(left_intern);
        //    pthread_mutex_lock(right_intern);
        //}
        //else
        //{
        //    lock = 1;
        //}
        
        /*// Every company grabs their left intern
         result += pthread_mutex_trylock(left_intern);
         // Now what if another company takes the right intern
         // and won't let go?
         // Then the comppany tries to grab their right intern ...
         // DREADLOCK!
         lock += pthread_mutex_trylock(right_intern);
         
         // If the 2 trylocks didn't both return 0, aka success
         // Then we couldn't get both locks
         if(result != 0 || lock != 0)
         {
         // We want to unlock what we have already locked
         // result == 0 means we get left_intern
         // lock == 0 means we get right_intern
         if(result == 0)
         {
         pthread_mutex_unlock(left_intern);
         }
         if(lock == 0)
         {
         pthread_mutex_unlock(right_intern);
         }
         // Set lock to 1 so we keep looping until its 0
         lock = 1;
         //printf("Failed\n");
         }*/
        
        //pthread_mutex_unlock(&arbitrate);
        //if(lock != 0)
        //{
        //usleep(100);
        //}
        //} while(lock != 0);
        //printf("Succeeded\n");
        
        Company_hire_interns(company);
        
        if(Company_get_company_number(company) % 2 == 1)
        {
            pthread_mutex_unlock(left_intern);
            pthread_mutex_unlock(right_intern);
        }
        else
        {
            pthread_mutex_unlock(right_intern);
            pthread_mutex_unlock(left_intern);
        }
        Company_have_board_meeting(company);
        
    }
    return NULL;
}
