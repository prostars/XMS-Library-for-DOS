;****************************************************************************;
;   Extended Memory Manager Library         Version 0.9                      ;
;                                           Program by Lee Sang Woo          ;
;   Copyright (c) 1997, Lee Sang Woo                                         ;
;****************************************************************************;

                .MODEL  LARGE, C
                .CODE

XMMaddress      DWORD   0
;****************************************************************************;
;   C언어 함수 원형 short XMMinstalled ();                                   ;
;   HIMEM.SYS 가 인스톨 되었는지 확인한다.                                   ;
;   리턴 값 : 인스톨 되어 있다면 1을                                         ;
;             인스톨 되어 있지 않다면 0을 리턴한다.                          ;
;****************************************************************************;
XMMinstalled    PROC    far
                mov     ax, 4300h
                int     2Fh
                cmp     al, 80h         ;al에 들어있는게 80h면 himem.sys 존재.
                jne     _NotInstalled

                mov     ax, 4310h
                int     2Fh
                mov     WORD PTR XMMaddress, bx     ;드라이버의 번지를 구함.
                mov     WORD PTR XMMaddress[2], es

                mov     ax, 1           ;himem.sys 가 존재 하므로 1을 리턴.
                ret
_NotInstalled:
                xor     ax, ax          ;himem.sys 가 존재치 않으므로 0을 리턴.
                ret
XMMinstalled    ENDP
;***************************************************************************;
;   C 언어 함수 원형 short GetXMMVersion (short num);                       ;
;   인수로 1, 2, 3 중 하나를 받는다.                                        ;
;   리턴 값 : 1 이 들어올경우, XMS 의 버젼을 리턴한다.                      ;
;             2 가 들어올경우, XMS Driver의 버전을 리턴한다.                ;
;             3 이 들어올경우, HMA 가 존재하는지 확인하며,                  ;
;               존재한다면 1을 그렇지 않다면 0을 리턴한다.                  ;
;   리턴 값은 16진수 이다.                                                  ;
;***************************************************************************;
GetXMMVersion   PROC    far     num:WORD    ; word 크기의 인수를 받습니다.
                xor     ah, ah              ; ah를 0으로 셋팅.
                call    XMMaddress          ; XMS Driver 호출.
                cmp     num, 2d             ; num을 10진수 2와 비교.
                jl      SHORT Xms_Ver       ; 2보다 num이 작으면 Xms_Ver 로
                jg      SHORT HMA           ; 2보다 num이 크면 HMA로 점프.
                mov     AX, BX              ; Xms_Driver 버젼을 리턴하기 위해
                                            ; BX의 값을 AX에 넣는다.
                ret                         ; AX의 값을 리턴한다.
Xms_Ver:
                ret                         ; AX의 값을 리턴한다.
HMA:
                mov     AX, DX              ; HMA의 존재 유무를 리턴하기 위해
                                            ; DX의 값을 AX에 넣는다.
                ret                         ; AX의 값을 리턴한다.
GetXMMVersion   ENDP
;***************************************************************************;
;   C 언어 함수 원형 short GetEMBSize (short num);                          ;
;   인수로 1, 1외의 값 중 하나를 받는다.                                    ;
;   리턴 값 : 1이 들어올경우, 사용가능한 EMB의 최대 크기를 리턴한다.        ;
;             1외의 값이 들어올 경우, 사용가능한 EMB의 전체 크기를 리턴한다.;
;             에러가 발생할 경우, -1, -2, -3 중 하나를 리턴한다.            ;
;             -1 일 경우 "지정 펑션을 사용할 수 없다."                      ;
;             -2 일 경우 "VDISK 가 검출되었다."                             ;
;             -3 일 경우 "모든 EMB 가 할당되었다." 가 에러의 내용이다.      ;
;***************************************************************************;
GetEMBSize      PROC    far     num:WORD
                xor     bl, bl              ; bl을 0으로 셋팅.
                mov     ah, 08h
                call    XMMaddress          ; XMS Driver 호출.
                cmp     bl, 0               ; bl을 0과 비교.
                jne     SHORT Error         ; bl이 0이 아니면 Error로 점프.
                cmp     num, 1              ; num을 1과 비교.
                jne     SHORT EMB_Total_Size    ;num이 1과 같지 않으면
                                            ; EMB_Total_Size로 점프.
                ret                         ; 사용가능한 EMB의 최대 크기
                                 ; 즉, 한번에 잡을수 있는 가장 큰 블럭 크기 리턴
