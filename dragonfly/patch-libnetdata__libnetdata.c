--- libnetdata/libnetdata.c.orig	2019-06-07 23:55:52.835206000 +0200
+++ libnetdata/libnetdata.c	2019-06-07 23:56:22.435502000 +0200
@@ -5,10 +5,10 @@
 #ifdef __APPLE__
 #define INHERIT_NONE 0
 #endif /* __APPLE__ */
-#if defined(__FreeBSD__) || defined(__APPLE__)
+#if defined(__FreeBSD__) || defined(__APPLE__) || defined(__DragonFly__)
 #    define O_NOATIME     0
 #    define MADV_DONTFORK INHERIT_NONE
-#endif /* __FreeBSD__ || __APPLE__*/
+#endif /* __FreeBSD__ || __APPLE__ || __DragonFly__*/
 
 struct rlimit rlimit_nofile = { .rlim_cur = 1024, .rlim_max = 1024 };
 int enable_ksm = 1;
@@ -1179,7 +1179,7 @@
 
 static int is_virtual_filesystem(const char *path, char **reason) {
 
-#if defined(__APPLE__) || defined(__FreeBSD__)
+#if defined(__APPLE__) || defined(__FreeBSD__) || defined(__DragonFly__)
     (void)path;
     (void)reason;
 #else
