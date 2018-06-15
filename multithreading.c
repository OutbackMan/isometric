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
  char* string_to_print;
} WorkQueueEntry;

GLOBAL uint32_t volatile entry_completion_count = 0;
GLOBAL uint32_t volatile next_entry_to_do = 0;
GLOBAL uint32_t volatile entry_count = 0;
WorkQueueEntry entries[256];

static void push_string(SDL_Sem* semaphore_handle, const char* str)
{
  SDL_assert(entry_count < array_count(entries));
  // threads may read data before it is written (compiler may move the increment before for optimisation)
  entries[entry_count].string_to_print = str;
  
  COMPLETE_PAST_WRITES_BEFORE_FUTURE_WRITES;
  
  ++entry_count;
  
  SDL_SemPost(semaphore_handle);
}

typedef struct {
  SDL_sem* semaphore_handle;
  int logical_thread_index;
} TheadInfo;

INTERNAL int thread_function(void* thread_param)
{
  ThreadInfo* thread_info = (ThreadInfo *)thread_param;
 
  while (true) {
    if (next_entry_to_do < entry_count) {
      int entry_index = InterlockedIncrement(&next_entry_to_do) - 1; // just use SDL_Lock()
      COMPLETE_PAST_READS_BEFORE_FUTURE_READS;
      puts(entries[entry_index]);
      
      InterlockedIncrement(&entry_completion_count);
    } else {
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
  
  for (int thread_index = 0; thread_index < ARRAY_COUNT(thread_info); ++thread_index) {
    thread_info[thread_index] = { .logical_thread_index = thread_index, .semaphore_handle = semaphore_handle };
    SDL_Thread* thread = SDL_CreateThread(thread_function, NULL, &thread_info);
  }
  
  push_string(semaphore_handle, "string 0");
  push_string(semaphore_handle, "string 1");
  push_string(semaphore_handle, "string 2");
  push_string(semaphore_handle, "string 3");
  push_string(semaphore_handle, "string 4");
  
  while (entry_count != entry_completion_count); // wait till all work has been done

  return 0;
}
