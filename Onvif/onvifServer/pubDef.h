/*
 * pubDef.h
 *
 *  Created on: Apr 15, 2014
 *      Author: root
 */

#ifndef PUBDEF_H_
#define PUBDEF_H_

#define _DEBUG_


typedef unsigned int 	UINT;

#define INFO_LENGTH   			1024
#define SMALL_INFO_LENGTH		128
#define LEN_HOSTNAME			255			//hostname length
#define	LEN_IP					64

#define PORT_SERVER				80
#define PORT_PROBE				3702/*7838*/

#define IP_SEARCH				"239.255.255.250"/*"230.1.1.1"*/
#define IP_SERVER				"192.168.0.48"

#define SIZE_PROFILE			10			//profile size
//Return val
enum RET
{
	RET_FAILED = -1			//FAILED
	,RET_SUC = 0				//SUC
};


/*
struct STU_PROFILE
{
	char *cName;
	char *cToken;
};
*/
#endif /* PUBDEF_H_ */
