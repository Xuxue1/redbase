//
// sm.h
//   Data Manager Component Interface
//

#ifndef SM_H
#define SM_H

// Please do not include any other files than the ones below in this file.

#include "sm_error.h"
#include <stdlib.h>
#include <string.h>
#include "redbase.h"  // Please don't change these lines
#include "parser.h"
#include "rm.h"
#include "ix.h"
#include "catalog.h"

//
// SM_Manager: provides data management
//
class SM_Manager {
  friend class QL_Manager;
 public:
  SM_Manager    (IX_Manager &ixm_, RM_Manager &rmm_);
  ~SM_Manager   ();                             // Destructor

  RC OpenDb     (const char *dbName);           // Open the database
  RC CloseDb    ();                             // close the database

  RC CreateTable(const char *relName,           // create relation relName
                 int        attrCount,          //   number of attributes
                 AttrInfo   *attributes);       //   attribute data
  RC CreateIndex(const char *relName,           // create an index for
                 const char *attrName);         //   relName.attrName
  RC DropTable  (const char *relName);          // destroy a relation

  RC DropIndex  (const char *relName,           // destroy index on
                 const char *attrName);         //   relName.attrName
  RC Load       (const char *relName,           // load relName from
                 const char *fileName);         //   fileName
  RC Help       ();                             // Print relations in db
  RC Help       (const char *relName);          // print schema of relName

  RC Print      (const char *relName);          // print relName contents

  RC Set        (const char *paramName,         // set parameter to
                 const char *value);            //   value
 private:
  RC IsValid() const;
  RC GetFromTable(const char *relName,           // create relation relName
                  int&        attrCount,          //   number of attributes
                  DataAttrInfo   *&attributes);       //   attribute data
  
  // Get the first matching row for relName
  // contents are return in rel and the RID the record is located at is
  // returned in rid.
  // method returns SM_NOSUCHTABLE if relName was not found
  RC GetRelFromCat(const char* relName, 
                   DataRelInfo& rel,
                   RID& rid) const;

  // Get the first matching row for relName, attrName
  // contents are returned in attr
  // location of record is returned in rid
  // method returns SM_NOSUCHENTRY if attrName was not found
  RC GetAttrFromCat(const char* relName,
                    const char* attrName,
                    DataAttrInfo& attr,
                    RID& rid) const;


 private:
  RM_Manager& rmm;
  IX_Manager& ixm;
  bool bDBOpen;
  RM_FileHandle relfh;
  RM_FileHandle attrfh;
  char cwd[1024];
};

#endif // SM_H