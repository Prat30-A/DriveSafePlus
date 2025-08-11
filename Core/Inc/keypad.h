/*
 * keypad.h
 *
 *  Created on: Jul 24, 2025
 *      Author: Prath
 */

#ifndef INC_KEYPAD_H_
#define INC_KEYPAD_H_

char Get_User_Type_From_Keypad(void);
void Get_Driver_ID_From_Keypad(char *id_buffer);
char Keypad_GetKey(void); // Optional: low-level API if needed

#endif /* INC_KEYPAD_H_ */
