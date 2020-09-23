/******************************************************************************
*
* Copyright (C) 2009 - 2014 Xilinx, Inc.  All rights reserved.
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* Use of the Software is limited solely to applications:
* (a) running on a Xilinx device, or
* (b) that interact with a Xilinx device through a bus or interconnect.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
* XILINX  BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
* WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF
* OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*
* Except as contained in this notice, the name of the Xilinx shall not be used
* in advertising or otherwise to promote the sale, use or other dealings in
* this Software without prior written authorization from Xilinx.
*
******************************************************************************/

/*
 * helloworld.c: simple test application
 *
 * This application configures UART 16550 to baud rate 9600.
 * PS7 UART (Zynq) is not initialized by this application, since
 * bootrom/bsp configures it to baud rate 115200
 *
 * ------------------------------------------------
 * | UART TYPE   BAUD RATE                        |
 * ------------------------------------------------
 *   uartns550   9600
 *   uartlite    Configurable only in HW design
 *   ps7_uart    115200 (configured by bootrom/bsp)
 */

#include <stdio.h>
#include "platform.h"
#include "xil_printf.h"
#include <stdlib.h>

int main()
{
	int d;

    init_platform();

    print("test Terminal program! \n\r");



    char key    = 0;
    char *pmp_str = "arty> ";
   	unsigned char 	int_tmp;
  	char			*dump_address;
  	unsigned long	start_address;
  	unsigned long	tmp_str;
	short			i,n;
	char		c_tmp[1000];
	char	ptr;

      printf( "%s" , pmp_str );

      while(1){
        key = fgetc( stdin );
        if( -1 == key ){
          continue;
        }
        switch( key ){
          case 0x0d:	//CR ïúãA
              break;
          case 0x0a:	//LF â¸çs
        	  printf( "\n\r%s" , pmp_str );
        	  break;
          case 'p':	//a
        	  printf( "\n\r[adr=%p]" , &ptr);
              break;
          case 'd':	//a
  			i=0;
  			n=1;
  			while(n){ //ÉäÉ^Å[ÉìÇ‹Ç≈ì«Ç›èoÇµ
  				c_tmp[i] = fgetc( stdin );
  				if( c_tmp[i] == '\r' ){
  					n=0;
  					c_tmp[i] = NULL;
  				}else	i++;
  			}
        	  sscanf(c_tmp," %lx", &start_address);
        	  dump_address = (char *)start_address;	//
        	  printf( "\n\r%sr address=0x%08x data=0x%02x" , pmp_str, dump_address, *(dump_address));
             break;


          case 'l':	//a
  			i=0;
  			n=1;
  			while(n){			// ÿ¿∞›∫∞ƒﬁÇ‹Ç≈ì«Ç›èoµäiî[ //
  				c_tmp[i] = fgetc( stdin );
  				if( c_tmp[i] == '\r' ){
  					n=0;
  					c_tmp[i] = NULL;
  				}else	i++;
  			}
        	  sscanf(c_tmp," %lx %x", &start_address, &int_tmp);
        	  dump_address = (char *)start_address;	//
       		*(dump_address) = int_tmp;

        	  printf( "\n\r%sw address=0x%08x data=0x%02x" , pmp_str, dump_address, *(dump_address));
             break;

          default:
        	  i=0;
    		  n=1;
    		  while(n){			// ÿ¿∞›∫∞ƒﬁÇ‹Ç≈ì«Ç›èoµäiî[ //
    				c_tmp[i] = fgetc( stdin );
    				if( c_tmp[i] == '\r' ){
    					n=0;
    					c_tmp[i] = NULL;
    				}else{
    					i++;
    				}
    			}
              printf( "unknown command\n\r" );
              break;
       		}
        }

////////////////////////test end
    cleanup_platform();
    return 0;
}
