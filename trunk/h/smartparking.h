#ifndef	__SMARTPARKING__
#define __SMARTPARKING__
#include    "define.h"

// 封包格式是這樣子去說的.,底下是範例供你們參考.
/*
 *   0                   1                   2                   3
 *   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
 *  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *  |        Inv_id                 |          Proto_id             |
 *  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *  |         length                |Unit Identifer |  MODBUS PDU   |
 *  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *
 * The MBAP header is 7 bytes long, and includes the following fields :

    inv_id  -  [ 2 bytes] invocation identification used for
               transaction pairing

    proto_id - [2 bytes] is always 0 for MODBUS services. Other
               values are reserved for further extensions.

    length - [2 bytes] The length field is a byte count of the
             remaining fields and includes the dst_id and data fields.

    unit_id - [1 byte] The unit identifier is used to identify a
              remote server located on a non-TCP/IP network.
 *
 *
    func_code - [1 byte] MODBUS function code

    data - [n bytes] This field is function code dependent and
           usually contains information such as variable references,
 *
 *   Code    Name              Meaning
     ----    --------         ------------
      01    ILLEGAL FUNCTION  The function code received in the request
   *                           is not an allowable action for the server.

     02    ILLEGAL DATA   The data address received in the request
            ADDRESS        is not an allowable address for the server.

 */

/***/




typedef struct _packet {
  uint8 length;
  uint8 type:4; // for different intention
  uint8 subtype:4;
  uint8 srcID;  //source ID
  uint8 dstID;  // destionation ID
  uint8 Data[4];  // data to be transmited/received
  uint32 crc;  //for crc
} Packet;



typedef struct client_info {
  uint8 ID;
  uint8 status;
  uint8 res[2]; //reserved
} Client;

#define MAX_CLIENT 10

//按word檔做, 但尚不知其意
typedef enum {RESET=1,ASK,ECHO,CMD, ACK} TYPE;
typedef enum {ENTER, PARKING} SUBTYPE ;  // role?









#endif