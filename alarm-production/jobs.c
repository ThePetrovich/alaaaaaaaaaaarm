/*
 * jobs.c
 * 
 * Created: 14.02.2021 09:15:16
 * Author: ThePetrovich
 */


#include "sched.h"
#include "jobs.h"
#include "lists.h"
#include <stddef.h>

sJob_t sched_createJob(void (*function)(void*), void* args, int delay, int period, int priority, sJobState_t initialState, const char* name)
{
    sJob_t newJob;

    newJob.function = function;
    newJob.args = args;
    newJob.delay = delay;
    newJob.period = period;

    if (priority > CFG_NUMBER_OF_PRIORITIES-1) {
        newJob.priority = CFG_NUMBER_OF_PRIORITIES-1;
    }
    else {
        if (priority < 0) {
            newJob.priority = 0;
        }
        else {
            newJob.priority = priority;
        }
    }

    newJob.name = name;

    newJob.schedReference = NULL;
    newJob.state = initialState;

    newJob.schedListItem.list = NULL;
    newJob.schedListItem.data = NULL;
    newJob.schedListItem.next = NULL;
    newJob.schedListItem.prev = NULL;

    return newJob;
}

void sched_setJobDelay(sJob_t* job, int delay) 
{
    if (job != NULL) {
        job->delay = delay;
    }
}

void sched_setJobPeriod(sJob_t* job, int period)
{
    if (job != NULL) {
        job->period = period;
    }
}

void sched_setJobFunction(sJob_t* job, void (*function)(void*), void* args)
{
    if (job != NULL) {
        job->function = function;
        job->args = args;
    }
}

void sched_setJobName(sJob_t* job, char* name)
{
    if (job != NULL) {
        job->name = name;
    }
}

void(*sched_getJobFunction(sJob_t* job))(void*)
{
    void (*result)(void*) = NULL;

    if (job != NULL) {
        result = job->function;
    }

    return result;
}

int sched_getJobDelay(sJob_t* job)
{
    int result = -1;

    if (job != NULL) {
        result = job->delay;
    }

    return result;
}

int sched_getJobPeriod(sJob_t* job)
{
    int result = -1;

    if (job != NULL) {
        result = job->period;
    }

    return result;
}

const char* sched_getJobName(sJob_t* job)
{
    const char* result = NULL;

    if (job != NULL) {
        result = job->name;
    }

    return result;
}

sJobState_t sched_getJobState(sJob_t* job)
{
    sJobState_t result = STATE_UNINIT;

    if (job != NULL) {
        result = job->state;
    }

    return result;
}
