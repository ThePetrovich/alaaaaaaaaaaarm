#include <kernel/kernel.h>

int main(void)
{
	kernel_init();
	while (1)
	{
		asm volatile("nop"::);
		debug_printk("Idling in mah main\r\n");
	}
	return 0;
}