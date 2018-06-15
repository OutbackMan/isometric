// logical cores, processes memory map, threads execution granularity
// 1. what work? 2. communicate?
// c language doesn't provide anything that can garuntee threads don't overlap. x64 provides the instructions
// to do so, e.g. locked exchange, locked compare exchange
// also have to worry about multiple writes
// cores read in memory on cache line boundaries, so two cores could be operating on the same cache line, resulting in possible overwrites
// as compiler doesn't know about threads, may have to use 'volatile' so it doesn't perform certain optimisations

typedef struct {
  char* string_to_print;
} WorkQueueEntry;

GLOBAL uint32_t next_entry_to_do = 0;
GLOBAL uint32_t entry_count = 0;
WorkQueueEntry entries[256];

static void push_string(const char* str)
{
  // these writes not in order
  entries[entry_count++].string_to_print = str;
}

typedef struct {
  int logical_thread_index;
} TheadInfo;

INTERNAL int thread_function(void* thread_param)
{
  ThreadInfo* thread_info = (ThreadInfo *)thread_param;
 
  while (true) {
    if (next_entry_to_do < entry_count) {
      int entry_index = next_entry_to_do++; // not interlocked, not volatile
      
      // these reads are not in order
      puts(entries[entry_index]);
    }
  }
  
  return 0;
}

int game_main(void)
{
  ThreadInfo thread_info[4];
  for (int thread_index = 0; thread_index < 4; ++thread_index) {
    thread_info[thread_index] = { .logical_thread_index = thread_index };
    SDL_Thread* thread = SDL_CreateThread(thread_function, NULL, &thread_info);
  }
  
  push_string("string 0");
  push_string("string 1");
  push_string("string 2");
  push_string("string 3");
  push_string("string 4");

  return 0;
}
