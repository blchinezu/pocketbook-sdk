#ifndef __PBRECORDSET_H__
#define __PBRECORDSET_H__

#include <inkview.h>
#include <map>
#include <string>
#include <utility>

class PBRecordset
{
public:
	enum AffectedRecords
	{
		NoRecords,
		AllRecords,
		MarkedRecords,
		CurrentRecord
	};

	PBRecordset();
	virtual ~PBRecordset();

	// This must be called to init Record Set
	virtual bool Open();

	// This must be called to destroy data in recordset. Please note: it will be called automatically in destructor
	virtual void Close();

	// This function could refresh data
	virtual void Refresh();

	// setup param for open
	void SetParam(const char *param, const char *value);

	// move to row. Row must be in range [ 0, rowCount() )
	bool Move(int row);

	// return row count
	virtual int RowCount();

	// return column count
	virtual int ColumnCount();

	// return text for column. Column must be in range [ 0, columnCount() )
	virtual const char *GetText(int column);

	// return text for column. Column must be in range [ 0, columnCount() )
	virtual int GetInt(int column);

	// return text for column. Column must be in range [ 0, columnCount() )
	virtual ibitmap *GetImage(int column);

	// return bool for column. Column must be in range [ 0, columnCount() )
	virtual bool GetBool(int column);

	// return void* for column. Column must be in range [ 0, columnCount() )
	virtual void *GetVoid(int column);

	// mark item
	virtual void Mark(bool value);

	// set what to do type. Return -1 by default
	virtual int Delete(PBRecordset::AffectedRecords whatToDo);

	// return param from param list
	const char *GetParam(const char *param);

protected:
	// use this method int getText && getInt && getImage to recieve current row position
	int currentRow();

	// need for current row remember
	int m_row;
	std::map<std::string, std::string> m_paramList;

private:
};

#endif // __PBRECORDSET_H__
