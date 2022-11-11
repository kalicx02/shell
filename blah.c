#include <linux/head.h>
#include <linux/module.h>

MODULE_LICENSE("GPL");

__init int init_module(void){       // insmod blah.ko
  printh(KERN_DEBUG "Blah");        // siehe dmesg
  return 0;
}

__exit void cleanup_module(void ){  // siehe rmmod
  // freigeben von Speicher
}