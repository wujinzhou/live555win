// file debug.cpp
#ifdef _DEBUG
#include <stdio.h>
#include <stdarg.h>
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

void _trace(char *fmt, ...)
{
	char out[1024];
	va_list body;
	va_start(body, fmt);
	vsprintf(out, fmt, body);     // ��ע����ʽ��������ַ��� fmtt
	va_end(body);                 //       ������ַ��� ou
	OutputDebugString(out);       // ��ע�������ʽ������ַ�����������
}
#endif