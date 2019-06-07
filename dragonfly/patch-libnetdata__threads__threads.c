--- libnetdata/threads/threads.c.orig	2019-06-07 23:56:12.755405000 +0200
+++ libnetdata/threads/threads.c	2019-06-07 23:56:16.365442000 +0200
@@ -26,7 +26,7 @@
 // compatibility library functions
 
 pid_t gettid(void) {
-#ifdef __FreeBSD__
+#if defined(__FreeBSD__) || defined(__DragonFly__)
 
     return (pid_t)pthread_getthreadid_np();
 
@@ -44,7 +44,7 @@
 
     return (pid_t)syscall(SYS_gettid);
 
-#endif /* __FreeBSD__, __APPLE__*/
+#endif /* __FreeBSD__, __APPLE__, __DragonFly__*/
 }
 
 // ----------------------------------------------------------------------------
