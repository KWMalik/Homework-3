#include "types.h"
#include "x86.h"
#include "defs.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "spinlock.h"
#include "rwlock.h"
#include "proc.h"

int
sys_tfork(void)
{
  int entry, arg, spbottom;

  if (getuserint(0, &entry) < 0)
    return -1;
  if (getuserint(1, &arg) < 0)
    return -1;
  if (getuserint(2, &spbottom) < 0)
    return -1;

  return tfork(entry, arg, spbottom);
}

int
sys_texit(void)
{
  return texit();
}

int
sys_twait(void)
{
  int pid;

  if (getuserint(0, &pid) < 0)
    return -1;

  return twait(pid);
}

int
sys_pschk(void)
{
  return pschk();
}

int
sys_fork(void)
{
  return fork();
}

int
sys_exit(void)
{
  exit();
  return 0;  // not reached
}

int
sys_wait(void)
{
  return wait();
}

int
sys_kill(void)
{
  int pid;

  if(getuserint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int
sys_getpid(void)
{
  return proc->pid;
}

int
sys_sbrk(void)
{
  int addr;
  int n;
  int fault = 0;

  if(getuserint(0, &n) < 0)
    return -1;

  if(growproc(n, &addr) < 0)
    fault = 1;

  if (fault)
    return -1;
  else
    return addr;
}

int
sys_sleep(void)
{
  int n;
  uint ticks0;
  
  if(getuserint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(proc->common->killed){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

// return how many clock tick interrupts have occurred
// since start.
int
sys_uptime(void)
{
  uint xticks;
  
  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}
