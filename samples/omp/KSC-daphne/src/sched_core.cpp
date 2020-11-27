#include "sched_core.hpp"

/* XXX use the proper syscall numbers */
#ifdef __x86_64__
#define __NR_sched_setattr		314
#define __NR_sched_getattr		315
#endif

#ifdef __i386__
#define __NR_sched_setattr		351
#define __NR_sched_getattr		352
#endif

#ifdef __arm__
#define __NR_sched_setattr		380
#define __NR_sched_getattr		381
#endif

#define BUFFER_SIZE 5000
#define MAX_TOKEN_COUNT 128

// system call hook to call SCHED_DEADLINE
int sched_setattr(pid_t pid,
    const struct sched_attr *attr,
    unsigned int flags)
{
	return syscall(__NR_sched_setattr, pid, attr, flags);
}

int sched_getattr(pid_t pid,
    struct sched_attr *attr,
    unsigned int size,
    unsigned int flags)
{
	return syscall(__NR_sched_getattr, pid, attr, size, flags);
}
