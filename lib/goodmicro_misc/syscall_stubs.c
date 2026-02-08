// stubs of unimplemented syscalls, used to avoid warnings from libnosys

#pragma GCC diagnostic ignored "-Wmissing-prototypes"

int _close  (void){ return -1; }
int _fstat  (void){ return -1; }
int _getpid (void){ return -1; }
int _isatty (void){ return -1; }
int _kill   (void){ return -1; }
int _lseek  (void){ return -1; }
int _read   (void){ return -1; }
int _write  (void){ return -1; }

int _close_r  (void){ return -1; }
int _fstat_r  (void){ return -1; }
int _getpid_r (void){ return -1; }
int _isatty_r (void){ return -1; }
int _kill_r   (void){ return -1; }
int _lseek_r  (void){ return -1; }
int _read_r   (void){ return -1; }
int _write_r  (void){ return -1; }
