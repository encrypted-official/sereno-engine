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

static bool scan_dir(const PWSTR dir)
{
	static wchar_t path[MAX_PATH + 1];
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
			
			scan_dir(path);
		}
		
		if (is_audio(fData.cFileName))
			// music file found hopefully.
		
		// debug printf.
		printf("%S\n", fData.cFileName);
			
	} while (FindNextFileW(hFind, &fData));
		
	FindClose(hFind);
	return true;
}

static void get_win_path(KNOWNFOLDERID rID, PWSTR* rPath, HRESULT* hr)
{
	*hr = SHGetKnownFolderPath(
		&rID,	// REFKNOWNFOLDERID
		0,	// default KNOWN_FOLDER_FLAG flag.
		NULL,	// forces current user
		rPath
	);
}	

bool scanner_scan_all(ScannerCTX* s_ctx)
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
	
	for (short i = 0; i < sizeof(impPaths)/sizeof(impPaths[0]); ++i)
	{
		get_win_path(impPaths[i], &rPath, &hr);
	
		if (FAILED(hr))
			return false;
	
		scan_dir(rPath);
	}
	
	return true;
}