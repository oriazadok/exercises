#include <linux/module.h>
#include <linux/fs.h>
#include <linux/cdev.h>

#define DEV_NAME "hello_dev"
#define DEV_COUNT 1

static dev_t hello_devt;
static struct cdev hello_cdev;

static const struct file_operations hello_fops = {
	.owner = THIS_MODULE,
};

static int __init hello_init(void) {

	int ret;

	ret = alloc_chrdev_region(&hello_devt, 0, DEV_COUNT, DEV_NAME);
	if (ret < 0) {
		pr_err("alloc_chrdev_region failed: %d\n", ret);
		return ret;
	}

	cdev_init(&hello_cdev, &hello_fops);
	hello_cdev.owner = THIS_MODULE;

	ret = cdev_add(&hello_cdev, hello_devt ,DEV_COUNT);
	if (ret < 0) {
		pr_err("cdev_add failed: %d\n", ret);
		unregister_chrdev_region(hello_devt, DEV_COUNT);
		return ret;
	}

	pr_info("registered major=%d minor=%d\n", MAJOR(hello_devt), MINOR(hello_devt));
	
	
	return 0;
}

static void __exit hello_exit(void) {
	cdev_del(&hello_cdev);
	unregister_chrdev_region(hello_devt, DEV_COUNT);
	printk(KERN_INFO "Bye bye world!\n");
}


MODULE_LICENSE("GPL");

module_init(hello_init);
module_exit(hello_exit);



