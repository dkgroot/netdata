--- collectors/proc.plugin/ipc.c.orig	2019-06-07 23:55:38.815066000 +0200
+++ collectors/proc.plugin/ipc.c	2019-06-07 23:56:26.455542000 +0200
@@ -2,10 +2,17 @@
 
 #include "plugin_proc.h"
 
+#ifdef __DragonFly__
+#define _KERNEL_STRUCTURES
+#define SEM_INFO 0
+#endif
 #include <sys/sem.h>
 #include <sys/msg.h>
 #include <sys/shm.h>
 
+#ifdef __DragonFly__
+#undef _KERNEL_STRUCTURES
+#endif
 
 #ifndef SEMVMX
 #define SEMVMX  32767  /* <= 32767 semaphore maximum value */
@@ -44,6 +51,7 @@
  *  would also define it.
  */
 #ifndef HAVE_UNION_SEMUN
+#if !defined(__DragonFly__)
 /* according to X/OPEN we have to define it ourselves */
 union semun {
     int val;
@@ -52,6 +60,7 @@
     struct seminfo *__buf;
 };
 #endif
+#endif
 
 struct message_queue {
     unsigned long long id;
