// Added for HW3
// Read-write mutexes

#define OP_INIT         0
#define OP_READLOCK     1
#define OP_READUNLOCK   2
#define OP_WRITELOCK    3
#define OP_WRITEUNLOCK  4
#define OP_DESTROY      5

struct rwlock {
  struct spinlock lk;
  int ok2read, ok2write; // Wait queues. 
  int ar; // # of active readers
  int aw; // # of active writers
  int wr; // # of waiting readers
  int ww; // # of waiting writers
};

