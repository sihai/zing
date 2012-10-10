/*
 * zing.c
 *
 *  Created on: Jan 24, 2012
 *      Author: sihai
 */

#include "type.h"
#include "asm.h"
#include "mm.h"

static void bootothers(void);
static void mpmain(void) __attribute__((noreturn));

/**
 * Bootstrap processor starts running C code here.
 */
int main(void)
{
	/**
	 * ld会生成如下几个变量用来标识程序的段
	 *
	 *  _etext(etext)	正文段结束后第一个地址
	 *	_edata(edata)	数据段结束后第一个地址
	 *	_end(end)		bss段结束后第一个地址
	 */
	extern char edata[], end[];

  /*	// clear BSS
  	memset(edata, 0, end - edata);

  	// collect info about this machine
  	mp_init();
  	lapic_init(mp_bcpu());

  	cprintf("\ncpu%d: starting myos\n\n", cpu());
	cprintf("Welcome to myos !\n");

	pinit();         // process table
	binit();         // buffer cache
	pic_init();      // interrupt controller
	ioapic_init();   // another interrupt controller

	kinit();         // physical memory allocator
	tvinit();        // trap vectors
	fileinit();      // file table
	iinit();         // inode cache
	console_init();  // I/O devices & their interrupts
	ide_init();      // disk
	if(!ismp)
			timer_init();  // uniprocessor timer
	userinit();      // first user process
	bootothers();    // start other processors

	// Finish setting up this processor in mpmain.
	mpmain();
*/}


// Bootstrap processor gets here after setting up the hardware.
// Additional processors start here.
static void
mpmain(void)
{
  /*cprintf("cpu%d: mpmain\n", cpu());
  idtinit();
  if(cpu() != mp_bcpu())
    lapic_init(cpu());
  setupsegs(0);
  xchg(&cpus[cpu()].booted, 1);

  cprintf("cpu%d: scheduling\n");
  scheduler();*/
}

static void
bootothers(void)
{
	extern uchar _binary____boot_x86_bootother_start[], _binary____boot_x86_bootother_size[];
	uchar *code;
	struct cpu *c;
	char *stack;

	// Write bootstrap code to unused memory at 0x7000.
	code = (uchar*)0x7000;
	/*memmove(code, _binary____boot_x86_bootother_start, (uint)_binary____boot_x86_bootother_size);

	for(c = cpus; c < cpus+ncpu; c++)
	{
		if(c == cpus+cpu())  // We've started already.
			continue;
		cprintf("Try to start cup:%d\n", c->apicid);
		// Fill in %esp, %eip and start code on cpu.
		stack = kalloc(KSTACKSIZE);
		*(void**)(code-4) = stack + KSTACKSIZE;
		*(void**)(code-8) = mpmain;
		lapic_startap(c->apicid, (uint)code);

		// Wait for cpu to get through bootstrap.
		while(c->booted == 0)
      ;
  }*/
}
