struct EMMStruct
{
	unsigned long  Length;
	unsigned short SourceHandle;
	unsigned long  SourceOffset;
	unsigned short DestHandle;
	unsigned long  DestOffset;
};

extern "C"
{
	short XMMinstalled ();
	short GetXMMVersion (short num);
	unsigned short GetEMBSize (short num);
	short EMBAlloc (short EMB_Size);
	short EMB_reSize (short handle, short EMB_size);
	short FreeEMB (short handle);
	short EMB_HandleInfo (short handle, short num);
	unsigned long EMB_Lock (short handle);
	short EMB_UNLock (short handle);
	short MoveEMB (EMMStruct far *moveInfo);
//  이하의 함수들은 MoveEMB ()를 쉽게 사용하기위하여 C로 만든 함수로
//  리턴 값은 MoveEMB ()의 리턴 값을 그대로 리턴한다.
	short MEMtoEMB (void far *Buffer, unsigned short Handle, unsigned long offset, unsigned long Length);
	short EMBtoMEM (unsigned short Handle, unsigned long offset, void far *Buffer, unsigned long Length);
	short EMBtoEMB (unsigned short S_Handle, unsigned long S_offset, unsigned short D_Handle, unsigned long D_offset, unsigned Length);
	short EMBWrite (unsigned short Handle, unsigned short offset, void far *Buffer, unsigned long Length);
	short EMBRead (unsigned short Handle, unsigned short offset, void far *Buffer, unsigned long Length);
}
