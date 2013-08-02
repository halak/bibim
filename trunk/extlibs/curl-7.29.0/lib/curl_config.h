#ifndef HEADER_CURL_CONFIG_H
#define HEADER_CURL_CONFIG_H

/* ================================================================ */
/*               Hand crafted config file for Android               */
/* ================================================================ */

/* ---------------------------------------------------------------- */
/*                          HEADER FILES                            */
/* ---------------------------------------------------------------- */

/* Define if you have the <arpa/inet.h> header file. */
#define HAVE_ARPA_INET_H 1 */

/* Define if you have the <assert.h> header file. */
#define HAVE_ASSERT_H 1

/* Define if you have the <crypto.h> header file. */
/* #define HAVE_CRYPTO_H 1 */

#define HAVE_PERROR 1
#define HAVE_PIPE 1
#define HAVE_POLL 1

#define HAVE_GETADDRINFO 1
#define HAVE_FREEADDRINFO 1

#define HAVE_PWD_H 1

/* Define if you have the <errno.h> header file. */
#define HAVE_ERRNO_H 1

/* Define if you have the <err.h> header file. */
#define HAVE_ERR_H 1 */

/* Define if you have the <fcntl.h> header file. */
#define HAVE_FCNTL_H 1

/* Define to 1 if you have a working fcntl O_NONBLOCK function. */
#define HAVE_FCNTL_O_NONBLOCK 1

/* Define if you have the <getopt.h> header file. */
#define HAVE_GETOPT_H 1

/* Define if you have the <io.h> header file. */
/* #define HAVE_IO_H 1 */

/* Define if you have the <limits.h> header file. */
#define HAVE_LIMITS_H 1

/* Define if you have the <locale.h> header file. */
#define HAVE_LOCALE_H 1

/* Define if you have the <netdb.h> header file. */
#define HAVE_NETDB_H 1

/* Define if you have the <netinet/in.h> header file. */
#define HAVE_NETINET_IN_H 1

/* Define if you have the <process.h> header file. */
/* #define HAVE_PROCESS_H 1 */

/* Define if you have the <signal.h> header file. */
#define HAVE_SIGNAL_H 1

/* Define if you have the <sgtty.h> header file. */
/* #define HAVE_SGTTY_H 1 */

/* Define if you have the <ssl.h> header file. */
/* #define HAVE_SSL_H 1 */

/* Define if you have the <stdlib.h> header file. */
#define HAVE_STDLIB_H 1

/* Define if you have the <sys/param.h> header file. */
#define HAVE_SYS_PARAM_H 1

/* Define if you have the <sys/select.h> header file. */
#define HAVE_SYS_SELECT_H 1

/* Define if you have the <sys/socket.h> header file. */
#define HAVE_SYS_SOCKET_H 1

/* Define if you have the <sys/sockio.h> header file. */
/* #define HAVE_SYS_SOCKIO_H 1 */

/* Define if you have the <sys/stat.h> header file. */
#define HAVE_SYS_STAT_H 1

/* Define if you have the <sys/time.h> header file. */
#define HAVE_SYS_TIME_H 1

/* Define if you have the <sys/types.h> header file. */
#define HAVE_SYS_TYPES_H 1

/* Define if you have the <sys/utime.h> header file. */
/* #define HAVE_SYS_UTIME_H 1 */

/* Define if you have the <termio.h> header file. */
/* #define HAVE_TERMIO_H 1 */

/* Define if you have the <termios.h> header file. */
/* #define HAVE_TERMIOS_H 1 */

/* Define to 1 if you have the <sys/uio.h> header file. */
#define HAVE_SYS_UIO_H 1

/* Define to 1 if you have the <sys/un.h> header file. */
#define HAVE_SYS_UN_H 1

/* Define to 1 if you have the <sys/utime.h> header file. */
#define HAVE_SYS_UTIME_H 1

/* Define to 1 if you have the <termios.h> header file. */
#define HAVE_TERMIOS_H 1

/* Define to 1 if you have the <termio.h> header file. */
/* #undef HAVE_TERMIO_H */

/* Define to 1 if you have the <time.h> header file. */
#define HAVE_TIME_H 1

/* Define if you have the <unistd.h> header file. */
#define HAVE_UNISTD_H 1

/* ---------------------------------------------------------------- */
/*                        OTHER HEADER INFO                         */
/* ---------------------------------------------------------------- */

/* Define if sig_atomic_t is an available typedef. */
#define HAVE_SIG_ATOMIC_T 1

/* Define if you have the ANSI C header files. */
#define STDC_HEADERS 1

/* Define if you can safely include both <sys/time.h> and <time.h>. */
#define TIME_WITH_SYS_TIME 1

