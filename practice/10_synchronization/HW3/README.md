# difference between semaphore synchronization and mutex and condition variable.

### 1. condition
- semaphore can implement number of process that acesss to critical section.
- So, That can check mutual exclusion and synchronization with condition.

- But, mutex and condition variable divid this rule.
- Mutex only do control mutual exclusion by locking.
- Condition variable check control condition.


### 2. stateful
- Semaphore is stateful, so semaphore keep state when process or thread do not wait.
- But, condition's wait is not consider it. So, if not wait, this signal will ignored.
