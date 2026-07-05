#include <shlobj.h>
#include <windows.h>

#include <stdio.h>
#include <wchar.h>

#include "scanner.h"

static bool is_audio(const wchar_t* fName)
{
	const wchar_t* ext = wcsrchr(fName, L'.');
	
	if (ext == NULL)
		return false;
	
	if (_wcsicmp(ext, L".mp3") == 0 ||
        _wcsicmp(ext, L".flac") == 0 ||
        _wcsicmp(ext, L".wav") == 0 ||
        _wcsicmp(ext, L".ogg") == 0 ||
        _wcsicmp(ext, L".opus") == 0 ||
        _wcsicmp(ext, L".aac") == 0 ||
        _wcsicmp(ext, L".m4a") == 0
    )
		return true;

	return false;
}

static bool scan_dir(char *pathList[], const PWSTR dir, int* c)
{
	wchar_t path[MAX_PATH];
	wchar_t fullPath[MAX_PATH];
	WIN32_FIND_DATAW fData;
	
	swprintf_s(
		path,
		MAX_PATH,
		L"%s\\*",
		dir
	);

	HANDLE hFind = FindFirstFileW(path, &fData);

	if (hFind == INVALID_HANDLE_VALUE)
		return false;

	do
	{
		if (wcscmp(fData.cFileName, L".") == 0 ||
			wcscmp(fData.cFileName, L"..") == 0
		)
			continue;
			
		if (fData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			swprintf_s(
				path,
				MAX_PATH,
				L"%s\\%s",
				dir,
				fData.cFileName
			);
			
			if(!scan_dir(pathList, path, c)) {goto fail;}
			continue;
		}
		
		if (is_audio(fData.cFileName))
		{
			swprintf_s(
				fullPath,
				MAX_PATH,
				L"%s\\%s",
				dir,
				fData.cFileName
			);

			int size = WideCharToMultiByte(CP_UTF8, 0, fullPath, -1, NULL, 0, NULL, NULL);
			if (size == 0) {goto fail;}

			pathList[*c] = malloc(size);
			if (pathList[*c] == NULL) {goto fail;}
			
			if (WideCharToMultiByte(CP_UTF8, 0, fullPath, -1, pathList[*c], size, NULL, NULL) == 0)
			{
				free(pathList[*c]);
				goto fail;
			}
			else {(*c)++;}
		}
			
	} while (FindNextFileW(hFind, &fData));
		
	FindClose(hFind);
	return true;

	fail:
		FindClose(hFind);
		return false;
}

static void get_win_path(KNOWNFOLDERID rID, PWSTR* rPath, HRESULT* hr)
{
	*hr = SHGetKnownFolderPath(&rID, 0,	NULL, rPath);
}	

bool scanner_scan_filepaths(ScannerCTX* s_ctx, ScanType type)
{
	KNOWNFOLDERID impPaths[] = {
		FOLDERID_Desktop,
		FOLDERID_Documents,
		FOLDERID_Downloads,
		FOLDERID_Music,
		FOLDERID_Pictures,
		FOLDERID_Videos
	};
	
	PWSTR rPath = NULL;
	HRESULT hr;

	int c = 0;
	
	for (short i = 0; i < sizeof(impPaths)/sizeof(impPaths[0]); ++i)
	{
		get_win_path(impPaths[i], &rPath, &hr);
		if (FAILED(hr)) {return false;}

		scan_dir(s_ctx->pathList, rPath, &c);
	}

	/* // debug print.
	for (int i = 0; i < 400; ++i) {
		printf("c:%d name:%s\n",i, s_ctx->pathList[i]);
	}
	*/
	
	return true;
}