
# include <stdio.h>
# include "am.h"
# include "pf.h"

/* The structure of the scan Table */
struct {
         int fileDesc;
         int op;
         int attrType;
         int pageNum;
         short index;
         short actindex;
         int nextpageNum;
         char nextvalue[AM_MAXATTRLENGTH];
         short nextIndex;
         // short nextRecIdPtr;
         int nextRecIdPtr;
         int lastpageNum;
         short lastIndex;
         int status;
         char* lowerboundpagebuf;
         int lowerboundpagenum;
         int lowerboundindex;
         char value[AM_MAXATTRLENGTH];
       } AM_scanTable[MAXSCANS];


/* Opens an index scan */
AM_OpenIndexScan(fileDesc,attrType,attrLength,op,value)
int fileDesc; /* file Descriptor */

char attrType; /* 'i' or 'c' or 'f' */
int attrLength; /* 4 for 'i' or 'f' , 1-255 for 'c' */
int op; /* operator for comparison */
char *value; /* value for comparison */

{
int scanDesc; /* index into scan table */
int status; /* whether value is found or not in the tree */
int index; /* index of value in leaf */
int pageNum;/* page number of leaf page where value is found */
int recSize; /* size of key,int pair in leaf */
char *pageBuf; /* buffer for page */
int errVal; /* return value of functions */
AM_LEAFHEADER head,*header; /* local header */
int searchpageNum;


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/* check the parameters */
if (fileDesc < 0)
  {
   AM_Errno = AME_FD;
   return(AME_FD);
  }

if ((attrType != 'i') && (attrType != 'c') && (attrType != 'f'))
  {
  AM_Errno = AME_INVALIDATTRTYPE;
  return(AME_INVALIDATTRTYPE);
  }
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* initialise header */
header = &head;

/* find a vacant place in the scan table */
for (scanDesc = 0; scanDesc <  MAXSCANS;scanDesc++)
  if (AM_scanTable[scanDesc].status == FREE) break;

/* scan table is full */
if (scanDesc > MAXSCANS - 1) 
{
  AM_Errno = AME_SCAN_TAB_FULL;
  return(AME_SCAN_TAB_FULL);
}

/* there is room */
AM_scanTable[scanDesc].status = FIRST;
AM_scanTable[scanDesc].attrType = attrType;

/* initialise AM_LeftPageNum */
AM_LeftPageNum = GetLeftPageNum(fileDesc);
// printf("The left page num is %d\n",AM_LeftPageNum);


attrLength = attrLength + AM_si; 

/* scan of all keys */
if (value == NULL)
{
  AM_scanTable[scanDesc].fileDesc = fileDesc;
  AM_scanTable[scanDesc].op = ALL;
  AM_scanTable[scanDesc].nextpageNum = AM_LeftPageNum;
  AM_scanTable[scanDesc].nextIndex = 1;
  AM_scanTable[scanDesc].actindex = 1;
  errVal = PF_GetThisPage(fileDesc,AM_LeftPageNum,&pageBuf);
  AM_Check;
  bcopy(pageBuf + AM_sl + attrLength,&AM_scanTable[scanDesc].nextRecIdPtr,AM_si);
  errVal = PF_UnfixPage(fileDesc,AM_LeftPageNum,FALSE);
  // printf("nextRec = %d\n", AM_scanTable[scanDesc].nextRecIdPtr);
  AM_Check;
  return(scanDesc);
}
// int val;
// bcopy(value,&val,AM_si);
// printf("The search index is opened with %d\n",val);
//////////////////////////////////////////OUR CHANGE///////////////////////////////////////
// attrType = 'c';
int recID_pseudo = 0;
bcopy(&recID_pseudo, value + attrLength-AM_si, AM_si);
// attrLength = attrLength + AM_si;  
//////////////////////////////////////////END///////////////////////////////////////

/* search for the pagenumber and index of value */
// if(op==GREATER_THAN_EQUAL) printf("value is %d",*value);
// printf("search start\n");
status = AM_Search(fileDesc,attrType,attrLength,value,&pageNum,&pageBuf,&index);
// printf("Status %d\n",status);
// printf("page number is %d\n",pageNum);
// if(op==GREATER_THAN_EQUAL || op==LESS_THAN || op==EQUAL) {
//   printf("index is %d",index);
//   bcopy((pageBuf+AM_sl+(index-1)*(attrLength+AM_si)+attrLength),&val,AM_si);
//   printf("value at the index is %d\n",val);
//   printf("status is %d\n",status);
// }
searchpageNum = pageNum;
errVal = PF_UnfixPage(fileDesc,pageNum,FALSE);
// printf("0\n");
int lowerboundpagenum;
int lowerboundindex;
char* lowerboundpagebuf;

recID_pseudo = AM_MAX_INT;
bcopy(&recID_pseudo,value+attrLength-AM_si,AM_si);

int lowerboundstatus = AM_Search(fileDesc,attrType,attrLength,value,&lowerboundpagenum,&lowerboundpagebuf,&lowerboundindex);
// printf("lower bound Status %d\n",lowerboundstatus);
// printf("lowerboundpagenum = %d\n",lowerboundpagenum);
// printf("lowerboundindex = %d\n",lowerboundindex);

if(lowerboundstatus==AM_NOT_FOUND)
{
  // printf("This should print now\n");
  AM_scanTable[scanDesc].lowerboundpagenum = pageNum;
  AM_scanTable[scanDesc].lowerboundindex = index;
  AM_scanTable[scanDesc].lowerboundpagebuf = pageBuf;
}
else
{
  // printf("our lowerboundindex is %d\n",lowerboundstatus);
  AM_scanTable[scanDesc].lowerboundpagenum = lowerboundpagenum;
  AM_scanTable[scanDesc].lowerboundindex = lowerboundindex;
  AM_scanTable[scanDesc].lowerboundpagebuf = lowerboundpagebuf;
}
errVal = PF_UnfixPage(fileDesc,lowerboundpagenum,FALSE);
// printf("1\n");
/* check for errors */
if (status < 0) 
{ 
  AM_scanTable[scanDesc].status = FREE;
  AM_Errno = status;
  return(status);
}

bcopy(pageBuf,header,AM_sl);
recSize = attrLength + AM_si;
AM_scanTable[scanDesc].fileDesc = fileDesc;
AM_scanTable[scanDesc].op = op;

/* value is not in leaf but if inserted will have to be inserted after the last
key */
if (index > header->numKeys) 
  if (header->nextLeafPage != AM_NULL_PAGE)
  {
    // printf("lol\n");
    errVal = PF_GetThisPage(fileDesc,header->nextLeafPage,&pageBuf);
    AM_Check;
    bcopy(pageBuf,header,AM_sl);
    errVal = PF_UnfixPage(fileDesc,header->nextLeafPage,FALSE);
    AM_Check;
    pageNum = header->nextLeafPage;
    index = 1;
  }
  else 
    pageNum = AM_NULL_PAGE;

AM_scanTable[scanDesc].pageNum = pageNum;
AM_scanTable[scanDesc].index = index;



/* case on op */
switch(op) 
 {
  case EQUAL : 
               {
                /* value not in leaf - no match */
		            if (status != AM_FOUND)
                  AM_scanTable[scanDesc].status = OVER;
                else
                {
                  AM_scanTable[scanDesc].nextpageNum = pageNum;
                  AM_scanTable[scanDesc].nextIndex = index;
                  AM_scanTable[scanDesc].actindex = index;
                  bcopy(pageBuf + AM_sl + (index - 1)*recSize + attrLength,
                          &AM_scanTable[scanDesc].nextRecIdPtr,AM_si);
                  // printf("The recId ptr is %d\n",AM_scanTable[scanDesc].nextRecIdPtr);
                  if(lowerboundstatus == AM_NOT_FOUND){
                    AM_scanTable[scanDesc].lastpageNum  = pageNum;
                    AM_scanTable[scanDesc].lastIndex  = index;
                  }
                  else{
                    AM_scanTable[scanDesc].lastpageNum  = lowerboundpagenum;
                    AM_scanTable[scanDesc].lastIndex  = lowerboundindex;
                  }
                }
                break;
               }
  case LESS_THAN : 
               {
                AM_scanTable[scanDesc].nextpageNum = AM_LeftPageNum;
                AM_scanTable[scanDesc].nextIndex = 1;
                AM_scanTable[scanDesc].actindex = 1;
                if (searchpageNum != AM_LeftPageNum)
		            { 
                  errVal = PF_GetThisPage(fileDesc,AM_LeftPageNum,&pageBuf);
                  AM_Check;
                }
                bcopy(pageBuf + AM_sl + attrLength,
                        &AM_scanTable[scanDesc].nextRecIdPtr,AM_si);
                // printf("The recId ptr is %d\n",AM_scanTable[scanDesc].nextRecIdPtr);
                if (searchpageNum != AM_LeftPageNum)
		            {    
		              errVal = PF_UnfixPage(fileDesc,AM_LeftPageNum,FALSE);
                  AM_Check;
                }
                AM_scanTable[scanDesc].lastpageNum  = pageNum;
                AM_scanTable[scanDesc].lastIndex  = index - 1;
                break;
               }
  case GREATER_THAN :
               {
                if(lowerboundstatus==AM_NOT_FOUND)
                {
                  if (status == AM_FOUND)
                   if ((index + 1) <= (header->numKeys))
                    {
                     AM_scanTable[scanDesc].nextpageNum = pageNum;
                     AM_scanTable[scanDesc].nextIndex = index + 1;
                     AM_scanTable[scanDesc].actindex = index + 1;
                     bcopy(pageBuf + AM_sl + (index)*recSize + attrLength,
                               &AM_scanTable[scanDesc].nextRecIdPtr,AM_si);
                    }
                   else
                     /* got to start from next leaf page */
  		              if (header->nextLeafPage != AM_NULL_PAGE)
                     {
                       AM_scanTable[scanDesc].nextpageNum = header->nextLeafPage;
                       AM_scanTable[scanDesc].nextIndex =  1;
                       AM_scanTable[scanDesc].actindex = 1;
                       errVal =PF_GetThisPage(fileDesc,header->nextLeafPage,&pageBuf);
                       AM_Check;
                       bcopy(pageBuf + AM_sl + attrLength,
                               &AM_scanTable[scanDesc].nextRecIdPtr,AM_si);
                       errVal = PF_UnfixPage(fileDesc,header->nextLeafPage,FALSE);
                       AM_Check;
                     }
                     else /* Nextleafpage is not last NULL page */
                       AM_scanTable[scanDesc].status = OVER;
                  else /* status == AM_NOT_FOUND */ 
                  {
                    AM_scanTable[scanDesc].nextpageNum = pageNum;
                    AM_scanTable[scanDesc].nextIndex = index ;
                    AM_scanTable[scanDesc].actindex = index;
                    bcopy(pageBuf + AM_sl + (index - 1)*recSize + attrLength,
                              &AM_scanTable[scanDesc].nextRecIdPtr,AM_si);
                  }
                }
                else
                {
                  bcopy(lowerboundpagebuf,header,AM_sl);
                   if ((lowerboundindex + 1) <= (header->numKeys))
                    {
                     AM_scanTable[scanDesc].nextpageNum = lowerboundpagenum;
                     AM_scanTable[scanDesc].nextIndex = lowerboundindex + 1;
                     AM_scanTable[scanDesc].actindex = lowerboundindex + 1;
                     bcopy(lowerboundpagebuf + AM_sl + (lowerboundindex)*recSize + attrLength,
                               &AM_scanTable[scanDesc].nextRecIdPtr,AM_si);
                    }
                   else
                     /* got to start from next leaf page */
                    if (header->nextLeafPage != AM_NULL_PAGE)
                     {
                       AM_scanTable[scanDesc].nextpageNum = header->nextLeafPage;
                       AM_scanTable[scanDesc].nextIndex =  1;
                       AM_scanTable[scanDesc].actindex = 1;
                       errVal =PF_GetThisPage(fileDesc,header->nextLeafPage,&pageBuf);
                       AM_Check;
                       bcopy(pageBuf + AM_sl + attrLength,
                               &AM_scanTable[scanDesc].nextRecIdPtr,AM_si);
                       errVal = PF_UnfixPage(fileDesc,header->nextLeafPage,FALSE);
                       AM_Check;
                     }
                     else /* Nextleafpage is not last NULL page */
                       AM_scanTable[scanDesc].status = OVER;
                  // else /* status == AM_NOT_FOUND */ 
                  // {
                  //   AM_scanTable[scanDesc].nextpageNum = pageNum;
                  //   AM_scanTable[scanDesc].nextIndex = index ;
                  //   AM_scanTable[scanDesc].actindex = index;
                  //   bcopy(pageBuf + AM_sl + (index - 1)*recSize + attrLength,
                  //             &AM_scanTable[scanDesc].nextRecIdPtr,AM_si);
                  // }
                }
                break;
               }
  case LESS_THAN_EQUAL :
               {
               AM_scanTable[scanDesc].nextpageNum = AM_LeftPageNum;
               AM_scanTable[scanDesc].nextIndex = 1;
               AM_scanTable[scanDesc].actindex = 1;
                if (searchpageNum != AM_LeftPageNum)
		 { errVal = PF_GetThisPage(fileDesc,AM_LeftPageNum,&pageBuf);
                  AM_Check;
                 }
               bcopy(pageBuf + AM_sl + attrLength,
                                 &AM_scanTable[scanDesc].nextRecIdPtr,AM_si);
               if (searchpageNum != AM_LeftPageNum)
		 {
		  errVal = PF_UnfixPage(fileDesc,AM_LeftPageNum,FALSE);
                  AM_Check;
                 }

                if(lowerboundstatus==AM_NOT_FOUND)
                {		   
                 AM_scanTable[scanDesc].lastpageNum  = pageNum;    
                 if (status == AM_FOUND)
                  AM_scanTable[scanDesc].lastIndex  = index ;
                 else
                  AM_scanTable[scanDesc].lastIndex  = index - 1;
                }
                else
                {
                  AM_scanTable[scanDesc].lastpageNum  = lowerboundpagenum;    
                  AM_scanTable[scanDesc].lastIndex  = lowerboundindex ;
                }
               break;
               }
  case GREATER_THAN_EQUAL :
                
               {
                AM_scanTable[scanDesc].nextpageNum = pageNum;
                AM_scanTable[scanDesc].nextIndex = index;
                AM_scanTable[scanDesc].actindex = index;
                bcopy(pageBuf + AM_sl + (index - 1)*recSize + attrLength,
                        &AM_scanTable[scanDesc].nextRecIdPtr,AM_si);
                break;
               }
  case NOT_EQUAL :
            {
              if(status == AM_FOUND)
              {
                AM_scanTable[scanDesc].nextpageNum = AM_LeftPageNum;
                AM_scanTable[scanDesc].nextIndex = 1;
                AM_scanTable[scanDesc].actindex = 1;
                bcopy(value, AM_scanTable[scanDesc].value, attrLength-AM_si);
                // AM_scanTable[scanDesc].value = value;
                if (searchpageNum != AM_LeftPageNum)
		            {
		              errVal = PF_GetThisPage(fileDesc,AM_LeftPageNum,&pageBuf);
                  AM_Check;
		            }
                bcopy(pageBuf + AM_sl + attrLength,
                              &AM_scanTable[scanDesc].nextRecIdPtr,AM_si);
                if (searchpageNum != AM_LeftPageNum)
		            { errVal = PF_UnfixPage(fileDesc,AM_LeftPageNum,FALSE);
                  AM_Check;
                }
              }
              else 
                AM_scanTable[scanDesc].pageNum = AM_NULL_PAGE;
              break;
            }
  default : {
             AM_scanTable[scanDesc].status = FREE;
	     AM_Errno = AME_INVALID_OP_TO_SCAN;
	     return(AME_INVALID_OP_TO_SCAN);
             break;
            }
 }
// printf("scandesc = %d\n",scanDesc);
// errVal = PF_UnfixPage(fileDesc,searchpageNum,FALSE);
// AM_Check;
return(scanDesc);
}

