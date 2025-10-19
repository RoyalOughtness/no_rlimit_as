# no_rlimit_as

**no_rlimit_as** is a shared library that, when preloaded, modifies the C
standard library function `setrlimit` to make it a no-op when called with
`RLIMIT_AS`. The Linux-specific function `prlimit` and the variants
`setrlimit64` and `prlimit64` are similarly modified.

This prevents processes from reducing their own available address space (virtual
memory). Some programs use `setrlimit` to reduce their address space as a way of
limiting memory usage. However, this is incompatible with security measures that
rely on having a large address space available, such as hardened memory
allocators like [hardened_malloc] and [PartitionAlloc].

There are other, more modern methods of restricting the memory available to a
process on Linux, such as [cgroups]. However, no_rlimit_as may be useful as a
workaround for existing software that's incompatible with hardened memory
allocators due to use of `setrlimit`.

Please keep in mind that this is a tradeoff:

- On the one hand, being able to use hardened_malloc with software that would
  otherwise be incompatible with it provides substantial improvements in
  security against a wide range of memory-related exploits.
- On the other hand, if the software relies on `setrlimit` as a layer of
  protection against excessive memory usage, no_rlimit_as will remove that
  protection. It's possible that in some scenarios this could increase
  vulnerability to a denial-of-service attack through excessive memory usage.

[hardened_malloc]: https://github.com/GrapheneOS/hardened_malloc/
[PartitionAlloc]:
    https://chromium.googlesource.com/chromium/src/+/master/base/allocator/partition_allocator/PartitionAlloc.md
[cgroups]: https://www.kernel.org/doc/html/latest/admin-guide/cgroup-v2.html
