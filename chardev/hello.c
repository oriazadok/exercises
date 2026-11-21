#include <linux/module.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>

#define DEV_NAME "hello_dev"
#define CLASS_NAME "hello_class"
#define DEV_COUNT 1

static dev_t hello_devt;
static struct cdev hello_cdev;
static struct class *hello_class;
static struct device *hello_device;

static const struct file_operations hello_fops = {
	.owner = THIS_MODULE,
};

static int __init hello_init(void) {

	int ret;

	// Get a device number
	ret = alloc_chrdev_region(&hello_devt, 0, DEV_COUNT, DEV_NAME);
	if (ret < 0) {
		pr_err("alloc_chrdev_region failed: %d\n", ret);
		return ret;
	}

	// Link the number to our file_operations
	cdev_init(&hello_cdev, &hello_fops);
	hello_cdev.owner = THIS_MODULE;

	ret = cdev_add(&hello_cdev, hello_devt ,DEV_COUNT);
	if (ret < 0) {
		pr_err("cdev_add failed: %d\n", ret);
		unregister_chrdev_region(hello_devt, DEV_COUNT);
		return ret;
	}

	// Create the class
	hello_class = class_create(CLASS_NAME);
	if(IS_ERR(hello_class)) {
		cdev_del(&hello_cdev);
		unregister_chrdev_region(hello_devt, DEV_COUNT);
		return PTR_ERR(hello_class);
	}

	// Create the device
	hello_device = device_create(hello_class, NULL, hello_devt, NULL, DEV_NAME);
	if(IS_ERR(hello_device)) {
		class_destroy(hello_class);
		cdev_del(&hello_cdev);
		unregister_chrdev_region(hello_devt, DEV_COUNT);
		return PTR_ERR(hello_class);
	}

	pr_info("hello: /dev/%s created,  major=%d minor=%d\n", 
		DEV_NAME, MAJOR(hello_devt), MINOR(hello_devt));
	
	
	return 0;
}

static void __exit hello_exit(void) {
	device_destroy(hello_class, hello_devt);
	class_destroy(hello_class);
	cdev_del(&hello_cdev);
	unregister_chrdev_region(hello_devt, DEV_COUNT);
	pr_info("Bye bye world!\n");
}


MODULE_LICENSE("GPL");

module_init(hello_init);
module_exit(hello_exit);



