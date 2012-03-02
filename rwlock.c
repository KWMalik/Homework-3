// Read-write mutexes. 
// Added for HW3, please implement your code here

#include "types.h"
#include "defs.h"
#include "param.h"
#include "x86.h"
#include "mmu.h"
#include "spinlock.h"
#include "rwlock.h"
#include "proc.h"

// you can use table for debugging
extern struct {
  struct spinlock lock;
  struct proc proc[NPROC];
} ptable;

void
initrwlock(struct rwlock *m)
{
}

void
destroyrwlock(struct rwlock *m)
{
}

void
readlock(struct rwlock *m)
{
}

void
readunlock(struct rwlock *m)
{
}

void
writelock(struct rwlock *m)
{
}

void
writeunlock(struct rwlock *m)
{
}

int
sys_rwlock()
{
  struct rwlock *m;
  int op;

  readlock(&proc->common->pglock);

  if (argptr(0, (char **)&m, sizeof(struct rwlock)) < 0 || argint(1, &op) < 0)
    goto error;

  switch (op) {
    case OP_INIT: initrwlock(m); break;
    case OP_READLOCK: readlock(m); break;
    case OP_READUNLOCK: readunlock(m); break;
    case OP_WRITELOCK: writelock(m); break;
    case OP_WRITEUNLOCK: writeunlock(m); break;
    case OP_DESTROY: destroyrwlock(m); break;
    default: goto error; // Invalid op. 
  }

  readunlock(&proc->common->pglock);
  return 0;

error:
  readunlock(&proc->common->pglock);
  return -1;
}

