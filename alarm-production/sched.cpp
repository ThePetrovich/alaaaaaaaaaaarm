/*
 * sched.c
 * 
 * Created: 14.02.2021 09:15:36
 * Author: ThePetrovich
 */


#include "sched.h"
#include "jobs.h"
#include "lists.h"
#include <stddef.h>

void sched_initScheduler(sSched_t* scheduler) 
{
    return;
}

void sched_restartJob(sSched_t* scheduler, sJob_t* job)
{
    if (scheduler != NULL && job != NULL) {
        sched_enterCriticalSection();

        if (job->state != STATE_UNINIT) {
            sched_listDeleteAny(job->schedListItem.list, &(job->schedListItem));
            job->schedReference = scheduler;
            job->schedListItem.data = job;
            scheduler->jobCount++;

            switch(job->state) {
                case STATE_ACTIVE:
                    sched_listAddBack(&(scheduler->activeJobList[job->priority]), &(job->schedListItem));
                    break;
                case STATE_SUSPENDED:
                    sched_listAddBack(&(scheduler->suspendedJobList), &(job->schedListItem));
                    break;
                case STATE_SLEEPING:
                    sched_listAddBack(&(scheduler->sleepingJobList), &(job->schedListItem));
                    break;
                default:
                    /* do nothing */
                    break;
            }
        }

        sched_exitCriticalSection();
    }
}

void sched_stopJob(sJob_t* job)
{
    if (job != NULL) {
        sched_enterCriticalSection();

        sched_listDeleteAny(job->schedListItem.list, &(job->schedListItem));
        if (job->schedReference != NULL) {
            job->schedReference->jobCount--;
            job->schedReference = NULL;
        }

        sched_exitCriticalSection();
    }
}

void sched_suspendJob(sJob_t* job)
{
    if (job != NULL) {
        sched_enterCriticalSection();

        if (job->schedReference != NULL) {
            sched_listDeleteAny(job->schedListItem.list, &(job->schedListItem));
            sched_listAddBack(&(job->schedReference->suspendedJobList), &(job->schedListItem));
            job->state = STATE_SUSPENDED;
        }

        sched_exitCriticalSection();
    }
}

static void sched_sleepJob(sJob_t* job)
{
    if (job->schedReference != NULL) {
        sched_enterCriticalSection();

        job->delay = job->period;
        sched_listDeleteAny(job->schedListItem.list, &(job->schedListItem));
        sched_listAddBack(&(job->schedReference->sleepingJobList), &(job->schedListItem));
        job->state = STATE_SLEEPING;

        sched_exitCriticalSection();
    }
}

void sched_activateJob(sJob_t* job)
{
    if (job != NULL) {
        sched_enterCriticalSection();

        if (job->schedReference != NULL) {
            sched_listDeleteAny(job->schedListItem.list, &(job->schedListItem));
            sched_listAddBack(&(job->schedReference->activeJobList[job->priority]), &(job->schedListItem));
            job->state = STATE_ACTIVE;
        }

        sched_exitCriticalSection();
    }
}

void sched_changeJobPriority(sJob_t* job, int priority)
{
    if (job != NULL) {
        sched_enterCriticalSection();

        if (priority > CFG_NUMBER_OF_PRIORITIES-1) {
            job->priority = CFG_NUMBER_OF_PRIORITIES-1;
        }
        else {
            if (priority < 0) {
                job->priority = 0;
            }
            else {
                job->priority = priority;
            }
        }
        sched_restartJob(job->schedReference, job);

        sched_exitCriticalSection();
    }
}

void sched_run(sSched_t* scheduler)
{
    sched_enterCriticalSection();

    for (int i = CFG_NUMBER_OF_PRIORITIES-1; i >= 0; i--) {
        sLinkedListItem_t* head = scheduler->activeJobList[i].head;
        if (head != NULL) {
            sched_listDropFront(&(scheduler->activeJobList[i]));
            if (head->data != NULL) {
                if (head->data->function != NULL) {
                    (head->data->function)(head->data->args); /* Call job function with its args */
                }

                if (head->data->period == 0) {
                    sched_suspendJob(head->data);
                }
                else {
                    sched_sleepJob(head->data);
                }
            }
            break;
        }
    }

    sched_exitCriticalSection();
}

void sched_tick(sSched_t* scheduler)
{
    sched_enterCriticalSection();

    if (scheduler != NULL) {
        sLinkedListItem_t* head = scheduler->sleepingJobList.head;
        while (head != NULL) {
            if (head->data != NULL) {
                if (head->data->delay <= 0) {
                    sched_activateJob(head->data);
                }
                else {
                    head->data->delay--;
                }
            }
            head = head->next;
        }
    }

    sched_exitCriticalSection();
}

int sched_getJobCount(sSched_t* scheduler)
{
    int result = -1;

    if (scheduler != NULL) {
        sched_enterCriticalSection();

        result = scheduler->jobCount;

        sched_exitCriticalSection();
    }

    return result;
}