/* returns the record id of the next record that satisfies the conditions
specified for index scan associated with scanDesc */
AM_FindNextEntry(scanDesc)
int scanDesc;/* index scan descriptor */

{
int recId; /* recordId to be returned */
char *pageBuf;/* buffer for page */
int errVal;/* return value for functions */
AM_LEAFHEADER head,*header; /* local header */
int recSize;/* size of key,ptr pair for leaf */
int compareVal; /* value returned by compare routine */


/* check if scanDesc is valid */
if ((scanDesc < 0) || (scanDesc > MAXSCANS - 1))
  {
   AM_Errno = AME_INVALID_SCANDESC;
   // printf("scandesc is %d\n",scanDesc);
   return(AME_INVALID_SCANDESC);
  }

/* check if scan is over */
if (AM_scanTable[scanDesc].status == OVER)
{
      // printf("2bfkjdfnjdsf\n");
      return(AME_EOF);
    }

if (AM_scanTable[scanDesc].nextpageNum == AM_NULL_PAGE)
 {
  AM_scanTable[scanDesc].status = OVER;
  // printf("1sfnldnflndlf\n");
  return(AME_EOF);
 }

header = &head;
errVal = PF_GetThisPage(AM_scanTable[scanDesc].fileDesc
                        ,AM_scanTable[scanDesc].nextpageNum,&pageBuf);
AM_Check;

bcopy(pageBuf,header,AM_sl);
recSize = header->attrLength + AM_si;

errVal = PF_UnfixPage(AM_scanTable[scanDesc].fileDesc
           ,AM_scanTable[scanDesc].nextpageNum,FALSE);
AM_Check;

/* Get next non empty leaf page */
while(header->numKeys == 0)
  if(header->nextLeafPage == AM_NULL_PAGE)
   {
    AM_scanTable[scanDesc].status = OVER;
    // printf("wodjwaojfdoa\n"); 
    return(AME_EOF);
   }
  else
   {
    errVal = PF_GetThisPage(AM_scanTable[scanDesc].fileDesc,header->nextLeafPage,&pageBuf);
    AM_Check;
    errVal = PF_UnfixPage(AM_scanTable[scanDesc].fileDesc,header->nextLeafPage,FALSE);
    AM_Check;
    AM_scanTable[scanDesc].nextpageNum = header->nextLeafPage;
    AM_scanTable[scanDesc].nextIndex = 1;
    AM_scanTable[scanDesc].actindex = 1;
    bcopy(pageBuf,header,AM_sl);
    bcopy(pageBuf + AM_sl +  (AM_scanTable[scanDesc].nextIndex-1)*recSize
    + header->attrLength, &AM_scanTable[scanDesc].nextRecIdPtr,AM_si);
    AM_scanTable[scanDesc].status = FIRST;
   }

/* if op is < or <= check if you are done - might have overshot while scanning
empty pages*/
if ((AM_scanTable[scanDesc].op == LESS_THAN) || 
  (AM_scanTable[scanDesc].op == LESS_THAN_EQUAL))
 if ((AM_scanTable[scanDesc].lastpageNum <= AM_scanTable[scanDesc].nextpageNum)
 && (AM_scanTable[scanDesc].lastIndex == 0))
 {
  AM_scanTable[scanDesc].status = OVER;
  // printf("3jnfjnsdf\n");
  return(AME_EOF);
 }

// if ((AM_scanTable[scanDesc].op == LESS_THAN))       
//  if ((AM_scanTable[scanDesc].lastpageNum <= AM_scanTable[scanDesc].nextpageNum)
//  && (AM_scanTable[scanDesc].lastIndex == 0))
//  {
//   AM_scanTable[scanDesc].status = OVER;
//   return(AME_EOF);
//  }

/* if op is not equal then check if we have to skip this value */
if (AM_scanTable[scanDesc].op == NOT_EQUAL)
{
  if(AM_scanTable[scanDesc].lowerboundpagenum==AM_scanTable[scanDesc].pageNum && AM_scanTable[scanDesc].lowerboundindex==AM_scanTable[scanDesc].index)
  {
    // printf("The printed value is %d\n", AM_scanTable[scanDesc].nextRecIdPtr);
    // printf("The next page is %d, page is %d, next index is %d and index is %d\n", AM_scanTable[scanDesc].nextpageNum,AM_scanTable[scanDesc].pageNum,AM_scanTable[scanDesc].nextIndex,AM_scanTable[scanDesc].index);
    if((AM_scanTable[scanDesc].nextpageNum==AM_scanTable[scanDesc].pageNum) && (AM_scanTable[scanDesc].actindex==AM_scanTable[scanDesc].index))
    {
      // printf("lol\n");
      AM_scanTable[scanDesc].nextIndex++;
      AM_scanTable[scanDesc].actindex++;
      bcopy(pageBuf + AM_sl + (AM_scanTable[scanDesc].nextIndex-1)*recSize
          + header->attrLength, &AM_scanTable[scanDesc].nextRecIdPtr,AM_si);
      // printf("The printed value is %d\n", AM_scanTable[scanDesc].nextRecIdPtr);
    }
  }
  else
  {
  // printf("Present Page number is %d\n",AM_scanTable[scanDesc].nextpageNum);
    int compare;
    compare = AM_Compare(pageBuf+AM_sl+(AM_scanTable[scanDesc].nextIndex-1)*recSize, AM_scanTable[scanDesc].attrType, length, AM_scanTable[scanDesc].value);
    // printf("Compare = %d\n",compare);
   while (((AM_scanTable[scanDesc].pageNum == AM_scanTable[scanDesc].nextpageNum)
    && (AM_scanTable[scanDesc].index <= AM_scanTable[scanDesc].actindex)) ||
     ((AM_scanTable[scanDesc].lowerboundpagenum == AM_scanTable[scanDesc].nextpageNum)
    && (AM_scanTable[scanDesc].lowerboundindex >= AM_scanTable[scanDesc].actindex)) ||
    ((AM_scanTable[scanDesc].pageNum < AM_scanTable[scanDesc].nextpageNum)
    && (AM_scanTable[scanDesc].lowerboundpagenum > AM_scanTable[scanDesc].nextpageNum))||(compare==0))
    {   
        // printf("skip\n");
        /*skip this value */
        if ((AM_scanTable[scanDesc].nextIndex + 1) <= (header->numKeys))
        {
          AM_scanTable[scanDesc].nextIndex++;
          AM_scanTable[scanDesc].actindex++;
          bcopy(pageBuf + AM_sl +  (AM_scanTable[scanDesc].nextIndex-1)*recSize
          + header->attrLength, &AM_scanTable[scanDesc].nextRecIdPtr,AM_si);
        }
        else
          if (header->nextLeafPage == AM_NULL_PAGE)
          {
            // printf("5nlfnldnf\n");
            return(AME_EOF); 
          }
          else
           {
            // printf("New page %d\n", header->nextLeafPage);
            // printf("Next page %d\n", AM_scanTable[scanDesc].nextpageNum);
            // printf("Last page %d\n", AM_scanTable[scanDesc].lowerboundpagenum);
            // printf("Last index %d\n",AM_scanTable[scanDesc].lowerboundindex);
            // printf("First page %d\n", AM_scanTable[scanDesc].pageNum);
            int newPage = header->nextLeafPage;
            AM_scanTable[scanDesc].nextpageNum = header->nextLeafPage;
            AM_scanTable[scanDesc].nextIndex =  1;
            AM_scanTable[scanDesc].actindex = 1;
            errVal =PF_GetThisPage(AM_scanTable[scanDesc].fileDesc,
                  header->nextLeafPage,&pageBuf);
            AM_Check;
            // printf("0\n");
            bcopy(pageBuf + AM_sl + header->attrLength,
               &AM_scanTable[scanDesc].nextRecIdPtr,AM_si);
            // printf("next rec ID is %d\n",AM_scanTable[scanDesc].nextRecIdPtr);
            bcopy(pageBuf,header,AM_sl);
            errVal = PF_UnfixPage(AM_scanTable[scanDesc].fileDesc
                ,newPage,FALSE);
            // printf("errval is %d\n",errVal);
            AM_Check;
           }
        compare = AM_Compare(pageBuf+AM_sl+(AM_scanTable[scanDesc].nextIndex-1)*recSize, AM_scanTable[scanDesc].attrType, length, AM_scanTable[scanDesc].value);
    }
  }
}
/* if not the first call to findnextentry , check if previous record has 
been deleted */
if (AM_scanTable[scanDesc].status != FIRST && AM_scanTable[scanDesc].op!=NOT_EQUAL)
 {
  compareVal = AM_Compare(pageBuf + (AM_scanTable[scanDesc].nextIndex - 1)
                *recSize + AM_sl,AM_scanTable[scanDesc].attrType,
		header->attrLength,AM_scanTable[scanDesc].nextvalue);
  if (compareVal != 0)
   {
    /* prev record deleted */
    AM_scanTable[scanDesc].nextIndex--;
    bcopy(pageBuf + AM_sl + (AM_scanTable[scanDesc].nextIndex -1)*recSize + 
    header->attrLength, &AM_scanTable[scanDesc].nextRecIdPtr,AM_si);
   }
 }
else 
  /* make the status busy - no more the first call */
  { AM_scanTable[scanDesc].status = BUSY;
    bcopy(pageBuf + AM_sl + (AM_scanTable[scanDesc].nextIndex - 1)*recSize,
    AM_scanTable[scanDesc].nextvalue, header->attrLength);
  }

/* copy the recId to be returned */
bcopy(&AM_scanTable[scanDesc].nextRecIdPtr,&recId,AM_si);

/* copy the place for next recId */
// bcopy(pageBuf + AM_scanTable[scanDesc].nextRecIdPtr + AM_si,
          // &AM_scanTable[scanDesc].nextRecIdPtr,AM_ss);


/* check if this keys list is over */
// if (AM_scanTable[scanDesc].nextRecIdPtr == (short)0)
if ((AM_scanTable[scanDesc].nextIndex + 1) <= (header->numKeys))
{
 AM_scanTable[scanDesc].nextIndex++;
 AM_scanTable[scanDesc].actindex++;
 bcopy(pageBuf + AM_sl + (AM_scanTable[scanDesc].nextIndex - 1)*recSize + 
 header->attrLength , &AM_scanTable[scanDesc].nextRecIdPtr, AM_si);
 bcopy(pageBuf + AM_sl + (AM_scanTable[scanDesc].nextIndex -1 )*recSize,
 AM_scanTable[scanDesc].nextvalue,header->attrLength); 
}
else
/* got to go to next page */
if (header->nextLeafPage == AM_NULL_PAGE)
{
  AM_scanTable[scanDesc].status = OVER;
  // printf("This should happen %d\n",header->nextLeafPage);
}
  
else
 {
  AM_scanTable[scanDesc].nextpageNum = header->nextLeafPage;
  AM_scanTable[scanDesc].nextIndex =  1;
  AM_scanTable[scanDesc].actindex = 1;
  errVal =PF_GetThisPage(AM_scanTable[scanDesc].fileDesc,
    header->nextLeafPage,&pageBuf);
  AM_Check;
  bcopy(pageBuf + AM_sl + header->attrLength,
     &AM_scanTable[scanDesc].nextRecIdPtr,AM_si);
  errVal = PF_UnfixPage(AM_scanTable[scanDesc].fileDesc
            ,header->nextLeafPage,FALSE);
  AM_Check;
  bcopy(pageBuf + AM_sl + (AM_scanTable[scanDesc].nextIndex -1 )*recSize,
  AM_scanTable[scanDesc].nextvalue,header->attrLength); 
  bcopy(pageBuf,header,AM_sl);
 }

/* If op is equal then see if you are done */
if (AM_scanTable[scanDesc].op == EQUAL)
  if ((AM_scanTable[scanDesc].lastpageNum <= AM_scanTable[scanDesc].nextpageNum)
    && (AM_scanTable[scanDesc].lastIndex < AM_scanTable[scanDesc].actindex))
     AM_scanTable[scanDesc].status = OVER;

/* see if you are at the last record if op is < or <= */
if ((AM_scanTable[scanDesc].op == LESS_THAN) || 
  (AM_scanTable[scanDesc].op == LESS_THAN_EQUAL))
{
   if ((AM_scanTable[scanDesc].lastpageNum == AM_scanTable[scanDesc].nextpageNum)
    && (AM_scanTable[scanDesc].lastIndex == AM_scanTable[scanDesc].actindex))
   {
      // printf("this should not happen %d\n",AM_scanTable[scanDesc].status);
      if(AM_scanTable[scanDesc].status!=OVER) AM_scanTable[scanDesc].status = LAST;
   }
  else  if ((AM_scanTable[scanDesc].lastpageNum == AM_scanTable[scanDesc].nextpageNum)
    && (AM_scanTable[scanDesc].lastIndex  <  AM_scanTable[scanDesc].actindex))
  {
        AM_scanTable[scanDesc].status = OVER;
  }
  else
    if (AM_scanTable[scanDesc].status == LAST)
  {
        AM_scanTable[scanDesc].status = OVER;
  }
}
        

return(recId);
}


/* terminates an index scan */
AM_CloseIndexScan(scanDesc)
int scanDesc;/* scan Descriptor*/

{
if ((scanDesc < 0) || (scanDesc > MAXSCANS - 1))
  {
   AM_Errno = AME_INVALID_SCANDESC;
   return(AME_INVALID_SCANDESC);
  }
AM_scanTable[scanDesc].status = FREE;
return(AME_OK);
}


GetLeftPageNum(fileDesc)
int fileDesc;

{
char *pageBuf;
int pageNum;
int errVal;

pageBuf = (char**)malloc(2*sizeof(char*));
pageNum = (int*)malloc(sizeof(int));

errVal = PF_GetFirstPage(fileDesc,&pageNum,&pageBuf);
AM_Check;
if (*pageBuf == 'l')
  AM_LeftPageNum = pageNum;
else
  AM_LeftPageNum = 2;
errVal = PF_UnfixPage(fileDesc,pageNum,FALSE);
AM_Check;
return(AM_LeftPageNum);

}
