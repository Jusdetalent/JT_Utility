#ifndef HN_THREAD_HPP_INCLUDED
#define HN_THREAD_HPP_INCLUDED

    #include <pthread.h>
    #include <vector>
	#include <string>

    namespace hnapi
    {
        namespace process
        {
            enum THREAD_MESSAGE{
                EMPTY_MESSAGE,  STOP_THREAD,    SUSPEND_THREAD,
                RESUME_THREAD
            };

            enum THREAD_TYPE{
                IDLE_THREAD,    PROCESS_THREAD, LIGHT_PROCESS_THREAD
            };

            enum THREAD_STATUS{
                RUNNING_THREAD, WAITING_THREAD, WAITING_CONDITION,
                FREE_THREAD
            };

            struct ThreadCondition{
                pthread_mutex_t mutex_var;
                pthread_cond_t  condition;
            };

            struct ThreadMessage{
                pthread_mutex_t         mutex;
                struct ThreadCondition  condition;
                std::string             buffer;
                enum THREAD_MESSAGE     message;
                void                    *data;
            };

            class HN_Thread{

                public:
                    // Global var
                    struct ThreadMessage message;

                    // Builder
                    HN_Thread(int PPID);

                    // Methods
                    bool start(void *(*f)(void *), void *data);
                    bool suspend(void);
                    bool resume(void);
                    bool stop(void);
                    bool join(void);

                    // Identifier management
                    void
                        setProcessId(int),              setUserId(int),
                        setGroupId(int),                setParentProcessId(int),
                        setStatus(enum THREAD_STATUS);
                    int
                        getProcessId(void), getUserId(void),
                        getGroupId(void),   getParentProcessId(void);
                    enum THREAD_STATUS      getStatus(void);

                    // Differenciation
                    void setType(enum THREAD_TYPE);
                    enum THREAD_TYPE    getType(void);
                    bool isRunning(void);

                    // Child threads management
                    std::vector<HN_Thread *>    &getChildren(void);
                    void
                        addChild(HN_Thread *),  removeChild(HN_Thread *),
                        cleanChildren(void);

                    // Destroyer
                    ~HN_Thread();

                private:
                    int                         pid,    uid,    gid,
                                                ppid;
                    pthread_t                   thread;
                    pthread_attr_t              attr;
                    enum THREAD_TYPE            type;
                    enum THREAD_STATUS          status;
                    std::vector<HN_Thread *>    children;
            };

            void freeProcessArray(void);
            int  generateNewProcessId(void);
        }
    }

#endif // HN_THREAD_HPP_INCLUDED
