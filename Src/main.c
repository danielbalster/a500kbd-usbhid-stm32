/**
  ******************************************************************************
  * File Name          : main.c
  * Description        : Main program body
  ******************************************************************************
  * This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * Copyright (c) 2017 STMicroelectronics International N.V. 
  * All rights reserved.
  *
  * Redistribution and use in source and binary forms, with or without 
  * modification, are permitted, provided that the following conditions are met:
  *
  * 1. Redistribution of source code must retain the above copyright notice, 
  *    this list of conditions and the following disclaimer.
  * 2. Redistributions in binary form must reproduce the above copyright notice,
  *    this list of conditions and the following disclaimer in the documentation
  *    and/or other materials provided with the distribution.
  * 3. Neither the name of STMicroelectronics nor the names of other 
  *    contributors to this software may be used to endorse or promote products 
  *    derived from this software without specific written permission.
  * 4. This software, including modifications and/or derivative works of this 
  *    software, must execute solely and exclusively on microcontroller or
  *    microprocessor devices manufactured by or for STMicroelectronics.
  * 5. Redistribution and use of this software other than as permitted under 
  *    this license is void and will automatically terminate your rights under 
  *    this license. 
  *
  * THIS SOFTWARE IS PROVIDED BY STMICROELECTRONICS AND CONTRIBUTORS "AS IS" 
  * AND ANY EXPRESS, IMPLIED OR STATUTORY WARRANTIES, INCLUDING, BUT NOT 
  * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A 
  * PARTICULAR PURPOSE AND NON-INFRINGEMENT OF THIRD PARTY INTELLECTUAL PROPERTY
  * RIGHTS ARE DISCLAIMED TO THE FULLEST EXTENT PERMITTED BY LAW. IN NO EVENT 
  * SHALL STMICROELECTRONICS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
  * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
  * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, 
  * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF 
  * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING 
  * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
  * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f1xx_hal.h"
#include "usb_device.h"

/* USER CODE BEGIN Includes */

#include <stdarg.h>
#include <stdint.h>
#include <limits.h>
#include "usbd_hid.h"
#include "usbhid.h"
#include "dwt_stm32_delay.h"

/* USER CODE END Includes */

/* Private variables ---------------------------------------------------------*/
TIM_HandleTypeDef htim1;
UART_HandleTypeDef huart1;

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/

#define SYSTEM_US_TICKS (SystemCoreClock / 1000000) // cycles per microsecond


