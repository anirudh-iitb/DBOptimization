We optimize the way indexing is done for duplicate keys in a B+ tree secondary index using a) bucket of pointers b) Appending primary key to the search key 


When a new index is created:

A leaf is created with header containing the attributes:
	pageType = 'l'
	nextLeafPage = null
	recIdPtr = PF_PAGE_SIZE (page size of a PF)
	keyPtr = AM_sl (size of a leaf header)
	freeListPtr = AM_NULL (null)
	numinfreeList = 0
	attrLength = attrLength
	numKeys = 0
	maxKeys = max - 1		max%2==1	(max = (PF_PAGE_SIZE - AM_sint - AM_si)/(AM_si + attrLength))
			  max           max%2==0
	For some reason maximum number of keys in an internal node(?) has to be even always

The leaf is stored in one page in a PF. Thus, the (recIDPtr - keyPtr) gives the memory left for inserting records into the leaf. If this values is less than the size of a single record, at any stage, then the record cannot be inserted into the leaf. So, I am guessing the keyPtr is the pointer to the the latest key or the farthest key of some sort(the key which is present at the end). We use freelistPtr to reach all the intermediate free spaces(formed due to deletion of records). In other words, freelistPtr stores the ptr to the earliest free space (numinfreeList stores the total number of free spaces).

The significance of recIdPtr remains yet to be seen.