#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#ifndef WIN32

#define __symver_tag FOO

#define __symver(S, at, M, N) \
	__asm__ (".symver " __str(V(S, M, N)) "," __V(S, at, M, N));
#define __V(symbol, at, major, minor) \
	__str(symbol) at __str(__symver_tag) "_" __str(major) "." __str(minor)
#define __str(s) ___str(s)
#define ___str(s) #s

#ifndef GENMAP_PARSING_PASS
#define V(symbol, major, minor) \
	__ ## symbol ## _ ## major ## _ ## minor
#define compatible_version(symbol, major, minor) \
	__symver(symbol, "@", major, minor)
#define default_version(symbol, major, minor) \
	__symver(symbol, "@@", major, minor)
#define only_version(symbol, major, minor)
#endif

#else

#define V(symbol, major, minor) symbol
#define compatible_version(symbol, major, minor)
#define default_version(symbol, major, minor)
#define only_version(symbol, major, minor)

#endif

#ifndef WIN32
int V(foo_open, 0, 0)(const char *pathname, int flags)
{
	return open(pathname, flags);
}
compatible_version(foo_open, 0, 0)
#endif

int V(foo_open, 1, 0)(const char *pathname)
{
	return open(pathname, O_RDONLY);
}
default_version(foo_open, 1, 0)

#ifndef WIN32
int V(foo_open, 1, 1)(void)
{
	return open("/dev/zero", O_RDONLY);
}
compatible_version(foo_open, 1, 1)
#endif

#ifndef WIN32
ssize_t V(foo_write, 1, 1)(int fd, const void *buf, size_t count)
{
	return write(fd, buf, count);
}
compatible_version(foo_write, 1, 1)
#endif

ssize_t V(foo_write, 2, 0)(int fd)
{
	return write(fd, "foo", 3);
}
default_version(foo_write, 2, 0)

int foo_close(int fd)
{
	return close(fd);
}
only_version(foo_close, 3, 0)