// http://www.keyboard-layout-editor.com/##@_name=Amiga%20500%20Keyboard%20w%2F%2F%20Custom%20Mapping&author=Daniel%20Balster&background_name=PBT%20Black&style=background-image%2F:%20url('%2F%2Fbg%2F%2Fplastic%2F%2Fpbt-black.png')%2F%3B&$$hashKey=0DF%3B&radii=10&css=.db%20%7B%7D%0D%0A.lmb%2F:after%20%7B%20%0D%0A%20%20%2F%2F*%20Set%20the%20background%20for%20this%20glyph%20to%20your%20image%20*%2F%2F%0D%0A%20%20background-image%2F:%20url('https%2F:%2F%2F%2F%2Fimage.flaticon.com%2F%2Ficons%2F%2Fsvg%2F%2F32%2F%2F32041.svg')%2F%3B%20%0D%0A%20%20background-repeat%2F:%20no-repeat%2F%3B%0D%0A%20%20background-position%2F:%20center%2F%3B%0D%0A%0D%0A%20%20%2F%2F*%20Content%20is%20required%20for%20it%20to%20appear%2F%3B%20this%20is%20a%20non-breaking-space%20*%2F%2F%0D%0A%20%20content%2F:'%5C00a0'%2F%3B%20%0D%0A%20%20display%2F:inline-block%2F%3B%20%0D%0A%0D%0A%20%20%2F%2F*%20Sizing%20in%20EMs%20allows%20the%20glyph%20to%20scale%20with%20the%20font-size%20*%2F%2F%0D%0A%20%20width%2F:%201em%2F%3B%20%0D%0A%20%20height%2F:%201em%2F%3B%20%0D%0A%20%20background-size%2F:%201em%2F%3B%20%0D%0A%7D%0D%0A%0D%0A.rmb%2F:after%20%7B%20%0D%0A%20%20%2F%2F*%20Set%20the%20background%20for%20this%20glyph%20to%20your%20image%20*%2F%2F%0D%0A%20%20background-image%2F:%20url('https%2F:%2F%2F%2F%2Fimage.flaticon.com%2F%2Ficons%2F%2Fsvg%2F%2F31%2F%2F31532.svg')%2F%3B%20%0D%0A%20%20background-repeat%2F:%20no-repeat%2F%3B%0D%0A%20%20background-position%2F:%20center%2F%3B%0D%0A%0D%0A%20%20%2F%2F*%20Content%20is%20required%20for%20it%20to%20appear%2F%3B%20this%20is%20a%20non-breaking-space%20*%2F%2F%0D%0A%20%20content%2F:'%5C00a0'%2F%3B%20%0D%0A%20%20display%2F:inline-block%2F%3B%20%0D%0A%0D%0A%20%20%2F%2F*%20Sizing%20in%20EMs%20allows%20the%20glyph%20to%20scale%20with%20the%20font-size%20*%2F%2F%0D%0A%20%20width%2F:%201em%2F%3B%20%0D%0A%20%20height%2F:%201em%2F%3B%20%0D%0A%20%20background-size%2F:%201em%2F%3B%20%0D%0A%7D%0D%0A.pointer%2F:after%20%7B%20%0D%0A%20%20%2F%2F*%20Set%20the%20background%20for%20this%20glyph%20to%20your%20image%20*%2F%2F%0D%0A%20%20background-image%2F:%20url('https%2F:%2F%2F%2F%2Fwww.shareicon.net%2F%2Fdownload%2F%2F2016%2F%2F11%2F%2F03%2F%2F850264%2F_arrow.svg')%2F%3B%20%0D%0A%20%20background-repeat%2F:%20no-repeat%2F%3B%0D%0A%20%20background-position%2F:%20center%2F%3B%0D%0A%0D%0A%20%20%2F%2F*%20Content%20is%20required%20for%20it%20to%20appear%2F%3B%20this%20is%20a%20non-breaking-space%20*%2F%2F%0D%0A%20%20content%2F:'%5C00a0'%2F%3B%20%0D%0A%20%20display%2F:inline-block%2F%3B%20%0D%0A%0D%0A%20%20%2F%2F*%20Sizing%20in%20EMs%20allows%20the%20glyph%20to%20scale%20with%20the%20font-size%20*%2F%2F%0D%0A%20%20width%2F:%201em%2F%3B%20%0D%0A%20%20height%2F:%201em%2F%3B%20%0D%0A%20%20background-size%2F:%201em%2F%3B%20%0D%0A%7D%0D%0A&plate:true%3B&@_c=%23aca693&p=SA%20R1%3B&=Esc&_x:0.5&w:1.25%3B&=F1%0AF11%0A%0A%3Ci%20class%2F='kb%20kb-Multimedia-Rewind-Start'%3E%3C%2F%2Fi%3E&_w:1.25%3B&=F2%0AF12%0A%0A%3Ci%20class%2F='kb%20kb-Multimedia-Stop'%3E%3C%2F%2Fi%3E&_w:1.25%3B&=F3%0AF13%0A%0A%3Ci%20class%2F='kb%20kb-Multimedia-Play-Pause'%3E%3C%2F%2Fi%3E&_w:1.25%3B&=F4%0AF14%0A%0A%3Ci%20class%2F='kb%20kb-Multimedia-FastForward-End'%3E%3C%2F%2Fi%3E&_w:1.25%3B&=F5%0AF15%0A%0A%3Ci%20class%2F='kb%20kb-Multimedia-Eject'%3E%3C%2F%2Fi%3E&_x:0.5&w:1.25%3B&=F6%0AF16&_w:1.25%3B&=F7%0AF17&_w:1.25%3B&=F8%0AF18%0A%0A%3Ci%20class%2F='kb%20kb-Multimedia-Mute-3'%3E%3C%2F%2Fi%3E&_w:1.25%3B&=F9%0AF19%0A%0A%3Ci%20class%2F='kb%20kb-Multimedia-Volume-Down-2'%3E%3C%2F%2Fi%3E&_w:1.25%3B&=F10%0AF20%0A%0A%3Ci%20class%2F='kb%20kb-Multimedia-Volume-Up-1'%3E%3C%2F%2Fi%3E%3B&@_y:0.25&w:1.5%3B&=~%0A'%0A%C2%B0%0A%5E&_c=%23d8d2c3&fa@:5&:5%3B%3B&=!%0A1&=%22%0A2%0A%0A%0A%2F@&=%C2%A7%0A3&=$%0A4%0A%0A%0A%C2%B0&=%25%0A5&=%2F&%0A6&=%2F%2F%0A7%0A%0A%7B&=(%0A8%0A%0A%5B&=)%0A9%0A%0A%5D&=%2F=%0A0%0A%0A%7D&=%3F%0A%C3%9F%0A%0A%5C&=%60%0A%C2%B4&_c=%23c87e74%3B&=%7C%0A%5C&_c=%23aca693&fa@:9%3B%3B&=%3Ci%20class%2F='kb%20kb-Arrows-Left'%3E%3C%2F%2Fi%3E&_x:0.75&c=%23768e72&f:3&w:1.5%3B&=Del%0A%0A%3Ci%20class%2F='db%20lmb'%3E%3C%2F%2Fi%3E%0A%0A%0A%0A%0A%0A%0A%0Aswitch%20fn%3B&@_c=%23aca693&f:3&w:2%3B&=%3Ci%20class%2F='kb%20kb-Line-Start'%3E%3C%2F%2Fi%3E%0A%3Ci%20class%2F='kb%20kb-Line-End'%3E%3C%2F%2Fi%3E&_c=%23d8d2c3&fa@:7%3B%3B&=Q&=W&=E&=R&=T&=Z&=U&=I&=O&=P&=%C3%9C&_fa@:5&:5%3B%3B&=*%0A+%0A%0A~&_x:0.25&c=%23aca693&a:7&fa@:9%3B&w:1.25&h:2&w2:1.5&h2:1&x2:-0.25%3B&=%3Ci%20class%2F='kb%20kb-Return-2'%3E%3C%2F%2Fi%3E%3B&@_a:4&f:3&w:1.25%3B&=Ctrl%0A%0A%0AL%20Alt&=%0ALock%0A%0A%0A%0A%0ACaps&_c=%23d8d2c3&fa@:7%3B%3B&=A&=S&=D&_n:true%3B&=F&=G&=H&_n:true%3B&=J&=K&=L&=%C3%96&=%C3%84&_f:3%3B&=%5E%0A%23%0A'%3B&@_c=%23aca693&fa@:9%3B&w:1.75%3B&=%3Ci%20class%2F='kb%20kb-Arrows-Top-4'%3E%3C%2F%2Fi%3E&_c=%23d8d2c3&f:3%3B&=%3E%0A%3C%0A%0A%7C&_fa@:7%3B%3B&=Y&=X&=C&=V&=B&=N&_c=%23768e72%3B&=M%0A%0A%0A%3Ci%20class%2F='db%20pointer'%3E%3C%2F%2Fi%3E&_c=%23d8d2c3&fa@:5&:5%3B%3B&=%2F%3B%0A,&=%2F:%0A.&=%2F_%0A-&_c=%23aca693&fa@:9%3B&w:2.75%3B&=%3Ci%20class%2F='kb%20kb-Arrows-Top-4'%3E%3C%2F%2Fi%3E%3B&@_x:0.75&t=%23171718&f:3&w:1.25%3B&=Alt%0A%0A%0AL%20Ctrl&_t=%23000000&f:3&w:1.25%3B&=%3Ci%20class%2F='kb%20kb-logo-commodore'%3E%3C%2F%2Fi%3E%0A%0A%0A%3Ci%20class%2F='kb%20kb-logo-windows-8'%3E%3C%2F%2Fi%3E&_c=%23d8d2c3&a:7&w:9%3B&=&_c=%23aca693&a:4&f:3&w:1.25%3B&=%3Ci%20class%2F='kb%20kb-logo-amiga'%3E%3C%2F%2Fi%3E%0A%0A%0AAlt%20Gr&_f:3&w:1.25%3B&=Alt%0A%0A%0AR%20Ctrl%3B&@_rx:0.25&y:1.25&x:17.5&c=%23768e72&f:3&w:1.5%3B&=Help%0A%0A%3Ci%20class%2F='db%20rmb'%3E%3C%2F%2Fi%3E&_x:0.75&c=%23aca693&a:0&f:3%3B&=%7B%0A%5B%0A%0A%0ANum%20L&_f:3%3B&=%7D%0A%5D%0A%0A%0AScr%20L&_a:4&f:3%3B&=%2F%2F&_c=%23768e72&a:0&f:3%3B&=*%0A%0A%0AMouse%20Off%0APrt%20Sc%3B&@_x:19.75&c=%23d8d2c3&f:3%3B&=7%0A%0A%0A%0AHome&_a:4&f:3%3B&=8%0A%0A%0A%0A%3Ci%20class%2F='kb%20kb-Arrows-Up'%3E%3C%2F%2Fi%3E&_a:0&f:3%3B&=9%0A%0A%0A%0A%0APg%20Up&_c=%23768e72&a:4&f:3%3B&=-%0A%0A%0ASpd-%3B&@_x:17&c=%23c5c7ca&f:3%3B&=%3Ci%20class%2F='kb%20kb-Arrows-Up'%3E%3C%2F%2Fi%3E&_x:1.75&c=%23d8d2c3&f:3%3B&=4%0A%0A%0A%0A%3Ci%20class%2F='kb%20kb-Arrows-Left'%3E%3C%2F%2Fi%3E&_f:3%3B&=5&_f:3%3B&=6%0A%0A%0A%0A%3Ci%20class%2F='kb%20kb-Arrows-Right'%3E%3C%2F%2Fi%3E&_c=%23768e72&f:3%3B&=+%0A%0A%0ASpd+%3B&@_x:16&c=%23c5c7ca&f:3%3B&=%3Ci%20class%2F='kb%20kb-Arrows-Left'%3E%3C%2F%2Fi%3E&_f:3%3B&=%3Ci%20class%2F='kb%20kb-Arrows-Down'%3E%3C%2F%2Fi%3E&_f:3%3B&=%3Ci%20class%2F='kb%20kb-Arrows-Right'%3E%3C%2F%2Fi%3E&_x:0.75&c=%23d8d2c3&a:0&f:3%3B&=1%0A%0A%0A%0AEnd&_a:4&f:3%3B&=2%0A%0A%0A%0A%3Ci%20class%2F='kb%20kb-Arrows-Down'%3E%3C%2F%2Fi%3E&_a:0&f:3%3B&=3%0A%0A%0A%0A%0APg%20Dn&_c=%23aca693&a:4&f:3&h:2%3B&=Enter%3B&@_x:19.75&c=%23d8d2c3&f:3&w:2%3B&=0%0A%0A%0A%0AIns&_f:3%3B&=1%0A%0A%0A%0ADel

