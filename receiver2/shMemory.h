#ifndef INCLUDE_MFSHAREDMEM    // Inclusion guard
#define INCLUDE_MFSHAREDMEM


/******************************************************************************/
/*                   I N C L U D E D        F I L E S                         */
/******************************************************************************/

#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>

#ifdef MFSHAREDMEM_EXPORTS
#define MFSHAREDMEM_API __declspec(dllexport)
#else
#define MFSHAREDMEM_API __declspec(dllimport)
#endif

#define SHARED_MEMORY_SIZE 0x01000000

/******************************************************************************/
/*                          G L O B A L    D A T A                            */
/******************************************************************************/

HANDLE	shMemHandle = NULL;
HANDLE	threadMutex = NULL, processMutex = NULL;

#ifdef __cplusplus    // If used by C++ code,
extern "C" {          // we need to export the C interface
#endif

/*****************************************************************************
 *
 *    Function Name : MFShMemGetPointer
 *    Function Id   : N/A
 *
 *    Author        : Francesco Aliprandi, NEXT for SelexES
 *    Creation Date : 02/04/2012
 *    Description   : Return the shared memory base address
 *					  
 *
 *
 *    Comments  :      None
 *
 *    Result Value
 *      Name        : N/A
 *      Type        : unsigned char*
 *      Description : Start address of the shared memory
 *					  							
 *
 *    Parameters
 *      Name        : N/A
 *      Type        : N/A
 *      Direction   : N/A
 *      Description : N/A 
 *                    
 *
 *****************************************************************************/
MFSHAREDMEM_API unsigned char *__stdcall MFShMemGetPointer(void);

/*****************************************************************************
 *
 *    Function Name : MFShMemRead
 *    Function Id   : N/A
 *
 *    Author        : Francesco Aliprandi, NEXT for SelexES
 *    Creation Date : 02/04/2012
 *    Description   : Read a data buffer from the shared memory
 *					  
 *
 *
 *    Comments  :     None
 *
 *    Result Value
 *      Name        : N/A
 *      Type        : N/A
 *      Description : N/A
 *					  							
 *
 *    Parameters
 *      Name        : destBuffer
 *      Type        : unsigned char*
 *      Direction   : out
 *      Description : Destination Data Buffer
 *        
 *      Name        : startOffset
 *      Type        : const unsigned int
 *      Direction   : in
 *      Description : Starting location of the	buffer to be copied 
 *        
 *      Name        : numOfBytes
 *      Type        : const unsigned int
 *      Direction   : in
 *      Description : Number of bytes to be stored in destBuffer
 *                    
 *
 *****************************************************************************/
MFSHAREDMEM_API void  __stdcall MFShMemRead (unsigned char *destBuffer, const unsigned int startOffset, 
                                                const unsigned int numOfBytes);

/*****************************************************************************
 *
 *    Function Name : MFShMemWrite
 *    Function Id   : N/A
 *
 *    Author        : Francesco Aliprandi, NEXT for SelexES
 *    Creation Date : 02/04/2012
 *    Description   : Write a data buffer to the shared memory
 *					  
 *
 *
 *    Comments  :     None
 *
 *    Result Value
 *      Name        : N/A
 *      Type        : N/A
 *      Description : N/A
 *					  							
 *
 *    Parameters
 *      Name        : sourceBuffer
 *      Type        : unsigned char*
 *      Direction   : in
 *      Description : Source Data Buffer
 *        
 *      Name        : startOffset
 *      Type        : const unsigned int
 *      Direction   : in
 *      Description : Starting location of the	buffer to be copied 
 *        
 *      Name        : numOfBytes
 *      Type        : const unsigned int
 *      Direction   : in
 *      Description : Number of bytes to be stored in the shared memory
 *                    
 *
 *****************************************************************************/
MFSHAREDMEM_API void  __stdcall MFShMemWrite(const unsigned char *sourceBuffer, const unsigned int startOffset, 
                                                const unsigned int numOfBytes);

/*****************************************************************************
 *
 *    Function Name : MFShMemSend
 *    Function Id   : N/A
 *
 *    Author        : Francesco Aliprandi, NEXT for SelexES
 *    Creation Date : 02/04/2012
 *    Description   : Signal that a reserved memory area is ready to be 
 *					  transmitted
 *
 *
 *    Comments  :     None
 *
 *    Result Value
 *      Name        : N/A
 *      Type        : char
 *      Description : 0 on success, -1 on error
 *					  							
 *
 *    Parameters
 *      Name        : startOffset
 *      Type        : const unsigned int
 *      Direction   : in
 *      Description : Starting location of the	buffer to be transmitted 
 *        
 *      Name        : numOfBytes
 *      Type        : const unsigned int
 *      Direction   : in
 *      Description : Number of bytes to be transmitted (max is 
 *                    MAX_TX_PAYLOAD_SIZE)
 *
 *****************************************************************************/
MFSHAREDMEM_API char  __stdcall MFShMemSend (const unsigned int startOffset, const unsigned int numOfBytes);

/*****************************************************************************
 *
 *    Function Name : MFShMemEnableComm
 *    Function Id   : N/A
 *
 *    Author        : Francesco Aliprandi, NEXT for SelexES
 *    Creation Date : 02/04/2012
 *    Description   : Enable shared memory capability to exchange parts of 
 *					  its area along local area network
 *
 *
 *    Comments  :     None
 *
 *    Result Value
 *      Name        : N/A
 *      Type        : unsigned char
 *      Description : 0 on success, 1 if communication is already enabled, 
 *					  error code otherwise							
 *
 *    Parameters
 *      Name        : listFile
 *      Type        : const char*
 *      Direction   : in
 *      Description : path to file containing other machines IP/port pairs		
 *        
 *
 *****************************************************************************/
//unsigned char __stdcall MFShMemEnableComm(const char* listFile);

/*****************************************************************************
 *
 *    Function Name : MFShMemDisableComm
 *    Function Id   : N/A
 *
 *    Author        : Francesco Aliprandi, NEXT for SelexES
 *    Creation Date : 02/04/2012
 *    Description   : Disable shared memory capability to exchange parts of 
 *					  its area along local area network
 *
 *
 *    Comments  :     None
 *
 *    Result Value
 *      Name        : N/A
 *      Type        : unsigned char
 *      Description : 0 on success, error code otherwise 
 *					  						
 *
 *    Parameters
 *      Name        : N/A
 *      Type        : N/A
 *      Direction   : N/A
 *      Description : N/A	
 *        			  
 *
 *****************************************************************************/
MFSHAREDMEM_API unsigned char __stdcall MFShMemDisableComm(void);

#ifdef __cplusplus
}
#endif

#endif   // Inclusion guard INCLUDE_MFSHAREDMEM