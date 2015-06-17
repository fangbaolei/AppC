1. 多线程是线程应用的核心！
   在一个进程中开辟几个独立的线程并不能称为真正意义上的多线程。多线程一般用于数据的共享数据，所以，其中就应该会涉及到同步等机制。
2. 多线程的同步机制
   1）互斥量：pthread_mutex_t。
	  互斥量的两种初始化方式：
      a）将互斥锁赋值为常量，PTHREAD_MUTEX_INITIALIZER
      b）当互斥量为动态分配是，使用pthread_mutex_init函数进行初始化，使用pthread_mutex_destroy函数销毁。
      加锁：pthread_mutex_lock
      解锁：pthread_mutex_unlock
   2）读写锁
      允许多个线程同时读，只能有一个线程同时写。适用于读的次数远大于写的情况。
      初始化：pthread_rwlock_init 
      销毁： pthread_rwlock_destroy 
      读加锁：pthread_rwlock_rdlock 
      写加锁：pthread_rwlock_wrlock
	  解锁用同一个函数：pthread_rwlock_unlock 
3.  条件变量
    初始化：pthread_cond_init
    销毁：pthread_cond_destroy
    条件等待：pthread_cond_wait
    唤醒条件：pthread_cond_signal