// page 362 of Amiga Hardware Reference Manual

enum {
  AMIGA_KEY_TILDE,
  AMIGA_KEY_1,
  AMIGA_KEY_2,
  AMIGA_KEY_3,
  AMIGA_KEY_4,
  AMIGA_KEY_5,
  AMIGA_KEY_6,
  AMIGA_KEY_7,
  AMIGA_KEY_8,
  AMIGA_KEY_9,
  AMIGA_KEY_0,
  AMIGA_KEY_UNDERSCORE,
  AMIGA_KEY_PLUS,
  AMIGA_KEY_BACKSLASH,
  AMIGA_KEY_NOT_CONNECTED_0E,
  AMIGA_KEY_KP_0,

  AMIGA_KEY_Q,
  AMIGA_KEY_W,
  AMIGA_KEY_E,
  AMIGA_KEY_R,
  AMIGA_KEY_T,
  AMIGA_KEY_Y,
  AMIGA_KEY_U,
  AMIGA_KEY_I,
  AMIGA_KEY_O,
  AMIGA_KEY_P,
  AMIGA_KEY_OPEN_BRACKET,
  AMIGA_KEY_CLOSE_BRACKET,
  AMIGA_KEY_NOT_CONNECTED_1C,
  AMIGA_KEY_KP_1,
  AMIGA_KEY_KP_2,
  AMIGA_KEY_KP_3,
                                                  
  AMIGA_KEY_A,
  AMIGA_KEY_S,
  AMIGA_KEY_D,
  AMIGA_KEY_F,
  AMIGA_KEY_G,
  AMIGA_KEY_H,
  AMIGA_KEY_J,
  AMIGA_KEY_K,
  AMIGA_KEY_L,
  AMIGA_KEY_COLON,
  AMIGA_KEY_QUOTE,
  AMIGA_KEY_HASH,
  AMIGA_KEY_NOT_CONNECTED_2C,
  AMIGA_KEY_KP_4,
  AMIGA_KEY_KP_5,
  AMIGA_KEY_KP_6,

  AMIGA_KEY_NON_US_BACKSLASH_AND_SLASH,
  AMIGA_KEY_Z,
  AMIGA_KEY_X,
  AMIGA_KEY_C,
  AMIGA_KEY_V,
  AMIGA_KEY_B,
  AMIGA_KEY_N,
  AMIGA_KEY_M,
  AMIGA_KEY_COMMA,
  AMIGA_KEY_DOT,
  AMIGA_KEY_SLASH,
  AMIGA_KEY_NOT_CONNECTED_3B,
  AMIGA_KEY_KP_DOT_AND_DELETE,
  AMIGA_KEY_KP_7,
  AMIGA_KEY_KP_8,
  AMIGA_KEY_KP_9,
                                                  
  AMIGA_KEY_SPACEBAR,
  AMIGA_KEY_BACKSPACE,
  AMIGA_KEY_TAB,
  AMIGA_KEY_KP_ENTER,
  AMIGA_KEY_ENTER,
  AMIGA_KEY_ESCAPE,
  AMIGA_KEY_DELETE,
  AMIGA_KEY_NOT_CONNECTED_47,
  AMIGA_KEY_NOT_CONNECTED_48,
  AMIGA_KEY_NOT_CONNECTED_49,
  AMIGA_KEY_KP_MINUS,
  AMIGA_KEY_NOT_CONNECTED_4B,
  AMIGA_KEY_UP,
  AMIGA_KEY_DOWN,
  AMIGA_KEY_RIGHT,
  AMIGA_KEY_LEFT,
                                                  
  AMIGA_KEY_F1,
  AMIGA_KEY_F2,
  AMIGA_KEY_F3,
  AMIGA_KEY_F4,
  AMIGA_KEY_F5,
  AMIGA_KEY_F6,
  AMIGA_KEY_F7,
  AMIGA_KEY_F8,
  AMIGA_KEY_F9,
  AMIGA_KEY_F10,
  AMIGA_KEY_KP_NUM_LOCK,
  AMIGA_KEY_SCROLL_LOCK,
  AMIGA_KEY_KP_DIVIDE,
  AMIGA_KEY_KP_MULTIPLY,
  AMIGA_KEY_KP_PLUS,
  AMIGA_KEY_HELP,

