#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"
#include "proc_stat.h"
int waitx_function(int *,int *);
int set_priority_function(int , int);
int getpinfo_function(struct proc_stat * , int );
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
sys_waitx(void)
{
  int *wtime;
  int *rtime;
 if(argptr(0, (void *)&wtime, sizeof(wtime)) < 0){// extract and store argument into num
   return -1;
 } 
 if(argptr(1, (void *)&rtime, sizeof(rtime)) < 0){// extract and store argument into num
   return -1;
 } 
  return waitx_function(wtime,rtime);
}
int sys_set_priority(void)
{
  int priority;
  int pid;
 if(argptr(0, (void *)&priority, sizeof(priority)) < 0){// extract and store argument into num
   return -1;
 } 
 if(argptr(1, (void *)&pid, sizeof(pid)) < 0){// extract and store argument into num
   return -1;
 }
  return set_priority_function(priority,pid);
}
int sys_getpinfo(void)
{
  struct proc_stat *process;
  int pid;
  if(argptr(0, (void *)&process, sizeof(process)) < 0){// extract and store argument into num
   return -1;
 }
 if(argptr(1, (void *)&pid, sizeof(pid)) < 0){// extract and store argument into num
   return -1;
 }
 return getpinfo_function(process,pid);
} 
int
sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int
sys_getpid(void)
{
  return myproc()->pid;
}

int
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

int
sys_sleep(void)
{
  int n;
  uint ticks0;

  if(argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(myproc()->killed){
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