/* ---------------------------------------------------------------- */
/*                             FUNCTIONS                            */
/* ---------------------------------------------------------------- */

/* Define if you have the closesocket function. */
/* #define HAVE_CLOSESOCKET 1 */

/* Define if you don't have vprintf but do have _doprnt. */
/* #define HAVE_DOPRNT 1 */

/* Define if you have the ftruncate function. */
#define HAVE_FTRUNCATE 1

/* Define if you have the gethostbyaddr function. */
#define HAVE_GETHOSTBYADDR 1

/* Define if you have the gethostname function. */
#define HAVE_GETHOSTNAME 1

/* Define if you have the getpass function. */
#define HAVE_GETPASS 1

/* Define if you have the getservbyname function. */
#define HAVE_GETSERVBYNAME 1

/* Define if you have the getprotobyname function. */
#define HAVE_GETPROTOBYNAME

/* Define if you have the gettimeofday function. */
#define HAVE_GETTIMEOFDAY 1

/* Define if you have the inet_addr function. */
#define HAVE_INET_ADDR 1

/* Define if you have the ioctlsocket function. */
/* #define HAVE_IOCTLSOCKET 1 */

/* Define if you have a working ioctlsocket FIONBIO function. */
/* #define HAVE_IOCTLSOCKET_FIONBIO 1 */

/* Define if you have the perror function. */
#define HAVE_PERROR 1

/* Define if you have the RAND_screen function when using SSL. */
#define HAVE_RAND_SCREEN 1

/* Define if you have the `RAND_status' function when using SSL. */
#define HAVE_RAND_STATUS 1

/* Define if you have the `CRYPTO_cleanup_all_ex_data' function.
   This is present in OpenSSL versions after 0.9.6b */
#define HAVE_CRYPTO_CLEANUP_ALL_EX_DATA 1

/* Define if you have the select function. */
#define HAVE_SELECT 1

/* Define if you have the setlocale function. */
#define HAVE_SETLOCALE 1

/* Define if you have the setmode function. */
#define HAVE_SETMODE 1

/* Define if you have the setvbuf function. */
#define HAVE_SETVBUF 1

/* Define if you have the socket function. */
#define HAVE_SOCKET 1

/* Define if you have the strcasecmp function. */
#define HAVE_STRCASECMP 1

/* Define if you have the strdup function. */
#define HAVE_STRDUP 1

/* Define if you have the strftime function. */
#define HAVE_STRFTIME 1

/* Define if you have the stricmp function. */
#define HAVE_STRICMP 1

/* Define if you have the strncasecmp function. */
#define HAVE_STRNCASECMP 1

/* Define if you have the strnicmp function. */
#define HAVE_STRNICMP 1

/* Define if you have the strstr function. */
#define HAVE_STRSTR 1

/* Define if you have the strtoll function. */
#define HAVE_STRTOLL 1

/* Define if you have the tcgetattr function. */
#define HAVE_TCGETATTR 1

/* Define if you have the tcsetattr function. */
#define HAVE_TCSETATTR 1

/* Define if you have the utime function. */
#define HAVE_UTIME 1

/* Define to the type qualifier of arg 1 for getnameinfo. */
#define GETNAMEINFO_QUAL_ARG1 const

/* Define to the type of arg 1 for getnameinfo. */
#define GETNAMEINFO_TYPE_ARG1 struct sockaddr *

/* Define to the type of arg 2 for getnameinfo. */
#define GETNAMEINFO_TYPE_ARG2 socklen_t

/* Define to the type of args 4 and 6 for getnameinfo. */
#define GETNAMEINFO_TYPE_ARG46 size_t

/* Define to the type of arg 7 for getnameinfo. */
#define GETNAMEINFO_TYPE_ARG7 int

/* Define if you have the recv function. */
#define HAVE_RECV 1

/* Define to the type of arg 1 for recv. */
#define RECV_TYPE_ARG1 int

/* Define to the type of arg 2 for recv. */
#define RECV_TYPE_ARG2 void *

/* Define to the type of arg 3 for recv. */
#define RECV_TYPE_ARG3 size_t

/* Define to the type of arg 4 for recv. */
#define RECV_TYPE_ARG4 int

/* Define to the function return type for recv. */
#define RECV_TYPE_RETV ssize_t

/* Define if you have the recvfrom function. */
#define HAVE_RECVFROM 1

/* Define to the type of arg 1 for recvfrom. */
#define RECVFROM_TYPE_ARG1 int

/* Define to the type pointed by arg 2 for recvfrom. */
#define RECVFROM_TYPE_ARG2 void