  AMIGA_KEY_MODIFIER_LEFT_SHIFT,
  AMIGA_KEY_MODIFIER_RIGHT_SHIFT,
  AMIGA_KEY_CAPS_LOCK,
  AMIGA_KEY_MODIFIER_LEFT_CTRL,
  AMIGA_KEY_MODIFIER_LEFT_ALT,
  AMIGA_KEY_MODIFIER_RIGHT_ALT,
  AMIGA_KEY_MODIFIER_LEFT_UI,
  AMIGA_KEY_MODIFIER_RIGHT_UI,
};

const uint8_t amiga_to_hid[128] = {
  HIDKEY_TILDE,                                  // 00
  HIDKEY_1,                                      // 01
  HIDKEY_2,                                      // 02
  HIDKEY_3,                                      // 03
  HIDKEY_4,                                      // 04
  HIDKEY_5,                                      // 05
  HIDKEY_6,                                      // 06
  HIDKEY_7,                                      // 07
  HIDKEY_8,                                      // 08
  HIDKEY_9,                                      // 09
  HIDKEY_0,                                      // 0A
  HIDKEY_UNDERSCORE,                             // 0B
  HIDKEY_PLUS,                                   // 0C
  HIDKEY_BACKSLASH,                              // 0D
  0,                                             // 0E not connected
  HIDKEY_KP_0,                                   // 0F

  HIDKEY_Q,                                      // 10
  HIDKEY_W,                                      // 11
  HIDKEY_E,                                      // 12
  HIDKEY_R,                                      // 13
  HIDKEY_T,                                      // 14
  HIDKEY_Y,                                      // 15
  HIDKEY_U,                                      // 16
  HIDKEY_I,                                      // 17
  HIDKEY_O,                                      // 18
  HIDKEY_P,                                      // 19
  HIDKEY_OPEN_BRACKET,                           // 1A
  HIDKEY_CLOSE_BRACKET,                          // 1B
  0,                                             // 1C not connected
  HIDKEY_KP_1,                                   // 1D
  HIDKEY_KP_2,                                   // 1E
  HIDKEY_KP_3,                                   // 1F
                                                  
  HIDKEY_A,                                      // 20
  HIDKEY_S,                                      // 21
  HIDKEY_D,                                      // 22
  HIDKEY_F,                                      // 23
  HIDKEY_G,                                      // 24
  HIDKEY_H,                                      // 25
  HIDKEY_J,                                      // 26
  HIDKEY_K,                                      // 27
  HIDKEY_L,                                      // 28
  HIDKEY_COLON,                                  // 29
  HIDKEY_QUOTE,                                  // 2A
  HIDKEY_HASH,                                   // 2B
  0,                                             // 2C not connected
  HIDKEY_KP_4,                                   // 2D
  HIDKEY_KP_5,                                   // 2E
  HIDKEY_KP_6,                                   // 2F

  HIDKEY_NON_US_BACKSLASH_AND_SLASH,             // 30
  HIDKEY_Z,                                      // 31
  HIDKEY_X,                                      // 32
  HIDKEY_C,                                      // 33
  HIDKEY_V,                                      // 34
  HIDKEY_B,                                      // 35
  HIDKEY_N,                                      // 36
  HIDKEY_M,                                      // 37
  HIDKEY_COMMA,                                  // 38
  HIDKEY_DOT,                                    // 39
  HIDKEY_SLASH,                                  // 3A
  0,                                             // 3B // not connected
  HIDKEY_KP_DOT_AND_DELETE,                      // 3C
  HIDKEY_KP_7,                                   // 3D
  HIDKEY_KP_8,                                   // 3E
  HIDKEY_KP_9,                                   // 3F
                                                  
  HIDKEY_SPACEBAR,                               // 40
  HIDKEY_BACKSPACE,                              // 41
  HIDKEY_TAB,                                    // 42
  HIDKEY_KP_ENTER,                               // 43
  HIDKEY_ENTER,                                  // 44
  HIDKEY_ESCAPE,                                 // 45
  HIDKEY_DELETE,                                 // 46
  0,                                             // 47
  0,                                             // 48
  0,                                             // 49
  HIDKEY_KP_MINUS,                               // 4A
  0,                                             // 4B
  HIDKEY_UP,                                     // 4C
  HIDKEY_DOWN,                                   // 4D
  HIDKEY_RIGHT,                                  // 4E
  HIDKEY_LEFT,                                   // 4F
                                                  
  HIDKEY_F1,                                     // 50
  HIDKEY_F2,                                     // 51
  HIDKEY_F3,                                     // 52
  HIDKEY_F4,                                     // 53
  HIDKEY_F5,                                     // 54
  HIDKEY_F6,                                     // 55
  HIDKEY_F7,                                     // 56
  HIDKEY_F8,                                     // 57
  HIDKEY_F9,                                     // 58
  HIDKEY_F10,                                    // 59
  HIDKEY_KP_NUM_LOCK,                            // 5A Numeric pad left (
  HIDKEY_SCROLL_LOCK,                            // 5B Numeric pad right )
  HIDKEY_KP_DIVIDE,                              // 5C
  HIDKEY_KP_MULTIPLY,                            // 5D
  HIDKEY_KP_PLUS,                                // 5E
  HIDKEY_HELP,                                   // 5F help

  HIDKEY_MODIFIER_LEFT_SHIFT,                    // 60 Left Shift
  HIDKEY_MODIFIER_RIGHT_SHIFT,                   // 61 Right Shift
  HIDKEY_CAPS_LOCK,                              // 62 Caps Lock
  HIDKEY_MODIFIER_LEFT_CTRL,                     // 63 Control
  HIDKEY_MODIFIER_LEFT_ALT,                      // 64 Left Alt
  HIDKEY_MODIFIER_RIGHT_ALT,                     // 65 Right Alt
  HIDKEY_MODIFIER_LEFT_UI,                       // 66 Left Amiga
  HIDKEY_MODIFIER_RIGHT_UI,                      // 67 Right Amiga
  0,                                             // 68
  0,                                             // 69
  0,                                             // 6A
  0,                                             // 6B
  0,                                             // 6C
  0,                                             // 6D
  0,                                             // 6E
  0,                                             // 6F
                                                  
  0,                                             // 70
  0,                                             // 71
  0,                                             // 72
  0,                                             // 73
  0,                                             // 74
  0,                                             // 75
  0,                                             // 76
  0,                                             // 77
  0,                                             // 78
  0,                                             // 79
  0,                                             // 7A
  0,                                             // 7B
  0,                                             // 7C
  0,                                             // 7D
  0,                                             // 7E
  0,                                             // 7F
};
const uint8_t ascii2hid[128] = {
  0, // 00
  0, // 01
  0, // 02
  0, // 03
  0, // 04
  0, // 05
  0, // 06
  0, // 07
  0, // 08
  0, // 09
  0, // 0A
  0, // 0B
  0, // 0C
  0, // 0D
  0, // 0E
  0, // 0F
  
  0, // 10
  0, // 11
  0, // 12
  0, // 13
  0, // 14
  0, // 15
  0, // 16
  0, // 17
  0, // 18
  0, // 19
  0, // 1A
  0, // 1B
  0, // 1C
  0, // 1D
  0, // 1E
  0, // 1F

  HIDKEY_SPACEBAR, // 20 space
  0, // 21 !
  0, // 22 "
  0, // 23 #
  0, // 24 $
  0, // 25 %
  0, // 26 &
  0, // 27 '
  0, // 28 (
  0, // 29 )
  0, // 2A *
  0, // 2B +
  0, // 2C ,
  0, // 2D -
  0, // 2E .
  0, // 2F /

  0, // 30 0
  0, // 31 1
  0, // 32 2
  0, // 33 3
  0, // 34 4
  0, // 35 5
  0, // 36 6
  0, // 37 7
  0, // 38 8
  0, // 39 9
  0, // 3A :
  0, // 3B ;
  0, // 3C <
  0, // 3D =
  0, // 3E >
  0, // 3F ?

  0, // 40 @
  0, // 41 A
  0, // 42 B
  0, // 43 C
  0, // 44 D
  0, // 45 E
  0, // 46 F
  0, // 47 G
  0, // 48 H
  0, // 49 I
  0, // 4A J
  0, // 4B K
  0, // 4C L
  0, // 4D M
  0, // 4E N
  0, // 4F O

  0, // 50 P
  0, // 51 Q
  0, // 52 R
  0, // 53 S
  0, // 54 T
  0, // 55 U
  0, // 56 V
  0, // 57 W
  0, // 58 X
  0, // 59 Y
  0, // 5A Z
  0, // 5B [
  0, // 5C 
  0, // 5D ]
  0, // 5E ^
  0, // 5F _

  0, // 60 apo
  HIDKEY_A, // 61 a
  HIDKEY_B, // 62 b
  HIDKEY_C, // 63 c
  HIDKEY_D, // 64 d
  HIDKEY_E, // 65 e
  HIDKEY_F, // 66 f
  HIDKEY_G, // 67 g
  HIDKEY_H, // 68 h
  HIDKEY_I, // 69 i
  HIDKEY_J, // 6A j
  HIDKEY_K, // 6B k
  HIDKEY_L, // 6C l
  HIDKEY_M, // 6D m
  HIDKEY_N, // 6E n
  HIDKEY_O, // 6F o

  HIDKEY_P, // 70 p
  HIDKEY_Q, // 71 q
  HIDKEY_R, // 72 r
  HIDKEY_S, // 73 s
  HIDKEY_T, // 74 t
  HIDKEY_U, // 75 u
  HIDKEY_V, // 76 v
  HIDKEY_W, // 77 w
  HIDKEY_X, // 78 x
  HIDKEY_Y, // 79 y
  HIDKEY_Z, // 7A z
  0, // 7B {
  0, // 7C |
  0, // 7D }
  0, // 7E ~
  0, // 7F DEL
};

