/*
library.h - custom dlls loader
Copyright (C) 2008 Uncle Mike

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
*/

#ifndef LIBRARY_H
#define LIBRARY_H

#define MAX_LIBRARY_EXPORTS		4096

typedef struct dll_user_s
{
	void	*hInstance;		// instance handle
	qboolean	custom_loader;		// a bit who indicated loader type
	qboolean	encrypted;		// dll is crypted (some client.dll in HL, CS etc)
	char	dllName[32];		// for debug messages
	string	fullPath, shortPath;	// actual dll paths

	// ordinals stuff, valid only on Win32
	word	*ordinals;
	dword	*funcs;
	char	*names[MAX_LIBRARY_EXPORTS];	// max 4096 exports supported
	int	num_ordinals;		// actual exports count
	dword	funcBase;			// base offset
} dll_user_t;

dll_user_t *FS_FindLibrary( const char *dllname, qboolean directpath );
void *COM_LoadLibrary( const char *dllname, int build_ordinals_table, qboolean directpath );
void *COM_GetProcAddress( void *hInstance, const char *name );
const char *COM_NameForFunction( void *hInstance, void *function );
void *COM_FunctionFromName_SR( void *hInstance, const char *pName ); // Save/Restore version
void *COM_FunctionFromName( void *hInstance, const char *pName );
void COM_FreeLibrary( void *hInstance );
const char *COM_GetLibraryError( void );

// TODO: Move to internal?
void COM_ResetLibraryError( void );
void COM_PushLibraryError( const char *error );
const char *COM_OffsetNameForFunction( void *function );
#endif//LIBRARY_H
