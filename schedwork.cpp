#ifndef RECCHECK
#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
// add or remove necessary headers as you please

#endif

#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;


// Add prototypes for any helper functions here

//function that recurses
bool schedHelper(const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched,
    size_t day,
    size_t worker
);

//checks if maxShifts is satisifed
bool isValid(DailySchedule& sched, const size_t maxShifts, Worker_T worker);


// Add your implementation of schedule() and other helper functions here

bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
)
{
    if(avail.size() == 0U){
        return false;
    }
    sched.clear();

    return schedHelper(avail, dailyNeed, maxShifts, sched, 0, 0);






}

bool isValid(DailySchedule& sched, const size_t maxShifts, Worker_T x)
{
    size_t count = 0;
    for (DailySchedule::iterator day = sched.begin(); day != sched.end(); day++) {
            for (vector<Worker_T>::iterator worker = day->begin(); worker != day->end(); worker++) {
                if (*worker == x) count++;
            }
    }
    return (count <= maxShifts);
}

bool schedHelper(const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched,
    size_t day,
    size_t availWorker
)
{
    if (day == avail.size()) {
        return true;
    }
    if (availWorker == dailyNeed) {
        return schedHelper(avail, dailyNeed, maxShifts, sched, day + 1, 0);
    }
    //iterates through the availWorkers in the day given
    for (size_t i = availWorker; i < avail[day].size(); i++) {
        if (availWorker == 0) {
            sched.push_back(vector<Worker_T>());
        }
        if (avail[day][i]) {
            //adds worker if available
            sched[day].push_back(i);
            //check maxShifts contraint
            if (isValid(sched, maxShifts, i)) {
                //moves on to next worker to be scheduled
                if (schedHelper(avail, dailyNeed, maxShifts, sched, day, availWorker + 1)) {
                    return true;
                }
            }
            //backtrack
            sched[day].pop_back();
        }
        if (sched[day].size() == 0) {
            sched.pop_back();
        }
    }
    return false;
}