uint8_t media_table[10] = {
  HIDKEY_MEDIA_SCAN_PREV,
  HIDKEY_MEDIA_STOP,
  HIDKEY_MEDIA_PAUSE,
  HIDKEY_MEDIA_SCAN_NEXT,
  HIDKEY_MEDIA_EJECT,
  0,
  0,
  HIDKEY_MEDIA_MUTE,
  HIDKEY_MEDIA_VOLUME_DOWN,
  HIDKEY_MEDIA_VOLUME_UP,
};

uint8_t fn_table[10] = {
  HIDKEY_F11,
  HIDKEY_F12,
  HIDKEY_F13,
  HIDKEY_F14,
  HIDKEY_F15,
  HIDKEY_F16,
  HIDKEY_F17,
  HIDKEY_F18,
  HIDKEY_F19,
  HIDKEY_F20,
};

uint8_t gamepad_button_table[16] = {
  AMIGA_KEY_A,
  AMIGA_KEY_B,
  AMIGA_KEY_X,
  AMIGA_KEY_Z,
  AMIGA_KEY_MODIFIER_LEFT_ALT,
  AMIGA_KEY_MODIFIER_RIGHT_ALT,
  AMIGA_KEY_MODIFIER_LEFT_SHIFT,
  AMIGA_KEY_MODIFIER_RIGHT_SHIFT,
  AMIGA_KEY_MODIFIER_LEFT_UI,
  AMIGA_KEY_MODIFIER_RIGHT_UI,
  AMIGA_KEY_HELP,
  AMIGA_KEY_DELETE,
  AMIGA_KEY_SPACEBAR,
  AMIGA_KEY_ENTER,
  AMIGA_KEY_ESCAPE,
  AMIGA_KEY_TAB,
  
};

struct mouseHID_t {
  uint8_t id;
  uint8_t buttons;
  int8_t x;
  int8_t y;
};
struct keyboardHID_t {
    uint8_t id;
    uint8_t modifiers;
    uint8_t key[6];
};

struct mediaHID_t {
  uint8_t id;
  uint8_t keys;
};

struct gamepadHID_t {
  uint8_t id;
  uint8_t pad;
  uint16_t buttons;
  int16_t x;
  int16_t y;
  int16_t x2;
  int16_t y2;
};

struct eeprom_config {
  char swap_ctrl_and_alt;
  char mouse_speed;
  char gamepad_sensitivity;
  char media_keys;
};
    
struct eeprom_config settings = {
  .swap_ctrl_and_alt = 0,
  .mouse_speed = 3,
  .gamepad_sensitivity = 128,
  .media_keys = 1,
};

struct keyboardHID_t keyboardHID;
struct mediaHID_t mediaHID, lastMediaHID;
struct mouseHID_t mouseHID, lastMouseHID;
struct gamepadHID_t gamepadHID, lastGamepadHID;

uint8_t buffer_data[8];
char help_mode = 0;
char extended_mode = 0;
char powerup_mode = 0;
char thrust_x = 0;
char thrust_y = 0;
int elapsed_ms_counter = 0;
int n_pressed_keys = 0;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_TIM1_Init(void);
static void MX_USART1_UART_Init(void);
static void MX_NVIC_Init(void);

/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/

void Printf(const char *_fmt, ... );

/* USER CODE END PFP */

/* USER CODE BEGIN 0 */

