This document covers the configuration of external interrupt INT1 on pin PD3 of the ATmega328 microcontroller. It explains how to enable the interrupt using EIMSK, select the trigger mode via EICRA, clear the interrupt flag, write the ISR, and apply it in common use cases.

---

## **INT1 Pin Overview**

| Signal | Pin | Port | Description                      |
|--------|-----|------|----------------------------------|
| INT1   | PD3 | PORTD.3 | External Interrupt Request 1 |

INT1 is a hardware interrupt source triggered by signal changes on PD3. It can be configured to respond to:

- Low level
- Any logical change
- Falling edge
- Rising edge

---

## **EIMSK – External Interrupt Mask Register**

| Bit | Name  | Description                      |
|-----|-------|----------------------------------|
| 1   | INT1  | Enable External Interrupt 1      |

### **Enable INT1:**

```c
bitSet(EIMSK, INT1); // Enable INT1 interrupt
```

---

## **EICRA – External Interrupt Control Register A**

| Bit | Name   | Description                      |
|-----|--------|----------------------------------|
| 3   | ISC11  | Interrupt Sense Control 1 for INT1 |
| 2   | ISC10  | Interrupt Sense Control 0 for INT1 |

### **Trigger Mode Selection:**

| ISC11 | ISC10 | Trigger Condition     |
|--------|--------|----------------------|
| 0      | 0      | Low level            |
| 0      | 1      | Any logical change   |
| 1      | 0      | Falling edge         |
| 1      | 1      | Rising edge          |

---

## **Trigger Mode Configuration Examples**

### **Low Level Trigger**

```c
// Configure INT1 to trigger on low level
bitClear(EICRA, ISC11);
bitClear(EICRA, ISC10);
```

### **Any Logical Change**

```c
// Configure INT1 to trigger on any logical change
bitClear(EICRA, ISC11);
bitSet(EICRA, ISC10);
```

### **Falling Edge Trigger**

```c
// Configure INT1 to trigger on falling edge
bitSet(EICRA, ISC11);
bitClear(EICRA, ISC10);
```

### **Rising Edge Trigger**

```c
// Configure INT1 to trigger on rising edge
bitSet(EICRA, ISC11);
bitSet(EICRA, ISC10);
```

---

## **EIFR – External Interrupt Flag Register**

| Bit | Name  | Description                      |
|-----|-------|----------------------------------|
| 1   | INTF1 | Interrupt Flag for INT1          |

### **Clear INT1 Flag Manually:**

```c
intFlag_clear(EIFR, INTF1); // Clear INT1 interrupt flag
```

> [!NOTE]
> The flag is automatically cleared when the ISR is executed, but can be cleared manually if needed.

---

## **Writing the ISR for INT1**

### **Example ISR:**

```c
ISR(INT1_vect) 
{
    // Handle external interrupt event
}
```

---

## **Complete Initialization Example**

```c
void extInt1_Init(void) 
{
    GPIO_Config_INPUT(DDRD, PD3);     // Configure PD3 as input
    bitSet(EIMSK, INT1);              // Enable INT1 interrupt
    bitSet(EICRA, ISC11);             // Rising edge trigger
    bitSet(EICRA, ISC10);
    globalInt_Enable;                 // Enable global interrupts
}
```

---

## **Summary of INT1 Setup**

| Step                        | Register | Action                                  |
|-----------------------------|----------|-----------------------------------------|
| Configure PD3 as input      | DDRD     | `GPIO_Config_INPUT(DDRD, PD3)`          |
| Select trigger mode         | EICRA    | Set `ISC11:ISC10` bits                  |
| Enable INT1 interrupt       | EIMSK    | Set `INT1` bit                          |
| Enable global interrupts    | SREG     | Set `SREG_I` bit                        |
| Write ISR                   | INT1_vect| Handle interrupt event                  |

> [!CAUTION]
> Keep ISR short and efficient. Use flags or buffers to defer heavy processing to the main loop.


# 🌟 Support Me
If you found this repository useful:
- Subscribe to my [YouTube Channel](https://www.youtube.com/@aKaReZa75).
- Share this repository with others.
- Give this repository and my other repositories a star.
- Follow my [GitHub account](https://github.com/aKaReZa75).

# ✉️ Contact Me
Feel free to reach out to me through any of the following platforms:
- 📧 [Email: aKaReZa75@gmail.com](mailto:aKaReZa75@gmail.com)
- 🎥 [YouTube: @aKaReZa75](https://www.youtube.com/@aKaReZa75)
- 💼 [LinkedIn: @akareza75](https://www.linkedin.com/in/akareza75)
