#include <linux/kernel.h>
#include <linux/module.h>
#include <asm/uaccess.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/proc_fs.h>
#include <linux/pid.h>

int pid = 1;
module_param(pid, int, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);

struct pid* pid_struct;
struct task_struct* task_list;

int proc_read() {
    int len = 0;
    pid_struct = find_get_pid(pid);
    if (pid_struct == NULL) pr_info("Null pid found!!\n");
    else {
        task_list = pid_task(pid_struct, PIDTYPE_PID);
        pr_info("%d\n%d\n%d\n", pid, task_list->cred->uid, task_list->cred->gid);
    }
    return len;
}

int read_init(void) {
    proc_read();
    return 0;
}

void clean_init(void) {
    pr_info("No cleanup necessary\n");
}

MODULE_LICENSE("GPL");
module_init(read_init);
module_exit(clean_init);