static inline void HID_Send(const void *data,const size_t size)
{
  //Printf("Sending: ");
  //for (int i=0; i<size; ++i)
  //{
  //  Printf("%02x ",((uint8_t*)data)[i]);
  //}
  //Printf("\n\r");
  uint8_t status;
  do
  {
    status = USBD_HID_SendReport(&hUsbDeviceFS, (uint8_t *)data, size);
    if (status==USBD_FAIL)
    {
      Printf("USB: fail\n\r");
    }
  }
  while (status == USBD_BUSY);
}

void ApplyThrust()
{
  int x = gamepadHID.x;
  int y = gamepadHID.y;
  x += ((int)thrust_x) * ((int)settings.gamepad_sensitivity);
  y += ((int)thrust_y) * ((int)settings.gamepad_sensitivity);
  if (x<-32768) x=-32768;
  if (x>32767) x=32767;
  if (y<-32768) y=-32768;
  if (y>32767) y=32767;
  if (x<0) x += 64;
  if (x>0) x -= 64;
  if (y<0) y += 64;
  if (y>0) y -= 64;
  gamepadHID.x = x;
  gamepadHID.y = y;
}

// activate DWT timer
void EnableTiming(void)
{
  CoreDebug->DEMCR &= ~CoreDebug_DEMCR_TRCENA_Msk;
  CoreDebug->DEMCR |=  CoreDebug_DEMCR_TRCENA_Msk;
  DWT->CTRL &= ~DWT_CTRL_CYCCNTENA_Msk;
  DWT->CTRL |=  DWT_CTRL_CYCCNTENA_Msk;
  DWT->CYCCNT = 0;
}

// microsecond version
uint32_t HAL_GetTicks_us()
{
  return DWT->CYCCNT / SYSTEM_US_TICKS;
}

// microsecond version
void HAL_Delay_us(uint32_t uSec)
{
  volatile uint32_t DWT_START = DWT->CYCCNT;
  if (uSec > (UINT_MAX / SYSTEM_US_TICKS))
  {
    uSec = (UINT_MAX / SYSTEM_US_TICKS);
  }

  volatile uint32_t DWT_TOTAL = (SYSTEM_US_TICKS * uSec);

  while((DWT->CYCCNT - DWT_START) < DWT_TOTAL);
}

void Print(const char *_buf )
{
  HAL_UART_Transmit(&huart1, (uint8_t *)_buf, strlen(_buf), 1000);
}

void Printf(const char *_fmt, ... )
{
  char buf[512];
  va_list ap;
  va_start(ap, _fmt);
  int len = vsprintf(buf, _fmt,ap);
  va_end(ap);
  HAL_UART_Transmit(&huart1, (uint8_t *)buf, len, 1000);
}

void Keyboard_Print(const uint8_t *s)
{
  struct keyboardHID_t khid;
  khid.id = 1;
  khid.modifiers = 0;
  khid.key[0] = 0;
  khid.key[1] = 0;
  khid.key[2] = 0;
  khid.key[3] = 0;
  khid.key[4] = 0;
  khid.key[5] = 0;
  
  for (;*s;++s)
  {
    //khid.modifiers = ascii2hid[*s].modifier;
    khid.key[0] = ascii2hid[*s];
    Printf("%c -> %02x \n\r",*s,ascii2hid[*s]);
    
    HID_Send(&khid,sizeof(khid));

    khid.modifiers = 0;
    khid.key[0] = 0;

    HID_Send(&khid,sizeof(khid));
  }
}

void SetExtendedMode(char on)
{
  extended_mode = on;
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, on ? GPIO_PIN_RESET : GPIO_PIN_SET);
}

void HardReset()
{
  GPIO_InitTypeDef GPIO_InitStruct;

  GPIO_InitStruct.Pin = RESET_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  HAL_GPIO_WritePin(GPIOA,RESET_Pin,GPIO_PIN_SET);
  HAL_Delay(200);
  HAL_GPIO_WritePin(GPIOA,RESET_Pin,GPIO_PIN_RESET);
  HAL_Delay(200);
  HAL_GPIO_WritePin(GPIOA,RESET_Pin,GPIO_PIN_SET);
  HAL_Delay(200);

  GPIO_InitStruct.Pin = RESET_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
}

void SoftReset()
{
  Printf("*** A500 USB HID Keyboard Firmware ***\n\r");

  uint32_t revid = HAL_GetREVID();
  uint32_t devid = HAL_GetDEVID();
  uint32_t uid[3];
  HAL_GetUID(uid);
  Printf("rev=%08lx dev=%08lx\n\r",revid,devid);
  Printf("uid=%08lx%08lx%08lx\n\r",uid[0],uid[1],uid[2]);
  
  keyboardHID.id = 1;
  keyboardHID.modifiers = 0;
  keyboardHID.key[0] = 0;
  keyboardHID.key[1] = 0;
  keyboardHID.key[2] = 0;
  keyboardHID.key[3] = 0;
  keyboardHID.key[4] = 0;
  keyboardHID.key[5] = 0;
  
  mediaHID.id = 2;
  mediaHID.keys = 0;

  mouseHID.buttons = 0;
  mouseHID.id = 3;
  mouseHID.x = 0;
  mouseHID.y = 0;
  
  gamepadHID.id = 4;
  gamepadHID.pad = 0;
  gamepadHID.buttons = 0;
  gamepadHID.x = 0;
  gamepadHID.y = 0;
  
  lastMediaHID = mediaHID;
  lastMouseHID = mouseHID;
  lastGamepadHID = gamepadHID;
  
  n_pressed_keys=0;
  
  thrust_x = 0;
  thrust_y = 0;
  
  SetExtendedMode(0);
  help_mode = 0;
  elapsed_ms_counter = 0;

  buffer_data[0] = 0;
  buffer_data[1] = 0;
  buffer_data[2] = 0;
  buffer_data[3] = 0;
  buffer_data[4] = 0;
  buffer_data[5] = 0;
  buffer_data[6] = 0;
  buffer_data[7] = 0;
}

