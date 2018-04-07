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
        
        // Odd Company
        if(Company_get_company_number(company) % 2 == 1)
        {
            // Odd Company's Right Intern is Even
            // Lock Even First
            pthread_mutex_lock(right_intern);
            pthread_mutex_lock(left_intern);
        }
        // Even Company
        else
        {
            // Even Company's Left Intern is Even
            // Lock Even First
            pthread_mutex_lock(left_intern);
            pthread_mutex_lock(right_intern);
        }
        
        Company_hire_interns(company);
        
        // We want to unlock interns in the reverse order we locked them
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
        // Have a board meeting to give other company's a chance to get interns
        Company_have_board_meeting(company);
        
    }
    return NULL;
}