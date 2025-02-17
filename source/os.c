/*
 * os.c
 *
 * Copyright (c) 2020-2025, DarkMatterCore <pabloacurielz@gmail.com>.
 *
 * This file is part of wad2bin (https://github.com/DarkMatterCore/wad2bin).
 *
 * wad2bin is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * wad2bin is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "os.h"

static bool g_isBigEndian = false, g_endiannessRetrieved = false;

bool os_is_big_endian(void)
{
    if (!g_endiannessRetrieved)
    {
        g_isBigEndian = (*((u16*)"\0\xff") < 0x100);
        g_endiannessRetrieved = true;
    }

    return g_isBigEndian;
}

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)

int os_snprintf(os_char_t *out, size_t len, const char *fmt, ...)
{
    if (!out || !len || !fmt || !*fmt) return -1;

    va_list args;

    char *fstr = NULL;
    size_t fstr_sz = 0;

    int ret = -1;

    va_start(args, fmt);

    ret = vsnprintf(NULL, 0, fmt, args);
    if (ret <= 0) goto end;

    fstr_sz = (size_t)ret;
    ret = -1;

    fstr = (char*)calloc(sizeof(char), fstr_sz + 1);
    if (!fstr) goto end;

    ret = vsprintf(fstr, fmt, args);
    if (ret <= 0) goto end;

    ret = snwprintf(out, len, L"%hs", fstr);

end:
    if (fstr) free(fstr);

    va_end(args);

    return ret;
}

#endif /* WIN32 || _WIN32 || __WIN32__ || __NT__ */
