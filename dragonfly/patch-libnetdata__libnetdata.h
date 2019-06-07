--- libnetdata/libnetdata.h.orig	2019-06-07 23:55:57.725255000 +0200
+++ libnetdata/libnetdata.h	2019-06-07 23:56:19.485473000 +0200
@@ -30,9 +30,13 @@
 
 #else /* !defined(ENABLE_JEMALLOC) && !defined(ENABLE_TCMALLOC) */
 
+#if defined(__DragonFly__)
+#include <sys/malloc.h>
+#else
 #if !(defined(__FreeBSD__) || defined(__APPLE__))
 #include <malloc.h>
 #endif /* __FreeBSD__ || __APPLE__ */
+#endif /* __DragonFly__ */
 
 #endif /* !defined(ENABLE_JEMALLOC) && !defined(ENABLE_TCMALLOC) */
 
@@ -80,7 +84,7 @@
 #include <sys/un.h>
 #include <time.h>
 #include <unistd.h>
-#include <uuid/uuid.h>
+//#include <uuid/uuid.h>
 
 #ifdef HAVE_NETINET_IN_H
 #include <netinet/in.h>
