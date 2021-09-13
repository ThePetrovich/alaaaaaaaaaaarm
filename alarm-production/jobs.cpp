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

void sched_createJob(sSched_t* sched, sJob_t* job, void (*function)(void*), void* args, int delay, int period, int priority, const char* name)
{
    if (sched != NULL && job != NULL && function != NULL) {
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
        newJob.state = STATE_SLEEPING;

        newJob.schedListItem.list = NULL;
        newJob.schedListItem.data = NULL;
        newJob.schedListItem.next = NULL;
        newJob.schedListItem.prev = NULL;

        *job = newJob;

        sched_restartJob(sched, job);
    }
}

void sched_setJobDelay(sJob_t* job, int delay) 
{
    if (job != NULL) {
        sched_enterCriticalSection();

        job->delay = delay;

        sched_exitCriticalSection();
    }
}

void sched_setJobPeriod(sJob_t* job, int period)
{
    if (job != NULL) {
        sched_enterCriticalSection();

        job->period = period;

        sched_exitCriticalSection();
    }
}

void sched_setJobFunction(sJob_t* job, void (*function)(void*), void* args)
{
    if (job != NULL) {
        sched_enterCriticalSection();

        job->function = function;
        job->args = args;

        sched_exitCriticalSection();
    }
}

void sched_setJobName(sJob_t* job, char* name)
{
    if (job != NULL) {
        sched_enterCriticalSection();

        job->name = name;

        sched_exitCriticalSection();
    }
}

void(*sched_getJobFunction(sJob_t* job))(void*)
{
    void (*result)(void*) = NULL;

    if (job != NULL) {
        sched_enterCriticalSection();

        result = job->function;

        sched_exitCriticalSection();
    }

    return result;
}

int sched_getJobDelay(sJob_t* job)
{
    int result = -1;

    if (job != NULL) {
        sched_enterCriticalSection();

        result = job->delay;

        sched_exitCriticalSection();
    }

    return result;
}

int sched_getJobPeriod(sJob_t* job)
{
    int result = -1;

    if (job != NULL) {
        sched_enterCriticalSection();

        result = job->period;

        sched_exitCriticalSection();
    }

    return result;
}

const char* sched_getJobName(sJob_t* job)
{
    const char* result = NULL;

    if (job != NULL) {
        sched_enterCriticalSection();

        result = job->name;

        sched_exitCriticalSection();
    }

    return result;
}

sJobState_t sched_getJobState(sJob_t* job)
{
    sJobState_t result = STATE_UNINIT;

    if (job != NULL) {
        sched_enterCriticalSection();

        result = job->state;

        sched_exitCriticalSection();
    }

    return result;
}