int HandleKey(uint8_t key)
{
  switch(key)
  {
  case 0x78:
    Printf("reset warning\n\r");
    return 0;
  case 0xF9:
    Printf("last key code bad\n\r");
    return 0;
  case 0xFA:
    Printf("keyboard key buffer overflow\n\r");
    return 0;
  case 0xFC:
    Printf("keyboard self test fail\n\r");
    return 0;
  case 0xFD:
    Printf("initiate power-up key stream\n\r");
    powerup_mode = 1;
    return 0;
  case 0xFE:
    Printf("terminate power-up key stream\n\r");
    powerup_mode = 0;
    SoftReset();
    return 0;
  default:
    break;
  }
  uint8_t raw = key & 0x7f;
  int pressed = ((key & 0x80) >> 7) ^ 1;
  char touched=0;
  uint8_t code;

  if (powerup_mode)
  {
    Printf("%02x\n\r",raw);
    return 0;
  }
 
  code = amiga_to_hid[raw];
 
  if (raw == AMIGA_KEY_CAPS_LOCK)
  {
     settings.swap_ctrl_and_alt = pressed;
     Printf("swap_ctrl_and_alt = %d\n\r",settings.swap_ctrl_and_alt);
     return 0;
  }

  if (extended_mode==1)
  {
    if (code==HIDKEY_KP_MULTIPLY)
    {
      SetExtendedMode(0);
      mouseHID.buttons = 0;
      mouseHID.x = 0;
      mouseHID.y = 0;
      Printf("turning off mouse mode\n\r");
    }

    if (code==HIDKEY_KP_PLUS)
    {
      if (pressed)
      {
        if (settings.mouse_speed<20) settings.mouse_speed++;
        Printf("mouse speed: %d\n\r",settings.mouse_speed);
      }
      return 0;
    }

    if (code==HIDKEY_KP_MINUS)
    {
      if (pressed)
      {
        if (settings.mouse_speed>1) settings.mouse_speed--;
        Printf("mouse speed: %d\n\r",settings.mouse_speed);
      }
      return 0;
    }

    if (code==HIDKEY_DELETE)
    {
      if (pressed)
        mouseHID.buttons |= 1;
      else
        mouseHID.buttons &=~ 1;
    }
    if (code==HIDKEY_HELP)
    {
      if (pressed)
        mouseHID.buttons |= 2;
      else
        mouseHID.buttons &=~ 2;
    }
    if (code==HIDKEY_UP)
    {
      mouseHID.y = pressed ? -settings.mouse_speed : 0;
    }
    if (code==HIDKEY_DOWN)
    {
      mouseHID.y = pressed ? +settings.mouse_speed : 0;
    }
    if (code==HIDKEY_LEFT)
    {
      mouseHID.x = pressed ? -settings.mouse_speed : 0;
    }
    if (code==HIDKEY_RIGHT)
    {
      mouseHID.x = pressed ? +settings.mouse_speed : 0;
    }
    
    if (memcmp(&lastMouseHID,&mouseHID,sizeof(mouseHID)))
    {
      lastMouseHID = mouseHID;
      HID_Send(&mouseHID,sizeof(mouseHID));
      return 0;
    }
  }
  else if (extended_mode==2)
  {
    if (raw==AMIGA_KEY_KP_MULTIPLY)
    {
      touched=1;
      SetExtendedMode(0);
      gamepadHID.buttons = 0;
      gamepadHID.x = 0;
      gamepadHID.y = 0;
      Printf("turning off gamepad mode\n\r");
    }
    for (int i=0; i<16; ++i)
    {
      if (gamepad_button_table[i] == raw)
      {
        touched = 1;
        if (pressed)
          gamepadHID.buttons |= (1 << i);
        else
          gamepadHID.buttons &=~ (1 << i);
      }
    }
    if (raw==AMIGA_KEY_UP)
    {
      touched=1;
      thrust_y = pressed ? -1 : 0;
    }
    if (raw==AMIGA_KEY_DOWN)
    {
      touched=1;
      thrust_y = pressed ? +1 : 0;
    }
    if (raw==AMIGA_KEY_LEFT)
    {
      touched=1;
      thrust_x = pressed ? -1 : 0;
    }
    if (raw==AMIGA_KEY_RIGHT)
    {
      touched=1;
      thrust_x = pressed ? +1 : 0;
    }
    if (touched)
    {
      ApplyThrust();
      if (memcmp(&lastMouseHID,&mouseHID,sizeof(mouseHID)))
      {
        lastGamepadHID = gamepadHID;
        HID_Send(&gamepadHID,sizeof(gamepadHID));
      }
      touched = 0;

      return 0;
    }
  }
  else
  {
    if (raw == AMIGA_KEY_HELP)
    {
      help_mode = pressed ? 1 : 0;
    }
  }
  
  if (help_mode)
  {
    switch (code)
    {
    case HIDKEY_M:
      Printf("turning on mouse mode\n\r");
      SetExtendedMode(1);
      help_mode = 0;
      elapsed_ms_counter = HAL_GetTick();
      return 0;

    case HIDKEY_G:
      Printf("turning on gamepad mode\n\r");
      SetExtendedMode(2);
      help_mode = 0;
      elapsed_ms_counter = HAL_GetTick();
      return 0;
    
    // help-escape = pause 
    case HIDKEY_ESCAPE:
      code = HIDKEY_PAUSE;
      break;
      
    case HIDKEY_DELETE:
      settings.media_keys ^= 1;
      if (settings.media_keys)
        Printf("function keys are media keys\n\r");
      else
        Printf("extended function keys\n\r");
      //help_mode = 0;
      return 0;

    case HIDKEY_F1:
    case HIDKEY_F2:
    case HIDKEY_F3:
    case HIDKEY_F4:
    case HIDKEY_F5:
    case HIDKEY_F6:
    case HIDKEY_F7:
    case HIDKEY_F8:
    case HIDKEY_F9:
    case HIDKEY_F10:
      {
        int n = code - HIDKEY_F1;
        if (settings.media_keys)
        {
          if (pressed)
          {
            mediaHID.keys |= media_table[n];
          }
          else
          {
            mediaHID.keys &=~ media_table[n];
          }
          HID_Send(&mediaHID,sizeof(mediaHID));
          return 0;

        }
        else
        {
          code = fn_table[n];
        }
      }
      break;
      
    default:
      return 0;
    }
    
  }
  
  if (code==0) return 0;

  // is modifier?
  if (raw>=0x60 && raw<0x68)
  {
    if (settings.swap_ctrl_and_alt)
    {
      switch(code)
      {
      case HIDKEY_MODIFIER_LEFT_CTRL:
        code = HIDKEY_MODIFIER_LEFT_ALT;
        break;
      case HIDKEY_MODIFIER_LEFT_ALT:
        code = HIDKEY_MODIFIER_LEFT_CTRL;
        break;
      case HIDKEY_MODIFIER_RIGHT_ALT:
        code = HIDKEY_MODIFIER_RIGHT_CTRL;
        break;
      case HIDKEY_MODIFIER_RIGHT_UI:
        code = HIDKEY_MODIFIER_RIGHT_ALT;
        break;
      default:
        break;
      }
    }
        
    if (pressed)
    {
      keyboardHID.modifiers |= code;
    }
    else
    {
      keyboardHID.modifiers &=~ code;
    }
  }
  else
  {
    if (pressed)
    {
      int found=0;
      for (int i=0; i<n_pressed_keys; ++i)
      {
        if (keyboardHID.key[i] == code)
        {
          found=1;
          break;
        }
      }
      if (!found)
      {
        if (n_pressed_keys<6)
        {
          keyboardHID.key[n_pressed_keys]=code;
          n_pressed_keys++;
        }
      }
    }
    else
    {
      for (int i=0; i<n_pressed_keys; ++i)
      {
        if (keyboardHID.key[i] != code) continue;
        n_pressed_keys--;
        if (n_pressed_keys>0 && i!=n_pressed_keys)
        {
          keyboardHID.key[i] = keyboardHID.key[n_pressed_keys];
        }
        keyboardHID.key[n_pressed_keys]=0;
        break;
      }
    }
  }
  return 1;
}

