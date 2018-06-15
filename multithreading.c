static int thread_function(void* data)
{
  while (global_is_running) {
    char* msg = (char *)data;
    puts(msg);
  } // as compiler doesn't know about threads, may have to use 'volatile' so it doesn't perform certain optimisations
  
  return 0;
}

int game_main(void)
{
  char* msg = "hello from the thread";
  SDL_Thread* thread = SDL_CreateThread(thread_function, "thread_name", msg);

  return 0;
}