EMB_Total_Size:
                mov     ax, dx              ; 사용가능한 EMB의 전체 크기를
                                            ; 리턴하기 위해 dx 값을 ax에 넣음.
                ret                         ; 몇 Kbyte 남았는지 리턴.
Error:
                cmp     bl, 80h             ; bl을 80h와 비교.
                je      SHORT Error_1       ; 같으면 Error_1로 점프.
                cmp     bl, 81h             ; bl을 81h와 비교.
                je      SHORT Error_2       ; 같으면 Error_2로 점프.
                cmp     bl, 0A0h            ; bl을 A0h과 비교.
                je      SHORT Error_3       ; 같으면 Error_3으로 점프.
Error_1:
                mov     ax, -1d             ; ax에 10진수 -1을 ax에 넣음.
                ret                         ; -1을 리턴.
Error_2:
                mov     ax, -2d             ; ax에 10진수 -2를 ax에 넣음.
                ret                         ; -2를 리턴.
Error_3:
                mov     ax, -3d             ; ax에 10진수 -3을 ax에 넣음.
                ret                         ; -3을 리턴.
GetEMBSize      ENDP
;***************************************************************************;
;   C 언어 함수 원형 short EMBAlloc (short EMB_Size);                       ;
;   인수로 할당받을 EMB의 크기(Kbyte) 를 받는다.                            ;
;   리턴값 : 성공적으로 할당이 이루어지면 그 메모리 블럭의 핸들을 리턴한다. ;
;            핸들은 16비트 값이다.                                          ;
;            에러가 발생하면, 음수 값이 리턴된다.                           ;
;            자세한 사항은 소스의 에러 처리부분을 보라.                     ;
;***************************************************************************;
EMBAlloc        PROC    far     EMB_Size:WORD ;word(short형) 인수를 하나 받는다.
                mov     ah, 09h               ;기능번호 09h를 넣는다.
                mov     dx, EMB_Size          ;할당받을 크기를 dx에 넣는다.
                call    XMMaddress            ;XMS Driver 호출.
                cmp     ax, 1
                jne     SHORT Error         ;ax의 값이 1이 아니면 에러이다.
                mov     ax, dx              ; 할당된 메모리 블럭의 핸들(16bit)을
                                            ; ax에 넣는다.
                ret                         ; 핸들을 리턴한다.
Error:                                      ; 에러 처리
                cmp     bl, 80h
                je      SHORT Error_1       ; 지정 펑션을 사용할수 없다.
                cmp     bl, 81h
                je      SHORT Error_2       ; VDISK 가 검출되었다.
                cmp     bl, 0A0h
                je      SHORT Error_3       ; 모든 EMB 가 할당되었다.
                jg      SHORT Error_4       ; 모든 EMB 핸들이 사용되었다.
Error_1:
                mov     ax, -1d             ; 10진수 -1을 리턴.
                ret
Error_2:
                mov     ax, -2d
                ret
Error_3:
                mov     ax, -3d
                ret
Error_4:
                mov     ax, -4d
                ret
EMBAlloc        ENDP
;***************************************************************************;
;   C 언어 함수 원형 short EMB_reSize (short handle, short EMB_size);       ;
;   인수로 EMB의 핸들(16bit)과 새 EMB 크기(KByte) 를 받는다.                ;
;   리턴값 : 성공적으로 변경이 이루어지면 1을 리턴한다.                     ;
;            에러가 발생하면, 음수 값이 리턴된다.                           ;
;            자세한 사항은 소스의 에러 처리부분을 보라.                     ;
;***************************************************************************;
EMB_reSize      PROC    far     handle:WORD, EMB_size:WORD
                mov     dx, handle
                mov     bx, EMB_size
                mov     ah, 0Fh
                call    XMMaddress
                cmp     ax, 1
                jne     Error
                ret
Error:
                cmp     bl, 80h
                je      Error_1                 ;지정 펑션을 사용할 수 없다.
                cmp     bl, 81h
                je      Error_2                 ;VDISK가 검출되었다.
                cmp     bl, 0A0h
                je      Error_3                 ;모든 EMB 가 할당되었다.
                cmp     bl, 0A1h
                je      Error_4                 ;모든 EMB 핸들이 사용되었다.
                cmp     bl, 0A2h
                je      Error_5                 ;핸들 지정이 잘못되었다.
                jg      Error_6                 ;핸들이 록(LOCK) 상태이다.
Error_1:
                mov     ax, -1d
                ret
Error_2:
                mov     ax, -2d
                ret
Error_3:
                mov     ax, -3d
                ret
Error_4:
                mov     ax, -4d
                ret