// called by EXTI0_IRQHandler
//
// see Appendix G, Keyboard Interface in Amiga Hardware Reference Manual
//
void clock_irq_handler()
{
  static uint8_t val=0;
  static uint8_t clocks=0;
  
  // (1) collect bits, convert to logical LOW and HIGH
  val <<= 1;
  val |= (HAL_GPIO_ReadPin(GPIOA,DATA_Pin)^1);
  ++clocks;
  if (clocks==8)
  {
      // last bit was KEY PRESSED bit, reorder
      uint8_t key=(val>>1) | (val<<7);
      val = 0;
      clocks=0;
      
      // I'm collecting up to 8 keypresses in case mainloop is blocked/busy in a simple array
      if (buffer_data[7]<7)
      {
        buffer_data[buffer_data[7]]=key;
        buffer_data[7]++;
      }
      
      // finally, handshake back to the keyboard as described
      GPIO_InitTypeDef GPIO_InitStruct;
      GPIO_InitStruct.Pin = DATA_Pin;
      GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
      GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
      HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
      
      HAL_GPIO_WritePin(GPIOA,DATA_Pin,GPIO_PIN_RESET);
      HAL_Delay_us(85);
      GPIO_InitStruct.Pin = DATA_Pin;
      GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
      GPIO_InitStruct.Pull = GPIO_NOPULL;
      HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
  }
}

/* USER CODE END 0 */

int main(void)
{

  /* USER CODE BEGIN 1 */
   
  /* USER CODE END 1 */

  /* MCU Configuration----------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_TIM1_Init();
  MX_USB_DEVICE_Init();
  MX_USART1_UART_Init();

  /* Initialize interrupts */
  MX_NVIC_Init();

  /* USER CODE BEGIN 2 */

  EnableTiming();

  // reset amiga keyboard
  HardReset();
  
  uint8_t keys[8];
  uint64_t *pkeys = (uint64_t*)keys;
  uint64_t *pbuff = (uint64_t*)buffer_data;
  *pkeys = 0;
  *pbuff = 0;
  
  SoftReset();
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
  /* USER CODE END WHILE */

  /* USER CODE BEGIN 3 */

    __disable_irq();
    *pkeys = *pbuff;
    *pbuff = 0;
    __enable_irq();
   
    if (USBD_HID_Is_Configured(&hUsbDeviceFS) == USBD_OK)
    {
    }
    
    if (extended_mode==1)
    {
      int now = HAL_GetTick();
      if (now-elapsed_ms_counter >= 10)
      {
        elapsed_ms_counter = now;
        if (mouseHID.x || mouseHID.y)
        {
          HID_Send(&mouseHID,sizeof(mouseHID));
        }
      }
    }

    if (extended_mode==2)
    {
      int now = HAL_GetTick();
      if (now-elapsed_ms_counter >= 10)
      {
        elapsed_ms_counter = now;
        ApplyThrust();
        if (memcmp(&lastGamepadHID,&gamepadHID,sizeof(gamepadHID)))
        {
          lastGamepadHID = gamepadHID;
          Printf("buttons = %04x %d %d\n\r",gamepadHID.buttons,gamepadHID.x,gamepadHID.y);
          HID_Send(&gamepadHID,sizeof(gamepadHID));
        }
      }
    }
    
    int send = 0;
    for (int i=0; i<keys[7]; ++i)
    {
      send += HandleKey(keys[i]);
    }
    if (send>0)
    {
      HID_Send(&keyboardHID,sizeof(keyboardHID));
    }
  }
  /* USER CODE END 3 */

}

/** System Clock Configuration
*/
void SystemClock_Config(void)
{

  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_PeriphCLKInitTypeDef PeriphClkInit;

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL6;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV4;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USB;
  PeriphClkInit.UsbClockSelection = RCC_USBCLKSOURCE_PLL;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Configure the Systick interrupt time 
    */
  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

    /**Configure the Systick 
    */
  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

/** NVIC Configuration
*/
static void MX_NVIC_Init(void)
{
  /* EXTI0_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(EXTI0_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI0_IRQn);
}

/* TIM1 init function */
static void MX_TIM1_Init(void)
{

  TIM_ClockConfigTypeDef sClockSourceConfig;
  TIM_MasterConfigTypeDef sMasterConfig;

  htim1.Instance = TIM1;
  htim1.Init.Prescaler = 0;
  htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim1.Init.Period = 0;
  htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim1.Init.RepetitionCounter = 0;
  htim1.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim1) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim1, &sClockSourceConfig) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim1, &sMasterConfig) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

}

/* USART1 init function */
static void MX_USART1_UART_Init(void)
{

  huart1.Instance = USART1;
  huart1.Init.BaudRate = 115200;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

}

/** Configure pins as 
        * Analog 
        * Input 
        * Output
        * EVENT_OUT
        * EXTI
*/
static void MX_GPIO_Init(void)
{

  GPIO_InitTypeDef GPIO_InitStruct;

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13|GPIO_PIN_14, GPIO_PIN_RESET);

  /*Configure GPIO pins : PC13 PC14 */
  GPIO_InitStruct.Pin = GPIO_PIN_13|GPIO_PIN_14;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pin : CLOCK_Pin */
  GPIO_InitStruct.Pin = CLOCK_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(CLOCK_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : DATA_Pin RESET_Pin */
  GPIO_InitStruct.Pin = DATA_Pin|RESET_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  None
  * @retval None
  */
void _Error_Handler(char * file, int line)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  while(1) 
  {
  }
  /* USER CODE END Error_Handler_Debug */ 
}

#ifdef USE_FULL_ASSERT

/**
   * @brief Reports the name of the source file and the source line number
   * where the assert_param error has occurred.
   * @param file: pointer to the source file name
   * @param line: assert_param error line source number
   * @retval None
   */
void assert_failed(uint8_t* file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
    ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */

}

#endif

/**
  * @}
  */ 

/**
  * @}
*/ 

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
