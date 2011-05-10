// file debug.h
#ifndef __DEBUG_H__
#define __DEBUG_H__

#ifndef ASSERT

#ifdef _DEBUG

#pragma warning(disable:4127)

void _trace(char *fmt, ...);

#define ASSERT(x) {if(!(x)) _asm{int 0x03}}
#define VERIFY(x) {if(!(x)) _asm{int 0x03}}  // ��ע��Ϊ���԰汾ʱ�����ж���Ч

#else
#define ASSERT(x)
#define VERIFY(x) x                  // ��ע��Ϊ���а汾ʱ�������ж�
#endif

#ifdef _DEBUG
#define TRACE _trace

#else
inline void _trace(LPCTSTR fmt, ...) {fmt; }
#define TRACE  1 ? (void)0 : _trace
#endif

#endif // ASSERT

#endif // __DEBUG_H__