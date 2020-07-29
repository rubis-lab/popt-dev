#ifndef __SCHED_CORE_H__
#define __SCHED_CORE_H__

#include <linux/kernel.h>
#include <linux/types.h>
#include <unistd.h>
#include <sys/syscall.h>

#define gettid() syscall(__NR_gettid)

struct thr_arg {
    int task_id;
    int thr_id;
    int parent;
    int exec_time;
    int deadline;
    int period;
};

struct sched_attr {
	__u32 size;

	__u32 sched_policy;
	__u64 sched_flags;

	/* SCHED_NORMAL, SCHED_BATCH */
	__s32 sched_nice;

	/* SCHED_FIFO, SCHED_RR */
	__u32 sched_priority;

	/* SCHED_DEADLINE (nsec) */
	__u64 sched_runtime;
	__u64 sched_deadline;
	__u64 sched_period;
};

int sched_setattr(pid_t pid,
    const struct sched_attr *attr,
    unsigned int flags);

int sched_getattr(pid_t pid,
    struct sched_attr *attr,
    unsigned int size,
    unsigned int flags);

#endif
