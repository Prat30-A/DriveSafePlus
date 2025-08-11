#include "keypad.h"
#include "LCD1602.h"
#include "main.h"
#include <string.h>

#define ROWS 4
#define COLS 4

// ROWS: PC8, PC6, PC5, PA12
GPIO_TypeDef* rowPorts[ROWS] = { GPIOC, GPIOC, GPIOC, GPIOA };
uint16_t rowPins[ROWS] = { GPIO_PIN_8, GPIO_PIN_6, GPIO_PIN_5, GPIO_PIN_12 };

// COLS: PA11, PB12, PB14, PB13
GPIO_TypeDef* colPorts[COLS] = { GPIOA, GPIOB, GPIOB, GPIOB };
uint16_t colPins[COLS] = { GPIO_PIN_11, GPIO_PIN_12, GPIO_PIN_14, GPIO_PIN_13 };


char keymap[ROWS][COLS] = {
    { '1', '2', '3', 'A' },
    { '4', '5', '6', 'B' },
    { '7', '8', '9', 'C' },
    { '*', '0', '#', 'D' }
};

// Scans keypad and returns character if pressed
char Keypad_GetKey(void) {
    for (int row = 0; row < ROWS; row++) {
        // Set current row LOW
        HAL_GPIO_WritePin(rowPorts[row], rowPins[row], GPIO_PIN_RESET);

        for (int col = 0; col < COLS; col++) {
            if (HAL_GPIO_ReadPin(colPorts[col], colPins[col]) == GPIO_PIN_RESET) {
                HAL_Delay(20); // debounce
                if (HAL_GPIO_ReadPin(colPorts[col], colPins[col]) == GPIO_PIN_RESET) {
                    // Wait for release
                    while (HAL_GPIO_ReadPin(colPorts[col], colPins[col]) == GPIO_PIN_RESET);
                    HAL_GPIO_WritePin(rowPorts[row], rowPins[row], GPIO_PIN_SET);
                    return keymap[row][col];
                }
            }
        }
        HAL_GPIO_WritePin(rowPorts[row], rowPins[row], GPIO_PIN_SET);
    }
    return 0; // No key pressed
}

// User selects '1' or '2' to define user_type
char Get_User_Type_From_Keypad(void) {
    char key = '\0';

    lcd_clear();
    lcd_put_cur(0, 0);
    lcd_send_string("Press 1=Teen");
    lcd_put_cur(1, 0);
    lcd_send_string("2=Adult");

    while (key != '1' && key != '2') {
        key =  Keypad_GetKey();
        HAL_Delay(50);  // debounce
    }

    // wait until key is released
    while (Keypad_GetKey() == key);
    HAL_Delay(100); // allow bounce to settle

    return (key == '1') ? 'T' : 'A';
}


// Captures 5-digit ID from keypad and stores it in id_buffer
void Get_Driver_ID_From_Keypad(char* id_buffer) {
    lcd_clear();
    lcd_put_cur(0, 0);
    lcd_send_string("Enter 5-digit ID:");
    int count = 0;

    while (count < 5) {
        char key = Keypad_GetKey();

        if (key >= '0' && key <= '9') {
            id_buffer[count++] = key;

            // Display entered digit (optional)
            lcd_put_cur(1, count - 1);
            lcd_send_data(key);

            // wait until released
            while (Keypad_GetKey()== key);
            HAL_Delay(100);
        }
    }

    id_buffer[5] = '\0'; // null terminator
}