Error_5:
                mov     ax, -5d
                ret
Error_6:
                mov     ax, -6d
                ret
EMB_reSize      ENDP
;***************************************************************************;
;   C 언어 함수 원형 short FreeEMB (short handle);                          ;
;   인수로 EMB의 핸들(16bit) 를 받는다.                                     ;
;   리턴값 : 성공적으로 해제가 이루어지면 1을 리턴한다.                     ;
;            에러가 발생하면, 음수 값이 리턴된다.                           ;
;            자세한 사항은 소스의 에러 처리부분을 보라.                     ;
;***************************************************************************;
FreeEMB         PROC    far     handle:WORD ;핸들을 인수로 받는다.
                mov     ah, 0Ah             ;기능 번호 0Ah를 넣는다.
                mov     dx, handle          ;해제 하려는 핸들을 dx에 넣는다.
                call    XMMaddress
                cmp     ax, 1
                jne     SHORT Error         ;ax가 1이 아니면 에러.
                ret
Error:
                cmp     bl, 80h
                je      Error_1             ;지정 펑션을 사용할 수 없다.
                cmp     bl, 81h
                je      Error_2             ;VDISK가 검출되었다.
                cmp     bl, 0A0h
                je      Error_3             ;모든 EMB 가 할당 되었다.
                cmp     bl, 0A1h
                je      Error_4             ;모든 EMB 핸들이 사용되었다.
                cmp     bl, 0A2h
                je      Error_5             ;핸들 지정이 잘못되었다.
                jg      Error_6             ;핸들이 록(lock) 상태이다.
Error_1:
                mov     ax, -1d
                ret
Error_2:
                mov     ax, -2d
                ret
Error_3:
                mov     ax, -3d
                ret
Error_4:
                mov     ax, -4d
                ret
Error_5:
                mov     ax, -5d
                ret
Error_6:
                mov     ax, -6d
                ret
FreeEMB         ENDP
;***************************************************************************;
;   C 언어 함수 원형 short EMB_HandleInfo (short handle, short num);        ;
;   인수로 EMB의 핸들과 기능번호(1,2,3)를 받는다.                           ;
;   리턴값 : 1이 들어오면, 록(lock) 상태인 블록 수를 리턴.                  ;
;            2가 들어오면, 시스템에서 사용 가능한 EMB 핸들 수를 리턴.       ;
;            3이 들어오면, 블록 길이(KByte 단위)를 리턴.                    ;
;            에러가 발생하면, 음수 값이 리턴된다.                           ;
;            자세한 사항은 소스의 에러 처리부분을 보라.                     ;
;***************************************************************************;
EMB_HandleInfo  PROC    far     handle:WORD, num:WORD
                mov     dx, handle
                mov     ah, 0Eh
                call    XMMaddress
                cmp     ax, 1
                jne     Error
                cmp     num, 2d
                jl      Lock_Block_Count
                je      EMB_Handle_Count
                jg      Block_Length
Lock_Block_Count:
                mov     al, bh
                ret
EMB_Handle_Count:
                mov     al, bl
                ret
Block_Length:
                mov     ax, dx
                ret
Error:
                cmp     bl, 80h
                je      Error_1                 ;지정 펑션을 사용할 수 없다.
                cmp     bl, 81h
                je      Error_2                 ;VDISK가 검출되었다.
                jg      Error_3                 ;핸들 지정이 잘못되었다.
Error_1:
                mov     ax, -1d
                ret
Error_2:
                mov     ax, -2d
                ret
Error_3:
                mov     ax, -3d
                ret
EMB_HandleInfo  ENDP
;***************************************************************************;
;   C 언어 함수 원형 unsigned long EMB_Lock (short handle);                 ;
;   인수로 EMB의 핸들를 받는다.                                             ;
;   리턴값 : 성공적으로 잠금이 이루어지면 Lock된 블록 번지(32bit)를         ;
;            리턴한다.                                                      ;
;            에러가 발생하면, 16비트 크기의 1부터 5 상이의 값이 리턴된다.   ;
;            자세한 사항은 소스의 에러 처리부분을 보라.                     ;
;***************************************************************************;
EMB_Lock        PROC    far     handle:WORD
                mov     dx, handle
                mov     ah, 0Ch
                call    XMMaddress
                cmp     ax, 1
                jne     Error
                mov     ax, bx
                ret
