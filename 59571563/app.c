// gcc -Wall app.c

#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

volatile sig_atomic_t g_process_run = 1;

void signal_handler(int signal) { g_process_run = 0; }

int child_process(int *pipe) {
  close(pipe[0]); // close read pipe
  srand(1234);
  int chars_to_send[] = {95, 97, 99, 100, 101, 103, 104, 105,
                         95, 97, 99, 100, 101, 103, 104, 105};
  // int chars_to_send[] = {6, 7, 8, 9,12,14,15,16};
  int fd = open("a.txt", O_RDONLY);
  if (fd == -1) {
    printf("Child: can't open file\n");
    return -1;
  }
  struct stat sb;
  if (fstat(fd, &sb) == -1) {
    printf("Child: can't get file stat\n");
    return -1;
  }
  off_t file_size = sb.st_size;
  char *addr = mmap(NULL, file_size, PROT_READ, MAP_PRIVATE, fd, 0);
  if (addr == MAP_FAILED) {
    printf("Child:mmap failed");
    return -1;
  }
  int start_address = 0;
  while (g_process_run != 0) {
    long index = rand();
    index = (index * 16) / RAND_MAX;
    int len = chars_to_send[index];
    if (start_address + len > file_size) {
      start_address = 0;
    }
    len = write(pipe[1], &addr[start_address], len);
    start_address = start_address + len;
    sleep(1);
  }
  munmap(addr, file_size);
  close(fd);
  close(pipe[1]);
  printf("child process exiting\n");
  return 0;
}
int parent_process(int *pipe) {
  close(pipe[1]); // close write pipe
  const int BUFF_SIZE = 99;
  char buff[BUFF_SIZE + 1];
  char buff_temp[10];
  int continueCount = 0;
  while (g_process_run != 0) {
    int len = read(pipe[0], &buff[continueCount],
                   BUFF_SIZE - continueCount) +
              continueCount; // addjust buffer position and size based
                             // on previous partial utf-8 sequence
    continueCount = 0;
    for (int i = len - 1; i > -1;
         --i) { // find and save if last sequence are partial utf-8
      if (0 != (0x80 & buff[i])) {
        buff_temp[continueCount] = buff[i];
        buff[i] = '\0';
        continueCount++;
      } else {
        break;
      }
    }
    buff[len] = '\0';
    printf("Parent:%s\n", buff);
    if (continueCount > 0) { // put partial utf-8 sequence to start of buffer,
                             // so it will prepend in next read cycle.
      printf("will resume with %d partial bytes\n", continueCount);
      for (int i = 0; i < continueCount; ++i) {
        buff[i] = buff_temp[continueCount - i - 1];
      }
    }
  }
  close(pipe[0]);
  wait(NULL);
  printf("parent process exiting\n");
  return 0;
}
int init_signal() {
  if (signal(SIGINT, signal_handler) == SIG_ERR) {
    return -1;
  }
  return 0;
}

int main(int argc, char **argv) {
  if (init_signal() != 0)
    return -1;
  int pipefd[2];
  if (pipe(pipefd) == -1) {
    printf("can't create pipe\n");
    return -1;
  }
  pid_t pid = fork();
  if (pid == -1) {
    printf("Can't fork process\n");
    return -1;
  } else if (pid == 0) { // child process
    return child_process(pipefd);
  }
  return parent_process(pipefd);
}
