# Introduction #


uint8 ccGetPkg(uint8 **buf);
-->說明此函式參數意義,並描描述收的方式及行為**


void ccSendPkg(uint8 **buf);
-->說明此函式參數意義,並描描述送的方式及行為**


// 封包格式.,底下是範例供參考. (請按此修改)
/*** 0                   1                   2                   3
  * 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
  * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
  * |        Inv\_id                 |          Proto\_id             |
  * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
  * |         length                |Unit Identifer |  MODBUS PDU   |
  * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
  * 
  * The MBAP header is 7 bytes long, and includes the following fields :**

> inv\_id  -  [2 bytes](.md) invocation identification used for
> > transaction pairing


> proto\_id - [bytes](2.md) is always 0 for MODBUS services. Other
> > values are reserved for further extensions.


> length - [bytes](2.md) The length field is a byte count of the
> > remaining fields and includes the dst\_id and data fields.


> unit\_id - [byte](1.md) The unit identifier is used to identify a
> > remote server located on a non-TCP/IP network.
  * 
  * 
> > func\_code - [byte](1.md) MODBUS function code


> data - [bytes](n.md) This field is function code dependent and
> > usually contains information such as variable references,
  * 
  * Code    Name              Meaning
> > ----    --------         ------------
> > > 01    ILLEGAL FUNCTION  The function code received in the request
    * is not an allowable action for the server.


> 02    ILLEGAL DATA   The data address received in the request
> > ADDRESS        is not an allowable address for the server.

  * 

# Details #

Add your content here.  Format your content with:
  * Text in **bold** or _italic_
  * Headings, paragraphs, and lists
  * Automatic links to other wiki pages