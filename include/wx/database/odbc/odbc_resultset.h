#ifndef _WX_DATABASE_ODBC_RESULT_SET_H_
#define _WX_DATABASE_ODBC_RESULT_SET_H_

#include "wx/database/wxprec.h"

class wxOdbcPreparedStatement;
class wxOdbcDatabase;

WX_DECLARE_OBJARRAY(wxVariant, ValuesArray);
WX_DECLARE_HASH_SET( int, wxIntegerHash, wxIntegerEqual, IntegerSet );
WX_DECLARE_HASH_MAP( int, wxMemoryBuffer, wxIntegerHash, wxIntegerEqual, BlobMap );

class wxOdbcResultSet : public wxDatabaseResultSet
{
public:
  // ctor
  wxOdbcResultSet(wxOdbcInterface* pInterface);
  wxOdbcResultSet(wxOdbcInterface* pInterface, wxOdbcPreparedStatement* pStatement, bool bManageStatement = false, int nCol = 0);

  // dtor
  virtual ~wxOdbcResultSet();
  
  virtual bool Next();
  virtual void Close();
  
  // get field
  virtual int GetResultInt(int nField);
  virtual wxString GetResultString(int nField);
  virtual long GetResultLong(int nField);
  virtual bool GetResultBool(int nField);
  virtual wxDateTime GetResultDate(int nField);
  virtual void* GetResultBlob(int nField, wxMemoryBuffer& Buffer);
  virtual double GetResultDouble(int nField);
  virtual bool IsFieldNull(int nField);
  virtual int GetFieldLength(int nField);
  
  virtual int GetFieldLength(const wxString& strField);

  // get MetaData
  virtual wxResultSetMetaData* GetMetaData();

private:
  void RetrieveFieldData(int nField);
  void InterpretErrorCodes( long nCode, SQLHSTMT stmth_ptr=NULL );
  virtual int LookupField(const wxString& strField);
  bool IsBlob(int nField);
  
  wxOdbcPreparedStatement* m_pStatement;
  SQLHSTMT m_pOdbcStatement;

  StringToIntMap m_FieldLookupMap;
  ValuesArray m_fieldValues;
  // List of values that have been retrieved
  IntegerSet m_RetrievedValues;
  // List of values that are NULL
  IntegerSet m_NullValues;

  bool m_bManageStatement;
  SQLHSTMT m_pHStmt;
  wxOdbcInterface* m_pInterface;

  BlobMap m_BlobMap;
};

#endif//_WX_DATABASE_ODBC_RESULT_SET_H_