Error:
                cmp     bl, 80h
                je      Error_1                 ;지정 펑션을 사용할 수 없다.
                cmp     bl, 81h
                je      Error_2                 ;VDISK가 검출되었다.
                cmp     bl, 0A2h
                je      Error_3                 ;핸들 지정이 잘못되었다.
                cmp     bl, 0ACh
                je      Error_4                 ;블록 LOCK 수가 초과되었다.
                jg      Error_5                 ;록(lock) 실패
Error_1:
                mov     ax, 1d
                ret
Error_2:
                mov     ax, 2d
                ret
Error_3:
                mov     ax, 3d
                ret
Error_4:
                mov     ax, 4d
                ret
Error_5:
                mov     ax, 5d
                ret
EMB_Lock        ENDP
;***************************************************************************;
;   C 언어 함수 원형 short EMB_UNLock (short handle);                       ;
;   인수로 EMB의 핸들를 받는다.                                             ;
;   리턴값 : 성공적으로 해제가 이루어지면 1을 리턴한다.                     ;
;            에러가 발생하면, 음수 값이 리턴된다.                           ;
;            자세한 사항은 소스의 에러 처리부분을 보라.                     ;
;***************************************************************************;
EMB_UNLock      PROC    far     handle:WORD
                mov     dx, handle
                mov     ah, 0Dh
                call    XMMaddress
                cmp     ax, 1
                jne     Error
                ret
Error:
                cmp     bl, 80h
                je      Error_1                 ;지정 펑션을 사용할 수 없다.
                cmp     bl, 81h
                je      Error_2                 ;VDISK가 검출되었다.
                cmp     bl, 0A2h
                je      Error_3                 ;핸들 지정이 잘되었다.
                jg      Error_4                 ;불록이 록(LOCK) 상태가 아니다.
Error_1:
                mov     ax, -1d
                ret
Error_2:
                mov     ax, -2d
                ret
Error_3:
                mov     ax, -3d
                ret
Error_4:
                mov     ax, 04d
                ret
EMB_UNLock      ENDP
;***************************************************************************;
;   C 언어 함수 원형 short MoveEMB (EMMStruct *moveInfo);                   ;
;   인수로 EMMStruct 형 구조체의 주소를 받는다.                             ;
;   리턴값 : 성공적으로 이동이 이루어지면 1을 리턴한다.                     ;
;            에러가 발생하면, 음수 값이 리턴된다.                           ;
;            자세한 사항은 소스의 에러 처리부분을 보라.                     ;
;***************************************************************************;
MoveEMB         PROC    far USES ds si, moveInfo:DWORD  ;far 포인터이므로
                                                        ;DWORD(32bit크기)이다.
                lds     si, moveInfo            ;moveInfo의 세그먼트와 오프셋을
                                                ;ds와, si에 넣는다.
;               mov     si, WORD PTR moveInfo   ;위와 같은 코드이다.
;               mov     ds, WORD PTR moveInfo[2]
                mov     ah, 0Bh                 ;기능번호 0Bh 를 넣는다.
                call    XMMaddress
                cmp     ax, 1
                jne     Error                   ;ax가 1이 아니면 에러.
                ret                             ;1을 리턴한다.
Error:
                cmp     bl, 80h
                je      Error_1                 ;지정 펑션을 사용할 수 없다.
                cmp     bl, 81h
                je      Error_2                 ;VDISK가 검출되었다.
                cmp     bl, 82h
                je      Error_3                 ;A20 에러 발생
                cmp     bl, 0A3h
                je      Error_4                 ;소스 핸들 지정이 잘못되었다.
                cmp     bl, 0A4h
                je      Error_5                 ;소스 옵셋 지정이 잘못되었다.
                cmp     bl, 0A5h
                je      Error_6                 ;목적 핸들 지정이 잘못되었다.
                cmp     bl, 0A6h
                je      Error_7                 ;목적 옵셋 지정이 잘못되었다.
                cmp     bl, 0A7h
                je      Error_8                 ;길이 지정이 잘못되었다.
                cmp     bl, 0A8h
                je      Error_9                 ;이동시 잘못 겹쳐(overlap)졌다.
                jg      Error_10                ;패리티(parity)에러가 발생했다.
Error_1:
                mov     ax, -1d
                ret
Error_2:
                mov     ax, -2d
                ret
Error_3:
                mov     ax, -3d
                ret
Error_4:
                mov     ax, -4d
                ret
Error_5:
                mov     ax, -5d
                ret
Error_6:
                mov     ax, -6d
                ret
Error_7:
                mov     ax, -7d
                ret
Error_8:
                mov     ax, -8d
                ret
Error_9:
                mov     ax, -9d
                ret
Error_10:
                mov     ax, -10d
                ret
MoveEMB         ENDP
                END
