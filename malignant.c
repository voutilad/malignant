/*
 * Linux Kernel module to making it easier to screw with hypervisors.
 *
 * Copyright (c) 2023 Dave Voutila <voutilad@gmail.com>
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/init.h>
#include <linux/kernel.h>

static int __init malignant_init(void);
static void __exit malignant_exit(void);

static int __init malignant_init(void)
{
	printk(KERN_INFO "%s\n", __func__);

	return 0;
}

static void __exit malignant_exit(void)
{
	printk(KERN_INFO "%s\n", __func__);
}

static int com1 = 0;

static int get_com1(char *buffer, const struct kernel_param *kp)
{
	*buffer = '\0';
	return 1;
}

static int set_com1(const char *val, const struct kernel_param *kp)
{
	if (strcmp(val, "bad\n") == 0) {
		printk(KERN_INFO "got bad!\n");
	} else {
		printk(KERN_INFO "not bad.\n");
	}

	return 0;
}

static const struct kernel_param_ops com1_param_ops = {
	.set = set_com1,
	.get = get_com1,
};

module_param_cb(com1, &com1_param_ops, &com1, 0664);

module_init(malignant_init);
module_exit(malignant_exit);

MODULE_LICENSE("ISC");
MODULE_DESCRIPTION("Malignant Kernel Module");
MODULE_AUTHOR("Dave Voutila <dv@openbsd.org>");
