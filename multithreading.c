// logical cores, processes memory map, threads execution granularity
// 1. what work? 2. communicate?
// c language doesn't provide anything that can garuntee threads don't overlap. x64 provides the instructions
// to do so, e.g. locked exchange, locked compare exchange
// also have to worry about multiple writes
// cores read in memory on cache line boundaries, so two cores could be operating on the same cache line, resulting in possible overwrites
// as compiler doesn't know about threads, may have to use 'volatile' so it doesn't perform certain optimisations

#define COMPLETE_PAST_WRITES_BEFORE_FUTURE_WRITES _WriteBarrier(); __mm_sfence() // fence is cpu intrinsic, not necessary for intel
#define COMPLETE_PAST_READS_BEFORE_FUTURE_READS _ReadBarrier()

typedef struct {
  void* user_ptr;
} WorkQueueEntryStorage;

GLOBAL uint32_t volatile entry_completion_count = 0;
GLOBAL uint32_t volatile next_entry_to_do = 0;
GLOBAL uint32_t volatile entry_count = 0;
WorkQueueEntry entries[256];

static void push_string(SDL_Sem* semaphore_handle, const char* str)
{
  SDL_assert(entry_count < array_count(entries));
  
  entries[entry_count].string_to_print = str;
  
  COMPLETE_PAST_WRITES_BEFORE_FUTURE_WRITES;
  
  ++entry_count;
  
  SDL_SemPost(semaphore_handle);
}

typedef struct {
  int logical_thread_index;
} TheadInfo;

inline bool thread_work()
{     
  bool has_done_work = false;
  if (next_entry_to_do < entry_count) { // SDL_AtomicGet() perhaps
    int entry_index = InterlockedIncrement(&next_entry_to_do) - 1; // just use SDL_Lock()
    COMPLETE_PAST_READS_BEFORE_FUTURE_READS;
    puts(entries[entry_index]);
      
    InterlockedIncrement(&entry_completion_count);
    has_done_work = true;
  }
  
  return has_done_work;
}

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
  
  WorkQueueEntry entry;
  while (queue_work_still_in_progress(queue)) {
    entry = complete_and_get_next_work_queue_entry();
    if (entry.is_valid) {
       do_thread_work(entry, total_threads - 1); 
    }
  }

  return 0;
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

INTERNAL void add_work_queue_entry(WorkQueue* queue, void* ptr) // public
{
  queue->entries[queue->entry_count].user_ptr = ptr;
  ++queue->entry_count;
  SDL_SemWait(queue->semaphore_handle);
}

typedef struct {
  void* data;
  size_t index;
} WorkQueueItem;

INTERNAL WorkQueueItem complete_and_get_next_work_queue_item(WorkQueue* queue, WorkQueueEntry* completed) // public
{
  WorkQueueItem result;
  result.is_valid = false;
  
  if (completed->is_valid) {
    InterlockedIncrement(&queue->entry_completion_count);
  }
    
  if (next_entry_to_do < entry_count) { // SDL_AtomicGet() perhaps
    int entry_index = InterlockedIncrement(&queue->next_entry_to_do) - 1; // just use SDL_Lock()
    result.data = queue->entries[index].usr_ptr;
    result.is_valid = true;
    COMPLETE_PAST_READS_BEFORE_FUTURE_READS;
  }
  
  return result;
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
 
  WorkQueueEntry* entry;
  while (true) {
    entry = complete_and_get_next_work_queue_entry(queue, entry);
    if (entry->is_valid) {
        thread_work(entry, thread_info->thread_index);
    } else {
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




