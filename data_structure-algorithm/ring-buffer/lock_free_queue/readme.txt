mpmc的测试结果：
push thread 1, push num 100000001, use time 33.940102 sec
push thread 2, push num 100000001, use time 33.940056 sec

然后消费者陷入死循环


concurrentqueue测试结果:
lock_free_queue git:(master) ✗ ./concurrentqueue
=push thread 1, push num 100000000, use time 39.604717 sec
push thread 2, push num 100000001, use time 39.604687 sec
pop thread 2, pop num 100000001, use time 45.509796 sec
pop thread 1, pop num 100000001, use time 45.509861 sec