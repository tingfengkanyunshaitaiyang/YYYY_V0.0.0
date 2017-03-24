#ifndef ACTIVITY_H
#define ACTIVITY_H





#include <QThread>
#include <QMutex>
#include <QMutexLocker>

/*******************************************************************************

 类    名：Activity
 版    本：1.0
 功    能：自定义线程类
 描    述：处于AtcLib命名空间下的线程类

*******************************************************************************/
template<class C>
class Activity:public QThread
{
public:

    typedef void (C::*CallBack)();
    Activity(C* object,CallBack method):_pObject(object),_method(method),
        _stopped(true),
        _running(false)
    {

    }

    virtual ~Activity()
    {
        stop();
        wait();
    }

    void start()
    {
         QMutexLocker locker(&_mutex);
         if(!_running)
         {
             try
             {
                 QThread::start();
                 _stopped = false;
                 _running = true;
             }
             catch(...)
             {
                 _running = false;
                 throw;
             }

         }
    }

    void stop()
    {

        _stopped = true;
        _running = false;

        QMutexLocker locker(&_mutex);

    }

    void wait(long milliseconds)
    {
        if(_running)
        {
            QMutexLocker locker(&_mutex);
        }

    }

    void wait()
    {
        QMutexLocker locker(&_mutex);
    }

    bool isStopped() const
    {
        return _stopped;
    }

    bool isRunning() const
    {
        return _running;
    }

    void msleep(unsigned long microseconds)
    {
        QThread::msleep(microseconds);
    }

    void sleep(unsigned long sec)
    {
        QThread::sleep(sec);
    }

protected:
    void run()
    {
        QMutexLocker locker(&_mutex);
        try
        {

            (_pObject->*_method)();

        }
        catch(...)
        {
            _running = false;
            throw;

        }

        _running = false;
    }

private:
    C* _pObject;
    CallBack _method;

    volatile bool _stopped;
    volatile bool _running;

    QMutex _mutex;

};


#endif // ACTIVITY_H
