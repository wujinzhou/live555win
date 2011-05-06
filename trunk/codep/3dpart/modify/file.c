/*
 * Buffered file io for ffmpeg system
 * Copyright (c) 2001 Fabrice Bellard
 *
 * This file is part of FFmpeg.
 *
 * FFmpeg is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * FFmpeg is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with FFmpeg; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 */

#include "libavutil/avstring.h"
#include "avformat.h"
#include <fcntl.h>
#if HAVE_SETMODE
#include <io.h>
#endif
#include <unistd.h>
#include <sys/stat.h>
#include <stdlib.h>
#include "os_support.h"
#include "url.h"
#include "avfile.h"

FUN_fseek  td_fseek = lseek;
FUN_fread  td_fread = read;
FUN_fwrite td_fwrite = write;
FUN_fopen  td_fopen = open;
FUN_ftell  td_ftell = tell;
FUN_fclose td_fclose = close;
FUN_stat    td_stat = stat;
FUN_fstat   td_fstat= fstat; 
/* standard file protocol */

/* standard file protocol */
int setFileCallBack(FUN_fopen o,FUN_fwrite w,FUN_fread r, FUN_fseek  s,FUN_ftell t,FUN_fclose c,FUN_stat Fstat,FUN_fstat fst)
{
	if (NULL != o)
	{
		td_fopen = o;
	}
	if (NULL != w)
	{
		td_fwrite = w;
	} 
	if (NULL !=  r)
	{
		td_fread = r;
	} 
	if (NULL !=  s)
	{
		td_fseek = s;
	} 
	if (NULL != t )
	{
		td_ftell = t;	
	} 
	if (NULL !=  c)
	{
		td_fclose = c;
	} 
	if (NULL != Fstat )
	{
		td_stat = Fstat;
	} 
	if (NULL != fst )
	{
		td_fstat = fst;

	}  	
}
static int file_read(URLContext *h, unsigned char *buf, int size)
{
    int fd = (intptr_t) h->priv_data;
    return td_fread(fd, buf, size);
}

static int file_write(URLContext *h, const unsigned char *buf, int size)
{
    int fd = (intptr_t) h->priv_data;
    return write(fd, buf, size);
}

static int file_get_handle(URLContext *h)
{
    return (intptr_t) h->priv_data;
}

#if CONFIG_FILE_PROTOCOL

static int file_open(URLContext *h, const char *filename, int flags)
{
    int access;
    int fd;

    av_strstart(filename, "file:", &filename);

    if (flags & AVIO_RDWR) {
        access = O_CREAT | O_TRUNC | O_RDWR;
    } else if (flags & AVIO_WRONLY) {
        access = O_CREAT | O_TRUNC | O_WRONLY;
    } else {
        access = O_RDONLY;
    }
#ifdef O_BINARY
    access |= O_BINARY;
#endif
    fd = td_fopen(filename, access, 0666);
    if (fd == -1)
        return AVERROR(errno);
    h->priv_data = (void *) (intptr_t) fd;
    return 0;
}

/* XXX: use llseek */
static int64_t file_seek(URLContext *h, int64_t pos, int whence)
{
    int fd = (intptr_t) h->priv_data;
    if (whence == AVSEEK_SIZE) {
        struct stat st;
        int ret = td_fstat(fd, &st);
        return ret < 0 ? AVERROR(errno) : st.st_size;
    }
    return td_fseek(fd, pos, whence);
}

static int file_close(URLContext *h)
{
    int fd = (intptr_t) h->priv_data;
    return td_fclose(fd);
}

static int file_check(URLContext *h, int mask)
{
    struct stat st;
    int ret = td_stat(h->filename, &st);
    if (ret < 0)
        return AVERROR(errno);

    ret |= st.st_mode&S_IRUSR ? mask&AVIO_RDONLY : 0;
    ret |= st.st_mode&S_IWUSR ? mask&AVIO_WRONLY : 0;
    ret |= st.st_mode&S_IWUSR && st.st_mode&S_IRUSR ? mask&AVIO_RDWR : 0;

    return ret;
}

URLProtocol ff_file_protocol = {
    .name                = "file",
    .url_open            = file_open,
    .url_read            = file_read,
    .url_write           = file_write,
    .url_seek            = file_seek,
    .url_close           = file_close,
    .url_get_file_handle = file_get_handle,
    .url_check           = file_check,
};

#endif /* CONFIG_FILE_PROTOCOL */

#if CONFIG_PIPE_PROTOCOL

static int pipe_open(URLContext *h, const char *filename, int flags)
{
    int fd;
    char *final;
    av_strstart(filename, "pipe:", &filename);

    fd = strtol(filename, &final, 10);
    if((filename == final) || *final ) {/* No digits found, or something like 10ab */
        if (flags & AVIO_WRONLY) {
            fd = 1;
        } else {
            fd = 0;
        }
    }
#if HAVE_SETMODE
    setmode(fd, O_BINARY);
#endif
    h->priv_data = (void *) (intptr_t) fd;
    h->is_streamed = 1;
    return 0;
}

URLProtocol ff_pipe_protocol = {
    .name                = "pipe",
    .url_open            = pipe_open,
    .url_read            = file_read,
    .url_write           = file_write,
    .url_get_file_handle = file_get_handle,
    .url_check           = file_check,
};
 
#endif /* CONFIG_PIPE_PROTOCOL */
