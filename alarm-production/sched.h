/*
 * sched.h
 * 
 * Created: 14.02.2021 09:20:53
 * Author: ThePetrovich
 */


#ifndef SCHED_SCHED_H_
#define SCHED_SCHED_H_

#ifdef __cplusplus
extern "C" {
#endif

#define LIBSCHED_VERSION "1.0.0"

#define CFG_NUMBER_OF_PRIORITIES 8

#include "lists.h"
#include "jobs.h"

typedef struct sSchedStruct_t 
{
    sLinkedList_t activeJobList[CFG_NUMBER_OF_PRIORITIES];
    sLinkedList_t sleepingJobList;
    sLinkedList_t suspendedJobList;

    int jobCount;
} sSched_t;

void sched_initScheduler(sSched_t* scheduler);

void sched_startJob(sSched_t* scheduler, sJob_t* job);
void sched_stopJob(sJob_t* job);

void sched_suspendJob(sJob_t* job);
void sched_activateJob(sJob_t* job);
void sched_changeJobPriority(sJob_t* job, int priority);

void sched_run(sSched_t* scheduler);
void sched_tick(sSched_t* scheduler);

int sched_getJobCount(sSched_t* scheduler);

#ifdef __cplusplus
}
#endif

#endif