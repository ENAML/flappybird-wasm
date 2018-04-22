/**
 * -----------------------------------------------------------------------------
 * IO
 * -----------------------------------------------------------------------------
 */
#pragma once

void loadConfig(const char *path);
char *loadFileBuffer(const char *path);
void freeFileBuffer(char *buffer);
void loadJSON(const char *path);