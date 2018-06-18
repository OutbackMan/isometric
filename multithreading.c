// logical cores, processes memory map, threads execution granularity
// 1. what work? 2. communicate?
// c language doesn't provide anything that can garuntee threads don't overlap. x64 provides the instructions
// to do so, e.g. locked exchange, locked compare exchange
// also have to worry about multiple writes
// cores read in memory on cache line boundaries, so two cores could be operating on the same cache line, resulting in possible overwrites
// as compiler doesn't know about threads, may have to use 'volatile' so it doesn't perform certain optimisations

#define ARRAY_COUNT(arr) (sizeof(arr) / sizeof(a[0]))

#define COMPLETE_PAST_WRITES_BEFORE_FUTURE_WRITES _WriteBarrier(); __mm_sfence() // fence is cpu intrinsic, not necessary for intel
#define COMPLETE_PAST_READS_BEFORE_FUTURE_READS _ReadBarrier()

typedef struct {
  work_queue_callback callback;
  void* data;
} WorkQueueEntry;

GLOBAL uint32_t volatile entry_completion_count = 0;
GLOBAL uint32_t volatile next_entry_to_do = 0;
GLOBAL uint32_t volatile entry_count = 0;
WorkQueueEntry entries[256];

typedef struct {
  int logical_thread_index;
} TheadInfo;

INTERNAL int thread_function(void* thread_param)
{
  ThreadInfo* thread_info = (ThreadInfo *)thread_param;
 
  while (true) {
    if (!thread_work()) {
      SDL_SemWait(thread_info->semaphore_handle);
    }
  }
  
//  return 0; (prevent unreachable code warning)
}

int game_main(void)
{
  ThreadInfo thread_info[4];
  
  uint32_t starting_active_threads = 0;
  SDL_sem* semaphore_handle = SDL_CreateSemaphore(starting_active_threads);
  
  for (int thread_index = 0; thread_index < ARRAY_COUNT(thread_info) - 1; ++thread_index) {
    thread_info[thread_index] = { .logical_thread_index = thread_index, .semaphore_handle = semaphore_handle };
    SDL_Thread* thread = SDL_CreateThread(thread_function, NULL, &thread_info);
  }
  
  push_string(queue, "string 0");
  push_string(queue, "string 1");
  push_string(queue, "string 2");
  push_string(queue, "string 3");
  push_string(queue, "string 4");
  
  complete_all_work(queue);
  
  return 0;
}

void complete_all_work(WorkQueue* queue)
{
  WorkQueueEntry entry;
  while (queue->entry_count != queue->entry_completion_count) {
    do_next_queue_work_entry(queue);
  }
}

/*************************************************************************
ABSTRACT WORK QUEUE
*************************************************************************/
typedef struct {
  volatile size_t entry_count;
  volatile size_t next_entry_to_do;
  volatile size_t entry_completion_count;
  SDL_sem* semaphore_handle;
  WorkQueueEntryStorage entries[256];
} WorkQueue;

void do_next_work_queue_entry(WorkQueue* queue)
{
  int original_next_entry_to_do = queue->next_entry_to_do;
  if (queue->next_entry_to_do < queue->entry_count) { // SDL_AtomicGet() perhaps
    int entry_index = InterlockedCompareExchange(&queue->next_entry_to_do, original_next_entry_to_do + 1, original_next_entry_to_do);
    if (entry_index == original_next_entry_to_do) { 
      result.data = queue->entries[index].usr_ptr;
      result.is_valid = true;
      COMPLETE_PAST_READS_BEFORE_FUTURE_READS;
      InterlockedIncrement(&queue->entry_completion_count);
    } else {
      // another thread beaten to increment
    }
  }
  
  return result;
}

#define WORK_QUEUE_CALLBACK(name) void name(WorkQueue* queue, void* data)
// can now do: INTERNAL WORK_QUEUE_CALLBACK(render_work) {}
typedef void (*work_queue_callback)(WorkQueue* queue, void* data);

void add_entry(WorkQueue* queue, work_queue_callback callback, void* data)
{
  WorkQueueEntry* entry = queue->entries[queue->entry_count];
  entry->callback = callback;
  entry->data = data;
  WRITE_BARRIER;
  ++queue->entry_count;
  SDL_SemWait(queue->semaphore_handle);
}

INTERNAL bool queue_work_still_in_progress(WorkQueue* queue) // public
{
  return queue->entry_completion_count != queue->entry_count;
}

INTERNAL void thread_work(WorkQueueEntry* entry, int thread_index)
{     
   assert(entry->is_valid);
   puts((const char *)entry->data);
}

INTERNAL int thread_function(void* thread_param)
{
  ThreadInfo* thread_info = (ThreadInfo *)thread_param;
  
  while (true) {
    if (do_next_work_queue_entry(queue)) {
      SDL_SemWait(thread_info->semaphore_handle);
    }
  }
  
//  return 0; (prevent unreachable code warning)
}

INTERNAL size_t get_next_available_work_queue_index(Queue* work_queue)
{
    return queue->entry_count;
}

INTERNAL void push_string(WorkQueue* queue, const char* str)
{
    add_work_queue_entry(queue, str);
}




