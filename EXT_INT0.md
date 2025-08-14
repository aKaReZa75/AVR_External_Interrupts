This document covers the configuration of external interrupt INT0 on pin PD2 of the ATmega328 microcontroller. It explains how to enable the interrupt using EIMSK, select the trigger mode via EICRA, clear the interrupt flag, write the ISR, and apply it in common use cases.

---

## **INT0 Pin Overview**

| Signal | Pin | Port | Description                      |
|--------|-----|------|----------------------------------|
| INT0   | PD2 | PORTD.2 | External Interrupt Request 0 |

INT0 is a hardware interrupt source triggered by signal changes on PD2. It can be configured to respond to:

- Low level
- Any logical change
- Falling edge
- Rising edge

---

## **EIMSK – External Interrupt Mask Register**

| Bit | Name  | Description                      |
|-----|-------|----------------------------------|
| 0   | INT0  | Enable External Interrupt 0      |

### **Enable INT0:**

```c
bitSet(EIMSK, INT0); // Enable INT0 interrupt
```

---

## **EICRA – External Interrupt Control Register A**

| Bit | Name   | Description                      |
|-----|--------|----------------------------------|
| 1   | ISC01  | Interrupt Sense Control 1 for INT0 |
| 0   | ISC00  | Interrupt Sense Control 0 for INT0 |

### **Trigger Mode Selection:**

| ISC01 | ISC00 | Trigger Condition     |
|--------|--------|----------------------|
| 0      | 0      | Low level            |
| 0      | 1      | Any logical change   |
| 1      | 0      | Falling edge         |
| 1      | 1      | Rising edge          |

---

## **Trigger Mode Configuration Examples**

### **Low Level Trigger**
```c
// Configure INT0 to trigger on low level
bitClear(EICRA, ISC01); 
bitClear(EICRA, ISC00);
```

---

### **Any Logical Change**

```c
// Configure INT0 to trigger on any logical change
bitClear(EICRA, ISC01); 
bitSet(EICRA, ISC00);  
```

---

### **Falling Edge Trigger**

```c
// Configure INT0 to trigger on falling edge
bitSet(EICRA, ISC01);   
bitClear(EICRA, ISC00);
```

---

### **Rising Edge Trigger**

```c
// Configure INT0 to trigger on rising edge
bitSet(EICRA, ISC01); 
bitSet(EICRA, ISC00);  
```
---

## **EIFR – External Interrupt Flag Register**

| Bit | Name  | Description                      |
|-----|-------|----------------------------------|
| 0   | INTF0 | Interrupt Flag for INT0          |

### **Clear INT0 Flag Manually:**

```c
intFlag_clear(EIFR, INTF0); // Clear INT0 interrupt flag
```

> [!NOTE]
> The flag is automatically cleared when the ISR is executed, but can be cleared manually if needed.

---

## **Writing the ISR for INT0**

### **Example ISR:**

```c
ISR(INT0_vect) 
{
    // Handle external interrupt event
}
```

---

## **Complete Initialization Example**

```c
void extInt0_Init(void) 
{
    GPIO_Config_INPUT(DDRD, PD2);     // Configure PD2 as input
    bitSet(EIMSK, INT0);              // Enable INT0 interrupt
    bitSet(EICRA, ISC01);             // Rising edge trigger
    bitSet(EICRA, ISC00);
    globalInt_Enable;                 // Enable global interrupts
}
```

---

## **Summary of INT0 Setup**

| Step                        | Register | Action                                  |
|-----------------------------|----------|-----------------------------------------|
| Configure PD2 as input      | DDRD     | `GPIO_Config_INPUT(DDRD, PD2)`          |
| Select trigger mode         | EICRA    | Set `ISC01:ISC00` bits                  |
| Enable INT0 interrupt       | EIMSK    | Set `INT0` bit                          |
| Enable global interrupts    | SREG     | Set `SREG_I` bit                        |
| Write ISR                   | INT0_vect| Handle interrupt event                  |

> [!CAUTION]
> Avoid long operations inside the ISR. Use flags or buffers to defer processing to the main loop if needed.


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
