/* linenoise.h -- guerrilla line editing library against the idea that a
 * line editing lib needs to be 20,000 lines of C code.
 *
 * See linenoise.c for more information.
 *
 * Copyright (c) 2010, Salvatore Sanfilippo <antirez at gmail dot com>
 * Copyright (c) 2010, Pieter Noordhuis <pcnoordhuis at gmail dot com>
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *   * Redistributions of source code must retain the above copyright notice,
 *     this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *   * Neither the name of Redis nor the names of its contributors may be used
 *     to endorse or promote products derived from this software without
 *     specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef __LINENOISE_H
#define __LINENOISE_H

#define LINENOISE_VERSION "1.2.0"
#define LINENOISE_VERSION_MAJOR 1
#define LINENOISE_VERSION_MINOR 2
#define LINENOISE_VERSION_PATCH 0

#ifdef __cplusplus
extern "C" {
#endif

typedef struct linenoiseCompletions linenoiseCompletions;

typedef void(linenoiseCompletionCallback)(const char*, linenoiseCompletions*);
typedef char*(linenoiseHintsCallback)(const char *buf, int *color, int *bold);
typedef void(linenoiseFreeHintsCallback)(void *hint);
typedef char*(linenoiseSyntaxCallback)(const char* buf);
typedef int (*linenoiseUserKeyCallback)(const char* line, int pos, char** new_line, int* new_pos, void* userData);
void linenoiseSetCompletionCallback(linenoiseCompletionCallback* fn);
void linenoiseSetHintsCallback(linenoiseHintsCallback* fn);
void linenoiseSetFreeHintsCallback(linenoiseFreeHintsCallback* fn);
void linenoiseSetSyntaxCallback(linenoiseSyntaxCallback* fn);
void linenoiseSetRightPrompt(const char* prompt);
void linenoiseAddCompletion(linenoiseCompletions* lc, const char* str);

char* linenoise(const char* prompt);
void linenoisePreloadBuffer(const char* preloadText);
int linenoiseHistoryAdd(const char* line);
int linenoiseHistorySetMaxLen(int len);
int linenoiseHistoryGetMaxLen();
char* linenoiseHistoryLine(int index);
int linenoiseHistorySave(const char* filename);
int linenoiseHistoryLoad(const char* filename);
void linenoiseHistoryFree(void);
void linenoiseClearScreen(void);
void linenoiseMaskModeEnable(void);
void linenoiseMaskModeDisable(void);
void linenoiseSetMenuComplete(int enable);
void linenoiseSetCompletionCaseInsensitive(int ci);
void linenoiseSetFilenameCompletion(int enable);
void linenoiseSetReadTimeout(int ms);
void linenoiseSetMultiLine(int ml);
void linenoiseSetAutoDedent(const char* indentStr, char32_t dedentChar);
void linenoiseSetUserKeyCallback(linenoiseUserKeyCallback cb);
void linenoiseBindKey(int keyCode, void* userData);
void linenoiseUnbindKey(int keyCode);
void linenoisePrintKeyCodes(void);
/* the following are extensions to the original linenoise API */
int linenoiseInstallWindowChangeHandler(void);
/* returns type of key pressed: 1 = CTRL-C, 2 = CTRL-D, 3 = TIMEOUT, 0 = other */
int linenoiseKeyType(void);
/* returns the terminal width in columns */
int linenoiseColumns(void);
/* returns the terminal height in rows */
int linenoiseRows(void);

#ifdef __cplusplus
}
#endif

#endif /* __LINENOISE_H */
