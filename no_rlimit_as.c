/*
Copyright (C) 2025 Daniel Hast

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
the Software, and to permit persons to whom the Software is furnished to do so,
subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#include <dlfcn.h>
#include <stddef.h>
#include <sys/resource.h>
#include <sys/types.h>

int setrlimit(int resource, const struct rlimit *rlim) {
    if (resource == RLIMIT_AS) {
        return 0;
    }
    int (*real_setrlimit)(int, const struct rlimit*) = dlsym(RTLD_NEXT, "setrlimit");
    return real_setrlimit(resource, rlim);
}

#ifdef __USE_LARGEFILE64
int setrlimit64(int resource, const struct rlimit64 *rlim) {
    if (resource == RLIMIT_AS) {
        return 0;
    }
    int (*real_setrlimit64)(int, const struct rlimit64*) = dlsym(RTLD_NEXT, "setrlimit64");
    return real_setrlimit64(resource, rlim);
}
#endif

#ifdef _GNU_SOURCE
int prlimit(pid_t pid, int resource, const struct rlimit *new_limit, struct rlimit *old_limit) {
    int (*real_prlimit)(pid_t, int, const struct rlimit*, struct rlimit*) = dlsym(RTLD_NEXT, "prlimit");
    if (resource == RLIMIT_AS) {
        return real_prlimit(pid, resource, NULL, old_limit);
    }
    return real_prlimit(pid, resource, new_limit, old_limit);
}

#ifdef __USE_LARGEFILE64
int prlimit64(pid_t pid, int resource, const struct rlimit64 *new_limit, struct rlimit64 *old_limit) {
    int (*real_prlimit64)(pid_t, int, const struct rlimit64*, struct rlimit64*) = dlsym(RTLD_NEXT, "prlimit64");
    if (resource == RLIMIT_AS) {
        return real_prlimit64(pid, resource, NULL, old_limit);
    }
    return real_prlimit64(pid, resource, new_limit, old_limit);
}
#endif
#endif
