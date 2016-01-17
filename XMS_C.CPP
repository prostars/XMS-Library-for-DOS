#include "xms.h"

short MEMtoEMB (void far *Buffer, unsigned short Handle, unsigned long offset, unsigned long Length)
{
	short		error;
	EMMStruct	moveinfo;

	moveinfo.Length = Length;
	moveinfo.SourceHandle = 0;
	moveinfo.SourceOffset = (unsigned long) Buffer;
	moveinfo.DestHandle = Handle;
	moveinfo.DestOffset = offset;

	error = MoveEMB (&moveinfo);

	return (error);
}

short EMBtoMEM (unsigned short Handle, unsigned long offset, void far *Buffer, unsigned long Length)
{
	short		error;
	EMMStruct	moveinfo;

	moveinfo.Length = Length;
	moveinfo.SourceHandle = Handle;
	moveinfo.SourceOffset = offset;
	moveinfo.DestHandle = 0;
	moveinfo.DestOffset = (unsigned long) Buffer;

	error = MoveEMB (&moveinfo);

	return (error);
}

short EMBtoEMB (unsigned short S_Handle, unsigned long S_offset, unsigned short D_Handle, unsigned long D_offset, unsigned Length)
{
	short		error;
	EMMStruct	moveinfo;

	moveinfo.Length = Length;
	moveinfo.SourceHandle = S_Handle;
	moveinfo.SourceOffset = S_offset;
	moveinfo.DestHandle = D_Handle;
	moveinfo.DestOffset = D_offset;

	error = MoveEMB (&moveinfo);

	return (error);
}

short EMBWrite (unsigned short Handle, unsigned short offset, void far *Buffer, unsigned long Length)
{
	short			error;
	EMMStruct		moveinfo;
//	struct			Last_Move_Point;

	moveinfo.Length = Length;
	moveinfo.SourceHandle = (unsigned long) Buffer;
	moveinfo.SourceOffset = 0;
	moveinfo.DestHandle = Handle;
	moveinfo.DestOffset = offset;

	error = MoveEMB (&moveinfo);

	return (error);
}

short EMBRead (unsigned short Handle, unsigned short offset, void far *Buffer, unsigned long Length)
{
	short			error;
	EMMStruct		moveinfo;

	moveinfo.Length = Length;
	moveinfo.SourceHandle = Handle;
	moveinfo.SourceOffset = offset;
	moveinfo.DestHandle = (unsigned long) Buffer;
	moveinfo.DestOffset = 0;

	error = MoveEMB (&moveinfo);

	return (error);
}