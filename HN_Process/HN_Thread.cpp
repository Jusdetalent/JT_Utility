/*
 * Threading management
 * Henock @ Comedac :: 11/ 08/ 2018 || 21:23
 */


 #include <iostream>
 #include <vector>
 #include <map>
 #include "HN_Thread.hpp"


 using namespace hnapi::process;


 std::vector<std::pair<HN_Thread*, int> > PROCESS_ARRAY;


 // Builder
HN_Thread::HN_Thread(int PPID)
{
    this->pid   = generateNewProcessId();
    this->uid   = 0;
    this->ppid  = PPID;
    this->gid   = 0;
    this->type  = PROCESS_THREAD;
    this->status= FREE_THREAD;

    std::pair<HN_Thread*, int> item;
        item.first  = this;
        item.second = this->pid;
    PROCESS_ARRAY.push_back(item);

    this->message.mutex     = PTHREAD_MUTEX_INITIALIZER;
    this->message.message   = EMPTY_MESSAGE;
    this->message.data      = NULL;

    this->message.condition.mutex_var   = PTHREAD_MUTEX_INITIALIZER;
    this->message.condition.condition   = PTHREAD_COND_INITIALIZER;

    pthread_attr_init(&this->attr);
    pthread_attr_setscope(&this->attr, PTHREAD_SCOPE_SYSTEM);
}


 // Methods
bool HN_Thread::start(void *(*f)(void *data), void *data)
{
    if(this->status == FREE_THREAD)
        {
        this->message.data = data;
        int res = pthread_create(&this->thread, NULL, f, this);

        if(res != 0)
            {
            return false;
        }
    }

    this->status  = RUNNING_THREAD;
    return true;
}

bool HN_Thread::suspend(void)
{
    if(this->status == FREE_THREAD)return false;

    pthread_mutex_lock(&this->message.mutex);
    this->message.message = SUSPEND_THREAD;
    pthread_mutex_unlock(&this->message.mutex);

    return true;
}

bool HN_Thread::resume(void)
{
    if(this->status == FREE_THREAD)return false;
    pthread_mutex_lock(&this->message.mutex);

    if(this->message.message == SUSPEND_THREAD)
        {
        pthread_mutex_lock(&this->message.condition.mutex_var);
        pthread_cond_signal(&this->message.condition.condition);
        pthread_mutex_unlock(&this->message.condition.mutex_var);
    }

    this->message.message = EMPTY_MESSAGE;
    pthread_mutex_unlock(&this->message.mutex);
    return true;
}

bool HN_Thread::stop(void)
{
    // Kill thread if running
    if(this->status == FREE_THREAD)return false;

    // Verify if not busy
    for(;;)
    {
        if(pthread_mutex_lock(&this->message.mutex) != EBUSY){
            // Unlock thread
            this->message.message = STOP_THREAD;
            pthread_mutex_unlock (&this->message.mutex);

            void *thread_result;

            pthread_join(this->thread, &thread_result);
            break;
        }
    }

    // Free threads from vector
    std::vector<HN_Thread *>::iterator th_it;
    for(
        th_it = this->children.begin();
        th_it!= this->children.end();
        th_it++
    ){
        (*th_it)->stop();
    }

    return true;
}

bool HN_Thread::join(void)
{
    if(this->status != FREE_THREAD)
        {
        void *thread_result;
        pthread_join(this->thread, &thread_result);
        return true;
    }

    return false;
}


 // Identifier management
void HN_Thread::setProcessId(int __pid)         {this->pid   = __pid;}
void HN_Thread::setUserId(int __uid)            {this->uid   = __uid;}
void HN_Thread::setGroupId(int __gid)           {this->gid   = __gid;}
void HN_Thread::setParentProcessId(int __ppid)  {this->ppid  = __ppid;}
void HN_Thread::setStatus(enum THREAD_STATUS _t){this->status= _t;}

int HN_Thread::getProcessId(void)               {return this->pid;}
int HN_Thread::getUserId(void)                  {return this->uid;}
int HN_Thread::getGroupId(void)                 {return this->gid;}
int HN_Thread::getParentProcessId(void)         {return this->ppid;}
enum THREAD_STATUS HN_Thread::getStatus(void)   {return this->status;}


 // Differenciation
void HN_Thread::setType(enum THREAD_TYPE __type){this->type = __type;}
enum THREAD_TYPE HN_Thread::getType(void)       {return this->type;}
bool HN_Thread::isRunning(void)
{
    return this->status != FREE_THREAD ? true : false;
}


 // Child threads management
std::vector<HN_Thread *> &HN_Thread::getChildren(void)
{
    return this->children;
}

void HN_Thread::addChild(HN_Thread *th)
{
    this->children.push_back(th);
}

void HN_Thread::removeChild(HN_Thread *th)
{
    // Free threads from vector
    std::vector<HN_Thread *>::iterator th_it;
    for(
        th_it = this->children.begin();
        th_it!= this->children.end();
        th_it++
    ){
        if(th == *th_it)
            {
            this->children.erase(th_it);
            break;
        }
    }
}

void HN_Thread::cleanChildren(void)
{
    // Free threads from vector
    std::vector<HN_Thread *>::iterator th_it;
    for(
        th_it = this->children.begin();
        th_it!= this->children.end();
        th_it++
    ){
        delete *th_it;
    }

    // Clean all vector elements
    this->children.clear();
}


 // Destroyer
HN_Thread::~HN_Thread()
{
    // Erase from process array
    std::vector<std::pair<HN_Thread*, int> >::iterator it;
    for(
        it = PROCESS_ARRAY.begin();
        it!= PROCESS_ARRAY.end();
        it++
    ){
        if((*it).first == this)
            {
            PROCESS_ARRAY.erase(it);
            break;
        }
    }

    // Kill thread if running
    if(this->status != FREE_THREAD)
        {
        // Verify if not busy
        for(;;)
            {
            if(pthread_mutex_trylock(&this->message.mutex) != EBUSY)
                {
                // Unlock thread
                this->message.message = STOP_THREAD;
                pthread_mutex_unlock (&this->message.mutex);

                void *thread_result;
                pthread_join(this->thread, &thread_result);
                break;
            }
        }
    }

    // Free threads from vector
    std::vector<HN_Thread *>::iterator th_it;
    for(
        th_it = this->children.begin();
        th_it!= this->children.end();
        th_it++
    ){
        delete *th_it;
    }

    // Destroy mutual exclusion
    pthread_mutex_destroy(&this->message.mutex);
    pthread_attr_destroy(&this->attr);
    pthread_mutex_destroy(&this->message.condition.mutex_var);
    pthread_cond_destroy(&this->message.condition.condition);
}

void hnapi::process::freeProcessArray(void)
{
    std::vector<std::pair<HN_Thread*, int> >::iterator it;
    for(
        it = PROCESS_ARRAY.begin();
        it!= PROCESS_ARRAY.end();
        it++
    ){
        delete (*it).first;
        it--;
    }
}

int hnapi::process::generateNewProcessId(void)
{
    std::vector<std::pair<HN_Thread*, int> >::iterator it;
    bool finded = false;

    for(int i = 1; ; i++)
        {

        for(
            it = PROCESS_ARRAY.begin();
            it!= PROCESS_ARRAY.end();
            it++
        ){
            if((*it).second == i)
                {
                finded = true;
                break;
            }
        }

        if(!finded)return i;
        finded = false;
    }

    return 1;
}