/* Define to the type of arg 3 for recvfrom. */
#define RECVFROM_TYPE_ARG3 size_t

/* Define to the type of arg 4 for recvfrom. */
#define RECVFROM_TYPE_ARG4 int

/* Define to the type pointed by arg 5 for recvfrom. */
#define RECVFROM_TYPE_ARG5 struct sockaddr

/* Define to the type pointed by arg 6 for recvfrom. */
#define RECVFROM_TYPE_ARG6 socklen_t

/* Define to the function return type for recvfrom. */
#define RECVFROM_TYPE_RETV ssize_t

/* Define if you have the send function. */
#define HAVE_SEND 1

/* Define to the type of arg 1 for send. */
#define SEND_TYPE_ARG1 int

/* Define to the type qualifier of arg 2 for send. */
#define SEND_QUAL_ARG2 const

/* Define to the type of arg 2 for send. */
#define SEND_TYPE_ARG2 void *

/* Define to the type of arg 3 for send. */
#define SEND_TYPE_ARG3 size_t

/* Define to the type of arg 4 for send. */
#define SEND_TYPE_ARG4 int

/* Define to the function return type for send. */
#define SEND_TYPE_RETV ssize_t

/* ---------------------------------------------------------------- */
/*                       TYPEDEF REPLACEMENTS                       */
/* ---------------------------------------------------------------- */

/* Define to the return type of signal handlers (int or void). */
#define RETSIGTYPE void

/* ---------------------------------------------------------------- */
/*                            TYPE SIZES                            */
/* ---------------------------------------------------------------- */

/* Define to the size of `int', as computed by sizeof. */
#define SIZEOF_INT 4

#define SIZEOF_LONG 4

/* Define to the size of `long double', as computed by sizeof. */
#define SIZEOF_LONG_DOUBLE 12

/* Define to the size of `long long', as computed by sizeof. */
#define SIZEOF_LONG_LONG 8

/* Define to the size of `short', as computed by sizeof. */
#define SIZEOF_SHORT 2

/* Define to the size of `size_t', as computed by sizeof. */
#define SIZEOF_SIZE_T 4

/* ---------------------------------------------------------------- */
/*                          STRUCT RELATED                          */
/* ---------------------------------------------------------------- */

/* Define if you have struct sockaddr_storage. */
#define HAVE_STRUCT_SOCKADDR_STORAGE 1

/* Define if you have struct timeval. */
#define HAVE_STRUCT_TIMEVAL 1

/* Define if struct sockaddr_in6 has the sin6_scope_id member. */
#define HAVE_SOCKADDR_IN6_SIN6_SCOPE_ID 1

/* ---------------------------------------------------------------- */
/*                        COMPILER SPECIFIC                         */
/* ---------------------------------------------------------------- */

/* Define to nothing if compiler does not support 'const' qualifier. */
/* #define const */

/* Define to nothing if compiler does not support 'volatile' qualifier. */
/* #define volatile */

/* Windows should not have HAVE_GMTIME_R defined */
/* #undef HAVE_GMTIME_R */

/* Define if the compiler supports C99 variadic macro style. */
#define HAVE_VARIADIC_MACROS_C99 1

/* gcc variadic macros */
#define HAVE_VARIADIC_MACROS_GCC 1

/* Define if the compiler supports the 'long long' data type. */
#define HAVE_LONGLONG 1

#define SIZEOF_TIME_T 4

/* ---------------------------------------------------------------- */
/*                       DNS RESOLVER SPECIALTY                     */
/* ---------------------------------------------------------------- */

/*
 * Undefine both USE_ARES and USE_THREADS_WIN32 for synchronous DNS.
 */

/* Define to enable c-ares asynchronous DNS lookups. */
/* #define USE_ARES 1 */

/* Define to enable threaded asynchronous DNS lookups. */
/* #define USE_THREADS_WIN32 1 */

#if defined(USE_ARES) && defined(USE_THREADS_WIN32)
#  error "Only one DNS lookup specialty may be defined at most"
#endif

/* ---------------------------------------------------------------- */
/*                           LDAP SUPPORT                           */
/* ---------------------------------------------------------------- */

#define CURL_DISABLE_LDAP 1
#define CURL_DISABLE_LDAPS 1

/* ---------------------------------------------------------------- */
/*                       ADDITIONAL DEFINITIONS                     */
/* ---------------------------------------------------------------- */

/* Define cpu-machine-OS */
#undef OS
#define OS "arm-android-linux"

/* Name of package */
#define PACKAGE "curl"

/* If you want to build curl with the built-in manual */
#define USE_MANUAL 1

#define ENABLE_IPV6 1

#endif /* HEADER_CURL_CONFIG_H */