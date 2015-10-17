/*
 * Copyright (C) 2011 Denis Kuzko <kda6666@ukr.net>
 */

#ifndef PBSYNOPSISSETTINGS_H
#define PBSYNOPSISSETTINGS_H

#include "pbsynopsisdefines.h"
#include <inkview.h>
#include "pbsynopsisdefines.h"
#include "pbsynopsistypes.h"
#include "pbsynopsisresource.h"
#include <map>

class PBSynopsisTOC;

class EXPORT PBSynopsisSettings
{
public:
	PBSynopsisSettings(PBSynopsisTOC *SynTOC);
	~PBSynopsisSettings();

	void SetShow(int index, int show);
	int GetShow(int index);
	void SetShowInfo(int index, int showinfo);
	int GetShowInfo(int index);
	void SetSelect(int sel);
	int GetSelect();
	PBSynopsisTOC *GetTOC();
	void Open(PBSynopsisTOC *SynTOC);

	// FB2
	int GetFB2SettingsId(fb2_settings fb2);
	fb2_settings GetFB2Settings(int id);
	// EPUB
	int GetEPUBSettingsId(epub_settings epub);
	epub_settings GetEPUBSettings(int id);
	// Save-Load
	void Save(FILE *f);
	void Load(const char *data);

private:
	void DrawGoodSelection(int x, int y, int w, int h);
	void DrawCheck(int x, int y, int w, int h, int c);
	int GetType(int i);
	void Draw();
	static int SettingsHandler(int type, int par1, int par2);

	// FB2
	int AddFB2Settings(fb2_settings fb2);
	// EPUB
	int AddEPUBSettings(epub_settings epub);

	std::map<int, int> m_ShowInfo;
	std::map<int, int> m_Show;

	PBSynopsisTOC *s_pTOC;

	static PBSynopsisSettings *s_pTOCSettings;
	int m_Select;

	// FB2
	std::vector<fb2_settings> m_vFB2;
	// EPUB
	std::vector<epub_settings> m_vEPUB;
};

#endif // PBSYNOPSISSETTINGS_H
