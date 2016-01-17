#include <stdio.h>
#include <alloc.h>
#include <dos.h>
#include <mem.h>
#include <conio.h>
#include "xms.h"

void main ()
{
	short 			temp, num;
	unsigned short 	us_temp;
	short			handle;
	EMMStruct		moveInfo;
	char 			*Mem_Buf;
	char			*Put_Buf;
	FILE			*f_Ptr, *f_Ptr_2;
	unsigned short	count = 0, i = 0;
	unsigned long   lock;

	f_Ptr   = fopen ("e:\\asm_work\\ega3.cpi", "rb");
	f_Ptr_2 = fopen ("e:\\asm_work\\ega3_2.cpi", "wb");

	temp = XMMinstalled ();
	printf ("XMS DRIVER INSTALL : %d\n", temp);
//--------------------------------------------------------
	num = 1;
	temp = GetXMMVersion (num);
	printf ("%x\n", temp);
	num = 2;
	temp = GetXMMVersion (num);
	printf ("%x\n", temp);
	num = 3;
	temp = GetXMMVersion (num);
	printf ("%x\n", temp);
//--------------------------------------------------------
	num = 1;
	us_temp = GetEMBSize (num);
	printf ("%u\n", us_temp);
	num = 2;
	us_temp = GetEMBSize (num);
	printf ("%u\n", us_temp);
//--------------------------------------------------------
	num = 50;
	handle = EMBAlloc (num);

	if (handle == -3)
		printf ("Error No.3\n");
	else if (handle == -2)
		printf ("Error No.2\n");
	else if (handle == -1)
		printf ("Error No.1\n");
//--------------------------------------------------------
	num = 1;
	us_temp = GetEMBSize (num);
	printf ("%u\n", us_temp);
	num = 2;
	us_temp = GetEMBSize (num);
	printf ("%u\n", us_temp);
//--------------------------------------------------------
	num = 100;
	temp = EMB_reSize (handle, num);

	if (temp == 1)
		printf ("True\n");
	else if (temp == -1)
		printf ("Error No.1\n");
	else if (temp == -2)
		printf ("Error No.2\n");
	else if (temp == -3)
		printf ("Error No.3\n");
	else if (temp == -4)
		printf ("Error No.4\n");
	else if (temp == -5)
		printf ("Error No.5\n");
	else if (temp == -6)
		printf ("Error No.6\n");
//--------------------------------------------------------
	num = 1;
	us_temp = GetEMBSize (num);
	printf ("%u\n", us_temp);
	num = 2;
	us_temp = GetEMBSize (num);
	printf ("%u\n", us_temp);
//--------------------------------------------------------
	lock = EMB_Lock (handle);

	if (lock == 5)
		printf ("Error No.1\n");
	else if (temp == -2)
		printf ("Error No.2\n");
	else if (temp == -3)
		printf ("Error No.3\n");
	else if (temp == -4)
		printf ("Error No.4\n");
	else if (temp == -5)
		printf ("Error No.5\n");
//--------------------------------------------------------
	num = 1;
	temp = EMB_HandleInfo (handle, num);
	printf ("Lock Block Count : %d\n", temp);
	num = 2;
	temp = EMB_HandleInfo (handle, num);
	printf ("EMB Handle Count : %d\n", temp);
	num = 3;
	temp = EMB_HandleInfo (handle, num);
	printf ("Block Length : %d\n", temp);
//--------------------------------------------------------
	printf ("Main MEM : %lu\n", coreleft ());

	Mem_Buf = (char *) malloc (50 * 1024);
	if (Mem_Buf == NULL)
			printf ("Base Mem Alloc Error\n");

	printf ("Main MEM : %lu\n", coreleft ());

	while (!feof (f_Ptr))
	{
//		printf ("in put %d\n", count);
		Mem_Buf[count] = fgetc (f_Ptr);
		count++;
	}
	putchar ('\n');

//--------------------------------------------------------
/*	moveInfo.Length 	  = 50 * 1024L;
	moveInfo.SourceHandle = 0;
	moveInfo.SourceOffset = (unsigned long) Mem_Buf;
	moveInfo.DestHandle   = handle;
	moveInfo.DestOffset   = 0;

	temp = MoveEMB (&moveInfo); */
	temp = MEMtoEMB (Mem_Buf, handle, 0L, 50 * 1024L);
	if (temp == -1)
		printf ("Error No.1\n");
	else if (temp == -2)
		printf ("Error No.2\n");
	else if (temp == -3)
		printf ("Error No.3\n");
	else if (temp == -4)
		printf ("Error No.4\n");
	else if (temp == -5)
		printf ("Error No.5\n");
	else if (temp == -6)
		printf ("Error No.6\n");
	else if (temp == -7)
		printf ("Error No.7\n");
	else if (temp == -8)
		printf ("Error No.8\n");
	else if (temp == -9)
		printf ("Error No.9\n");
	else if (temp == -10)
		printf ("Error No.10\n");

	Put_Buf = (char *) malloc (50 * 1024);

/*	moveInfo.Length 	  = 50 * 1024L;
	moveInfo.SourceHandle = handle;
	moveInfo.SourceOffset = 0;
	moveInfo.DestHandle   = 0;
	moveInfo.DestOffset   = (unsigned long) Put_Buf;

	temp = MoveEMB (&moveInfo); */
	temp = EMBtoMEM (handle, 0L, Put_Buf, 50 * 1024L);
	if (temp == -1)
		printf ("Error No.1\n");
	else if (temp == -2)
		printf ("Error No.2\n");
	else if (temp == -3)
		printf ("Error No.3\n");
	else if (temp == -4)
		printf ("Error No.4\n");
	else if (temp == -5)
		printf ("Error No.5\n");
	else if (temp == -6)
		printf ("Error No.6\n");
	else if (temp == -7)
		printf ("Error No.7\n");
	else if (temp == -8)
		printf ("Error No.8\n");
	else if (temp == -9)
		printf ("Error No.9\n");
	else if (temp == -10)
		printf ("Error No.10\n");

	for (i=0; i < count; i++)
	{
		fputc (Put_Buf[i], f_Ptr_2);
	}
	putchar ('\n');
//--------------------------------------------------------
	temp = EMB_UNLock (handle);
	num = FreeEMB (handle);
	if (num == -1)
		printf ("Error No.1\n");
	else if (num == -2)
		printf ("Error No.2\n");
	else if (num == -3)
		printf ("Error No.3\n");
	else if (num == -4)
		printf ("Error No.4\n");
	else if (num == -5)
		printf ("Error No.5\n");
	else if (num == -6)
		printf ("Error No.6\n");

	free (Mem_Buf);
	printf ("Main MEM : %lu\n", coreleft ());
	free (Put_Buf);
	printf ("Main MEM : %lu\n", coreleft ());
	fclose (f_Ptr);
	fclose (f_Ptr_2);
//--------------------------------------------------------
	num = 1;
	us_temp = GetEMBSize (num);
	printf ("%u\n", us_temp);
	num = 2;
	us_temp = GetEMBSize (num);
	printf ("%u\n", us_temp);
//--------------------------------------------------------
	num = 50;
	handle = EMBAlloc (num);

	if (handle == -3)
		printf ("Error No.3\n");
	else if (handle == -2)
		printf ("Error No.2\n");
	else if (handle == -1)
		printf ("Error No.1\n");
//--------------------------------------------------------
/*	lock = EMB_Lock (handle);

	if (lock == 5)
		printf ("Error No.1\n");
	else if (temp == -2)
		printf ("Error No.2\n");
	else if (temp == -3)
		printf ("Error No.3\n");
	else if (temp == -4)
		printf ("Error No.4\n");
	else if (temp == -5)
		printf ("Error No.5\n"); */
//--------------------------------------------------------
	char far *S_Buffer = (char far *)farmalloc (10*1024L);
	char far *D_Buffer = (char far *)farmalloc (10*1024L);
	char far *p_lock;
//--------------------------------------------------------
	_fmemset (S_Buffer, 'T', 10*1024);
	moveInfo.Length = 10*1024;
	moveInfo.SourceHandle = 0;
	moveInfo.SourceOffset = (unsigned long) S_Buffer;
	moveInfo.DestHandle = handle;
	moveInfo.DestOffset = 0;
	temp = MoveEMB (&moveInfo);

	_fmemset (S_Buffer, 'Z', 10*1024);
	moveInfo.Length = 10*1024;
	moveInfo.SourceHandle = 0;
	moveInfo.SourceOffset = (unsigned long) S_Buffer;
	moveInfo.DestHandle = handle;
	moveInfo.DestOffset = (10 * 1024) + 1;
	temp = MoveEMB (&moveInfo);

	if (temp == -1)
		printf ("Error No.1\n");
	else if (temp == -2)
		printf ("Error No.2\n");
	else if (temp == -3)
		printf ("Error No.3\n");
	else if (temp == -4)
		printf ("Error No.4\n");
	else if (temp == -5)
		printf ("Error No.5\n");
	else if (temp == -6)
		printf ("Error No.6\n");
	else if (temp == -7)
		printf ("Error No.7\n");
	else if (temp == -8)
		printf ("Error No.8\n");
	else if (temp == -9)
		printf ("Error No.9\n");
	else if (temp == -10)
		printf ("Error No.10\n");

	getch ();

	moveInfo.Length = 10*1024;
	moveInfo.SourceHandle = handle;
	moveInfo.SourceOffset = 0;
	moveInfo.DestHandle = 0;
	moveInfo.DestOffset = (unsigned long) D_Buffer;
	temp = MoveEMB (&moveInfo);

	if (temp == -1)
		printf ("Error No.1\n");
	else if (temp == -2)
		printf ("Error No.2\n");
	else if (temp == -3)
		printf ("Error No.3\n");
	else if (temp == -4)
		printf ("Error No.4\n");
	else if (temp == -5)
		printf ("Error No.5\n");
	else if (temp == -6)
		printf ("Error No.6\n");
	else if (temp == -7)
		printf ("Error No.7\n");
	else if (temp == -8)
		printf ("Error No.8\n");
	else if (temp == -9)
		printf ("Error No.9\n");
	else if (temp == -10)
		printf ("Error No.10\n");

	getch ();

	puts (D_Buffer);
	getch ();


	moveInfo.Length = 10*1024;
	moveInfo.SourceHandle = handle;
	moveInfo.SourceOffset = (10 * 1024) + 1;
	moveInfo.DestHandle = 0;
	moveInfo.DestOffset = (unsigned long) D_Buffer;
	temp = MoveEMB (&moveInfo);

	if (temp == -1)
		printf ("Error No.1\n");
	else if (temp == -2)
		printf ("Error No.2\n");
	else if (temp == -3)
		printf ("Error No.3\n");
	else if (temp == -4)
		printf ("Error No.4\n");
	else if (temp == -5)
		printf ("Error No.5\n");
	else if (temp == -6)
		printf ("Error No.6\n");
	else if (temp == -7)
		printf ("Error No.7\n");
	else if (temp == -8)
		printf ("Error No.8\n");
	else if (temp == -9)
		printf ("Error No.9\n");
	else if (temp == -10)
		printf ("Error No.10\n");

	getch ();

	puts (D_Buffer);
	getch ();

//--------------------------------------------------------
/*	p_lock = (char far *) lock;
	_fmemset (S_Buffer, 'T', 10*1024);
	for (i=0; i<(10*1024); i++)
	{
		*(p_lock+i) = *(S_Buffer+i);
	}
	puts (S_Buffer);	*/
//--------------------------------------------------------
/*	_fmemset (S_Buffer, 'T', 10*1024);

	moveInfo.Length = 10*1024;
	moveInfo.SourceHandle = 0;
	moveInfo.SourceOffset = (unsigned long) S_Buffer;
	moveInfo.DestHandle = handle;
	moveInfo.DestOffset = lock;
	temp = MoveEMB (&moveInfo);

	if (temp == -1)
		printf ("Error No.1\n");
	else if (temp == -2)
		printf ("Error No.2\n");
	else if (temp == -3)
		printf ("Error No.3\n");
	else if (temp == -4)
		printf ("Error No.4\n");
	else if (temp == -5)
		printf ("Error No.5\n");
	else if (temp == -6)
		printf ("Error No.6\n");
	else if (temp == -7)
		printf ("Error No.7\n");
	else if (temp == -8)
		printf ("Error No.8\n");
	else if (temp == -9)
		printf ("Error No.9\n");
	else if (temp == -10)
		printf ("Error No.10\n");

	getch ();
//--------------------------------------------------------
	puts ("base Mem put start");
	*(S_Buffer+((10*1023)+1)) = 0;
	puts (S_Buffer);
	puts ("base Mem put end");
	getch ();
//--------------------------------------------------------
	moveInfo.Length = 10*1024;
	moveInfo.SourceHandle = handle;
	moveInfo.SourceOffset = lock;
	moveInfo.DestHandle = 0;
	moveInfo.DestOffset = (unsigned long)D_Buffer;
	temp = MoveEMB (&moveInfo);
//--------------------------------------------------------
	puts ("xms to mem put start");
	*(D_Buffer+((10*1023)+1)) = 0;
	puts (D_Buffer);
	puts ("xms to mem put end");
	getch ();
//--------------------------------------------------------
	_fmemset (S_Buffer, 'Z', 10*1024);
	moveInfo.Length = 10*1024;
	moveInfo.SourceHandle = 0;
	moveInfo.SourceOffset = (unsigned long) S_Buffer;
	moveInfo.DestHandle = handle;
	moveInfo.DestOffset = lock + (10*1024);
	temp = MoveEMB (&moveInfo);
//--------------------------------------------------------
	puts ("mem put start");
	*(S_Buffer+((10*1023)+1)) = 0;
	puts (S_Buffer);
	puts ("mem put end");
//--------------------------------------------------------
	moveInfo.Length = 10*1024;
	moveInfo.SourceHandle = handle;
	moveInfo.SourceOffset = lock + (10*1024);
	moveInfo.DestHandle = 0;
	moveInfo.DestOffset = (unsigned long)D_Buffer;
	temp = MoveEMB (&moveInfo);
//--------------------------------------------------------
	puts ("xms to mem put start");
	*(D_Buffer+((10*1023)+1)) = 0;
	puts (D_Buffer);
	puts ("xms to mem put end");
	getch ();
//--------------------------------------------------------*/
	farfree (S_Buffer);
	farfree (D_Buffer);
//	EMB_UNLock (handle);
	FreeEMB (handle);
//--------------------------------------------------------
}