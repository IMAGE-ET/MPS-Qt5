#ifndef PROGRESS_H
#define PROGRESS_H

#include <utils/Status.h>

class Progress
{
public:
    virtual Status notifyProgress(void** params){}
    virtual ~Progress(){}
};

#endif // PROGRESS_H
