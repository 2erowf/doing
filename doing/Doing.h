#pragma once
#include <windows.h>
#include <map>
#include "Activity.h"
#include <mutex>
#include <queue>
#include "ConcurrentQueue.h"
#include <memory>

class Doing
{
public:
    typedef std::map<std::wstring, Activity*> ProcActivityMap;
    typedef std::pair<std::wstring, Activity*> ProcActivityPair;
    void Monitor();
    void StartReportActivities() const;
    Doing(ConcurrentQueue<Activity>& ptr_queue);
    ~Doing();
private:
    Doing();
    void FillActivityKey(ActivityKey& key);
    ConcurrentQueue<Activity>& _job_queue;
    std::wstring _last_metric_key;
    unsigned long long _acitive_duration = 0;
    void Sample();

    //OS(specific calls)
    static std::wstring ReportUrlByHandle(const HWND hwnd);
    static unsigned long long GetLastInputTime();
    unsigned long long _last_time = 0;
    //activity that's idle for more than <_MAX_IDLE_TIME> will be flagged as non-active activity
    const unsigned int _MAX_IDLE_TIME = 12000;
    //machine  name
    std::wstring _machine_name;
};
